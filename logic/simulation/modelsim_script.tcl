vlib work

vlog ../testbench.v ../../top.v

vsim work.testbench

add wave sim:/testbench/*

run -all

wave zoom full