# W3DPropDraw Snapshot provider repair

Remove the TU-local macro that renamed Snapshot to BfmeModuleDataSnapshotBase.
That spelling already belongs to a different native post-effect base: its
13-byte constructor at 0x0011646E installs table 0x00BCFB24 and clears +4.
The copied Snapshot constructor only installs its own table and occupies nine
bytes. Emitting it under the post-effect symbol selected non-retail code and
blocked both the real base owner and LookupTablePostEffect's 22-byte constructor
at 0x00111B84. The original static identity of the opaque post-effect base is
not recovered here; its current owner is retained unchanged.

Use the registered Snapshot header's real identity. Its native constructor is
already rowed at 0x000053A6, with the canonical table at 0x007BB554. No new
class, symbol, alias, pin, row or shared-header change is introduced.

Private before/trial compiles pass all seven W3DPropDraw rows and EXACT parent
EH. All 64 external code/data definitions and their relocation edges are
identical after normalizing only the corrected base spelling. The production
object reproduces that trial. Three lifetime definitions lose the wrong name
and gain their canonical Snapshot names; three retained methods change only
their symbolic Snapshot-table relocation. The native row bytes stay identical.

Strict supported preparation verifies 17 rows and one data row across five
sources: W3DPropDraw, the post-effect base constructor, LookupTablePostEffect's
constructor, Snapshot.cpp and LivingWorldRegionConnectionCopy.cpp. The normal
W3DPropDraw build also passes all seven rows and data/ref checks.

Against published index ccafe54d1d, the ordinary five-unit preview changes
154 -> 189 authored linking bytes. The two post-effect constructors newly
preview LINKS (13 + 22 bytes); both Snapshot witnesses retain LINKS (32 + 122).
W3DPropDraw remains blocked by its DrawModule table and deleting-destructor
context. This is a bounded preview, not a census or whole-image link result.
The remaining LINK-102/107 native table prerequisites remain open.

Publication follow-up: the accepted batch's wider link audit is INCONCLUSIVE
on the older index and missing current 0CreateAHeroManager21FE49.cpp consumer
receipt. The code-identity check reports ModuleData's retargeted destructor as
a divergent shadow definition. Its raw code is unchanged; the only relocation
change replaces the false table spelling with canonical Snapshot, and the
owned native destructor row remains exact. No baseline was expanded or retired.
The wider consumer/selected-provider checks remain scheduled-census work.
