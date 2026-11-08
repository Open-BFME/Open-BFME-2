# LightningDraw constructor table bindings

Root recovery seat, 2026-11-09, base 559a3702ea. The picker served the whole
Rva00561527.cpp file (28-byte transfer wrapper and two hand-written strong
table arrays). The wrapper and its consumer were checked for frozen bodies
before editing; neither has unmatched definitions. The copy-provider file
was checked too, and remains unchanged.

The native 38-byte Rva005EBCC0Object copy constructor at 003AE792 gives
independent zero-addend DIR32 proofs for existing compiler symbols:

| Copy operand | Compiler table suffix | Native RVA |
| --- | --- | --- |
| 003AE7A0 | ModuleInfoHeadBase_3AE7B8 | 0081CD54 |
| 003AE7A7 | ModuleInfoSecondBase_3AE7B8 | 0081CD50 |
| 003AE7AE | bare 6B@ | 0081CD40 |

The two old array names V3Slot0/V3Slot2 are removed. The three live stores
in ModuleCtorChainsA_Rva003ABAF3_Rva003ABB93.cpp now reference the head and
bare compiler symbols at the same native addresses: 003ABB93's +18 store,
and 003ACE5C's +0/+18 stores. The wrapper no longer defines either table
or references their slot bodies. An unused private
FXParticleSystem::LightningDrawModuleInfoBase declaration also disappears;
its only two textual occurrences were its class head and destructor.
The conservative unused-view picker reports no candidate because it skips
namespaced bodies. Direct complete object comparison, rather than a claim
about that picker's coverage, verifies this removal with the array repair.

Every retained code body, relocation position, flag and COMDAT policy in
both changed files is equal after normalizing only the two table referents.
No definition is added. All remaining external data is equal, and the
copy-provider object's complete code/data/external facts are unchanged.
Normal and strict three-source checks pass 23/23 code rows and two owned
data rows. No EH rows occur in this scope. No source path, pin, alias,
function identity, shared header or verifier is changed.

## Deliberately bounded result

The existing compiler tables are only four bytes each. Retail's head and
info tables are 44 and 16 bytes. Before and after cached replay uses the
same two generated compiler-table bridges with the same fifteen slots and
target bindings; only the two strong-definition refusals disappear. The
one changed metadata path in a slot report is normalized from the saved
before-object path to the current path after proving that wrapper's whole
code equal. The third, four-byte second-base table is unchanged.

The replay reads seventeen cached provider objects. Thirteen support units
lack strict current receipts, including held ConstIntGetters4.cpp and
animobj.cpp; they were not compiled or edited. `proof.json` lists every gap.
Thus this is a bounded cached result, not current global provider closure.
The native secondary targets are 003ABABB, 000B3FD0, 003ABBBD and 003ABBC3;
the latter is the this-minus-18 transfer thunk. The compiler view's own G
name has no row/pin, and full class/table recovery is still needed.

The three-source current preview reports LINKS 744 bytes at index
c885072a48 (2026-11-08 19:18). Its displayed 393-byte gain in the constructor
file was already present after the earlier alpha repair, so it is not
credited to this change. A new census and real image must confirm the two
retired names disappear without a new consumer loss. No bridge-retirement,
byte-coverage, full class-layout or game-running gain is claimed.

`proof.json` records native operand bindings, complete object comparisons,
bridge counts and support currency. The raw address index is regenerated
only with tools/data_ledger.py and audited separately in index-audit.json.
The full regeneration changes exactly the two retired-name rows, keeping
their 16/44-byte bounds and every one of 34,433 addresses and 2,354 explicit
owners. Both old strong-definition counts fall from one to zero. The
downloaded index's only users of each old name are the two changed files;
two other source files retain unused extern declarations, and their cached
objects contain neither old symbol (`reference-scope.json`). This still
does not close broad unread-object or directive gaps.

Published as e51aeb84af on the first attempt (36.6 seconds; rebase 3.8,
hook/push 32.8). Required byte/data/DIR32 checks pass, and the object/native
proof passes again after publication. The broader audit remains
INCONCLUSIVE: index c885072a48 versus outgoing base
b7f4e5d3b01df4a507625e0dbc821640d0ec1f7c, because unchanged held
ConstIntGetters4.cpp lacks a current receipt. It was not compiled or edited.
Carry that gap and the remaining short-table debt into the next census and
image; both table addresses have blocked handoffs rather than a claim of
finished class recovery. All six scope/address claims are released.
