# Streak texture getter consolidation, 2026-10-30

Inspected base: `1b0276b877`. Owner: `yasinschroeder-codex`.
No census or image-ownership measurement is recorded by this work.

## Verified prerequisite

The default picker claimed streak.cpp and its destructor/getter donors. The
WW3D2 evidence planner records the getter and destructor as whole-file
candidates for streak.cpp, with placement, declaration and compiler blockers.
The supported merge rebuilds current TU assignments in memory; the committed
TU map is not regenerated. Its initial trial rejects the getter solely for
`-O2 -G7 -arch:SSE` versus the seed's `-arch:SSE -G7`, and the destructor for
C2908 (explicit SimpleVec destructor specialization after instantiation).

The build's base command already supplies /O2. Removing the getter's redundant
/O2 and ordering /arch:SSE /G7 like the seed preserves its effective settings.
`flag_defaults.py propose` verifies current/default variants and records the
new override spelling: one row, one default-lost row, unchanged scope.

The seed's ZH-derived shared StreakLine view declared Get_Texture as a raw
pointer. BFME 2's already-rowed 33-byte getter at 0x00741750 instead returns
ParticleBufferClass::TextureHandleClass through its caller buffer and calls
the owned BFMELineRendererTexture getter at 0x00191210. The seed now carries
the donor view locally, with its attribution and license, and changes that
one return declaration to the existing target-proven handle type. All other
fields, methods and inheritance are retained. The getter uses its existing
pointer view of LineRenderer at +0x100, allowing composition with the complete
seed view without changing shared renderer headers. No layout or BFME 2
original header recovery is inferred from the external donor.

The normal build verifies all 67 affected rows, 11 floating literals and one
named import. EH verification reports three EXACT graphs. Both prerequisite
objects retain every external COMDAT name, size and byte/relocation digest:
275 for streak.cpp and one for the getter. Their complete external symbol
facts and relocation-root/edge graphs are identical before and after.
Strict baseline receipts had verified all 68 rows across the three inputs.
The three current previews retain LINKS for 5,575 authored bytes against
index `6fe1089c24` (2026-10-30 04:25). This is prediction, not a new census.
No data/header/identity debt is retired, and no hatch or pin is added.

The destructor's separate inline/out-of-line template cleanup contract and
the mixed Common getter files remain outside this prerequisite.

## Applied merge and batch audit

The prerequisite's full gate passed 99,012/99,012 function rows, all 2,238
data rows and every reference, identity and no-op-patch check. Its enforced
converged-data pass judged 20,354 sources and 11 addresses with zero second
names or unjudged rows. Runner publication rebased the prerequisite to
`2cb44b0cb2` on `b92e718066`; that rebase changed no StreakLine input and
the runner handed it to the fleet publisher.

The evidence planner was regenerated after that rebase under
`build/consolidation/codex-streak-20261030-rebased`. The supported
`tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WW3D2/streak.cpp`
rebuilt current assignments in memory and absorbed StreakLineGetTexture.cpp.
Only its already-approved 0x00741750 source cell moves in the committed TU
map. The destructor again fails C2908 and remains separate; both mixed Common
files remain untouched. Three census-linked inputs pass the merge's LinkGuard.
The result removes one C++ source file without losing any matched row.

The applied TU passes the normal build for 67/67 rows and all three EXACT EH
graphs. The frozen-file check passes with the same 14 existing unclaimed
definitions. Its 276 external COMDAT bodies exactly equal the two original
objects' union: no added, removed or changed name, size or byte/relocation
digest. Complete external symbol facts and relocation-root/edge graphs also
equal that union. No changed provider binding is observed in these facts.

Strict current preparation additionally verifies 74/74 rows and one data row
across the merged TU, separate destructor and LightningDrawModuleDoParticles.cpp
and StreakDrawModuleDoParticles.cpp. All four ordinary previews retain LINKS:
5,248, 327, 1,740 and 913 authored bytes respectively, against `6fe1089c24`.
The two providers still total 5,575 bytes; adding the callers gives the same
8,228 bytes the five former files owned. The getter's 33 bytes moved owners;
the preview's per-file increase is not a linking gain. Existing unreferenced
renderer getter and shader-assignment diagnostics remain outside this repair.

The merge tool carries the getter's compiler override into the seed, keeping
the summed 63 rows/22 default-lost counts. Its hatch-counter refresh changes
no baseline line or count. Neither absorbed getter nor destination has affected
data/identity baseline keys or a class-header queue row. The owning tools
refresh header/MS-header queues: the destination retains its one array-delete
finding, now classified adapt/unknown with current include locations. No debt
retirement is claimed. No active data, body-owner or doxygen source record
names the removed getter.

The path-consumer audit covers outgoing common base `b92e718066` through staged
tree `e2fe6455c5d2f1a10738ea69356d65b6a39702bc`, including the pending Recorder
and prerequisite commits. The sole source-path move absorbs the getter into
streak.cpp. Searching tools, hooks, workflows, source/shim includes, build.sh,
ledgers and documentation finds no active path consumer requiring a repair.
Intentional old-name references remain in the merged provenance comment,
historical link_status.csv, re_attempts.log and the 2026-10-26 attempt handoff.

The staged batch audit exits 2, INCONCLUSIVE: index `6fe1089c24` is older than
that outgoing base and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. It does not complete the full consumer selection/loss checks. Carry
the merged provider, removed getter, its shared-helper consumers and the two
direct particle callers into the next scheduled census. The bounded object
comparisons and previews above do not clear this remaining scope or record a
census/image-ownership gain. The destructor's template-contract reconciliation
remains a prerequisite for its later consolidation.

## Reference freshness follow-up

The last-check stamp was under 72 hours old when this pass began and crossed
that threshold during its full-gate wait. A read-only official-upstream check
then found BFME 1 master `5279f2cdd7790639d8684b5d1c648f612acca187`, beyond
the clean repository-pinned checkout `337e4b48e8f295f74bdd1155ad2b6dd848b63c32`.
All checks here keep that pinned checkout fixed. No reference update or fresh
success stamp is recorded; a new pass needs the routine reference-update
procedure, including paired verification and affected donor refreshes.
