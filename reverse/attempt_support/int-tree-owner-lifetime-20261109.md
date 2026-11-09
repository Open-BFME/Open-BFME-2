# Rva00072FE6 owning tree member

Inspected6856b21969. The canonical12B tree now stores its header pointer in
the shared4B owning holder. Count+4 and opaque+8 are unchanged. The destructor
provider includes that header instead of its private eight-byte view.

Ten existing pointer expressions use explicit node casts: six in the System
clear provider, two in W3DShroud's range erase, and two in SpawnArmy's visitor.
Repeated reads remain repeated, including the visitor's sentinel comparison
after virtual calls. Full-file review found no missed consumer or new direct
holder lifetime. No constructor, copy operation, STL specialization, COMDAT
control, pointer payload identity or original container name is added.

Normal verification over the staged header graph passes944/944 bodies across
22 sources,17 data rows,171 string references,137 floats,40 imports and199
EXACT EH graphs. Frozen-file checks pass. The canonical contract is refreshed
through class_contract.decide with one exact-declaration compiler probe:
class/sizeof12, holder+0, count+4, no undecided attribute. Those view counts
describe the probe, not original retail translation units.

link_check reports21/22 LINKS. W3DShroud.cpp already differs from the index's
first `??_7Rva00072FE1@@6B@` copy: the unchanged source and HEAD header reproduce
the same `comdat ... (first)` verdict through the supported private LinkGuard.
Its complete8B table metadata, section flags, pointer targets, weak default and
raw bytes are identical before/after. This change introduces no such conflict.
The index's2030B difference is not a loss caused by the header repair. The
pre-existing table-selection gap and actual next-image selection remain open.

Owning acceptance retires the destructor provider's one header queue row.
PlayerTemplate.cpp still needs its inherited set constructor and operations;
that separate row remains. One other provider class remains queued in
RvaTreeDtorFamily.cpp after this repair.

Scratch receipts: build/int-tree-owner-lifetime-20261109/, including the full
cohort, private before/after Shroud objects and shroud-baseline-proof.json.
The ordinary object CLI correctly refuses that private old object as not
current; the baseline comparison uses LinkGuard's explicit candidate-object
interface, without altering Code, the index or any verifier.

Publication carry-forward: vector-owner packageb5680524db landed on attempt1.
Its broader audit was INCONCLUSIVE for unchanged AIBuildable.cpp's missing
receipt (index138c18d3c9, basebb93d5e0c6). Its own23-source preview passed.
No image or runtime clearance is claimed by either package.
