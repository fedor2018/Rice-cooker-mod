
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 01/19/2013 at 19:37
// Component: acc1
module acc1 (
	trigger,
	clk,
	pwmin
);
	output  trigger;
	input   clk;
	input   pwmin;
//`#start body` -- edit after this line, do not edit this line
    reg		pwm_temp;
	reg		pwm_temp_pre;
	reg		pwm_flag;
    
   
    reg     [5:0] count;
    reg     trigger;
    
    always @(posedge clk)
    begin
        pwm_temp <= pwmin;
        if({pwm_temp_pre,pwm_temp} == 2'b01) pwm_flag <= 1;
        pwm_temp_pre <= pwm_temp;
        
        if(pwm_flag)
        begin
            pwm_flag <= 0;
            count <= count + 1;

            if(count == 6'b101100)  trigger <= 1;
            else if(count == 6'b110001)
            begin
            
                trigger <= 0;
                count <= 0;
            end
        end
    end
    
//        Your code goes here

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
