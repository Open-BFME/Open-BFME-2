# WWLib prototype base preflight

Served table 007D5090 has sixteen native slots. Its current Rva00180EA0
producer inherits canonical Rva0061ED80, whose sole virtual destructor places
the deleting destructor in slot 0. Native slot 0 is the six-byte name getter
00180E60; the deleting destructor 00180E80 actually belongs in slot 9.
The unchanged served source passes all 9/9 code rows.

GenBase009EB7D0.h already documents the measured fifteen-slot parent, including
its destructor at slot 9 and size 14h. Its destructor declaration currently
resolves to a five-byte derived destructor at 00135E35, while this source's
eleven-byte destructor must call the actual base body 0061ED80. The two are
not interchangeable byte-exact callees. LINK-354 also records the canonical
base's four missing slot providers. No private replacement base or new alias
is introduced, and no source, header or ledger edit is retained.

The constructor sibling and factory producer describe the same table with
different incomplete class views. Repair needs a coordinated base identity
and provider reconciliation before draining the derived slots. The tombstone
register is claimed by another contributor at this check, so symbol ownership
migrations are deferred. The table/file/class scopes are released. The next
real-link bridge pass test remains open.
