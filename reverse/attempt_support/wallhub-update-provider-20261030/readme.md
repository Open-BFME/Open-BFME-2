# WallHubBehavior native update provider

## Target facts and change

LINK-160 records the removal of a link-wide alias that had supplied the undefined
`UpdateModuleInterface::update` named by WallHub's private interface table.
The current 2026-10-30 14:18 census (`e1f7c1dd18`) records the constructor unit
unlinked, with one unresolved name. This is a provider repair, not missing byte
coverage or a new match.

The constructor at `00452E27/154` installs native update table RVA `0084B1E0`.
Its slot zero contains VA `008A6563`, targeting the existing whole six-byte
`B8 FF FF FF 3F C3` returner at RVA `004A6563`. The `ConstIntGetters.cpp` row
at that address is retained unchanged. These are retail placement and behavior
facts; a constant body alone would not establish a unique class identity.

The existing class view now uses a pure typed `UpdateSleepTime update()`
interface and an ordinary inline WallHub override returning
`UPDATE_SLEEP_FOREVER`. Its emitted definition supplies the native table slot
directly. No ledger row, pin, alias, unmatched marker, header or hatch is added.
There is no donor-source attribution. Existing retail module identity and the
native constructor's own table binding establish the repair's scope.

## Verification

Private before/after objects preserve all three existing constructor/handler/
cleanup rows and the EXACT parent EH graph. The new update is exactly six bytes,
without any relocation. The native slot points to that complete body, and the
emitted table names this same-object definition. The other three emitted table
bindings and all four table sizes are unchanged. See
[private comparison](private-comparison.json).

The normal strict three-provider preparation verifies 104/104 rows across the
constructor, existing constant-getter unit and existing MI destructor family.
Four literals and one float reference pass; the owned EH graph is EXACT.
The normal preview against `e1f7c1dd18` reports 3/3 LINKS, 1,836 -> 1,990 authored
bytes: WallHub 0 -> 154, providers 246 and 1,590 unchanged. Frozen-definition
and CSV checks pass. [The actual strict object](actual-proof.json) independently
records the complete native update body, table target, unchanged other tables
and EXACT constructor EH graph, using no added production symbol-map binding.

These checks clear the bounded missing-provider scope only. Broader consumer
selection and the next scheduled census remain separate. No official linking
percentage or unique-byte increase is claimed; the other LINK-160 units retain
their recorded identity or claim prerequisites.
