# AptSkirmish appender fold debt

Inspected base: `f4d813d60d`. Published preview index: `d92e7e6635`,
2026-10-28 15:58. BFME 1 freshness receipt: 2026-10-27, verified reference
`e74410b3738a2bb75d626085d9ebfd3406a43ff7`.

The default picker served AptSkirmishCallbacks.cpp as an unresolved link unit.
The current source already contains b46f564676's TheMessageStream correction;
ordinary preview is LINKS for 4,008 authored bytes before this change. This
is a stale queue lead, not a newly repaired link regression.

The source retains GameMessage::wb00EC9680, a real C++ helper already admitted
as a pinned ICF twin of appendIntegerArgument at 0x0030F936. The original pin
records two distinct WorldBuilder appenders, EC9680 and EC9420, and the native
caller at 0x00521DFA. These are inherited provenance, not a new donor-name
finding. The helper's semantic name remains unknown.

The target evidence is its complete 19-byte compiled body, including allocArg's
relocation, verified against the existing retail owner. `add_match.py` with
`--icf-owner ?appendIntegerArgument@GameMessage@@QAEXH@Z` registers this existing
helper with its source as `fold-proof`. It replaces the pin's address binding
with a byte-verified fold row. The original owner stays in MessageStream.cpp;
this is one retail body with two proven emitted spellings, not new coverage.
No executable C++ changes or source-path moves are retained.

A direct-call trial changed the helper call to appendIntegerArgument and
removed the helper body. VC7.1 then merged the branch tails, shortening the
358-byte StartGameAfterCDCheck by 19 bytes. The trial was reverted and logged;
the separate existing helper spelling is necessary for the current exact body.
This was a valid byte mismatch, not a false reject.

Debt reduction: exactly one pin and one present-unmatched marker. The supported
hatch update also noticed unrelated stale BfmeLexEAN path bookkeeping; those
unrelated hunks are excluded. No new name, coverage, census-linked-byte gain,
TU approval, source-file reduction or runtime result is claimed.

Verification:

- Frozen-file check passes before and after; the remaining unclaimed helper
  reported before the change is now rowed.
- `./build.sh` passes all 55 rows after removing the pin; six string references,
  the import reference and both STLport folds also pass.
- All 11 exception graphs are EXACT.
- CSV and pin-consistency checks pass; scoped data check reports zero findings.
- Staged hatch check credits only pin 9,416 -> 9,415 and present-unmatched
  3,717 -> 3,716. The two counts describe this base, not subsequent master.
- Strict preparation passes both the consumer and MessageStream provider:
  73 function rows and one data row, with reusable current receipts.
- Ordinary previews both remain LINKS. The consumer's authored-row total rises
  from 4,008 to 4,027 only because the existing 19-byte ICF helper is now rowed;
  MessageStream remains 573. These totals overlap at the fold, so they are not
  new covered or census-linked bytes.
- The staged-tree outgoing audit exits 2, INCONCLUSIVE: the published index
  predates the base and affected consumer Common/0CreateAHeroManager21FE49.cpp
  lacks a current receipt. Carry the fold-row/pin replacement, its consumers
  and that receipt into the next scheduled census. No full consumer clearance
  is claimed; the byte and local preview checks above are the verified scope.
