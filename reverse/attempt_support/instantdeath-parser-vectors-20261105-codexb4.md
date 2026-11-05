# InstantDeathBehavior parser-vector reconciliation, 2026-11-05

Base: `7a2219e8cf`. Scope: the already-merged InstantDeathBehavior seed and
its two parser donors. The separate AI source edits in the checkout predate
this work and are excluded.

Retail evidence: field table `0x00841FA8` registers OCL `0x0045D1BD`, Weapon
`0x0045D200`, and Sound `0x0045D2F6`. Those rowed implementations append
OCL pointers, WeaponTemplate pointers, and opaque four-byte sound records at
`+0x44`, `+0x50`, and `+0x5C`. The seed now uses the existing donor views and
names for those fields. This does not establish the original sound-record type
name; `Rva0005A084Element` remains structural. FX retains neutral int storage.

The native 71-byte module-data constructor `0x0045D176` calls `0x00211E58`
for these vectors. `add_match.py --icf-owner` admitted the emitted sound-record
storage constructor as an identical 29-byte fold at that address, including
the resolved allocator-proxy chain. No new pin, unique coverage or linking
gain is claimed. The existing WeaponTemplate constructor row is the fold
owner used for admission.

Checks before composition: `./build.sh` passes all 8 seed rows, including
its parent-bound static-guard funclet after compiler label renumbering;
`code_identity_gate.py --staged` reports zero new findings. Normal and
converged data checks report zero findings, and frozen-file checks pass.
Before adding the fold row, current-index link previews of seed and both
parser donors all LINKS, preserving their 242 + 389 + 127 accounted bytes.
The fold row accounts for an already-covered 29-byte body, not new coverage.

Composition trial with typed fields accepts both parser donors. OnDie still
requires the FX/module-data view and canonical AIUpdateInterface /
Rva0036CA00Str adoptions; the destructor still differs in composition.
Those rejected sources remain untouched. The applying merge and complete
path/debt/provider audit will be recorded separately after this prerequisite.
