# AptPlayerStatus objective-text CRT prerequisite, 2026-10-29

Inspected base: `b492fdd6a013e5dbd031d769d6a6ddc7d38a0629`.
The stock merge trial uses census index `d92e7e6635`, dated
2026-10-28 15:58. The retained objective-text CRT declaration fix passes all
three standalone rows and clears its compiler error in the changed-input
stock composition trial. The composed bytes pass, but missing destination
census coverage prevents link admission. The callback experiments are
discarded. All files remain separate; no source-file, linked-byte or
image-ownership gain is claimed.

## Scope and placement

The map rebuilt in memory by `tools/tu_skeleton.py --plan` approves 42 rows
for the provisional `GUICallbacks/Apt/AptPlayerStatus.cpp` TU. Its five
whole-file candidates own 32 matched rows:

- `AptPlayerStatus.cpp` (23 rows);
- `AptPlayerStatusCallbacks.cpp` (4 rows);
- `AptPlayerStatusObjectiveText.cpp` (3 rows);
- `AptObjectivesMenu.cpp` (1 row);
- `Common/Rva004E44C9Check.cpp` (1 row).

`AptPlayerStatusDtor.cpp` and `Common/Rva0050E9D3Enable.cpp` are mixed files
and remain outside this work. No source or ledger row moved, and the committed
TU map was not regenerated. There is no old-to-new path map for this batch.

The supported final naming packet is under
`build/consolidation/apt-player-status-final`. The initial GUI-wide packet
under `build/consolidation/gui-lane1-20261029`
records WorldBuilder's `Gui/GUICallbacks/Apt/AptObjectivesMenu.cpp` spelling
as a lead. That donor path does not establish the original BFME 2 filename.
The current approved provisional grouping, rather than the path lead, is the
basis for the stock merge trial. The packet also flags private type views,
compiler context and path-keyed registers for review.

## Initial supported trial

`tools/tu_skeleton.py --merge .../AptPlayerStatus.cpp --dry-run` accepts no
combination and changes no source or index. Its exact report is preserved in
`build/consolidation/apt-player-status/dry-run-before.log`.

The compiler rejects the callbacks donor because the composed header set
redeclares `perror` with different linkage. The
objective-text donor declares `_mbscpy` with `char *` arguments, conflicting
with the seed's CRT declaration using `unsigned char *`. The standalone
`Rva004E44C9Check.cpp` donor reaches byte verification but is rejected there.

The objective-index helper already composes with exact bytes. Its separate
admission refusal is:

> AptObjectivesMenu.cpp links at the census; the merged object would not:
> a file without a census object would place the merged unit earlier in link
> order than the guard can judge

The missing destination census object is an evidence boundary, independent of
the CRT errors. The published index asset was checked once: its SHA-256 is
`35ae2fbbc23588a0e51e061784f87c9c995dd37b9208f21f0c0b3dcfc1bc2d3d`, matching
the local index, with asset update time 2026-10-28 16:42:29 UTC. No newer
published index was available. No measurement, smoke run or guard change was
attempted.

## Retained declaration repair and discarded callback trials

`AptPlayerStatusObjectiveText.cpp` now spells the CRT's unsigned-character
`_mbscpy` signature and casts its text-buffer arguments at the call. This
retains the direct call and removes the incompatible C declaration.

An initial callback trial replaced the headers with five explicit prototypes.
Although its final object matched the original, independent review found five
new private Microsoft declarations. That trial was discarded. A second trial
retained the existing CRT headers and saved/restored `_CRTIMP` around them
with `push_macro`/`pop_macro` and an explicit `#undef`. It added no private
declarations and preserved all four standalone rows, but the changed-input
stock trial still reports the same `perror` C2375 error. That trial is also
discarded; `AptPlayerStatusCallbacks.cpp` is identical to the inspected base.

The retained objective-text fix preserves function identities, private
layouts, compiler flags and external call targets. No merged source is
retained.

## Changed-input stock trial

The supported dry run was repeated once after the objective-text fix and the
header-preserving callback experiment. Its report is
`build/consolidation/apt-player-status/dry-run-header-scope.log`; exit status
is 2, with 42 approved rows, two mixed files, no refused rows and
`accepted: []`.

- `AptPlayerStatusCallbacks.cpp`: still C2375, `perror` redefinition with
  different linkage; the scoped macro change is therefore discarded.
- `AptPlayerStatusObjectiveText.cpp`: the original C2733 `_mbscpy` declaration
  error is gone. Its candidate passes byte verification and reaches link
  admission, which refuses the same missing-destination-census ordering
  boundary quoted above, now naming this source.
- `AptObjectivesMenu.cpp`: the same census/order admission refusal remains.
- `Rva004E44C9Check.cpp`: still rejected on bytes.

Thus the retained fix clears one proven composition compiler blocker. It
does not prove link closure or authorize a merge. No guard was bypassed,
no mixed file was split and no merge was applied.

## Verification

The ordinary Windows build entrypoint, `python tools/build.py`, verifies
32/32 rows across the five original files before editing, including 27 string
literals, one empty-string reference and four named imports. The original
objects are saved under `build/consolidation/apt-player-status/before`.
The retained objective-text source passes 3/3 rows, with a clean frozen-file
check and an EXACT EH graph.

| Source | External COMDAT digests | External definitions | Undefined dependencies |
|---|---:|---:|---:|
| AptPlayerStatusObjectiveText.cpp | 10 unchanged | 10 unchanged | 9 unchanged |

The complete external COMDAT bytes and normalized relocation-target
identities, external definition set, unresolved dependency set, weak bindings
and relocation graph equal the saved original object. The comparison is
`objective-text-object-comparison.json` in the same scratch directory.
Independent review confirms that the objective-text object's local EH labels
renumber, while their section/value targets, raw sections and all external
symbols remain unchanged. There are no added or removed providers.

`link_check.py --prepare-current` separately gives the objective-text source a
strict reusable receipt and passes its three rows through the normal gates.
`prepare-current-objective-text.log` records the supported mapping from the
ledger's `$L1233` to `$L1235` at 0x00791EA9. This command does not measure link
closure or change the census. An earlier preparation command stopped before
compilation on Git's worktree ownership check; the successful invocation uses
process-local `safe.directory` entries and changes no Git configuration.

Scoped data checking reports zero findings before and after the fix.
The four original EH graphs are EXACT; the edited objective-text source's
graph remains EXACT after its compiler label renumbers. No code/data debt,
hatch or header-adoption register key is transferred or retired.

The baseline identity scan has 139 references and one existing wrong/unknown
binding: the unchanged seed's `rva004E476C` calls
`vector<Rva004E476CColor>::push_back` at row offset 602, targeting
0x002E01C6. This work neither changes nor claims to settle that identity.

## Next prerequisites

Keep the five files separate. The callback `perror` linkage error and
`Rva004E44C9Check.cpp` byte difference still need independent, verified
prerequisites. The normal census must supply sufficient destination/provider
order evidence before LinkGuard can admit the otherwise byte-exact helpers.
Rerun the stock dry run only after relevant inputs change. The planner's
private-view hints are not proven compiler failures. The two mixed files
still need their own approved split work if they are to move.

No path consumers changed in this batch. The final outgoing audit and normal
commit hooks remain the publication owner's responsibility.
