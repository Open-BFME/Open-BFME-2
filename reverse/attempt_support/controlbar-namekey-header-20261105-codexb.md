# ControlBar NameKeyGenerator header prerequisites

Base: `dba4e36e1e`; worker: `yasinschroeder-codexb`; 2026-11-05.

The current-map `tu_skeleton.py --merge
Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp --dry-run`
accepted no donors. Its 18 clean donors still fail on incompatible declarations
or compiled bytes; seven mixed sources remain outside this merge. No source or
ledger path moved, and no source-file reduction is claimed.

The dry run reports `SubsystemInterface` redefinitions in UpdateVirtual,
ForgetStaleCommandSet, ReloadNotice, SwitchContext and the destructor donor.
Other failures include `Overridable` in InitSpecialPowerShortcut, Rva0031D230
and populateSpecialPowerShortcut; `Coord2D` in ControlBar_Rva0031B99A;
incompatible STLport `allocator`, `pair` and `__false_type` declarations; and
byte failures in stlport_vector_voidptr_opt and StlSweepW5Rva0031B9EB. These
are consolidation prerequisites, not newly lost rows or measured link losses.

## Applied prerequisite

Adopt `Code/GameEngine/Include/Common/NameKeyGenerator.h` in these already
claimed donors:

- `ControlBarUpdateVirtual.cpp`: `0x0031E25E`, 604 B.
- `ControlBarInitSpecialPowerShortcut.cpp`: `0x0031BAC3`, 658 B, its 10 B EH
  handler and four 8 B compiler funclets.
- `ControlBarRva0031D230.cpp`: `0x0031D230`, 968 B, and its 10 B EH handler.

The first two previously included the subsystem shim, which defines a second
`SubsystemInterface` independently of the canonical header guard. Include the
canonical NameKeyGenerator header there before other subsystem consumers. It
selects the full subsystem slots and includes the canonical base. Drop the
unused subsystem-shim include flag in those two sources. The context donor
already selects the canonical full-slot base; the adoption tool replaces only
its private NameKeyGenerator body. No class layout, recovered name, function
implementation, alias, pin or ledger identity is changed.

## Verification and remaining work

The individual byte gates pass for all nine rows (2,282 B), including EH
metadata-based verification of renumbered funclet labels. Literal, float and
import reference checks pass. Declared-unmatched scans pass before and after
the edits. `header_adopt_lane.py accept --class NameKeyGenerator` accepts all
three donors and retires their three queue rows through the supported path; acceptance
includes an ordinary link preview with no loss of census-linked bytes.

Continue reconciling the remaining subsystem and private-view conflicts before
the next normal merger run. This prerequisite does not assert that a merged TU
now compiles or links; the post-edit merger has not been run. No census, real
link or smoke measurement was started.

## Landing receipt

The prerequisite landed as `5ae67ad8f3`. Pre-push reverified all nine code rows,
three exact EH graphs, DIR32 identities and converged data ownership. Its batch
link audit was **inconclusive**: the census index was at `3a95b274a2`, older than
the outgoing base `b500074091`, and all three changed source objects lacked
current audit receipts. The successful header-adoption previews above do not
resolve that outgoing-audit gap. Carry these three donors into the next census
for confirmation; no measured linking improvement is claimed.
