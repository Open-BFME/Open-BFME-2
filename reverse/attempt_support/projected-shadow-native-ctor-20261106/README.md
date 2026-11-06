# Compiler-owned projected-shadow constructor and base lifetime

After the supported owner fold, the native25-byte constructor can use C++'s
automatic table store instead of an extern __identifier table declaration and
explicit write through this. Its view declares the existing virtual destructor
out of line, so it does not instantiate a different base destructor chain.
The compiler's new owner table and28-byte deleting destructor are byte/relocation
twins of the seed's existing providers, with identical COMDAT/storage policy.
No new slot, symbol pin, alias, inline wrapper or target name is introduced.

The seed's padding-only Rva007AFF00Base class and unused destructor definition
are removed. Rva007AFF00Owner derives from its already rowed constructor base
Rva000F0F2B. Its existing implicit inline reset retains the exact86-byte owner
destructor and parent EH, while three unused old-base providers disappear.
A tracked-tree search found no other source/header spelling that old base.
The constructor's flat0x68-byte base declaration is a storage/ABI projection,
not proof that this is retail's complete class definition or virtual interface.

Private verification retains59 seed rows, all nine seed parent EH records and
the25-byte constructor. The normal build passes60/60 rows over both sources,
one data row, string/float references and eight renumbered funclet locations.
The old base's one present-unmatched marker is genuinely unnecessary and is
removed; hatch_counters --update owns the corresponding baseline decrease.

The previous full-view trial emitted a different base deleting-destructor
implementation despite matching constructor bytes. It was never applied.
The present trial avoids that emission by declaring the existing owner/base
destructors explicitly rather than allowing a new implicit owner destructor.
The new owner providers are compared directly with the verified seed, not
accepted merely because the constructor row matches.

No combined-object merge guard is claimed by this two-object prerequisite
proof. Publication fc7590d725's audit was INCONCLUSIVE: index7bd55416c6 versus
outgoing base7523f06674513d785f41dd50cc0af713ce5edd26, three objects without
current receipts, first AIStatBase.cpp. Carry these units into the next census.
The native owner's table still needs all three justified slots; the existing
one-slot compiler table is retained here. This cleanup is not real-image,
menu, skirmish, save/load or CRC clearance.
