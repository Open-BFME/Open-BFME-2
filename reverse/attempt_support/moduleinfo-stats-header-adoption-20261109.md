# Statistics consumers use canonical ModuleInfo

Inspected at cf14f42c4a on 2026-11-09. INIStatsRecord.cpp and
Rva0050CBA2StatsDump.cpp replace their private ModuleInfo declarations with
the unchanged canonical header. Their otherwise unused twenty-byte
ModuleInfoNugget stand-ins disappear with those views. No diagnostic operation,
record layout, resource lifetime, method identity or source path is changed.

The first source owns the file/CSV record operations; the second owns the
diagnostic traversal. The latter's embedded module descriptor remains twelve
bytes at the enclosing view's+0x2F0, with twenty-byte records. Canonical
getCount() preserves the inline pointer-difference computation without the
source-local dllimport/forceinline member definition. No ModuleInfo/Nugget
instance is constructed or destroyed by this pointer-only use. Other diagnostic
views, their unresolved original names and the private vector declarations are
retained. Existing donor comments remain distinct; no donor is imported and no
additional original-name/TU evidence is claimed.

All29 rows pass the first private trials and normal build.sh. Four parent EH
graphs are exact. Normal verification covers five literals, eight empty-string
references, two floating literals and six named imports. Seventeen compiler
funclet labels renumber; trusted exact-parent EH resolves the same retail
addresses without a ledger/pin rewrite. Frozen checks pass before/after.
Current-input previews against index5b5011469d (2026-11-09 19:12, census
9b9d058303 at17:41) preserve LINKS535+1143=1678 bytes. Owning acceptance retires
two ModuleInfo header rows, leaving20 locally and no header key in either file.
Both changed sources have strict reusable receipts.

All32 retained COMDAT payloads/sizes, public definitions, undefined references
and selection policies are preserved. No definition is removed. The diagnostic
writer emits one additional ordinary getCount() copy:12B, select-any policy2,
digestd2b57ba9852a, identical to all six indexed canonical copies. It is an
existing logical symbol from the shared header, not a new function identity or
new byte coverage. Weak defaults, aliases and /INCLUDE directives are unchanged.
There is no shared-header, flag, ledger identity/extent, pin, alias declaration
or hatch change.

Target facts are the retained accesses, operations and verification results;
the new getter is compared to current indexed copies rather than presented as
a new independently recovered retail row. Local evidence is under
build/thingtemplate-header-cohort-20261109/: moduleinfo-stats-sources.json,
probe-moduleinfo-stats.py, moduleinfo-stats-private-proof.json,
moduleinfo-stats-private-eh.json, moduleinfo-stats-build.log,
moduleinfo-stats-frozen-*.log, moduleinfo-stats-link.log,
moduleinfo-stats-accept.log, moduleinfo-stats-prepare.log and
moduleinfo-stats-provider-diff.json. The provider audit uses
prove-moduleinfo-filters.py with prefix moduleinfo-stats and only the existing
?getCount@ModuleInfo@@QBEHXZ clone allowed. Historical baselines are not to be
overwritten by rerunning probes.

Remaining work includes the wider ModuleInfo views/lifetimes and the separate
map-owner naming prerequisites. These statistics fragments also retain private
record/CRT declarations which need their own supported consolidation check;
this pass does not approve a merge or move any row. The preceding publication's
broader audit remains INCONCLUSIVE for AIBuildable.cpp at
index5b5011469d/base27fb34c964. Carry it into the next census. No new global
linking coverage, maintained image or runtime outcome is claimed.
