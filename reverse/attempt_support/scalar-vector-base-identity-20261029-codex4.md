# Scalar-vector base constructor identity

Base: `95bb9e1d6b`, 2026-10-29. The default picker claimed
`Code/GameEngine/Source/Common/StringScalarVectorCopyBFME2.cpp` and
`0x000BBA1A`. The existing owners at `0x000B6378` and `0x00523D6C`
were also claimed before adding fold rows. No C++ source, pin, compiler
option, generated header or TU assignment changes.

## Target and object facts

The starting source passes all five existing rows and ordinary preview already
predicts LINKS for 213 authored bytes against index `85f6b7f40c`
(2026-10-29 15:08). Its historical census failure is not a new regression.
The identity scan instead reports one registered wrong/unknown binding: the
copy constructor at `0x000BC61D` calls its emitted vector-base constructor
at `0x000B6378`, whose name has a pin but no row in this source.

That complete emitted constructor is 58 bytes. Its nonrelocation bytes match
the existing `vector<BfmeE8>` base-constructor owner at `0x000B6378`.
Its two calls resolve to the allocator proxy constructor at `0x0014F3C4`
and the eight-byte allocator at `0x00523D6C`. An initial `add_match` trial
correctly refused the base row because the STLport 4.6 nonconst allocator
spelling had no row or pin; the failed append was automatically restored.

The same source emits that allocator as a complete 28-byte body, identical
to the existing `allocator<BfmeE8>` owner at `0x00523D6C`, including the
resolved byte-allocation call. Adding its fold row through
`add_match.py --icf-owner` first lets the base constructor's fold row pass
the complete byte and callee checks too. Both notes name this source as
their fold proof. Neither row adds unique coverage or establishes the
application identity of the eight-byte record.

## Scoped verification

- `./build.sh` through both admissions verifies 7/7 rows, the existing parent
  EH placement and all string, float and import checks.
- `link_check.py --prepare-current` verifies this explicit provider with a
  strict reusable compiler receipt; census/index/status remain unchanged.
- `allowed_symbols.py --source` reports 14 references: eight owner, four
  fold and two EH; zero wrong bindings, versus one before admission.
- `find_declared_unmatched.py` reports all defined functions matched.
- Ordinary preview retains LINKS against the same index. Its 298-byte
  per-file figure includes the newly attributed folded bodies; it is not
  a census gain or an increase in unique authored coverage.

The first owning retirement verdict refused to remove the registered key
because 198 ledger provider objects were absent. The normal `./build.sh`
gate then passed those exact 198 sources: 1,759/1,759 function rows, 37 data
rows, 284 string references, 111 floats and 53 imports. It restored 124 objects
from the fetched store and compiled the remaining stale inputs. No source
changes were needed for this preparation.

The fresh `repair_queue.py retire identity` verdict then passed and removed
this source's one registered key, leaving zero. Pin consistency and CSV
checks also pass. This is one identity-debt retirement; full consumer and
census confirmation remain pending. Carry the provider and its consumers
into the next scheduled census.

The outgoing batch's eight providers also have fresh strict receipts: all
42/42 function rows and four data rows pass, including the earlier pending
commits. `link_batch_audit.py` remains INCONCLUSIVE because its index is at
`85f6b7f40c`, behind the outgoing base, and the affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. This is pending consumer verification, not a clean batch result.
