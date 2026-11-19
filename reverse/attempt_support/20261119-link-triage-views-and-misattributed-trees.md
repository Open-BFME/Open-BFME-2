# Link triage, 2026-11-19: three units read, none repaired

Index `53b35fb75b` (2026-11-18 18:09), tree at `a72dd74941`. Target facts are retail bytes; the
names are the ledger's current rows. No source, row or pin in the tree changed for these three.

## AIEconomyBuilder.cpp (1,566 B): two views of `Rva004EA3B8`

`link_check.py`: `??_7Rva004EA3B8@@6BRva00506B1B@@@` and `??_7Rva004EA3B8@@6BBaseA@@@` differ from
the first copies, which are OpaqueScalarDeletingDtorsB11.cpp's.

| table | AIEconomyBuilder.cpp | OpaqueScalarDeletingDtorsB11.cpp | retail |
|---|---|---|---|
| primary (BaseA), 0x008628A0 | purecall, purecall, `??_E` | purecall, purecall, `??_E`, `rva004EA33A` | 0x0050B238 (the shared `ret 8` stub), 0x004EA1A5, 0x004EAB6E (`??_G`) |
| secondary (Rva00506B1B at +0xC), 0x00862894 | thunk, purecall, `rva004EA33A` | thunk, purecall, purecall | 0x004EA418 (thunk), 0x004EA7FB, 0x004EA33A |

- Retail's secondary slot 1 is `?update@AIEconomyBuilder@@UAEXXZ` (AIEconomyBuilderUpdate.cpp) and
  primary slot 1 is `?rva004EA1A5@Rva004EA1A5@@QAEXPAX@Z`: `Rva004EA3B8`, `Rva004EA1A5` and
  `AIEconomyBuilder` are one class (the constructor 0x004EAAF3 installs both tables).
- `rva004EA33A` is an override in the secondary base, as AIEconomyBuilder.cpp has it: giving that
  unit the canonical `Rva00506B1B.h` (`v1`, `v2` pure) with `rva004EA33A` as a new virtual fails
  `??1Rva004EA3B8` and `rva004EA33A` (their bodies take the adjusted `this`). So B11's view is the
  wrong one, and it cannot name the slot: the canonical base calls it `v2`.
- AIEconomyBuilder.obj already emits `??_GRva004EA3B8` (28 B) and the `??_E` adjustor thunk (8 B)
  equal to retail 0x004EAB6E and 0x004EA418 (relocations masked). The map approves 0x004EA418 for
  AIEconomyBuilder.cpp and only proposes it (K) for 0x004EAB6E, so B11 must keep the `??_G` row and
  with it a view of the class.

Unblocks it: an approval of 0x004EAB6E for AIEconomyBuilder.cpp (both rows move, B11's view and its
`EmitVtableTag` constructor go), or the class fold with the slot names. `rename.py function
--to-class` cannot move 0x004EA1A5 into primary slot 1: the canonical `BaseA::UnRegister` takes
`Object *`, the row takes `void *`, and the mode keeps parameters.

## MapUtil.cpp (1,174 B): waypoint-tree rows are another tree's bodies

Blockers: `_Construct<pair<const AsciiString, Coord3D>>` (pin 0x0016CC80),
`__uninitialized_copy<ICoord2D*>` (pin 0x004C3121), `~_Rb_tree_base<pair<const AsciiString,
Coord3D>>` (row 0x0007FAB3, 14 B; the unit's copy is 11 B and first in order) and
`_M_find<AsciiString>` of the MapMetaData map (row 0x001F8437, 78 B; the unit's is 94 B, first).

Retail 0x0016CC80 is a 35-byte copy of four dwords with no call: no AsciiString is copied, so the
pin is on a 16-byte POD element's `_Construct` (rowed as `_Construct<W3DRopeDraw::SegInfo>`). The
rows that need it, `??0_Rb_tree_base` 0x0016D590 and `_M_create_node` 0x0016D760, sit in the
MeshGeometry range and the fresh map approves both for `WW3D2/meshgeometry.cpp`; 0x00181770
(`_M_insert_overflow<ICoord2D>`) is approved for `dx8fvf.cpp`, 0x00620720 and 0x00620E90 for
`BfmeResourceEnumerator.cpp`. This is LINK-682's pattern: rows spelled for this unit's maps whose
bodies belong to other units' trees. Unlike 0x00759460 there, the approved unit does not emit the
body today (the three-int-key map lives in `RvaMapIndexGenP12pod00928690.cpp` and its siblings), so
nothing moved. The 11-byte and 94-byte copies are the unit's /O2 shapes of bodies retail has in
size-optimised form.

## `rename.py class --fold Rva00462151 --into RunOffMapBehavior`: verifies, then costs two units their link

The fold passes the tool (25/25 rows; retail vftable 0x00C4307C), and the bridged
`??_7RunOffMapBehavior@@6B...` slot 0 would resolve through the renamed `??_G` row. Reverted, because
`link_check.py` over the nine units spelling the class then reports
Rva0049B47CThreeVptrDerived.cpp (389 B) and RunOffMapBehaviorCtor.cpp (100 B) out:

- duplicate `??1RunOffMapBehavior@@UAE@XZ`: the constructor unit's view declares no destructor, so
  it emits the implicit one beside the rowed body;
- `??_7RunOffMapBehavior@@6B@` differs: the family file's stand-in view (`PrimaryP`,
  `Rva00462151_B2`) emits a one-slot table under the class's name and comes first in link order.

The fold needs the destructor defined against the real view. The fresh map approves the
constructor 0x0046217B, `??_G` 0x004621F7 and 0x004621AC for `Behavior/RunOffMapBehavior.cpp`, so
this is that TU's merge: one class view, the destructor `{}` beside the constructor, then the fold.
`Rva001505CD -> FXShaderParameterSourceNamespaceSAS` and `Rva006F3990 -> AptSound` pass the same
dry run and were not applied; expect the same two findings.

Of 13 single-identity candidates read from `reverse/vtable_bridge_queue.tsv` (a table whose only
mismatch is an unrowed `??_E` in slot 0 while the unit's own `??_G` equals retail's slot body),
those three pass the dry run; the others refuse on a register key the placeholder scopes
(`Rva0026AF86` -> Squad, `Rva0054F434` -> GameSpyConfig, `Rva0020D9EC`), a second constructor row, a
table shared by two classes, or two views in one unit (BuddyThreadClass).
