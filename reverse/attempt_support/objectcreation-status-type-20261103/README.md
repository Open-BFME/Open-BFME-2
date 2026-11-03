# ObjectCreationUpgrade status type before Xfer composition

The existing status field at+0x28 is unsigned in the current Xfer donor, whose
native call uses the unsigned Xfer slot+0x78. Keep that existing target binding
when reconciling the two class views: change only the seed's int m_status28
to unsigned int. Its current uses assign the same positive constant; every
one of19 rows and all29 external definitions/ordinary relocations remain
identical in the private control proof. Normal nineteen-row/data verification
also passes. No name, row, pin, class extent or source path changes.

The earlier all-donor tu_views trial was restored after a missing ModuleData
forward declaration in a borrowed helper; that compile refusal is separate.
This prerequisite selects the existing unsigned transfer type for a narrow
seed/Xfer view reconciliation, not a claim that the broad trial reached and
failed a signedness comparison. Complete class/table/census recovery remains
outside this one-field repair.
