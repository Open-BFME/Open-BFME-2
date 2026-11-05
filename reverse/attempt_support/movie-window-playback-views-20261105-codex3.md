# MovieWindowPlayback private-view reconciliation

Inspected base: `129b9824c7`. Scope: `Code/GameEngine/Source/Common/MovieWindowPlayback.cpp`
and `MovieWindowPlayback_draw.cpp`. Model: GPT-6 Codex.

Target facts: the existing matched draw row at RVA 0x00524973 reads the movie
pointer at +0x0C, rectangle dwords at +0x10..+0x1C, flags at +0x24 and colour at
+0x28. Its ledger already records virtual decoration. The seed's matched clear,
timestamp and progress bodies use the same pointer, flags and timing offsets.
The constructor source separately establishes callback storage at +0x34/+0x38.
No donor name, complete virtual interface or original BFME source path is inferred.

Change: give the seed and draw file the same partial class declaration. The
implicit vfptr plus eight padding bytes replaces twelve padding bytes in the
seed. Expose the rectangle fields already used by draw, keep the seed's pointer
view, and cast that pointer to draw's existing dispatch view at its uses. No
constructor is added and neither changed object emits this class's vtable.

Checks: `./build.sh` on both sources passed 10/10 function rows and 7/7 data
rows; declared-unmatched passed. `tools/link_check.py` against index census
2026-11-05 05:17 at c95fcfcfcd reports both LINKS, preserving 354 + 186 bytes.
The seed's unreferenced 3-byte TreeHint default constructor diagnostic is
nonblocking and unchanged in scope. These are local previews, not a new census.

The initial supported merge probe accepted no fragments: draw lacked its method
and fields in the selected seed view; the explicit-vptr constructor conflicted
with the polymorphic view and Rva00524BB4 vtable declaration; the destructor
fragment failed compilation; update failed byte comparison. The layout planner
also reports a callback-holder identity conflict between TreeHintRef00217D4C
and Rva00524BB4Ref. The present change addresses only the seed/draw view.

After reconciliation the supported merge dry run accepts the seed and draw
fragment (10 rows), with the same compiler flags as the seed. The remaining
three fragments still fail: constructor and destructor compile, update bytes.
The saved verified composition can now remove one source file through
`tu_skeleton.py --merge`; no map regeneration or manual file move is needed.
