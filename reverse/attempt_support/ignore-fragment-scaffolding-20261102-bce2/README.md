# Deferred ignore-map fragment: unused scaffolding removed

Base `145e03d5466`. The picker served UserPreferencesDeferredIgnores.cpp,
13 matched rows. The fragment's independent string-keyed preference methods
already live in UserPreferences.cpp. Remove 52 net obsolete scaffolding lines:
unused string-map specializations/comparator, duplicate PreferenceMap typedef,
Bool/Real aliases, stdio and GlobalData includes, and its unused global
forward declaration. Keep the canonical UserPreferences layout and all real
int-keyed map contracts. No method body, compiler flag, ledger, pin, shared
header, protected register, file path or class layout is changed.

## Current proof

All 13 rows match before and after. Strict reusable preparation passes, the
two EH graphs are EXACT, and no definition becomes unmatched. All 59 external
COMDAT byte/relocation fingerprints and all 73 external symbol binding facts
are identical before/after. The adjacent fact table and proof record them.
The same ordinary preview retains zero linked bytes, with exactly the same
three losing COMDATs and two wrongly selected providers. It is intentionally
an exit-1 receipt, not a passing link test. This is source cleanup only: no
new C++, census improvement, retired debt or provider-identity fix is claimed.

## Remaining link prerequisites

The existing family handoffs still apply. getIgnores calls native tree copy
3B1EBB, while its decorated constructor currently owns 52D25D. The insertion
family and node construction names conflate genuine int/AsciiString with two
larger placeholder values; correct their existing owners rather than adding
pins or suppressing the real providers. The pair destructor has direct
releaseBuffer and AsciiString-thunk copies across the ignore/assign and
PeerDefs/WOL providers. The October 27 fold-only trial regressed PeerDefs;
no repeat of that admission or generated-funclet move was made here.

The full affected-consumer audit remains separate from these identical
object facts. See the outgoing audit receipt and shared obstacle register.
No source path moves, so no path-consumer migration is needed.

## Publication audit

The outgoing audit is INCONCLUSIVE: index984a4cdc4d predates base145e03d5466,
and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Carry this source/provider/consumer scope into the next scheduled
census. No full current-object consumer closure is claimed. The commit hook
also reports eight findings outside the code-identity register in shadow
mode: seven existing wrong bindings and the divergent pair destructor. The
identical 59 body/relocation and 73 external-binding facts establish that this
cleanup does not alter those emitted contracts. No register is relaxed or
retired. The whole-file family-identity repair remains open.
