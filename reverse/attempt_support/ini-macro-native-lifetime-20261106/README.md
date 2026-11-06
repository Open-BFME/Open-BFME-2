# INI macro-map lifetime view, 2026-11-06

Base: da93446935. This is type-model reconciliation, not missing byte coverage,
original typedef/name recovery, or a cleared real-link/runtime obstacle.

Target facts: native `2CCC3` is a 57-byte hashtable destructor. It calls the
existing clear owner `2234FE`, frees the bucket storage through `30830`, and has
the exact compiler EH graph at FuncInfo `8FE4D0`. Its caller `2CD71` is a five-byte
tail jump. The global cleanup `7B6A6E` calls `2CD7B` on `DDF58C`; that destructor
calls the nocase set cleanup at `2CC38` on `this+14`, then `2CCC3`. Constructor
`2DC3C` builds the map at zero and set at `+14`, then zeros `+20/+24`.

Existing view evidence: INI.cpp's macro lookup uses a pair with AsciiString key,
the address-derived one-AsciiString mapped view `Rva0002C9E7Value`, `rts::hash`,
and `rts::equal_to` (compareNoCase). Native `_M_find` at `2C9E7` independently
calls the nocase hash `2BF8C` and comparison `6A00`. Official STLport's
`stl/_hashtable.h` defines the independent key, value, hash and equality template
parameters and the ordinary clear/member-destruction sequence. The old
one-byte `Rva0002CCC3Record` hash-set view contradicts these established users.

The first repair adopts that existing macro-map view for the destructor and its
sole direct holder consumer. It preserves the existing explicit specialization's
call through the real ICF clear owner. The retained cast remains cleanup debt.
The mapped view and holder keep their address-derived names: their original
typedef/class names are not established. The full new decorated template name is
not asserted as retail's spelling; `name_basis.csv` is unchanged. The hand
signature reconciliation follows docs/naming.md's bookkeeping, including both
old-name tombstones and the EH parent-note rewrite. No source path, TU approval,
pin, alias, data owner or hatch is added or changed.

Verification: normal build.sh passes all 137 rows across the two files, four data
rows, 74 literals, 17 empty strings, one float and 23 named imports. The normal
objects' external code/provider facts equal the private winners. Fully resolved
57-byte/5-byte native comparisons and the destructor's EXACT EH result are in
normal-summary.json. The bounded link preview retains 9,185 bytes in the two
previously linking units; the EvacuateDamage constructor remains unlinked with
its existing PB_DeepBase/DamageModule obstacles. This is not a census result.

Remaining order: reconcile INIMacroTable's constructor view and its existing
template providers, re-identify `2CD7B` without inventing TU approval, then close
DamageModule's canonical lifetime cohort and remove the incorrect implicit
destructors from the EvacuateDamage constructor unit. The constructor writes 40
bytes while current data ownership splits 32-byte storage plus two generation
words; no second overlapping data owner is introduced here. The independently
retained case-sensitive table destructor at `2236B9` is untouched.
