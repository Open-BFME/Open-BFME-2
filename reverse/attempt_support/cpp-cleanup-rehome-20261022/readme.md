# Six manual MASM cleanups emitted by recovered C++ parents

At BFME2 a00ba94d02 (with evidence-only local commits), the six remaining
manual state-bit cleanup rows below already have real recovered C++ parents.
This changes ownership from manual MASM to the compiler's actual cleanup; no
synthetic parent, helper alias, new pin, asm wrapper or new class is introduced.
The original ASM files remain as evidence. Each manual owner is retracted in a
separate commit as add_match requires, followed by a verified C++ row commit.

| Cleanup RVA | Bytes | Parent RVA | Current local label |
| --- | ---: | --- | --- |
| 0x00785033 | 25 | 0x00405E3D | $L6957 |
| 0x0075D09B | 25 | 0x000470D5 | $L3210 |
| 0x007667DC | 34 | 0x0014C470 | $L11915 |
| 0x007667FE | 34 | 0x0014C470 | $L11917 |
| 0x007695F4 | 25 | 0x001D9484 | $L8552 |
| 0x0076B15A | 25 | 0x001F1634 | $L7226 |

Total: 168 bytes of real cleanup code transferred from ASM-only to C++ exact.
The source files and parent names are in verification.json. The parent prologue
selects its retail handler; FuncInfo's unwind map names each action. Independently,
eh_verify verifies the whole associated object EH graph, then places its local
$L label at that same address. All six locations are unique and all six full
bodies match retail with no unresolved relocations. Each row carries the real
parent name; object-symbol aliases and adjacency guesses are unnecessary.

The normal scoped build passed 31/31 rows across all five parent source files,
plus literal, float and import checks. The ownership replay and complete result
are preserved here. Copy verify.py.txt to build/ and run from the repository root
after building those five sources; its hard-coded target population is the
remaining manual EH rows, so a successful rehome removes them from its output.
Its output is a current-label diagnostic; the ledger verifier binds labels
through exact parent EH data if future edits renumber them.

Compiler: pinned MSVC 13.10.3077, SHA256
2ecf86a3edfd3deae498e08298e210e984537ce9e11759930561e43f40bd2515.
BFME1 pin: 37c3022de1ab944c7ffe536440d637dc8199091c. Verification uses
the normal host build and the read-only source share into the local Debian x86
QEMU/Wine VM. No old-snapshot experiment is used as proof for this rehome.
