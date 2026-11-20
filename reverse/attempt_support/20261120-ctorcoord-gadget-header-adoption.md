# CtorCoord shared-header adoption in five gadget units

Base: 136ee37e6f6e0742135060bab7d9d2d8a5f9d331. Served native queue item:
CtorCoord in W3DCheckBox, W3DHorizontalSlider, W3DProgressBar, W3DRadioButton
and W3DVerticalSlider under the W3DDevice GUI/Gadget source directory.

Each unit's old CtorCoord definition was the same empty-constructor struct
derived from ICoord2D. The existing canonical CtorCoord and ICoord2D headers
describe the same eight-byte, nonvirtual layout, with int x/y at offsets 0/4.
The Zero Hour BaseType header already defined its own coordinate type,
causing C2011 on ordinary adoption. Load that donor header once under a
TU-local BfmeDonorICoord2D spelling, then include the real target coordinate
header. The canonical target headers remain active and unchanged.

The native adopter then replaces all five private CtorCoord definitions.
Fresh private CodeView comparisons preserve the complete inspected CtorCoord
and ICoord2D contracts in every unit; external provider byte/relocation graphs
are unchanged (39/54/44/47/33 definitions, respectively). Native ordinary
build verifies all 32 existing rows, six strings and 15 compiler float literals.
Native declared-unmatched checks before editing found every definition rowed.

After a native index refresh to the current base (5,903 objects reread),
header_adopt_lane.py accept returns PASS for all five units and removes only
their five CtorCoord header-queue entries. Its acceptance includes byte and
linked-coverage preservation checks. This is one completed served item,
five removed maintenance entries, zero new recovered code bytes and no
full-image link or runtime result.

Private source hashes, CodeView/provider inventories and reproduction are
retained in diagnostics/continue-20261120-body-recovery-1656/agents/thing/:
ctorcoord-evidence.json, ctorcoord-private.json and ctorcoord-handoff.md.
