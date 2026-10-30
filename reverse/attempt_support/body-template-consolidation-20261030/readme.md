# Living World body-template partial map views

The two existing level lookups expose different parts of one class: hitpoints
uses the map at +0, regeneration the map at +0x0C. Preserve the seed's existing
`m_map` name and add the neutral offset label `m_map0C`. Both views now declare
the same two maps; only the donor's field references select the second map.
This establishes the two accessed fields, not the complete original class.
Existing operation names and their earlier WorldBuilder evidence are unchanged.

Ordinary strict preparation verifies the complete 55- and 58-byte bodies with
every call resolved and no masking. Both preview LINKS against the published
`ccafe54d1d` index, retaining 113 authored bytes. Frozen-definition checks pass.
[The actual source/object proof](view-proof.json) records exact code extents,
native bytes, symbolic relocations and native disassembly. The matching bodies
keep the original map subobject addresses and lookup/decrement operations.

The supported planner at `build/consolidation/body-template-20261030` was rebuilt
with the current decoder and verified reference. Its file packets have no
original-path evidence or alternatives; the seed flags its existing hatch
register ownership. A fresh supported TU plan separately approves both rows
under the existing provisional N destination LivingWorldAutoResolveBodyTemplate.cpp:
two rows/two sources, no mixed or refused donor. This grants grouping under
current routing and does not prove an original filename.

No row, pin, header, data definition or hatch is added. The seed keeps its two
existing address-global occurrences; no donor register key needs transfer.
Bank the declaration prerequisite separately, refresh the planner, then use the
supported merge/dry-run workflow and audit all affected path consumers before
publishing a source move. The identical imported-inline comparator specialization
must remain visible without creating an extra external provider.
