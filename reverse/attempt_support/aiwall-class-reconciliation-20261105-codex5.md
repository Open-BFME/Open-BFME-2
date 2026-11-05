# AIWall class reconciliation, 2026-11-05

Inspected base: b4e237084b. This follows the blocked merge documented in
[the 2026-11-03 handoff](aiwall-consolidation-prerequisites-20261103/README.md).

Target facts: constructor 0x004EB583 installs VA 0x00C62928; slot 0 reaches
wrapper 0x004EB778 and destructor 0x004EB5E9. `rename.py class --fold` verifies
that these are one class. This establishes identity, not its original name.
The destructor's pointer loops establish pointer elements at +8/+0x1C. The
third vector keeps its compatible BfmeE16 view; its original element type is
still unknown.

Applied the supported `rename.run_batch(..., source_edits=...)` transaction:

- Folded Rva004EB583 into Rva004EB5E9, with the tool's constructor-row
  respelling and tombstone.
- Aligned the constructor's two pointer-vector members with the destructor's
  view and declared the public virtual destructor out of line. Removed the
  donor's empty inline destructor and its BfmeE16 destructor specialization.
- Removed AIWallBuilder.cpp's fake novtable forwarding subclass. Its heap and
  stack walls now use the same class directly. AIWall.cpp declares the matching
  constructor for subsequent composition.

Verification: `./build.sh` on AIWall.cpp, AIWallBuilder.cpp and
Rva004EB583Ctor.cpp passes 56/56 code rows, four data rows, 17 funclet bindings
and two folded STLport constructors. Declared-unmatched checks pass for all
three. `check_csv.py` passes. `link_check.py --new-variants` passes. Ordinary
current-object previews against census index c95fcfcfcd (2026-11-05 05:17)
preserve LINKS for all three: 3,689 + 1,722 + 102 = 5,513 bytes. These are
previews, not a new census or real-link measurement.

No pin, alternatename, register retirement, shared header or TU map change.
The data ledger's old placeholder vtable name is historical cached metadata;
the class-fold tool reports it, while the installing current object binds the
unified name. No whole-register regeneration is included. Next step: the
supported AIWall.cpp merge, then its full consolidation/path-consumer audit.
