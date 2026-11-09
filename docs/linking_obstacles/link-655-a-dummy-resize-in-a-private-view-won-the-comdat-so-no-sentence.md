### LINK-655: a dummy Resize in a private view won the COMDAT, so no sentence ever held text
Status: Repair landed / awaiting verification. Updated: 2026-11-09 (swarm Crash triage lane, P95).

Evidence / affected units: `Render2DSentenceDestructorBFME2.cpp` declared
`VectorClassWide<TextureStatisticsStructWide>::Resize` in its private view with the body `{ return false; }`,
so its object carried a COMDAT of `xor al, al; ret 8`. That object comes first on the link line among the
definers, so the image kept the dummy under the name retail pins at 0x00155490 (345 B). Read from the map and
bytes of diagnostic images 12f2bbf1ef and 1a6707e43c.

`Render2DSentenceClass::SentenceData` grows through it: `Add` 0x00155630 calls the table's slot 2,
`DynamicVectorClassWide::Resize` 0x001566E0, which calls this name. Each `Add` therefore failed. A run-time
dump of `W3DDisplayString`'s sentence at +0x14 during draw (receipt
`2026-11-09T111743Z-boot_smoke-f3512fd74929`, test-only 12f2bbf1ef, base 0x2000000) shows `SentenceData`
with no storage and count 0, `Renderers` the same, and `PendingSurfaces` with capacity 10 and count 0, on
every string the game draws. So the menu's button labels were requested, sized and placed, and never had
anything to render. The byte gate can't see this: every row involved matches, and only a name with no row
binds wrongly.

Repair: the unit declares the specialization without a body, its existing pattern for the same class's
other members. Its object now only references the name (checked by reading its symbols), and the first
definer is `TextureStatisticsVectorWide.cpp`'s explicit instantiation, 345 B, whose instructions match retail's
0x00155490, 116 of 116 by mnemonic and operand apart from relocation fields. `./build.sh` 8/8;
`link_check` LINKS 484 -> 484. Not yet run: the pass test is P95's, a plain image containing this commit
recording `reached-menu` and `menu_check` `matches-retail`.

Remaining: the pin still names a function rowed as `VectorClassBfmeThingFT::Resize`, so the row's byte-verified
copy and the copy the image runs are separate compilations of one body. Renaming the owner is the lasting fix
(LINK-631 covers stacked pin names).

Related lead, not repaired: the kept-copies list reads rows only. The same comparison over pin names finds
196 of 5,261 kept names whose instructions differ from retail at the pinned address; that list is a lead, most
may be benign:
[pins_kept_body_differs_1a6707e43c.tsv](../../reverse/attempt_support/pin-kept-bodies-20261109/pins_kept_body_differs_1a6707e43c.tsv).
