# Possible-to-attack filter: retire the duplicate table array

Root recovery seat, 2026-11-08/09, source base a46241d8d1. The picker served
Common/Rva00149E60Set.cpp (one 36-byte row at 00262387) for the strong array
`?g_010956C4@@3PAPBXA` bound at table RVA 007F91B0. The whole file was read;
the declared-unmatched check is clean before and after.

The array is removed and the same DIR32 store now names the existing
`??_7PartitionFilterPossibleToAttack@@6B@` compiler table. No code row, pin,
alias, source path or new definition is added. The complete 36-byte code,
relocation position, flags and COMDAT policy are identical after normalizing
this one referent. The old array had three external dependencies; the new
source depends only on the existing table. All uses of the removed name in
Code were confined to this source.

Retail's table has exactly three slots, followed by the next datum at
007F91BC. Current matched providers independently verify all targets:

| Slot | Native RVA | Existing real provider |
| --- | --- | --- |
| 0 | 00395A19 | PartitionFilterPossibleToAttack scalar deleting destructor, 28 bytes; table's weak E name defaults to G |
| 1 | 00260FD0 | PartitionFilterPossibleToAttack::allow, 37 bytes |
| 2 | 0036CC7A | Rva000421C8::getPlayerMask, 4 bytes |

Normal verification of the changed source and these provider units passes
59/59 code rows; all seven EH graphs are exact. Bounded normal bridge replay
removes the strong-definition refusal (1 to 0), with already_correct=1
and zero bridges both before and after. The compiler table was already
correct; this work removes its redundant strong alias, not a bridge. The
four-source preview conserves LINKS 8,124 bytes at index c885072a48
(2026-11-08 19:18). This does not establish global provider or runtime closure.

## Constructor recovery remains a separate naming transition

Native stores establish object +8, command source +C, attack type +10,
base link +4=0, table BF91B0, and ret 12. An isolated real constructor using
the canonical Rva000421C8 base and the existing derived class spells all
36 native bytes exactly. Its destructor is declared, so the emitted G
wrapper calls the existing 49C38A teardown rather than an invented inline
one. The declaration and fields agree with the existing matched allow view;
some placeholder consumers' comments swap the last two field meanings.

That trial does not authorize changing the current setter's name/signature
to a constructor. The row remains under its old unverified view in this
repair. No canonical name or name_basis record is claimed. The trial report
is banked as structural evidence for a supported naming/identity transition,
not as source recovery credit. Its newly emitted base/derived COMDATs would
also need the ordinary complete provider audit before landing.

`proof.json` records native table targets, source-object comparison and
bounded before/after results. `constructor-trial.json` records the isolated
candidate and its exact matched address; it is not a landed implementation.
The raw data index is regenerated only through tools/data_ledger.py. The
complete regeneration changes exactly this one row: the old name disappears
and strong definitions fall from one to zero. All 34,433 addresses and all
2,354 explicit verified owners retain their addresses, extents and identities;
`index-audit.json` records that comparison.
Confirmation that the next real image drops the obsolete table name remains
pending. No byte-coverage, source-file-count, census or game-running gain
is claimed.
