# RousingSpeechUpdate module-data vector identity

The native ModifierName entry in BfmeRousingSpeechUpdateFields uses
INI::parseAsciiStringVectorAppend at offset E4. The existing module-data
destructor and trigger independently use vector<AsciiString> there. This
target evidence establishes the element type; no donor layout is claimed.

The constructor now uses that type instead of BfmeE16. Its three rows pass
normal verification, and the constructor, seed and trigger pass 31 strict
rows. All nine external code definitions retain their complete raw bytes;
symbolic relocations are identical after substituting the established element
type in the seven STL helper identities. No helper is otherwise added or lost.
The complete constructor EH graph is EXACT.

The six-source cohort, including the native field-table provider, predicts
LINKS 3,364 -> 3,364 bytes against index 86db074988. This is scoped evidence,
not a census improvement. Constructor/base views and the other donor conflicts
still prevent the supported TU merge. No path move is made.

The proven parent graph places a string-vector cleanup at 78E457 (14 bytes).
A trial repoint to the compiler-local cleanup emitted by the real constructor
passes all four strict rows: all 14 resolved bytes match without masking or
unresolved references, and the following handler proves the exact body extent.
The ownership audit nevertheless identifies the approved retail TU as
RousingSpeechUpdate.cpp, rather than the current constructor donor. The trial
is reverted before publication. The generated row remains the sole owner;
this evidence does not count as source recovery. The parent and cleanup must
join the approved TU together through the supported merge.
The other cleanup at 78E44F (8 bytes) is placed by the same graph but still
references an unresolved SpecialAbilityUpdateModuleData destructor spelling;
the native target 44ECCE already has a different existing owner. It remains
generated until that ownership is reconciled, with no added pin or alias.

The preceding header-cleanup publication's consumer audit was inconclusive:
its index predates its outgoing base and its seed strict receipt was missing.
The present three-source strict check refreshes that receipt, without claiming
to clear the historical audit or advance the census.

The outgoing batch has no source-file moves or ledger-path repoints. A combined search of active
tools, hooks, workflows and includes finds no consumer of the old cleanup
name or the constructor source basename. No path consumer requires an update.
No register or pin is hand-admitted. This audit covers the constructor
prerequisite and its reverted cleanup trial, based on 3079f4acd4.

## Filter member and remaining base fold

The constructor's +F4 filter member now uses Rva00360D26Member, matching the
seed. ObjectFilter.cpp already owns its folded 82-byte constructor at 3623E5,
and ObjectFilterRelease.cpp owns its eight-byte destructor at 360D26. This
reuses existing identities and adds no alias or pin. All nine external code
definitions retain their raw bytes and symbolic relocations after substituting
the existing member-owner name. The parent EH graph remains EXACT. The
constructor and both providers pass 41 strict rows; the four-source preview
retains 4,783 linking bytes. The unreferenced AsciiString::str relocation
diagnostic in ObjectFilter.cpp is unchanged.

The supported class fold from Rva0044ECCE into SpecialAbilityUpdateModuleData
has a unique native C3F2A8 vtable proof. Its three row renames would reconcile
the base destructor without a second pin, but five of its twenty source files
are held by other contributors. The applying tool refuses before edits; its
plan and refusal are retained. Complete that atomic fold when its full scope
can be claimed. The constructor/destructor novtable difference remains a
separate code-generation prerequisite, not an approved merge.

The last publication's AIBaseBuilder consumer receipt has now been refreshed:
27 rows pass strict checks. This does not retroactively clear the prior audit.
