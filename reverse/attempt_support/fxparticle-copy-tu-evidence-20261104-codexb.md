# FXParticle copy-constructor TU evidence: no anchor (2026-11-04)

Inspected revision: 072392c730. Picker scope: 0x003AE0D5..0x003AE358,
12 rows in 11 files. This is cleanup of existing matched bodies, not lost rows.
No source, ledger placement, symbol or baseline was changed.

Target facts: tu_evidence --source on Rva003AE0D5CopyCtor.cpp emits its CSV
header and no signal. Current tu_map rows for copy 0x003AE0D5, clone 0x003AE18A
and destructor 0x003AE358 have no TU. find_declared_unmatched reports all
Rva003AE0D5CopyCtor.cpp definitions matched. The constructor/copy link for
Rva003AE0D5 is already documented by the matched 0x0056413D constructor;
it identifies a LifeEvent family layout, not a retail source path.

WorldBuilder leads: none for 0x003AE0D5/18A/1A7/1CD/2A9/2CF/358.
The 0x0055F840 lead is UNROWED with score 1 (alignment), not a name or path.
worldbuilder_source_paths.csv contains an editor fxpsmodulecategory.cpp path
whose game_path_present field is no. That editor path does not anchor this run.

Donor facts: the pinned BFME1 source includes
LifeEventModuleTemplateCopyCtorThunk.cpp and DefaultModule2CtorThunk.cpp.
Their hand-reconstructed family/type spellings offer structural leads; neither
is an original-path anchor for the BFME2 rows. No donor name is promoted here.
The supported consolidation planner likewise leaves Rva003AE0D5CopyCtor.cpp
without an original-path investigation group.

Next useful evidence is a target self-asserting path/name or a stronger
WorldBuilder name-and-path pairing for the factory/constructor family.
Without it, moving the run to FXParticleSystem.cpp or fxpsmodulecategory.cpp
would assert an unsupported TU. Leave the rows in their current sources.
