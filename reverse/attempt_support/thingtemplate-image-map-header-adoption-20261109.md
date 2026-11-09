# ThingTemplate image and locomotor consumers

Inspected at 592396ae2c on 2026-11-09. Three complete source files replace
their private ThingTemplate declarations with the existing canonical header.
The shared header and every ledger identity/extent remain unchanged.

The button and portrait resolvers keep AsciiString members +0x78/+0x74 and
their respective pointer storage +0x48C/+0x488. The canonical layout still
spells the latter as opaque four-byte unsigned words; explicit pointer views
preserve their existing reads/writes without binding another global or giving
those words a new class-wide name. The portrait path retains its measured
debug-call order and existing string-selection helper. Its +0x64 name uses
the canonical m_nameString member.

The locomotor store views the canonical twelve bytes +0x3AC as its existing
BfmeLocomotorSetMap. Its two subscript calls, clear/push sequence, template
identities and declaration-only provider bindings remain. No container lifetime,
vtable, alias, pin, hatch or compiler flag is introduced.

These offsets, native bodies and existing member operations are target facts.
Earlier donor commentary stays with the sources; this change imports no donor
and does not establish an original TU, additional layout or original member
spellings. The array/scalar views remain visible cleanup prerequisites.

Private checks and normal build.sh pass all three native rows (305 ledger
bytes), two literals and one empty-string reference; there are no float/import
obligations or EH-bearing rows, and no missing private EH object. Frozen checks
pass before/after. Current-input link_check against index 138c18d3c9 at
2026-11-09 16:08 reports all three LINKS: 55+59+189 = 303 -> 303 linked bytes.
These linked byte counts exclude the two row-tail padding bytes; they are not
new coverage. Owning acceptance retires three header rows, leaving 75 queued
ThingTemplate consumers in this checkout. Strict receipts are prepared for
all three changed providers.

Evidence is under build/thingtemplate-header-cohort-20261109/: probe-image-map.py,
image-map-private-proof.json, image-map-private-eh.json, image-map-build.log,
image-map-link.log, image-map-accept.log and image-map-prepare.log. Historical
before/candidate snapshots must not be overwritten. Other ThingTemplate
consumer/lifetime blockers remain, including the static field-table access
described in the preceding common-member packet and LINK-582's W3D cases.

The preceding publication's broad audit is INCONCLUSIVE for unchanged
GapBodiesGE26.cpp at index138c18d3c9/base26b34a803f. Carry this receipt gap into
the next census. This scoped source cleanup establishes neither global provider
selection nor a real image/runtime result.
