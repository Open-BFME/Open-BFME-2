# Pointer-tree native helper bindings

Base: 7cce6ba90783. Source:
`Code/Libraries/Source/WWVegas/WWLib/stlport_map_int_ptr_lower.cpp`.
The ledger's unsigned/pointer names are legacy byte-shape views; this work
does not establish their original retail type identities.

## Copy at 0x00603B9C, 115 bytes

Both native clone calls (+14 and +62) target 0x00413E55. Its existing
30-byte owner is the ModuleFactory/ModuleTemplate tree clone in
stlport_modulefactory_map_copy.cpp. The source now spells this dependency
directly in the rowed copy specialization, retaining the STLport structural
copy loop and the original inline COMDAT selection contract. No new pin,
alias, ledger row, shared-header edit or source move is needed.

All ten source rows remain exact; one EH graph is EXACT. Across the source
and the two existing helper-provider units, exactly two of 48 normalized
bindings change names, keeping their native target. Both provider objects are
unchanged. Strong definitions and weak aliases are unchanged; only the copy's
relocation fingerprint changes, its unused legacy clone COMDAT disappears,
and the real clone reference is added. The source retains LINKS for 747
authored bytes against published index 85f6b7f40c (2026-10-29 15:08).

An initial inline clone bridge byte-matched but introduced an unrowed source
definition; it was removed. The final change is entirely inside the existing
rowed copy body. A non-inline copy specialization introduced a duplicate
strong definition; it was corrected to preserve the original COMDAT contract.
No such duplicate remains in the accepted scoped preview.

The owning retirement tool refuses to delete any register line: 231 ledger
objects are missing, three referenced providers are not proven current, and
the unchanged copy constructor already has a third wrong base-constructor
binding outside this source's two registered keys. The before snapshot proves
that finding predates this change. Preserve the register; no debt retirement
or census-linked gain is claimed. The second registered insert-helper binding
at 0x005348E7 remains to investigate in this same file.
