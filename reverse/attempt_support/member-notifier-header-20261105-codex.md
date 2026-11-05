# Member and notifier header adoption, 2026-11-05

Inspected revision: `264eab81ce`. Changed consumers: `SecondaryBase.cpp`
and `SidesListCtor.cpp`. The class/header and consumer scopes were claimed.

Both consumers now include the existing canonical `Rva00330757Member` header.
Their TU-local inline destructor releases canonical `field00` with the existing
`free` spelling. SecondaryBase's implicit base teardown replaces its private
release helper; SidesListCtor retains inline nullable release in its destructor
and EH actions. No shared header changes or new identity claims are involved.

SidesListCtor also adopts the existing `SidesListNotifier` header. Its member
callback overload copies the four-byte callback representation into canonical
Post storage with memcpy; `/Oi` keeps that fixed copy intrinsic. The entire
30-byte post body remains exact, as do the constructor, destructor and EH
rows. The element type and original member/listener identities remain unknown.

## Verification

- `./build.sh` on both sources: **46/46** code rows exact; 22 funclet rows
  verified through parent EH data after compiler-label renumbering; three
  emitted STLport constructor folds verified. String, float and import checks
  pass.
- `find_declared_unmatched.py` passes both sources before and after editing.
- Owning `header_adopt_lane.py accept` passes both member consumers together
  and the final notifier consumer; it retires **three** header-queue rows.
- Ordinary `link_check.py` against the published index at `f44cbcf5b0`
  (2026-11-05 15:19) preserves **1,060 -> 1,060** census-linked bytes:
  SecondaryBase **25 -> 25**, SidesListCtor **1,035 -> 1,035**. This is a
  prediction preserving existing linking, not a new census or real-link run.

## Provider safety

The two original sources are unchanged between index revision `f44cbcf5b0`
and the inspected revision. Comparing their index definitions with final
objects finds no lost SidesListCtor definitions. SecondaryBase loses only
`?release@Rva00330757Member@@QAEXXZ`, and gains the canonical destructor.
A scan of **26,622** objects under `build/match/`, parsing matching symbol
and directive tables, finds **zero** references or alternatename bindings to
that removed helper. An old Rva004FAC80Release object still defines it, but
safety does not depend on that object remaining in the real link. The emitted
member destructors have the same complete 14-byte body as the rowed owner;
`_free` and that owner's pinned free spelling resolve to retail RVA 0x30830.
No aliases or other external definitions are removed.

LINK-199's remaining constructor caller is accepted. LINK-214 retains six
queued constructor-emitting/vector/Header or scope-sensitive consumers;
those sources are unchanged. Normal commit and push hooks still apply.
