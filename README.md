# YRV-Plus RISC-V CPU for OMDAZZ board with VGA and PS/2 keyboard

## Scripts description
In  Plus/boards/omdazz/ run
```
  01_clean.bash                   Clean project
  05_synthesize_for_fpga.bash     Synthesize project and load ro FPGA
  06_configure_fpga.bash          Load project to FPGA
  07_upload_soft_to_fpga.bash     Upload binary using UART
  
```
You need USB-to-Serial adapter for loading binary to the FPGA Board.


## Programs Description
```
  01_hello_text        Simple hello world 
  01_tetris            ASCII based tetris game
```

After build you copy  _code_demo.mem32_ to the _Plus/design_ directory

You can run ./07_upload_soft_to_fpga.bash directly form source folder

## Toolchain 

Toolchain shoul be installed in:  _/opt/riscv_native

Minimal version of GCC should be 12.1.0

## Tetris game 
![ASCII Tetris game](/tetris.jpg "Tetris")

## Related books:
"Inside An Open-Source Processor" ISBN 978-3-89576-443-1

"Modern C." Manning, 2019, 9781617295812. ffhal-02383654 Jens Gustedt. 


