# BFME 1 reference freshness, 2026-10-29

The local freshness receipt was older than 72 hours. The clean checkout and
committed gitlink were e42b9782fd4cce1f79832a6ed591b0b8fdbbc2fc, already
verified by BFME 2 commit db41f2b901. The older ignored local receipt still
named de077dd5. Official Open-BFME/Open-BFME-1 master was fetched without
recursion; the fixed update target is
b53c85e7f9d65a7f636271a06e9d0ce2ed2deabb. No dirty or unpublished reference
work is discarded. No nested cross-repository reference is initialized.

The upstream difference has 494 paths and five shim headers. The existing
game/ and inputs/reference/ layout remains applicable; the used include roots
and changed headers resolve at both pointers. Refreshed dependency receipts
identify 23 current matched consumers, owning 72 function and 15 data rows.
A stale receipt for a removed source is excluded. At BFME 2 revision
656dc5717d13f333beece8a9625e342cf57499c3, supported old/new scoped builds both
pass 72/72 rows, 15 data rows, 22 literals plus ten empty-string references,
24 float references and zero imports. All 23 objects retain identical COMDAT
fingerprints and external symbol entries. The subsequent publication rebase
and memcmp cleanup change none of those 23 sources, their flags or headers.

Changed donor StateMachine layouts and getter types describe BFME 1 inputs;
they do not establish BFME 2 class layout or identity. None of the 23 affected
objects emits a changed external reference after this update. Scratch evidence:
build/codexb4-reference-inputs-20261029.json, old/new-consumers-20261029.log,
old-objects/facts.json, new-objects-facts.json and object-deltas.json.

An earlier old-reference full gate passed 98,944 function rows, 2,235 data rows,
9,116 float references and 6,424 imports. Its run spanned a publication rebase;
it is not a same-revision old/new full-gate comparison. The bounded old/new
consumer comparison above was run after that rebase at a fixed revision.
The final full gate at the new reference and donor refresh are recorded below
only after completion. No census gain, source-file reduction or debt retirement
is attributed to this reference update. No BFME 2 production source path moves.

Final verification at BFME 2 revision
58d73a74bd54cd77c477d9f7b5b29728c8a2a9ca with only this reference gitlink and
evidence staged: `PYTHONUNBUFFERED=1 BUILD_POOL=16 ./build.sh` exits zero,
FULL GATE: OK. It verifies 98,944/98,944 functions across 20,768 source paths,
2,235 data rows, 31,537 string literals plus 2,247 empty-string references,
9,116 float references and 6,424 imports. DIR32 consistency (18,883 symbols),
pins, 329 module registrations, source claims and the no-op patch all pass.
There are no residual failures. The full log is
build/codexb4-reference-new-full-20261029.log. No concurrent source edit,
rebase or compiler-input change occurs during this run.

The refreshed `python3 tools/bfme1_sweep.py scan --min-size 16` also exits
zero: 38,910 clean donor bodies, 5,538 unique placements (all covered),
5,534 independent exact-boundary controls, zero free placements and 617
near misses. Its match.json SHA256 is
0b6364cf14cb231fc692c3214c2e1b234eeaff9828022707d256f8842f5d80ec.
The donor revision, BFME 2 revision, command and hash are recorded in
build/bfme1_sweep/codexb4-20261029-inputs.json. Previous scratch results are
preserved as build/codexb4-reference-sweep-before.json and are not reused as
fresh evidence. No compile trial involving changed donor sources is reused.

Only after these checks pass is the ignored local freshness receipt eligible
to be stamped with the verified b53c85e7 pointer. The update changes no BFME 2
production source path, provider binding or source registry. The dependency
comparison finds no emitted code or external-symbol differences to carry into
the census as an update regression; the separate Player cleanup's consumer
confirmation remains pending as recorded in the linking registers.

Publication rebase follow-up: upstream BFME 2 independently advanced the
reference to verified f64f0f32 (commit f61ea90efc). That donor commit is an
ancestor of b53c85e7; the shim-header diff between the two is empty. Keep the
newer b53c85e7 target when resolving the gitlink conflict. None of the 23
compared consumers changed in the rebase. Preserve both independent linking
handoffs at the documentation conflict. A full verification of the completed
rebase is run before retrying publication; its separate receipt is
build/codexb4-reference-rebased-full-20261029.log. The earlier full result
above remains evidence for its explicitly recorded BFME 2 revision.
