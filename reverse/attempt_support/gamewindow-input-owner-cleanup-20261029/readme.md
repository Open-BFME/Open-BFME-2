# GameWindow input callback: one existing owner, two consumers

Native facts: GameWindow table C0BBCC slot1 and gadget tables BC8D04 /
BC8D30 slot1 all select RVA A0CFF. The complete35-byte guarded callback
reads+1E0 and passes the window plus three message words. The ledger had
two matched claims for that same range: BfmeThingEHCa::bfmeGoEHCa in
BfmeConv812_bfmeGoEHC.cpp and the existing GameWindow::input in
W3DGadgetWindowDrawSlots.cpp. The old donor's masked placement did not
establish a separate BFME2 identity. This is an over-claim, not a new ICF
alias or missing function.

Remove only the duplicate helper and its row, tombstone that row, and bind
both explicit gadget-table consumers to the already rowed GameWindow input
member. Its existing name and provider remain unchanged. The system callback
stays in its present source. No pin, alias, compiler flag, generated source,
source path or shared header is added or changed.

Control:158/158 rows,2 data rows. After:157/157 rows,2 data rows across6
sources, all frozen checks clean,6/6 ordinary previews LINKS against index
840db2d676. The cohort includes the current getter providers published in
85f6b7f40c; the index predates their symbols. An initial four-source preview
omitted those providers and was unresolved; its failed output is preserved.
The explicit current six-source control and after-preview both link.

Authored per-source totals fall2394->2359 because one duplicate35B row is
removed. The unique covered range A0CFF..A0D22 remains unchanged through
GameWindow::input. This is zero new unique matched bytes and no measured
census-linked-byte gain; do not sum per-source over-claims as real coverage.

Preceding batch landed on2026-10-29:
679567389df0281e4e702bce1465873dce32e380 font ABI/11-slot width;
d28ce94082614f8544249590b74b0bf2ec8daa4e header evidence;
84dc1f46b9c3fc254d1b4b2d77d9e79007d26085 system slot2;
85f6b7f40cd3c1ce528d1f89787664346d95c4a1 predicate slots6/8/9.
Their normal broad gate passes5585/5585 rows across292 sources,122 data
rows,730 EXACT EH graphs and1337 DIR32 symbols. The final push passes
741/741 across79 sources,44 data rows,61 EXACT EH graphs and251 DIR32
symbols. No removed-name consumers remain in the20920-source scan.

Whole-batch linking remains UNVERIFIED: the newer index has consumer
metadata, but67 affected objects lack current receipts, first
GameEngine_GameEngine_createFileSystem.cpp. Carry that header/provider
scope into the next scheduled census. Source byte verification alone does
not clear those consumers or prove executable placement.

Slot10 still incorrectly uses purecall in the two GameWindow table emitters;
retail selects the heavily shared3B constant at0050B5C6. Its47-file scope
includes TextureAssetGet.cpp held by another seat when checked2026-10-29,
so no source trial or broad claim was taken. Slot7 is genuinely pure. Original
method names and complete object layout remain open. No smoke/full cycle
was run. Model GPT-6; t=5; lane=R; budget=30m.
