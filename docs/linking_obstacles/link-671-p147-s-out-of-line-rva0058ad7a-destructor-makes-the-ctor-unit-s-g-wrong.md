### LINK-671: P147's out-of-line Rva0058AD7A destructor makes the constructor unit's `??_G` wrong
Status: Open (blocked on a TU approval; two units, 81 B). Updated: 2026-11-13 (seat halilkkaya-rg1); base
`d605b7a1a05`, census index `16b6c8496e` (census `b25a313d87`).

**Symptom.** Census 04:18 (`6e37424cf7`) "yes", census 07:05 (`b25a313d87`) "no": Rva0058AD7ACtor.cpp (45 B) and
Rva0058AD7ABase.cpp (36 B). Both report wrong selected `??_GRva0058AD7A@@UAEPAXI@Z`.

**Cause.** "Rva0058AD7A.h: declare the destructor out of line, as its one owner defines it (P147)"
(`5d9351a4ce4`, Jon Farmer). It fixed an LNK2005 on `??1Rva0058AD7A@@UAE@XZ` and said in its message that it
accepted this effect. The constructor unit (0x0058AD4D) stores the vptr, so it emits the table and a `??_G`.
With the destructor out of line, that `??_G` calls `??1` (28 B, verdict `wrong`). Retail's 0x0058AE36 (29 B, rowed
in Rva0058AD7ABase.cpp) stores the vptr inline. Census order keeps the constructor unit's copy, so both units
select a wrong body. The real link's path order keeps Base's copy.

**Fix.** Constructor, destructor and `??_G` are one TU in retail. No TU is approved for 0x0058AD4D, 0x0058AD7A or
0x0058AE36 in `reverse/tu_map.csv`, so the merge that would fix this is not yet allowed. Once a TU is approved, merge
the constructor into the destructor's unit (`tu_skeleton.py --merge`). A header change cannot fix it: an inline
destructor brings back the LNK2005.
