
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
// Generated on 01/19/2013 at 18:14
// Component: Accu
module Accu (
	seg,
	timing,
	clk,
	pwm_in
);

	output  seg;
	output  timing;
	input   clk;
	input   pwm_in;

//`#start body` -- edit after this line, do not edit this line
    reg		pwm_temp;
	reg		pwm_temp_pre;
	reg		pwm_flag;
    
   
    reg     [2:0] count;
    reg     [4:0] timing_count;
    reg     seg;
    reg     timing;
    
    always @(posedge clk)
    begin
        pwm_temp <= pwm_in;
        if({pwm_temp_pre,pwm_temp} == 2'b01) pwm_flag <= 1;
        pwm_temp_pre <= pwm_temp;
        
        if(pwm_flag)
        begin
        
            pwm_flag <= 0;
            count <= count + 1;
            timing_count <= timing_count +1;
            
            
            if(count == 3'b010)  seg <= 1;
            else if(count == 3'b011)
            begin
            
                seg <= 0;
                count <= 0;
            end
            
            
            if(timing_count == 5'b10010) timing <= 1;
            else if(timing_count == 5'b10011)
            begin
            
                timing <= 0;
                timing_count <= 0;
            end
        end
    end
//        Your code goes here

//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
