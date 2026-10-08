# BFME 1 reference verification

Official Open-BFME/Open-BFME-1 master fetched earlier in this pass was
fb45feac8d0ae08a8c400050ce5c9eab776cfde7. The previous committed and actual
verified checkout was 34f59164f6d1efd413c5fd37f4894ec834c3c0fe; it was clean
before the detached checkout update. The previous pointer remains recoverable
from the BFME 2 parent tree.

Both full gates ran at the same BFME 2 revision
c4d681aac9a9152a179f6991fa093021068d578f. Both passed 70,688/70,688 functions
and every full-gate check. There were no update regressions or pre-existing
failures in these fixed-revision comparisons. The earlier Snapshot DIR32 failure
had been repaired upstream before this baseline was recorded.

The normal dependency cache recompiled seven affected GameSpy ghttp units.
The changed ghttpConnection.h contains provenance-comment changes; the removed
JPEG/LibPNG headers have no dependencies in the current object receipts.
Old and new resolved include inventories found zero missing directories in
those seven units. The existing layout resolver still selects game/ and
inputs/reference/, inputs/toolchains/, inputs/baselines/ and inputs/vendor/.
No headers were substituted and no target layouts or verifier rules were changed.
Zero Hour source, headers and toolchain inputs did not change, so its existing
compile cache remains applicable.

The refreshed donor sweep found 5,415 placements including 5,340 independently
matched control boundaries; its eligible exact donor-file queue was empty.
The near queue still has three 25-byte EH leads. The lift lane lists 230 bodies
and 137,120 bytes; these lifted bytes are source leads and earn no recovery credit.
The changed clean quaternion unit was also compiled in an isolated trial using
BFME 2's matched sibling SSE2/G7 flags: place_bodies proposed zero bodies or pins.
No external donor path was added to the BFME 2 ledger.

Ignored local evidence and SHA-256 receipts:

- old full gate: build/indefinite-strategic-resolved-full-gate.txt
  d61315a08288a50454e3e1b20b53a34973d6b3f70ac2085bac79a9b26882beb9
- new full gate: build/indefinite-reference-fb45-fixed-full-gate.txt
  34dfffd47c7c864a50d90898b69936a68abd900c786075b99faf721d24b0c606
- old include audit: build/indefinite-reference-inputs-old.txt
  46a5493f4a2c143145ff9880d4054c56e143d7d7244ab21a44b529fb898e5af7
- new include audit: build/indefinite-reference-inputs-new.txt
  46a5493f4a2c143145ff9880d4054c56e143d7d7244ab21a44b529fb898e5af7

Reproduce the full gate at the BFME 2 revision above with each donor checkout;
use the normal dependency cache so changed headers invalidate their consumers.
Link-census and runtime tests were not run for this pointer update.
Completed UTC: 2026-10-08 19:29.
The fixed BFME 2 comparison predates publication rebases. To preserve it after
those commit IDs change, fixed-bfme2.patch reconstructs its source tree from
published master revision cc989ab1801be1e35866f839328aea4444b61276. Apply that
patch on the named base; the resulting tree is
1eb461545beda3b290e636a92ae212bc38f8b5d9.
The patch SHA-256 is 0d8201c26f6cf8d0428e186d67299ab15e727e812ba1dc27a444410b8d5db5b5 (71565 bytes).
Its reverse applicability was checked against the verified local source tree
without modifying any files. The patch is reproducibility evidence and adds
no recovery or coverage credit.
