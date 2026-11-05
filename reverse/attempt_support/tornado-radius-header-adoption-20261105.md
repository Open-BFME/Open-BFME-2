# Tornado radius: canonical RadiusDecalTemplate adoption

Inspected base: `74914d73026366914c809281bb85fd90df3193fd`.
Changed source: `Code/GameEngine/Source/GameClient/Drawable/Update/W3DTornadoDrawRadius.cpp`.

The target's template access at +0x24 is retained through the canonical
`RadiusDecalTemplate::m_unmodelled24` field. The private padded class is
replaced by `GameClient/RadiusDecalTemplate.h`; no header, layout, method
identity, pin, alias or row extent changes. This does not establish a recovered
name for the +0x24 member.

Verification:

- `./build.sh` on the changed source: 3/3 matched; float, string and import
  checks pass. The parent EH graph verifies the renumbered unwind label.
- `find_declared_unmatched.py`: all defined functions already matched, before
  and after editing.
- `header_adopt_lane.py accept --class RadiusDecalTemplate`: PASS; the tool
  retired exactly this source's one header queue row.
- `link_check.py` on the changed source: LINKS, LINKED 239 -> 239 bytes,
  census 2026-11-05 05:17 at c95fcfcfcd. This is a preview, not a new census.

The automatic adopter stopped in STLport's `stl_dec_vms.h` at a trigraph or
continued-comment diagnostic. The explicit source substitution above passed
the normal byte, structural and link acceptance checks.

## Remaining consolidation work

The fresh in-memory TU plan approves the radius donor for the provisional
`Code/GameEngine/Source/GameClient/Drawable/Update/W3DTornadoDraw.cpp` seed.
Its guarded merge dry run accepted no donors: the seed and radius donor have
different definitions of the two list-node allocator deallocation
specializations, producing C2995 in the composite. The dry run also identified
the RadiusDecalTemplate adoption completed here and the differing
W3DTornadoDraw class views. The seed inherits the opaque intermediate
Rva000B19A1; the radius donor uses flat +4/+8 storage.

Next: reconcile the allocator wrappers with byte verification of both units,
then reconcile the class views without changing the destructor/vtable ABI.
The existing canonical DrawModule and vtable-emitter prerequisites in LINK-412
still apply. No allocator or class-view trial is retained in this change, and
no source-file reduction is claimed.
