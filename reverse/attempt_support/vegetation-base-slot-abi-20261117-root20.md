# Vegetation base: supported ABI and alias-family recovery required

Inspected2026-11-17 at9dcb0c7478c. The served Rva000E6AC0 table7CEAB4
has six retail slots `[E6D78, pure, E6B93, E63DC, pure, B3FD0]`; its current
source emits four slots. The native words were reread from the retail image.
Slot1 remains pure. The matched binder caller supports neutral `bool slot04()`
(nonconst/noargs), not an original semantic name. Slot5 is empty in the base;
a derived enable setter is a separate body and not a source-name proof.

The six-byte getter atE6B93 returns the unique class literal
`W3DVegetationBufferBase`. The transfer atE63DC is already rowed as a42-byte
free `__stdcall` function taking `Rva000E63DCObj *`; its argument is Xfer-like,
not the vegetation receiver. Existing typed callers pass their Xfer pointer.
This is an ABI/type ownership problem, not missing executable coverage.

Owning `rename.py function --to-class Rva000E6AC0 --new xfer --dry-run` refuses
the free function as unsupported. A correct future path must prove the incoming
receiver is unused, preserve stack cleanup and argument meaning, and byte-check
all rewritten direct callers and real table installers together. No wrapper,
second body row, hand ledger rename or alias was introduced.

The retail class-identity fold dry run also refuses because table slot0 still
names the Rva000E6C6F deleting-destructor alias. Folding that placeholder into
Rva000E6AC0 with the owning class-fold route refuses the two existing deleting
rows at the same RVA E6D78. This mode does not merge such alias pairs. The old
complete-dtor pin and linker alias remain. Fresh claims show symbols.csv and
hatch_counts.json held by another worker, so no pin/hatch retirement was attempted.
These are closed unsupported boundaries, not clearance to bypass the checks.

Controls remain **66/66 rows across three sources, plus1data row**, and the
constructor/destructor have **2/2 EXACT EH graphs** with no baseline debt.
All sources equal their unchanged forms; every plan was a dry run. The private
W3DShrubBuffer header is explicitly a storage projection with an existing vptr
word: adding virtuals there without reconciling that layout would grow it.
No source, class name, ABI, header, pin, table or queue change was admitted.

Next: implement a general byte/caller-bound free-stdcall to virtual-member
signature recovery path in a separate verifier change; reconcile the existing
opaque/native deleting family and its active pin through a supported retirement
path when ledger claims permit it. Then recover all six base slots and the
actual derived hierarchy, preserving all rows and EH, and await scheduled real
bridge absence. Do not infer successful runtime or a working image.

[Native table, current symbols, exact refusals and control hashes](vegetation-base-slot-abi-20261117-root20.json).
