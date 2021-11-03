#!/bin/bash
rm -rf sim
mkdir sim
cd sim

echo Start simulation
/home/zlobec/intelFPGA_lite/20.1/modelsim_ase/bin/vsim -do ../modelsim_script.tcl

echo 
cd ..
