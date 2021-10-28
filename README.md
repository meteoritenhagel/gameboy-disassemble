# gameboy-decode
Decoder for gameboy bytecode. Work in progress.

- [x] Supports local labels

Never use `JR ` with assembler-specific constants. Only labels, since the symbolic table saves each entry exactly once
and hence it will be treated as label (and calculating the difference).