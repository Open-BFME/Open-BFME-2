# BoneFX constructor cleanup native owner

Repoint only78C1DD/8 from gen_small/uw_gen_011.cpp to the already-emitted
compiler label in BoneFXUpdate.cpp, its approved parent TU. The original
generated source is untouched; its orphan harness body receives no row credit.

Retail FuncInfo93B80C and handler78C220 bind the exact307B constructor4878E6
to its four cleanup states. The EXACT parent graph places current$L55436 at
78C1DD. The whole parent and cleanup resolve unmasked, with no unresolved
reference. The cleanup is8b4df0e9b2e5abff and its only in-row relocation,REL32+4,
calls the existing virtual UpdateModule destructor at24A797. Seven later
relocations belong to other bodies in the same compiler section, not this row.

The earlier attempt in re_attempts.log was blocked by the old nonvirtual QAE
destructor spelling. The current native view supplies the existing UAE owner;
no new pin, alias, wrapper, generated code edit or manual row move is needed.
add_match --replace-rva verifies the new compiler-local row normally. Existing
parent rows and all other generated rows remain credited to their owners.

Ownership/path audit: both source paths remain. Only the core ledger source
and compiler-local identity change; the approved P-group assignment remains
BoneFXUpdate.cpp. No TU map assignment is regenerated or inferred from adjacency.
The orphan generated name has no active tool dependency. No protected debt,
data/header owner, fold-proof source or shared declaration is removed. Existing
census snapshots and historical attempt references are retained.

This repairs placeholder ownership with coverage preserved. It adds no unique
authored bytes and is not a real-link/runtime result. Publication audit carried
frombe0fa3bd1a was INCONCLUSIVE: index7bd55416c6 versus outgoing base
4b2bb61eb1d758e3485accbb5d78a98f7f9c44dc,2 missing current receipts, first the
Assisted module-data factory. Current-consumer/image confirmation remains open.
