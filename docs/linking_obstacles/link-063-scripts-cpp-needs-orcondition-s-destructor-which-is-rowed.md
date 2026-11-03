### LINK-063: `Scripts.cpp` needs `OrCondition`'s destructor, which is rowed under the placeholder `Rva003B262E`

**Status: Blocked on a name decision (`rename.py` refuses; no canonical evidence). Updated: 2026-10-26; inspected revision: 319adf8b41.**

- **Evidence / scope:** `Scripts.cpp` (512 B) has two blockers: unresolved
  `??1OrCondition@@MAE@XZ`, and an `??_7OrCondition@@6B@` copy that differs from
  `OrConditionCtor.cpp`'s, the first in link order. Retail's table 0x0081F3F4 has one
  slot, the 28-byte deleting dtor 0x003B331E, which calls the 68-byte dtor 0x003B262E.
  Both are matched in `Rva003B262EFinish.cpp` as `??_GRva003B262E@@MAEPAXI@Z` /
  `??1Rva003B262E@@MAE@XZ` (tier `address`/placeholder). The rowed `??0OrCondition`
  (0x003B238A) installs that table; the dtor body is Zero Hour's
  `OrCondition::~OrCondition` (`Scripts.cpp:1352`) without memory pools.
  `OrConditionCtor.cpp` spells the dtor public (`UAE`) and reaches the placeholder
  through `/alternatename:??1OrCondition@@UAE@XZ=??1Rva003B262E@@MAE@XZ`, a counted
  hatch. The three units' deleting-dtor bodies are already byte-identical (retail's
  28 B), and `??_E` is a weak alias of `??_G` in each.
- **Planned fix (not applied):** rename `Rva003B262E` to `OrCondition`; spell
  `OrConditionCtor.cpp`'s dtor protected and drop its alias. All three vtable copies
  would then name `??_EOrCondition@@MAEPAXI@Z`, and `Scripts.cpp` would resolve its dtor.
- **Why it is blocked:** `rename.py class` refuses any new name that already appears in
  the tree (`OrCondition already appears in ...`), whatever the basis, and so does
  the inferred lane's `apply`, which lands through it. A hand rename needs evidence
  that would pass as canonical. `canonical:zh` fails: a full `zh_sweep` (918 objects)
  places no ZH `??1OrCondition@@MAE@XZ` (130 B, pool-based) and the 30-byte ZH
  `??_G` has no needle. `canonical:bfme1` fails: `bfme1_sweep.py scan` has no placement
  for either body. The constructor-to-vtable link is a `vtable-slot` hint
  (`docs/naming.md`), and `??0OrCondition` is itself unverified in `name_tiers.csv`.
- **Remaining / next check:** a maintainer decision: either `rename.py` admits a
  rename into an existing class name when the old class is a placeholder whose rows
  are that class's own table entries, or a class-reconciliation commit adopts one
  `OrCondition` view and moves both rows. No source was changed.
- **Clearance:** none.
- **Census confirmation:** not claimed.

**2026-10-27 package c140 follow-up, inspected `a0b82f68445de8ab0254437ef7e97332ce48cfb0`, ordinary-preview index `bf3dd31211` (2026-10-27 00:39):** The three current providers retain their prior results: `Scripts.cpp` U1/L1, `OrConditionCtor.cpp` LINKS and `Rva003B262EFinish.cpp` LINKS. The emitted Scripts table is now explicitly measured as eight bytes: protected deleting destructor plus `getObjectMemoryPool`; retail 0x0081F3F4 has the single deleting-destructor slot at 0x003B331E. The TU-local `MEMORY_POOL_GLUE_WITHOUT_GCMP` override in Scripts.cpp still declares that pool accessor virtual. Fixing only the public/protected destructor spelling would leave this extra slot. The existing 68-byte destructor row at 0x003B262E and 28-byte deleting destructor remain the required OrCondition rename candidates; no new match is needed for those bodies. No unchanged rename or pool trial was repeated. Next: settle the existing row identity and remove the unsupported virtual pool slot coherently, retaining the constructor, duplicate and parser rows. Clearance and census confirmation remain pending.

**2026-10-28 reset cleanup, inspected `35eee2f3f0`, ordinary-preview index `41c28839bf` (11:08):** Scripts.cpp still byte-matches all ten code rows and retains the unresolved protected destructor and conflicting OrCondition vtable. Removed the destructor aliases in ScriptListSubrecordReset.cpp (0x003B7647) and Rva003B7C1EReset.cpp (0x003B7C1E) by calling their existing rowed destructor owners directly. Both complete 36-byte bodies remain exact; both helpers and both destructor providers still LINKS in preview. The hatch register shrinks by two. A broad Scripts.cpp dry merge was interrupted before returning a verdict; no merge or exhaustive failure is claimed. The destructor identity and extra pool slot remain prerequisites. [Scope, checks and remaining header entries](../../reverse/attempt_support/scripts-reset-alias-cleanup-20261028-codexb.md). No census gain or LINK-063 clearance is claimed.

**2026-10-28 skip-predicate cleanup, inspected `0e9a68f517`:** WriteGroupDataChunk (0x003B6975) now calls the existing int-returning skipGroup owner at 0x003B485A and truncates the result to a byte, preserving retail's AL test. Removed the bool alias and redundant pin; all 367 bytes across the predicate, writer and unchanged recursive caller remain exact and LINKS in ordinary preview. A fresh broad Scripts dry merge was interrupted after about 24 minutes without a donor verdict; no merge is claimed. The staged-tree link audit is inconclusive against older index `41c28839bf`, with a missing current receipt for affected consumer `Common/0CreateAHeroManager21FE49.cpp`; carry consumer confirmation into the next census. OrCondition identity and the extra pool slot remain open. [Scope and verification](../../reverse/attempt_support/scripts-skip-alias-cleanup-20261028-codexb4.md).

**2026-10-30 selection recheck, base `c9c0fea9be`, ordinary index `85f6b7f40c`:** Scripts.cpp still verifies ten code rows and one data row; preview retains the protected OrCondition destructor and conflicting table. No identity/header trial was repeated. A possible empty loadPostProcess alias was left untouched because its shared address is claimed elsewhere. The existing identity and pool-slot prerequisites remain; [checks and selection handoff](../../reverse/attempt_support/module-header-ms-headers-20261030-codexb5.md). No clearance or census gain.
