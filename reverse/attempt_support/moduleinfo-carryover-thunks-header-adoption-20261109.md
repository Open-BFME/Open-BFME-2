# Canonical ModuleInfo in carryover traversal and existing thunks

Inspected at 3a7b59cb3d on 2026-11-09. Rva0037DF8DIterate.cpp and
GapThunksSeat8.cpp replace their private ModuleInfo declarations with the
unchanged canonical header. GapThunksSeat8.cpp also removes its private
StringBase declaration, using the shared declaration brought by that header.

The carryover walk retains the twelve-byte embedded module descriptor. Its
count still divides the byte-pointer difference by twenty explicitly; canonical
Nugget pointers are viewed as byte pointers for this existing expression.
Neither the enclosing carryover view nor its module member is constructed or
destroyed here. The static iteration helper, horde list traversal and template
lookup remain unchanged.

The thunk source retains every existing destructor instantiation, scalar leaf,
string-empty adapter and rowed allocator/iterator binding. Its Nugget destructor
reference now uses the actual canonical Nugget declaration instead of an empty
class carrying only a destructor declaration. No function is renamed, moved or
added, and no shared header, ledger identity/extent, pin, alias declaration,
hatch or compiler flag changes.

Both first private candidates and normal build.sh pass all nineteen existing
rows. There are no EH-bearing rows or string/float/import obligations; private
EH objects are present, and frozen checks pass before/after. Two current-input
previews against index 5b5011469d (2026-11-09 19:12, census 9b9d058303 at17:41)
preserve LINKS271+172=443 bytes. Owning ModuleInfo acceptance retires two header
rows, leaving22 locally and no header queue key in either file. Both sources
have strict reusable receipts, including all17 rows in GapThunksSeat8.cpp.

Before/private and final/normal objects preserve all36 COMDAT payloads/sizes,
every public definition, undefined reference and selection policy. Weak defaults
and /INCLUDE directives are unchanged. Only the thunk object inherits the
canonical AsciiString header's seven existing alias directives; every identical
pair is already in the index. The carryover source already included that header.
No alias is declared, admitted or removed here.

Offsets, operations and verification results are target facts. Existing donor
comments remain distinct; this change imports no donor or original TU claim.
The carryover/horde partial views and unrelated header debts remain separate.
Local evidence: build/thingtemplate-header-cohort-20261109/{moduleinfo-carryover-
sources.json,probe-moduleinfo-carryover.py,moduleinfo-carryover-private-proof.json,
moduleinfo-carryover-private-eh.json,moduleinfo-carryover-build.log,
moduleinfo-carryover-frozen-*.log,moduleinfo-carryover-link.log,
moduleinfo-carryover-accept.log,moduleinfo-carryover-prepare.log,
moduleinfo-carryover-provider-diff.json}. The provider audit uses
prove-moduleinfo-filters.py with argument moduleinfo-carryover. Historical
before/candidate snapshots must not be overwritten.

The current GapThunks receipt gap is cleared only for this source, not the
broader historical GameLogic/query consumer closure. The preceding publication's
broader audit remains INCONCLUSIVE for AICowerState_onEnter.cpp at index
5b5011469d/basec942591408. Carry it into the next census. This scoped cleanup
does not establish new global linking coverage, a real image or runtime result.
