# HordeUpdate bounded emission repair

2026-10-28; base `afeacf59f48765b7f51635a491e4d52cae9ab09a`;
owner `yasinschroeder-codex3`. Preview index `d92e7e6635`,
2026-10-28 15:58. No census measurement is claimed.

## Target facts and identity limits

The only row in `Code/GameEngine/Source/GameLogic/Object/Update/HordeUpdate.cpp`
is `?isTrueHordeMember@HordeUpdate@@UBE_NXZ`, RVA 0x0049001F, 14 bytes.
Retail bytes are `33c03841097406384108740140c3`: zero EAX, test bytes
at interface-this +9 then +8, and return their logical AND. There are no
relocations. The existing LINK-072 investigation places a pointer to the
body at retail .rdata RVA 0x0084D054, in a vftable. The TU map approves
`LargeGroupBonusUpdate.cpp` with provisional C evidence for its enclosing
0x0048FFD4..0x0049002D cluster.

The existing Zero Hour class/method spelling is a masked-placement legacy,
not proof of retail identity. No row, name, source path or approval changes
in this repair. Name reconciliation and consolidation into the approved TU
remain outstanding. This is emission cleanup, not a recovered retail class.

## Donor facts and bounded reconstruction

The old file imported the Zero Hour HordeUpdate implementation, including
its update loop, flag draw callbacks, parser and snapshot methods. The
reference HordeUpdate header declares the row's expression as
`m_trueHordeMember && m_inHorde`, in a secondary interface, with an unsigned
refresh frame followed by three bools. These are donor facts; the reference
is not a BFME 2 source-path claim.

A small declaration view retains the old interface placement and field order,
and defines the override out of line. The compiler emits just the matched
method. No object, vftable anchor, assembly, pin or new hatch is needed.
The declared primary base size is 0x20, placing the secondary interface
there; its four-byte vptr and refresh frame put the tested bools at +8/+9
relative to that interface. Only those two loads are proven by this body.
The declarations do not establish a complete retail class layout.

BFME 1 freshness receipt was 2026-10-28T11:47:35.588522+00:00; its checked
reference HEAD was `0424131c818fba6641613ef826222ecf30845025`.

## Provider and verification evidence

- `./build.sh` before and after: 1/1 exact, all 14 bytes; no literal/import
  verification failures. The retained method's raw object bytes and
  relocations also compare equal between the saved before object and after.
- `find_declared_unmatched.py` after: no unclaimed definitions. Nine removed
  `present-unmatched` bodies also lose their nine hatch-baseline allowances.
- `data_check.py`: zero shadow findings. `eh_verify.py`: zero EH rows and no
  missing object. `link_check.py --prepare-current`: strict receipt created,
  normal byte gates 1/1.
- Current-provider ordinary preview before: five unresolved references
  (HordeUpdate Snapshot name and four Drawable decal/subobject methods),
  0 authored bytes linked. After: LINKS, 14 authored bytes; no unresolved
  external symbols remain in the object. This is a preview, not census gain.
- COFF external definitions fall from 689 to one, retaining the sole row;
  688 definitions removed and none added. Of the removed names, 42 have no
  remaining provider in the saved index, and no other indexed source touches
  any of those 42. The other removed names have indexed providers. This
  comparison uses the dated index and does not establish current whole-tree
  provider selection. The adjacent JSON retains the counts and unique names.
- Outgoing `link_batch_audit.py` on the staged tree exits 2: baseline index
  `d92e7e6635` predates this base, and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Consumer preservation is therefore UNVERIFIED by that audit;
  carry this scope into the next census. No missing consumer is treated clean.

Scratch before source/object and full COFF comparison are under
`build/horde-inline-link-20261028/`. The tracked JSON and this report retain
reviewable conclusions without depending on those local files. LINK-072 and
the target register retain the identity/TU and consumer-confirmation work.
