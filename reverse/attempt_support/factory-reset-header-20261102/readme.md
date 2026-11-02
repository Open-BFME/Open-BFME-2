# ThingFactory ordinary-method owner: exact storage-view repair

Ready candidate: `candidate.raw.cpp` (14991c44…). It preserves the immutable
09.original.cpp line endings/BOM and matches the privately compiled candidate.
No tracked source/header/ledger/shared object, claim, Git or network changes
were made by this probe.

The candidate selects the registered full-slot SubsystemInterface at the
original direct legacy include position, removes the private ThingFactory
body and includes the unchanged canonical factory header. Existing table
method calls/address uses now view private canonical field14 storage through
the same Rva000427195/Rva00056F61/Rva002CFEA5 receiver declarations. This uses
the native+14 receiver address without asserting the original container type
or any member lifetime. All other declarations, flags, global bindings and
callee exception promises stay the same.

Private original and candidate verification:

- 6/6 native rows match; reset's complete EH graph is EXACT.
- All 7 prior complete external code definitions and 7 data definitions have
  identical raw bytes and symbolic relocations.
- No definition is added, removed or changed. No new ThingFactory/base table,
  implicit destructor or constructor is emitted.

`proof.json` contains the immutable object fingerprints and full definitions;
`raw-candidate-proof.json` authenticates the source candidate. Root should run
normal/strict/link checks and retire the header queue through the owning
acceptance command. This does not establish a constructor/destructor recovery
or authorize changing the shared header's opaque storage.
