# Registration base identity prerequisite (2026-11-09)

Target: LINK-654, four army-action registration tables. This change only
reconciles the already matched base constructor with its existing vtable and
deleting-destructor identity; it does not recover the four derived tables.

`tools/rename.py class --fold Rva0052B894Registration --into Rva0052B668`
proves that constructor RVA 0x0052B894 installs VA 0x00C686BC as its sole
own-table store. The data ledger already calls that table
`??_7Rva0052B668@@6B@`; slot zero is the existing 29-byte deleting destructor
at RVA 0x0052B668. No donor spelling or readable class name is asserted.

The supported transaction rewrote all four source consumers and renamed the
89-byte constructor and its 10-byte EH handler at 0x007970C2 in place, with
tombstones for their former identities. Source paths and extents are unchanged.
Normal verification passed all 32 rows, four data rows and five string literals.
Five renumbered funclet labels were resolved through verified parent EH data.
The four sources' own link previews all say LINKS against census 5b5011469d
(2026-11-09 19:12), preserving 72 + 67 + 606 + 388 = 1,133 linked bytes.

The base still has inconsistent private views and a short compiler table.
Finishing LINK-654 requires a real 4-byte base with a destructor and pure
factory slot, four distinct derived classes, and a common factory identifier
and compatible signature. The 7-byte base destructor is currently rowed as
`Rva00052B588DwordImmSetter::apply`; reconcile that owner rather than adding a
second identity. The shared 5-byte destructor and 28-byte deleting destructor
represent folded derived bodies, not another intermediate base class.

Review also identified live factory callers in
`GameClient/GUI/Rva0052B634ArmyActionPrime.cpp`, including three helper pins
and alternatenames. Free/stdcall factories cannot use `function --to-class`;
they require reviewed ordinary prepared `--respell` transactions. Four different
virtual identifiers would leave the inherited factory slot pure and add slots.
Genuine distinct 5-byte destructor folds need the supported `add_match.py
--icf-owner` body route: the fold-pin admission's concrete-byte minimum does
not admit their 7-byte base-setter callee. No new fold, pin or alias is added
by this prerequisite.

Scratch before-texts and the source list are under
`build/registration-class-recovery-20261109/`. This is scoped source/identity
verification, not evidence of a newly linked game image or runtime progress.
