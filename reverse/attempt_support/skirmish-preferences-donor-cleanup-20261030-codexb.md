# Skirmish preference donor cleanup, 2026-10-30

Inspected base: `c647a75e55`. Scope:
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp`.
The source identifies itself as a verbatim Generals Zero Hour port. This is
cleanup of imported, unrowed definitions, not recovery of BFME 2 implementations
or a claim that retail dead-stripped these methods.

Removed `SkirmishPreferences::setSlotList`, `usesSystemMapDir`,
`setSuperweaponRestricted` and `setStartingCash`. None owns a ledger row or has
a caller in this file. The fetched provider index (2026-10-30 10:11,
`12b9e7a7c0`) has no other non-forgotten object touching their exact symbols.
Retained the other six marked preference bodies and all matched owners.

The before/after object comparison gives 839 -> 830 COMDATs. All 830 retained
COMDATs have identical normalized digests and sizes; there are no additions,
changed retained strong symbols or changed weak bindings. The removed copies
are the four methods, inline AsciiString assignment from `const char *`, and
the `%d`, `Yes`, `No` and `UseSystemMapDir` literals. Each shared copy still has
other indexed providers: respectively 126, 95, 7, 7 and 4, covering its outside
object touches. The four removed methods have no outside touches. These are
index-scoped provider facts, not current-ledger consumer closure.

No undefined symbol was added. Removed undefined references are
`GameInfoToAsciiString`, `UserPreferences::setAsciiString`,
`StringBase<char>::set(const char *)`, the AsciiString map subscript and
`__strcmpi`. The now-unused `stricmp` macro and its comment were removed too.
`tools/hatch_counters.py --update` supplied the four deleted
`present_unmatched` keys; unrelated stale-key deletions were left out.
The owning `ms_header_audit.scan_files` / `refresh_queue` pass found no remaining
local occurrence and retired this file's `stricmp:source` queue row.

Verification:

- `find_declared_unmatched.py` before/after: 7 matched rows; unclaimed
  definitions 10 -> 6; both checks pass.
- `./build.sh` before/after: all 5 function/EH rows and 2 data rows exact;
  string, float and import-reference checks pass. No ledger or pin changed.
- `eh_verify.py`: EXACT 1; the parent's EH data verifies the renumbered label.
- `link_check.py --prepare-current`: one safe provider passes strict byte
  verification with a reusable receipt.
- Ordinary before/after previews against the index above: unresolved 49 -> 46,
  COMDAT blockers 2 -> 2, selected-copy blockers 1 -> 1; linked bytes 0 -> 0.
- `link_batch_audit.py --base HEAD --tip
  302475ec5fce6b2d94fecdbc32b08db3e5c03d48 --sources-from ...`: exit 2,
  INCONCLUSIVE. The index predates the outgoing base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. The tree names the staged source, hatch and header-queue edits.

Remaining prerequisites: reconcile the legacy GUI/preference and GameInfo
interfaces, GameSlot vftable copies and Money copy-constructor selection.
Refresh current consumer receipts and carry this scope into the next scheduled
census. No whole-unit link clearance, census gain or runtime result is claimed.
