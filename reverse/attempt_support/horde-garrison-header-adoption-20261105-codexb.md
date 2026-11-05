# HordeGarrisonContainModuleData constructor consumers

Inspected revision: `7b7f299237`, 2026-11-05. Worker: `yasinschroeder-codexb`.
Published preview index: `c95fcfcfcd`, 2026-11-05 05:17. This is header-debt
cleanup, not a new link census or new byte coverage.

## Accepted repairs

- `SlaughterHordeContainModuleDataCtor.cpp`: replace the private base with
  `HordeGarrisonContainModuleData.h`. The old view placed only 0xAC bytes in
  the base and a further 0x28 bytes in the derived class. The canonical base
  already occupies 0xD4, so remove that derived padding. The first derived
  float stays at +0xD4, the handle at +0xD8 and the bitset at +0xDC.
- `TunnelContainModuleDataCtor.cpp`: replace private HordeGarrison/OpenContain
  bases and the private 0x58-byte filter view with their existing canonical
  headers. The registered four-byte handle starts at +0x40; its old oversized
  view also covered subsequent base fields. Use the canonical passenger-filter
  member at the same offset. The derived float remains at +0xD4.

Target layout evidence is recorded in the existing canonical headers:
HordeGarrison's factory allocates 0xD4 and constructor stores begin at +0xAC;
OpenContain constructs separate handles at +0x40/+0x44 and the next member
at +0x48. No donor layout or new field identity is inferred here.

Verification:

- `find_declared_unmatched.py` on the selected four units, then the changed
  two units: all defined functions already matched.
- `./build.sh` on both changed units: 7/7 rows match, including three existing
  unwind rows whose compiler labels renumbered. Float and string checks pass.
- After the rejected bit-set trial was restored, the Tunnel rebuild passes
  3/3 rows again, including its unwind row.
- Ordinary paired `link_check.py`: Slaughter LINKS 143 -> 143 bytes; Tunnel
  LINKS 115 -> 115 bytes; combined 258 -> 258. This is the preview's measured
  scope, not a census increase or a full-game link result.
- `header_adopt_lane.py accept --class HordeGarrisonContainModuleData` on both
  changed units passes and retires two queue rows.
- `accept --class OpenContainModuleData` and `accept --class Rva003623E5Member`
  on Tunnel each pass and retire one further row. All four retirements use
  the owning tool; no other debt register is changed.

## Retained blockers

The initial automatic adoption retried the other two selected consumers and
restored them after failure. `ModuleFactoryInit.cpp` still gets C2011 for
ModuleData through its existing include chain. `ContainModuleDeletingDtors.cpp`
still gets C2511 because its non-retail EmitVtableTag constructor is absent
from the canonical HordeGarrison declaration. Their queue rows remain.
The next work is reconciling those include/provider contracts, not repeating
the unchanged automatic swap.

Tunnel also has a queued `Rva00045411BitSet` adoption. The automatic member
mapper refuses its `m_bytes` token as ambiguous with an included DieMuxData
member. A direct include trial establishes a separate compiled blocker:
the canonical `struct` changes the by-value argument's mangling from `V` to
`U`, leaving `rva00362192` unresolved, and its implicit copy constructor plus
constructor exception contract changes stack/copy code. The original view
declares a class and an out-of-line copy constructor. Restore that matching
view, retain its queue row and record the blocked attempt with `re_log.py`.
Next check: prove the canonical bit-set copy/exception contract and reconcile
its class-key/call providers together before attempting this consumer again.

No shared header, pin, alias, ledger row, source path or hatch was added or
removed. Census confirmation of these consumer objects remains pending.
