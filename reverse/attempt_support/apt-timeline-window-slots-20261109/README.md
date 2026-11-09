# Timeline draw and tooltip overrides, 2026-11-09

Native table 0x008675DC belongs to the timeline constructor at 0x005202C8
and destructor at 0x005204EF. Its slot3 points to 0x000A12F8 and slot4 to
0x00444680. Both are six-byte return-one bodies with no relocations. The
current Rva005202C8 view inherited different GameWindow implementations.

Two actual overrides now express the canonical GameWindow draw/tooltip
contracts on the existing neutral receiver. Each is admitted through
add_match.py --icf-owner against its exact existing owner, with fold-proof
source notes and no new pin. These are twelve emitted bytes and zero
unique native bytes; original method or class names are not recovered.

All pre-existing code/helper bodies, relocations, flags and COMDAT policies
are unchanged. All pre-existing definitions remain, and only the two
verified methods are added. The primary table keeps its 44-byte extent;
only the two slot referents change. All other data remains equal. Native
table words independently confirm both addresses. No header, path, flag,
existing provider or hatch changes.

Normal verification passes 138 code rows plus one data row, 65 literals
and one empty reference, fourteen float literals and four named imports.
All fourteen EH graphs are EXACT; the seventy existing funclet bindings
remain verified through their parents despite label renumbering. Frozen
and new-variant checks pass. The unit predicts LINKS 10,032 to 10,044 bytes
against index 717b70f4ab; this is scoped prediction and duplicate ICF
ownership, not new unique coverage or a measured game-link gain.

The native table has fourteen slots (56 bytes). Other inherited mismatches
and the three missing tail slots remain; no bridge retirement is claimed.
Input and factory-return targets were held by other workers and are not
modified. Unique existing methods at 51FCA2 and 51E4B0 belong to separate
views of this same object. Completing the class needs their supported
owner reconciliation and consistent lifetime/container views, rather
than duplicating nontrivial bodies. LINK-002's eighty-byte element family
and the existing timeline reconciliation handoffs retain that wider scope.
The old constructor view owns vector<Rva00520211Element> and vector<int>;
the operational AptTimeLine view uses vector<AptTimeLinePlayer> and
vector<float>. Their byte layouts alone do not prove original type identity.

The downloaded index and broad outgoing audit remain separate from these
current-object checks. The newest real image must confirm selection and
the rest of the source class still needs recovery. No global provider,
image, menu, skirmish or runtime clearance follows from this partial pass.
