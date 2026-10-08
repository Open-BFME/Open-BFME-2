# Incoming Snapshot DIR32 inconsistency

At BFME2 `f6b4f9a987` with verified BFME1 `34f59164`, the full gate after
rebasing over a Coord3D shared declaration passed all 70302 function rows,
string/float/import checks, pins, registry and source claims. It failed DIR32
consistency for `??_7Snapshot@@6B@`, resolving to 0x00BBB554 and 0x00C1AD6C.
This is a real source/identity problem, not a requested whitelist change.

Read-only relocation tracing identifies the lone 0x00C1AD6C reference as
`??0Rva0039B893@@QAE@XZ`, 34 bytes at 0x0039B7FB, in
`Code/GameEngine/Source/Common/RTS/ScoreKeeperPerFrameStatsVectorResize.cpp`.
The class is declared novtable, so its constructor emits the Snapshot base
vtable symbol rather than its derived record vtable. The matched record
destructor in ScoreKeeperPerFrameStatsVectorXfer.cpp correctly restores
0x00BBB554.

An isolated trial removing novtable still emits and matches all 34 constructor
bytes, with the derived vtable symbol. The file and constructor are claimed by
other workers (`codex-continuous-recovery` and
`codex-cpp-byte-recovery-01a118a5`), so no competing tracked repair was made.
The isolated test is a lead; provider/consumer and full-gate validation remain
the repairing worker's responsibility. The unpushed 225-byte network recovery
has no Snapshot reference and its own provider/consumer gates passed.

Local evidence: `build/full-gate-native-notify-after-rebase.txt`,
`build/snapshot-dir32-owners.txt`, and
`build/snapshot-ctor-no-novtable-diff.txt`.
