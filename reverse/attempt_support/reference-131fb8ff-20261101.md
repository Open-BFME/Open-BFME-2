# BFME 1 reference check, 2026-11-01

The Cortys account's official upstream check fetched BFME 1 master once at
2026-11-01 17:30:51 UTC, finding
`131fb8ff0a515c504313ac10ec87c929d71cf214`. The previous verified pin was
`7a8a034afa7dd3530d9a99dc48cfec711626256c` (BFME 2 verification commit
`66158591559440624c5b9ff89017fafbb8fd97b5`). This isolated helper borrowed the
already-fetched target locally; it made no second official freshness fetch and
preserved the other checkouts.

The revision comparison changes 645 paths, including 411 game C++ sources,
three game assembly sources and one game header. The header, WW3D2/ww3d.h,
changes three render-device return declarations from WW3DErrorType to bool.
There are no toolchain or vendor changes and no layout migration. Under inputs/,
only the nested BFME 2 reference pointer changes; it remains uninitialized.
The expected game include tree, ww3d.h, inputs/reference, inputs/toolchains and
inputs/vendor paths were checked explicitly and exist.

The initial normal full verification used BFME 2
`88151d263f85548a3632a19f1969bc7d7d0c15a5` with the candidate reference.
It found precisely two failures among 99,276 function rows: sphereobj.cpp's
Peek_Color_Channel emitted offset 0x108 instead of 0x10C, and
Peek_Vector_Channel emitted 0x150 instead of 0x154. Its string, float, import,
DIR32, pin, module, source-claim and 2,253 data-row checks passed. The no-op
patch was correctly reported unrunnable after the function failures.

A scoped control at that same BFME 2 revision with the old verified reference
reproduced the identical two failures among sphereobj.cpp's three rows. These
were pre-existing failures, not candidate-reference regressions. Meanwhile,
master had received `9d05d65fe3`, which selects the verified donor rendobj view
explicitly. After rebasing the helper onto
`6b1a8fb85cc9ece311c33518151b034a028eb6d0`, sphereobj.cpp with the candidate
reference passes all three rows and its scoped reference checks. This helper
made no Code/ edits.

Donor sweeps were refreshed at the candidate revision in the isolated helper.
No cached donor compile trial was reused. Future transfers must validate their
own source, header and command inputs against this donor revision. Normal
builds independently validate dependency receipts for the private warm cache
and objects restored through the repository's supported object store.

The reference gitlink is a FULL_GATE_ROOT for the normal pre-push hook, so
publication requires the current-base full verification. The account's shared
successful-check record remains unwritten until that gate is green and this
pin lands; the publication output and shared record carry the final outcome.
No nightly, link-cycle or smoke runner was started, and no census gain is
claimed.

Local logs are under build/reference-131fb8ff-20261101/ in the isolated
build/bfme1-freshness-20261101 worktree: full.log, old-pin-control.log,
current-sphere-control.log, donor-scan.log and donor-scan-current.log.
