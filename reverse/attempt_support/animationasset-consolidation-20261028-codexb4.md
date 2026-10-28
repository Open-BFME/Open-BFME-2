# AnimationAsset constructor consolidation, 2026-10-28

Seat: yasinschroeder-codexb4. Inspected base: `4e52d316e4`.
Destination: `Code/Libraries/Source/WWVegas/WW3D2/AnimationAsset.cpp`.
Absorbed source: `Code/GameEngine/Source/Common/Rva0014CE67Ctor.cpp`.

## Routing and prerequisite

The scoped `name_lane.py consolidate` report for WW3D2 was current before
composition. It records WorldBuilder's animasset.cpp path as corroboration,
not a recovered BFME 2 source path. The supported TU planner rebuilt stale
assignments in memory and approved constructor 0x0014CE67 (77 bytes) and its
handler 0x007668C8 (10 bytes) in the existing AnimationAsset TU. Only their
source cells change in the committed TU map; assignments are not regenerated.

The first dry run rejected the constructor because the seed's StringClass
view lacked its existing two-argument constructor declaration. Prerequisite
`aafa39966b` adds that declaration without changing layout, COMDAT digests or
external definitions/references. All 15 seed rows and three EH graphs remain
exact. The next supported dry run accepts the seed and constructor donor.
The supported applied merge removes one source file and retains 17 matched
rows in the destination, including five older rows outside the approved span.

The earlier `tu-merge:.../AnimationAsset.cpp` attempt in re_attempts.log
identified both StringClass and prototype identity differences. This smaller
change preserves both existing prototype ABI names; it does not resolve their
shared-vtable identity. HAnimPrototypeOwnerCtor.cpp remains separate: its
RefCountPtr template conflicts with the included texture-handle header and
its wrapper member differs from the seed's raw-pointer view. Reconcile that
view and the prototype/base names in separate verified work. The generated
unwind 0x007668C0 stays in uw_gen_014.cpp; LINK-095's unmasked-callee prerequisite
is not claimed fixed. No generated source or pin is edited.

## Verification and bindings

Before composition, all three planned inputs passed `link_check.py
--prepare-current`: 19/19 rows, two string literals, two named imports and
strict reusable receipts. Original objects were saved under
build/animationasset-before. After composition, `./build.sh` and explicit
strict preparation pass 17/17 destination rows, both string references and
both imports. All four parent EH graphs are EXACT. Frozen-file, CSV integrity,
TU ownership and Microsoft-header staged checks pass. Code identity reports
17 rows and no new finding; data identity reports none. Converged enforcement
checks 11 addresses with no second names or unjudged rows.

The two original objects and merged object each supply the same union of
16 external definitions and 16 distinct COMDATs. No definition or COMDAT is
added or removed. External undefined sets, after excluding definitions supplied
within the composition, are identical. Fifteen byte-and-symbolic-relocation
COMDAT digests are unchanged. The sole changed digest is the compiler-generated,
unrowed `??1Rva0014CE67_Prototype@@UAE@XZ`: its instruction bytes are identical,
but REL32 at offset 25 targets StringClass::Free_String rather than the
out-of-line StringClass destructor because the seed defines that destructor
inline. All its other relocations are unchanged. Retail's rowed destructor
0x00065F5B is exactly `e9 e0 aa 5a 00`, a tail jump to Free_String at 0x00610A40.
Thus this changed cleanup call reaches the same implementation. The merged
constructor and its EH graph still match retail independently.

Neither absorbed-source code/data identity keys nor header-adoption queue keys
exist. The merge tool ran hatch_counters --update; the hatch register has no
diff and no count rises. Header queues are refreshed through the merge tool:
the seed's existing Microsoft-header row moves to the queue's end with the
same two occurrences and the same _mbscpy ABI finding / _strlwr match.
No header debt is retired and no unrelated queue row is removed.

## Full pending-batch path audit

Audited `origin/master` at `51853dba25` through the staged composition,
including the previously queued commits. Four absorbed paths occur across
that complete range: Common/AnimationSoundTree.cpp,
Common/U4GlobalGuardedNotifies_Rva004ca223.cpp,
Common/Thing/Rva001D9A00Finish.cpp and Common/Rva0014CE67Ctor.cpp. Destinations
are the existing AnimationSoundClientBehavior, INIAudioEventInfo and
AnimationAsset TUs. No directory is moved.

One combined basename/full-path search across all tracked files finds no
active tool, hook, workflow, include, build configuration or source registry
that needs repair. The 40 remaining references are source-origin comments,
historical census/log/evidence records, append-only naming provenance/votes,
and TU-map naming evidence. Their paths describe past evidence and are retained;
active ledger/map source columns resolve to current owners. The naming
agreements for the constructor's old parameter placeholders already carry
stale outcomes. Earlier batch audits document the other merges' registers
and bindings. The current ledger source is tracked, and the staged whitespace
check passes. Planner reports become stale after the applied ledger/source
move and must be regenerated before choosing further work.

## Link limits and abandoned selection

Index: `d92e7e6635`, 2026-10-28 15:58. The supported merge's LinkGuard accepts
the census-linked inputs and composition. Ordinary preview reports LINKS,
571 authored bytes versus the destination's previous 494-byte attribution.
The 77-byte difference moves existing coverage; it is not a census gain.

The outgoing audit against the inspected base, staged tree
`841b94edd943575e7aef42059b972d6fbccda02c`, is INCONCLUSIVE: the index predates
the base and affected consumer Common/AIHarvestPrepareSiteState.cpp lacks
a current receipt. Full consumer selection remains unverified. Carry the
merged provider and affected consumer cohort into the next scheduled census;
no census, smoke or ownership run was started. This change claims one fewer
source file with matched coverage preserved, not measured linking progress.

The initial default picker served PathfinderNewMap.cpp's already-landed
local-floorf repair. Fresh preview against the same index reports LINKS,
580 authored bytes; no source was changed and its claims were released.
LINK-132/133 remains global history, not a newly repaired scope here.

The consolidation picker first served provisional `WW3D2/RenderAsset.cpp`.
Its supported dry run accepts three donors / 11 rows, but a tracked
`WW3D2/renderasset.cpp` already exists. Applying the approved uppercase
destination would introduce a case collision on Windows. No merge was applied;
all nine scope claims were released. Resolve the approved destination's case
and ownership through TU evidence before retrying, rather than hand-moving rows
to the lowercase file. Five other donors still fail on private allocator /
StringBase definitions or the iterator view; the dry-run accepted subset does
not resolve those prerequisites.
