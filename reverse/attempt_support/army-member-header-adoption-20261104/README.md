# ArmyMemberIconMovieClip: adopt three caller/notification units

2026-11-04; inspected base `1d94f599243951702ce33896381eef58e12acf16`.
Scope: the four queued units for the existing canonical
`Code/GameEngine/Include/GameClient/ArmyMemberIconMovieClip.h`.

Applied:
- OpaqueScalarDeletingDtorsB18.cpp and Rva005FC9F0.cpp now include the
  canonical owner and define their existing nested Impl views separately.
  The latter still declares only its two callees; the former retains the
  existing 0x38-byte allocation view. No callable name or allocation changed.
- Rva005FC8FDApt.cpp uses the canonical owner. The notification walkers use
  the existing list view starting at the canonical observer base's field00
  (+8 in the owner), preserving the three native 15-byte bodies. The unused
  private base and Observable declarations were removed.
- `header_adopt_lane.py accept --class ArmyMemberIconMovieClip` passes these
  three units and retires exactly their three header_queue.tsv rows.

Target/layout facts are already documented in the canonical header and the
existing list-view source comment: the observer storage begins at +8, occupies
0x10 bytes and is initialized by 0x00330757. This change does not recover new
names, identify the opaque lifetime-owner class, or resolve the broader
ArmyHeroIcon lifetime/table obstacle in LINK-086.

Rejected constructor trial: replacing the private owner in
Rva005FC8FDApt_ArmyHeroIconMovieClip.cpp with the canonical header (included at
global scope) leaves a six-byte `mov [esi], vftable` from Rva0007DF07's inline
base construction before the observer constructor. Native 0x005FCEA9/101B
clears +4 and sets the EH state before the observer call, then installs the
owner table afterward; it has no first base-vptr store. The scoped verifier
reports only the owner constructor failing in this unit. The original private
base is novtable; the canonical base is not. This is an observed code-generation
boundary, not approval to change the shared base's contract. Reconcile its
lifetime/emission contract across dependents before retrying this unit.
The trial was reverted, its header queue row retained, and re_log records the
blocked verdict. No failed reconstruction remains in Code/.

The mechanical adoption command also placed includes inside StrategicHUD and
removed required nested Impl declarations in the smaller units. Those trials
were restored before the explicit adoptions above; no verifier was bypassed.
A pointer cast to the observer base in notification walkers initially added
null-preserving instructions. Taking the address of its actual field00 gives
the exact native adjustment.

Verification:
- [Final scoped build](build.log): all four cohort files, including the restored
  constructor file; 60/60 matched, strings/floats/import references pass.
- [Current three-unit link preview](link-check.log): LINKS for all three;
  census-linked bytes stay 1207 -> 1207. Index census 2026-11-04 05:53 at
  5a13f2cd61. This is a preview, not a new census or real-link measurement.
- find_declared_unmatched: clean for all four; check_csv: OK.
- No source paths, ledger identities, pins, alternatenames or shared headers
  changed. No new coverage or linking gain is claimed; header debt falls by 3.
