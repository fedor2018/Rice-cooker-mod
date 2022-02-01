    /* ========================================
 *  implementation of software rotary encoder routines:
 *
 *  using Oleg @ CircuitsAtHome 
 *  http://www.circuitsathome.com/mcu/programming/reading-rotary-encoder-on-arduino (link is dead..)
 *  https://www.ccsinfo.com/forum/viewtopic.php?t=41115
 *   
 *
 *
 * ========================================
*/

   
#include <`$INSTANCE_NAME`.h> // must specify API prefix in Symbol->Properties->Doc.APIPrefix


static const signed char enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // (pol/isr) 72/91 tic

#define TIMED_OUT  0
#define SW_MASK  0x4 // button pin: 2
#define EN_MASK  0x3 // encoder pins: 0,1
static volatile uint8 CYDATA SW_timeout;

CY_ISR_PROTO(`$INSTANCE_NAME`_Tick_ISR);    // ISR for button switch timeout
CY_ISR_PROTO(`$INSTANCE_NAME`_myDtrInt);    // interrupt on encoder pin states change
CY_ISR_PROTO(`$INSTANCE_NAME`_myPollInt);   // interrupt on external polling clock

//====================================
//        internal variables
//====================================

//'static' is required for multiple instances
static er_t aPosition = `$INSTANCE_NAME`_StartPosition; // encoder position (auto initialize to StartPosition)
static int8 aDirection;                                 // save last valid rotation direction:  +1 or -1
//static uint8 fPositionChanged;                        // flag indicating position change
static volatile uint8 fPositionChanged;                 // flag indicating position change
#if (`$INSTANCE_NAME`_BtnEnable)
    static uint8 fBtnPressed;                           // flag indicating button pressed
#endif    

//static volatile uint8 fDataReady = 0;               // flag on encoder pin interrupt 




//==============================================================================
// Checks all asigned pins events and signals that encoder position changed
// return: 0-no change, -1-rotated CCW, +1-rotated CW
//==============================================================================


int8 `$INSTANCE_NAME`_CheckStatus() 
{ 
    // 1. clear pins isr
    // 2. check button if enabled
    // 3. check rotation
    // 4. check position bounds
    // 5. update position
      
    
    int8 en_dir = `$INSTANCE_NAME`_CheckRotation(); // +11 ticks 
    
    
    if (en_dir==0) return 0;                        // no changes
    
    aDirection = en_dir;                            // store last (non-zero) direction of rotation
   
    #if (`$INSTANCE_NAME`_CheckBounds)              // check bounds 
        
        if (en_dir>0) { 
            if ( aPosition >= (er_t) `$INSTANCE_NAME`_UpperBound ) return 0; // UB repeated
        }
        else {// (en_dir<0)  
            if ( aPosition <= (er_t) `$INSTANCE_NAME`_LowerBound ) return 0; // LB repeated
        }
        
    #endif

    aPosition += en_dir;                            // update position //todo: increment?

    fPositionChanged = 1;                             // update flag
    
    return en_dir;                                  // value changed: -1=CCW, 1=CW 
} 


#if `$INSTANCE_NAME`_IsrEnable
    
//==============================================================================
// Circuits@Home algorithm with pin interrupts
// returns direction of rotation:  -1=CCW, 0=NAN, 1=CW 
//==============================================================================

int8 `$INSTANCE_NAME`_CheckRotation() // checks pin status
{
    static uint8 index = 0;
    static  int8 Acc   = 0;                     //internal accumulator to accumulate 1/4 microsteps
    
    
    #if (`$INSTANCE_NAME`_BtnEnable) 
        uint8 temp_stat = `$INSTANCE_NAME`_PINS3_ClearInterrupt(); //must clear //+ 12 bits P4-ok
        //`$INSTANCE_NAME`_PINS3_INTSTAT; // ClearInterrupt +7 ticks P5-ok P4-!ok

        //uint8 bits = `$INSTANCE_NAME`_PINS3_Read();  // read pins state
        uint8 bits  = (`$INSTANCE_NAME`_PINS3_PS & `$INSTANCE_NAME`_PINS3_MASK) >> `$INSTANCE_NAME`_PINS3_SHIFT;//+7tic (74 tic)
        
        if(((bits & SW_MASK) == 0) && (SW_timeout == TIMED_OUT)) // Btn pressed //
        //if((temp_stat & SW_MASK) != 0 && (SW_timeout == TIMED_OUT)) //
	    {
            SW_timeout = SW_DEBOUNCE_TIME; // reset the debounce timer for this button
            `$INSTANCE_NAME`_isrBtnSW_StartEx(`$INSTANCE_NAME`_Tick_ISR); // start debouncing timer isr +69 tic
            return 0; // ignore encoder if button pressed
	    }             
        
        //uint8 bits  = `$INSTANCE_NAME`_PINS3_Read() & EN_MASK;  // read pins state
        bits &= EN_MASK;  // pins state
    #else
        //StopWatch_1_Start();
        `$INSTANCE_NAME`_PINS2_ClearInterrupt(); //must clear    //+12 tick P4-ok
        //(`$INSTANCE_NAME`_PINS2_INTSTAT & `$INSTANCE_NAME`_PINS2_MASK) >> `$INSTANCE_NAME`_PINS2_SHIFT; // +7 ticks P4-!ok
        //`$INSTANCE_NAME`_PINS2_INTSTAT; // +7 ticks P5-ok, P4-!ok
        ///StopWatch_1_Stop();
        
        //StopWatch_1_Start();
        //uint8 bits  = `$INSTANCE_NAME`_PINS2_Read() & EN_MASK;  // read pins state // 91 tick (89->76_INLINE) +11 tick
        //uint8 bits  = `$INSTANCE_NAME`_PINS2_Read();          // read pins state // 91 tick (+11 tick)
        uint8 bits  = (`$INSTANCE_NAME`_PINS2_PS & `$INSTANCE_NAME`_PINS2_MASK) >> `$INSTANCE_NAME`_PINS2_SHIFT;//+7tic (58 tic)
        //StopWatch_1_Stop();
    #endif    

    #if (`$INSTANCE_NAME`_InvertDir)
        bits  = ((bits&1)<<1) | ((bits&2)>>1);  // swap bits 1&2
    #endif
    
    
    index <<= 2;                                // remember previous state by shifting the lower bits up 2    
    index |= bits;                              // OR bits with var old_AB to set new value
    
    
    Acc &= 0x03;                                // dont let it grow >3 or <-3
    Acc += enc_states[ index & 0x0f ];          // accumulate 1/4 steps   
 
    
    
    return Acc>>2;                              // -1=CCW, 0=NAN, 1=CW 
}

//==============================================================================
// Debouncing ISR - counts milliseconds elapsed after button press
// Rises semaphore flag when timeout
// Works on Button Pressed event
//==============================================================================
    
#if (`$INSTANCE_NAME`_BtnEnable)
CY_ISR(`$INSTANCE_NAME`_Tick_ISR)
{
	if(SW_timeout != 0) // this isr works continuously! make 100 Hz or use SysTick ISR!
	{
		if(--SW_timeout == TIMED_OUT) // edge was detected by the PICU. Decrement and check timeout.
		{
            // Timed out -> check if SW still pressed
			if((`$INSTANCE_NAME`_PINS3_Read() & SW_MASK) == 0) // 
            //if((`$INSTANCE_NAME`_PINS3_Read() & SW_MASK) == 1) //  not work (button released +rising edge) 
			{
                //`$INSTANCE_NAME`_isrBtnSW_Disable(); // ok if used Encoder_Start()
                `$INSTANCE_NAME`_isrBtnSW_Stop();
                //`$INSTANCE_NAME`_BtnPressed = 1; // set flag
                fBtnPressed = 1; // set flag
			}
		}
	}
}

#endif //(_BtnEnable)


//==============================================================================
// Clears pins interrupt
// If pins isr is enabled, then must clear inside ISR to allow further isr events
//==============================================================================

void `$INSTANCE_NAME`_ClearInterrupt() // todo: uint8? //todo: CY_INLINE move into #isr_enabled
{
        #if (`$INSTANCE_NAME`_BtnEnable)
            //`$INSTANCE_NAME`_PINS3_ClearInterrupt();
            
            ///(`$INSTANCE_NAME`_PINS3_INTSTAT & `$INSTANCE_NAME`_PINS3_MASK) >> `$INSTANCE_NAME`_PINS3_SHIFT; //+16 tick
            ///(`$INSTANCE_NAME`_PINS3_INTSTAT & `$INSTANCE_NAME`_PINS3_MASK); // +16
            `$INSTANCE_NAME`_PINS3_INTSTAT; // +16
        #else
            //`$INSTANCE_NAME`_PINS2_ClearInterrupt();
            `$INSTANCE_NAME`_PINS2_INTSTAT;
        #endif    
}


//==============================================================================
// interrupt on encoder pin states change
//==============================================================================
//static volatile CYBIT fDataReady = 0; // semaphore flag


CY_ISR(`$INSTANCE_NAME`_myDtrInt) //todo: rename PinInt
{   
    //`$INSTANCE_NAME`_fDataReady = 1;
    `$INSTANCE_NAME`_ClearInterrupt(); // must clear +11 ticks
    

    //StopWatch_1_Start();
    `$INSTANCE_NAME`_CheckStatus(); // C@H (pol/isr)  72/91 tic // 
                             // C@H (pol/isr)  53/58 tic // w/o button
                             // C@H (pol/isr)    /69 tic // w/button 
    //StopWatch_1_Stop(); 
}    

#else // (!IsrEnable)

    
    
    
    

//==============================================================================
// Circuits@Home algorithm w/o pins interrupt
// returns direction of rotation: -1=CCW, 0=NAN, 1=CW 
//==============================================================================

//static int8 `$INSTANCE_NAME`_CheckRotation()
int8 `$INSTANCE_NAME`_CheckRotation()
{
    static uint8 index = 0;
    static  int8 Acc = 0;                       // internal accumulator to accumulate 1/4 microsteps

    #if (`$INSTANCE_NAME`_BtnEnable)
        // check if BtnSW pressed 
           
        uint8 bit_SW = `$INSTANCE_NAME`_pin_btn_Read(); // 92
        //uint8 bit_SW = CyPins_ReadPin(`$INSTANCE_NAME`_pin_btn_0) != 0; //90
        //uint8 bit_SW = (`$INSTANCE_NAME`_pin_btn_PS & `$INSTANCE_NAME`_pin_btn_MASK) >> `$INSTANCE_NAME`_pin_btn_SHIFT;//90
        
        
        
	    if((bit_SW != 0) && (SW_timeout == TIMED_OUT)) // Btn pressed
        //if(((bit_SW) == 0) && (SW_timeout == TIMED_OUT)) // Btn pressed - not work
	    {
	    	SW_timeout = SW_DEBOUNCE_TIME; // reset the debounce timer for this button
            `$INSTANCE_NAME`_isrBtnSW_StartEx(`$INSTANCE_NAME`_Tick_ISR);
             return 0; // can return here 
	    }
        
        
        //uint8 bit_a = `$INSTANCE_NAME`_pin_A_Read(); //  todo: check speed  
        //uint8 bit_b = `$INSTANCE_NAME`_pin_B_Read();
        uint8 bit_a = (`$INSTANCE_NAME`_pin_A_PS & `$INSTANCE_NAME`_pin_A_MASK) >> `$INSTANCE_NAME`_pin_A_SHIFT; //6+6tick
        uint8 bit_b = (`$INSTANCE_NAME`_pin_B_PS & `$INSTANCE_NAME`_pin_B_MASK) >> `$INSTANCE_NAME`_pin_B_SHIFT;
        
    #else
        // todo: can we read it in a single read operation?
        //StopWatch_1_Start();
        //uint8 bit_a = `$INSTANCE_NAME`_pin_A_Read(); // 106 tick 
        //uint8 bit_b = `$INSTANCE_NAME`_pin_B_Read(); //+23tick
        //uint8 bit_a = CyPins_ReadPin(`$INSTANCE_NAME`_pin_A_0) != 0; // 72 tick  (69->55_INLINE))
        //uint8 bit_b = CyPins_ReadPin(`$INSTANCE_NAME`_pin_B_0) != 0; // 7+7 tick
        uint8 bit_a = (`$INSTANCE_NAME`_pin_A_PS & `$INSTANCE_NAME`_pin_A_MASK) >> `$INSTANCE_NAME`_pin_A_SHIFT; //6+6tick
        uint8 bit_b = (`$INSTANCE_NAME`_pin_B_PS & `$INSTANCE_NAME`_pin_B_MASK) >> `$INSTANCE_NAME`_pin_B_SHIFT;
        //StopWatch_1_Stop();

    #endif    
    
    
    #if (`$INSTANCE_NAME`_InvertDir)
        uint8 bits = ((bit_a << 1) | bit_b);
    #else
        uint8 bits = ((bit_b << 1) | bit_a);
    #endif

    index <<= 2;                                // remember previous state by shifting the lower bits up 2    
    index |= bits;                              // OR bits with var old_AB to set new value
   
    Acc &= 0x03;                                // dont let it grow >3 or <-3
    Acc += enc_states[ index & 0x0f ];          // accumulate 1/4 steps                                       
    
    return Acc>>2;                              // -1=CCW, 0=NAN, 1=CW  
}

//==============================================================================
// Debouncing ISR - counts milliseconds elapsed after button press
// Rises semaphore flag when timeout
// Works on Button Pressed event
//==============================================================================
    
#if (`$INSTANCE_NAME`_BtnEnable)
CY_ISR(`$INSTANCE_NAME`_Tick_ISR)
{
	if(SW_timeout != 0) // this isr works continuously! make 100 Hz or use SysTick ISR!
	{
		if(--SW_timeout == TIMED_OUT) // edge was detected by the PICU. Decrement and check timeout.
		{
            // Timed out -> check if SW still pressed  
            if (`$INSTANCE_NAME`_pin_btn_Read() == 0)  
			{
                `$INSTANCE_NAME`_isrBtnSW_Stop();
                //`$INSTANCE_NAME`_BtnPressed = 1;
                fBtnPressed = 1;
			}
		}
	}
}
#endif


//==============================================================================
// interrupt on external clock for polling states
//==============================================================================
//static volatile CYBIT fDataReady = 0; // semaphore flag


CY_ISR(`$INSTANCE_NAME`_myPollInt) 
{   
    //`$INSTANCE_NAME`_fDataReady = 1;
    //`$INSTANCE_NAME`_ClearInterrupt(); // must clear +11 ticks
    

    //StopWatch_1_Start();
    `$INSTANCE_NAME`_CheckStatus(); // C@H (pol/isr)  72/91 tic // 
                             // C@H (pol/isr)  53/58 tic // w/o button
                             // C@H (pol/isr)    /69 tic // w/button 
    //StopWatch_1_Stop(); 
}    


#endif //IsrEnable   



//==============================================================================
// Initialize encoder 
//==============================================================================

void `$INSTANCE_NAME`_Start()
{
    //`$INSTANCE_NAME`_Position = `$INSTANCE_NAME`_StartPosition;
    //`$INSTANCE_NAME`_SetPosition(`$INSTANCE_NAME`_StartPosition);
    
    //`$INSTANCE_NAME`_isrBtnSW_StartEx(Tick_ISR);
    //`$INSTANCE_NAME`_isrBtnSW_Disable();
    
    #if `$INSTANCE_NAME`_IsrEnable
        `$INSTANCE_NAME`_isrDtr_StartEx(`$INSTANCE_NAME`_myDtrInt);//start isrDtr interrupt
    #else    
        `$INSTANCE_NAME`_isrPoll_StartEx(`$INSTANCE_NAME`_myPollInt);//start isrPoll interrupt
    #endif    
} 

//==============================================================================
// Get encoder position 
// value must be in range [lower_bound, upper_bound]
// return: 0-failed, 1-success
//==============================================================================

er_t  `$INSTANCE_NAME`_GetPosition()
{
    return aPosition;
}




//==============================================================================
// Set encoder position
// value must be in range [lower_bound, upper_bound]
// return: 0-failed, 1-success
//==============================================================================

uint8 `$INSTANCE_NAME`_SetPosition(er_t value)
{
    uint8 result = 0;
    
    if (((er_t) `$INSTANCE_NAME`_LowerBound <= value) && (value <= (er_t) `$INSTANCE_NAME`_UpperBound))
    {
        if (value != aPosition)
        {
            fPositionChanged = 1;   // fire position changed event
            aPosition = value;      // update position
        }    
        result = 1;                 // success
    }
    
    return result;
}


//==============================================================================
// Get last direction of encoder rotation:
// return: -1=CCW, 1=CW
//==============================================================================

int8  `$INSTANCE_NAME`_GetDirection()
{
    return aDirection;
}

/*
//==============================================================================
// Clears pins interrupt
// If pins isr is enabled, then must clear inside ISR to allow further isr events
//==============================================================================

void `$INSTANCE_NAME`_ClearInterrupt() // todo: uint8? //todo: move into #isr_enabled
{
    #if `$INSTANCE_NAME`_IsrEnable
        #if (`$INSTANCE_NAME`_BtnEnable)
            //`$INSTANCE_NAME`_PINS3_ClearInterrupt();
            
            //(`$INSTANCE_NAME`_PINS3_INTSTAT & `$INSTANCE_NAME`_PINS3_MASK) >> `$INSTANCE_NAME`_PINS3_SHIFT; //+16 tick
            //(`$INSTANCE_NAME`_PINS3_INTSTAT & `$INSTANCE_NAME`_PINS3_MASK); // +16
            `$INSTANCE_NAME`_PINS3_INTSTAT; // +16
        #else
            //`$INSTANCE_NAME`_PINS2_ClearInterrupt();
            `$INSTANCE_NAME`_PINS2_INTSTAT;
        #endif    
    #endif    
}
*/

//==============================================================================
// Return button pressed flag, reset flag if non-zero
//
//==============================================================================
#if (`$INSTANCE_NAME`_BtnEnable)
//volatile 
uint8 `$INSTANCE_NAME`_GetBtnPressed() //must declare "volatile"! 
{
    uint8 result = fBtnPressed;
    if (fBtnPressed) fBtnPressed=0; // reset flag for one-time use only
    return result;
}
#endif

//==============================================================================
// Return position changed flag, reset flag if non-zero
//
//==============================================================================

//volatile 
uint8 `$INSTANCE_NAME`_GetPositionChanged() /////must declare "volatile"! 
{
    
    //uint8 result = fPositionChanged;
    //fPositionChanged=0; // reset flag
    
    uint8 intStatus = CyEnterCriticalSection(); // must have else skipped steps
    
    uint8 result = fPositionChanged;
    fPositionChanged=0; // reset flag 
    
    CyExitCriticalSection(intStatus);
    
    return result;
}


/* [] END OF FILE */



