# Callback table with incorrect virtual destructors

Fresh native read confirms base table81C780 has one purecall, and derived
7E6BA4 has one callback at5D124D. Adjacent7E6BA8 is a separate two-word
holder table, not another derived slot. Constructor2215D5 installs7E6BA4
and stores its owner at+8; destructor2215F4 installs it and tails2214A6.
Caller221635 allocates12 bytes. None of this establishes original class names.

Current source installs deleting destructors in those slots. It still passes
the ordinary build:12/12 rows349B, including both emitted unwind rows. The
existing LINK514 base-table deferral is therefore still structurally valid.
Fresh helper calls show the next action requires supported tooling: rename
has no virtual-to-nonvirtual mode; generic member selection rejects special
members and signature-only respell independently refuses U-to-Q changes.

The real28-byte scalar deleting helper2215FF is admitted and must remain
emitted. Correcting the table removes its current virtual-slot emission;
no legitimate existing delete-expression emitter was found. The holder clear
at22161B explicitly calls the destructor and then operator delete. Do not
invent an emission anchor or delete the admitted row.

Callback5D124D already has an original Rva005D124D owner and an admitted
Rva0010F7EE alias used by unrelated table7CFAB0. Ordinary to-class moves refuse
that shared ownership. An additional callback name needs supported ICF
admission, not class identity inferred from the common8-byte forwarding body.

No source, ledger, pin, alias or tooling edit was made. Independent review
confirmed native extents and current rename refusals. Next: add a reviewed
nonvirtual-destructor correction route with positive native proof, preserve
all existing emitted rows, and resolve folded callback ownership before
attempting the coherent class/table repair.
