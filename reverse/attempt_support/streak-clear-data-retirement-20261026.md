# Retire two stale data keys in the streak-resource clear wrapper

The default queue served `Rva0012641FClear.cpp` at upstream `2edd747b85`.
Its entire source was claimed and inspected. The frozen-file check passes.
No source change is required: commit `0bb6eb81be` already replaced the two
private holder globals with declarations of the existing pointer owners,
`g_Va00DEE86C` and `g_Va00DEE870`, casting their addresses at each call site.
The queue still held both prior `g_00DEE86C`/`g_00DEE870` wrong-name keys.

Normal verification preserves the wrapper's complete 20-byte boundary at
`0x0012641F..0x00126433` and both teardown rows in `Rva007B7024Cluster.cpp`:
three function rows total. The owner's two four-byte data rows also verify.
The existing source declares the same pointer type as the single owner; no
second definition, new pin or newly recovered application name is introduced.

`repair_queue.py retire data` passes, removes both keys, and reports zero
remaining findings for the served file. The ordinary link preview remains
clean at 20 -> 20 authored bytes against index `f995f30157` (2026-10-25 21:36).
This records two stale data-debt retirements, not a new source repair or
matched, C++ exact, census-linked or image-ownership gain.
