# sima
A simple computer simulator

## Instruction set

Instructions can have source (_src_) and/or destination (_dest_). Destination is always a memory location address,
expressed `[addr]` (a number enclose in brackets). For example `[8]` points to 8th byte in memory. Source can either
be a memory location `[addr]` (with brackets) or a constant number `val` (without brackets). For example,
`COPY [8], 5` copies value `5` into the 8th byte of memory.

`COPY dest, src`
Copy _src_ into _dest_.

`ADD dest, src`
Add values of _src_ and _dest_ and store the result into _dest_.

`SUB dest, src`
Subtract value of _src_ from _dest_ and store the result into _dest_.

`MUL dest, src`
Multiply values of _src_ and _dest_ and store the result into _dest_.
