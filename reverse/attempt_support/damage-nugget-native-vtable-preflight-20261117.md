# DamageNugget vtable preflight

Native864048 has15 entries; source currently emits its deleting destructor
only. Native slots1/6/14 hold5086CE/507D84/5084FC. Their providers are
rowed as nonvirtual QAE methods; slot6 is this source's924-byte doEffectPosition.
Those names must be virtualized with rename.py before a compiler table can
name their native virtual declarations. The retirement register deleted_rows
is held by another contributor. It is not changed or bypassed.

Slots2-5 already have named virtual DamageNugget providers at507943,50797D,
507A04,507991. Native slot8 is inherited Rva00507823::rva00507877 at507877.
Parent constructor50775B and destructor507823 use864010, not864048. A complete
base contract is needed, rather than adding the existing methods in arbitrary
source order. Remaining constant entries include50B5C6,50B238,47A6A9,D43D0,
47A699; shared50B238 and common constant providers are held.

No source/ledger/header changes or partial pure-slot placeholders are retained.
The normal unchanged whole-file baseline passes14/14 rows (see build log);
source declarations have no unmatched body. Bridge pass test remains open.
Native table and provider rows were read directly; prior donor-name notes
remain historical leads, not new target identity claims.
