/* ========================================
 *  Dual implementation of software rotary encoder routines:
 *
 *  using Oleg @ CircuitsAtHome 
 *  http://www.circuitsathome.com/mcu/programming/reading-rotary-encoder-on-arduino (link is dead..)
 *  https://www.ccsinfo.com/forum/viewtopic.php?t=41115
 *   
 *  
 *
 *
 * ========================================
*/




// todo: add unique prefix e.g. ENC1_... (?)
#ifndef `$INSTANCE_NAME`_H
#define `$INSTANCE_NAME`_H
 
    
#include <project.h>
#include <cytypes.h>
//#include <cyfitter.h> 

//CY_ISR_PROTO(`$INSTANCE_NAME`_Tick_ISR); // todo: reomove?

//volatile CYBIT `$INSTANCE_NAME`_flag_DataReady; // semaphore flag  
    
//CY_ISR_PROTO(`$INSTANCE_NAME`_myDtrInt);    // interrupt on encoder pin states change
//CY_ISR_PROTO(`$INSTANCE_NAME`_myPollInt);    // interrupt on external polling clock
    
#define SW_DEBOUNCE_TIME 50      // debounce time in milliseconds
//#define SW_DEBOUNCE_TIME_SLOW 20      // todo: debounce time in milliseconds for slow clock   
          
#define true  1
#define false 0


/***************************************
*        read-only parameters
***************************************/  
#define `$INSTANCE_NAME`_EncoderRange  `=$encoder_range `   // 
#define `$INSTANCE_NAME`_CheckBounds   `=$check_bounds  `   //  
#define `$INSTANCE_NAME`_LowerBound    `=$lower_bound   `   // 
#define `$INSTANCE_NAME`_UpperBound    `=$upper_bound   `   // 
#define `$INSTANCE_NAME`_StartPosition `=$start_position`   // todo: _position? (preset_position?)
#define `$INSTANCE_NAME`_BtnEnable     `=$btn_enable    `   // enable button switch 
#define `$INSTANCE_NAME`_InvertDir     `=$invert_dir    `   // 
#define `$INSTANCE_NAME`_IsrEnable     `=$state_check_type==1`   // use polling / interrupt to check pins state      

    

// use encoder built-in range types: int8_t, int16_t, int32_t, uint8_t, uint16_t, uint32_t        
#define er_t `=GetNameForEnum("encoder_range_type", $encoder_range)` // int8_t, uint8_t, ..., uint32_t



/***************************************
*        read-only variables
***************************************/  

//volatile uint8 `$INSTANCE_NAME`_BtnPressed;     // flag
//volatile uint8 `$INSTANCE_NAME`_PositionChanged;// flag

// encapsulation->  
#define `$INSTANCE_NAME`_BtnPressed      `$INSTANCE_NAME`_GetBtnPressed()      // flag
#define `$INSTANCE_NAME`_PositionChanged `$INSTANCE_NAME`_GetPositionChanged() // flag    
#define `$INSTANCE_NAME`_Position        `$INSTANCE_NAME`_GetPosition()        // current position // todo: check read-only?
#define `$INSTANCE_NAME`_Direction       `$INSTANCE_NAME`_GetDirection()       // save last rotation direction:  +1 or -1 

//todo: add _enable    
//extern const signed char enc_states[]; - not work
    
/***************************************
*        Function Prototypes
***************************************/

void  `$INSTANCE_NAME`_Start();                 // 
er_t  `$INSTANCE_NAME`_GetPosition();           // get current encoder position (type: encoder range type)
uint8 `$INSTANCE_NAME`_SetPosition(er_t value); //
int8  `$INSTANCE_NAME`_GetDirection();          // last rotation direction:  -1=CCW, 1=CW 
void  `$INSTANCE_NAME`_ClearInterrupt();        // clear pins interrupts 
//__INLINE void  `$INSTANCE_NAME`_ClearInterrupt();   // clear pins interrupts - no difference

//volatile 
uint8 `$INSTANCE_NAME`_GetBtnPressed();      //  
//volatile 
uint8 `$INSTANCE_NAME`_GetPositionChanged(); //

// todo: hide functions? (static?)
//int8  `$INSTANCE_NAME`_PositionChanged();       // return:  -1=CCW, 1=CW // rename as _PositionChange (?)
//int8  `$INSTANCE_NAME`_StateChanged();       // return:  -1=CCW, 1=CW // rename as _PositionChange (?)

int8  `$INSTANCE_NAME`_CheckStatus();       // return:  -1=CCW, 1=CW // rename as _PositionChange (?)
//int8  `$INSTANCE_NAME`_CheckStatus() __attribute__ ((section(".data")));

__INLINE int8  `$INSTANCE_NAME`_CheckRotation();         // rotation:  -1=CCW, 0=NAN, 1=CW (pol: 69->55 tic)
//__STATIC_INLINE int8  `$INSTANCE_NAME`_CheckRotation();         // rotation:  -1=CCW, 0=NAN, 1=CW (pol: 69->55 tic)




    
#endif /* `$INSTANCE_NAME`_H */

/* [] END OF FILE */



/*
`#DECLARE_ENUM encoder_range_type` 
        
#define `=GetNameForEnum("encoder_range_type", 1)`
#define `=GetNameForEnum("encoder_range_type", 2)`
#define `=GetNameForEnum("encoder_range_type", 3)`
#define `=GetNameForEnum("encoder_range_type", 4)`
*/

/*    
#if   (`$INSTANCE_NAME`_EncoderRange == `=int8_t`  ) // component built-in types
    #define er_t int8_t
#elif (`$INSTANCE_NAME`_EncoderRange == `=uint8_t` ) 
    #define er_t uint8_t
#elif (`$INSTANCE_NAME`_EncoderRange == `=int16_t` ) 
    #define er_t int16_t
#elif (`$INSTANCE_NAME`_EncoderRange == `=uint16_t`) 
    #define er_t uint16_t
#elif (`$INSTANCE_NAME`_EncoderRange == `=int32_t` ) 
    #define er_t int32_t
#elif (`$INSTANCE_NAME`_EncoderRange == `=uint32_t`) 
    #define er_t uint32_t
#endif    
*/

