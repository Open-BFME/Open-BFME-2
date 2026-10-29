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

## Insert at 0x005348E7, 294 bytes: blocked trial

The +107 native call reaches the existing State-pointer tree _M_insert at
0x0053479F (136 bytes, StateMachineDefineState.cpp). The legacy unsigned/void*
helper is a different emitted copy. STLport declares _M_insert private, so the
protected-member access used for clone cannot expose it.

A trial kept the rowed hinted-insert algorithm and replaced its helper calls
with an explicit typed native-symbol function pointer. VS2003 rejects the
__thiscall pointer declaration with C4234 (keyword reserved for future use).
The complete patch and compiler log are evidence only; the source was restored
to the separately committed, byte-verified clone repair. No trial body remains
under Code. Reconcile the caller/helper ABI through the native provider cohort
before repeating this trial. The two State-provider rows byte-match, but that
unit already previews blocked on its own create-node/insert_unique COMDATs and
selected copies. This work claims no repair of that cohort.

## Final retained scope

After restoration all ten caller rows verify, and strict current preparation
passes all 19 caller/native-clone-provider rows. The preparation leaves every
scoped object fact and binding identical to the accepted clone snapshot.
The caller and clone owner retain LINKS for 747 and 1,029 bytes. The batch
audit is INCONCLUSIVE: index 85f6b7f40c predates base 7cce6ba90783, and affected
consumer Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry
that consumer, the removed legacy clone copy and the native provider scope
into the next scheduled census. No code/data identity key is retired, no
source path moves, and no census-linked or new exact-byte gain is claimed.
