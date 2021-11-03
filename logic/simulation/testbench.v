`timescale 1ns/1ps
module testbench;
    reg [1:0] key_sw;
    wire [1:0] led ;

    top DUP (key_sw,led);
    initial begin
        key_sw=2'b00;
        #10;
        key_sw=2'b01;
        #10;
        key_sw=2'b10;
        #10;
        key_sw=2'b11;
        #10;
    end
    
    initial 
        $monitor("key_sw=%b led=%b",key_sw,led);
endmodule