### LINK-669: an adoption gives a second unit a retail-proven implicit destructor, and the old sole copy's out-of-line `~AsciiString` now loses
Status: Repair committed / awaiting landing and census confirmation (one instance). Updated: 2026-11-13 (seat
halilkkaya-rg1); base `d605b7a1a05`, census index `16b6c8496e` (census `b25a313d87`).

**Symptom.** PeerDefs.cpp: census 2026-11-12 22:09 (`27e4b01ed7`) "yes", 7,255 B; census 2026-11-13 01:15
(`e5da954ea6`) "no". link_check: comdat `??1AsciiUnicodePair@@QAE@XZ` "unproven and differs from the kept copy".

**Cause.** "Register canonical AsciiUnicodePair, adopt it in 3 units" (`50b66183c17`, StarkillerHDX) gave
Rva003829E5Init.cpp (compiled without `/O`, so it emits every inline special member) the full 32-byte layout in
place of an empty view. That unit now emits the implicit `??1AsciiUnicodePair@@QAE@XZ`, which calls
`StringBase<char>::releaseBuffer` (0x00036410) directly as retail's 0x0038240F does: verdict `retail`. Until then
PeerDefs.cpp's copy was the only one. PeerDefs.cpp compiles with `/DBFME_ASCII_DTOR_DECL`, which declares
`~AsciiString` out of line, so its copy calls `??1AsciiString@@QAE@XZ` (0x0048BA39, a `jmp 0x00036410`). Census
order puts PeerDefs.cpp first, so its unproven differing copy loses. The commit is in `e5da954ea6` and not in
`27e4b01ed7`.

**Repair.** "Drop PeerDefs.cpp's out-of-line AsciiString destructor switch" removes `/DBFME_ASCII_DTOR_DECL` from
the unit's `// cl:` line. All 136 rows still match. A REL32 check against retail (lk104's relchk) found 23 call
sites at HEAD that named `??1AsciiString` (0x0048BA39) where retail calls 0x00036410; after the change there are
0, and no site where retail calls 0x0048BA39 now calls something else. The object now also defines the inline
`??1AsciiString@@QAE@XZ` (`jmp releaseBuffer`), the same digest as the 2,219 retail-proven copies in the index.
link_check over PeerDefs.cpp, Rva003829E5Init.cpp, GameSpyInfoCtor.cpp, BfmeNodeValueEBDDestructor.cpp (the
0x0038240F row) and AsciiUnicodePairCopyCtor.cpp: 5/5 LINKS, LINKED 513 -> 7,768 B (PeerDefs.cpp 0 -> 7,255).

**Lead.** 200 sources still use `BFME_ASCII_DTOR_DECL`. LINK-662's sweep counted 467 rows that call
`??1AsciiString` where retail calls 0x00036410. Each such unit that also emits an implicit destructor with an
AsciiString member can lose the same way once another unit emits a retail-proven copy. Dropping the switch is safe
only when every row still matches and the REL32 check shows no new mismatch.
