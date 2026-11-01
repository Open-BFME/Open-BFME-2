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
Its separate scaffold recovery follows only after this prerequisite commit.
The other cleanup at 78E44F (8 bytes) is placed by the same graph but still
references an unresolved SpecialAbilityUpdateModuleData destructor spelling;
the native target 44ECCE already has a different existing owner. It remains
generated until that ownership is reconciled, with no added pin or alias.

The preceding header-cleanup publication's consumer audit was inconclusive:
its index predates its outgoing base and its seed strict receipt was missing.
The present three-source strict check refreshes that receipt, without claiming
to clear the historical audit or advance the census.
