# Word-vector STLport 4.6 migration

2026-10-30, base `32a7f941eb`, owner `yasinschroeder-codex3`.
The default picker served `stlport_vector_word_o1.cpp` with a file claim;
the allocator address and `stlport_wide_num_put.cpp` were claimed before
editing the provider. This is library cleanup, not new native coverage.

## Target facts and implementation

Retail's complete unsigned-word allocator at `00017710` is 29 bytes. The
existing const allocator in `stlport_wide_string.cpp` owns that range. It
checks the element count, doubles it, calls the existing GameMemory static
byte allocator at `000307F0` with a null hint, and returns null for zero.
Both the native `_M_insert_overflow` at `0007EAA7` and `_Vector_base`
constructor at `00513D55` call `00017710`.

The new non-const 4.6 specialization in `stlport_wide_num_put.cpp` equals
all 29 bytes of the existing owner, including its byte-allocator relocation.
`add_match.py --icf-owner` admitted the complete twin with byte verification.
There are no added pins or unique covered bytes. This does not establish
an original BFME translation unit for these recovery files.

The vector unit opts into the existing 4.6 patch layer, drops const from
its allocator declaration and removes the obsolete 4.5.3 proxy specialization.
The existing O2 num-put unit supplies the complete out-of-line provider;
explicit instantiation retains it for the vector callers. Its ten previous
external COMDATs associated with rows and all other existing definitions
remain unchanged. Every vector row is readmitted through `add_match.py`
with `migrated=stlport-4.6`.

## Trials and object changes

Marker plus const removal alone fails C2244: 4.6's proxy inherits the
allocator and does not have the specialized allocate member. Removing that
obsolete proxy lets five of seven rows match, but leaves both growth calls
without the non-const allocator identity/provider.

A clean specialization in the O1 vector unit emits 28 bytes, using two pops
and a shared return instead of retail's 29-byte O2 shape. That trial was
removed. The O2 provider produces the exact body; without explicit
instantiation it is not emitted because no num-put body references it.

[Object comparison](object-comparison.json) compares cached, normally built
objects against the clean base's saved objects. All seven vector raw bodies
and all ten prior num-put raw bodies are unchanged. Only the vector rows at
`0007EAA7` and `00513D55` change relocations: QBE const allocate becomes QAE
non-const allocate at the same proved native target.

The num-put object retains all 32 original external COMDATs with identical
digests and adds only the allocator. The vector object goes from 83 to 81:
four old helper names disappear and two 4.6 names appear; seven retained
definitions change digests. The report lists every name. In particular,
4.6 uses non-const deallocate and by-value two-argument vector resize.
Raw-row preservation alone does not prove all wider COMDAT consumers safe.

## Verification and scope

- `./build.sh` on the changed pair: 18/18 rows match, with string, float
  and import checks passing. Each of the seven readmissions also verifies
  the whole vector unit.
- `find_declared_unmatched.py` passes on both edited sources before and
  after the edit; the vector's existing absent-from-retail anchor is retained.
- `python3 .../proof.py` checks the complete allocator twin, the exact
  relocation, its native byte-allocator target and both native vector calls.
  It writes its receipt under `build/word-vector46/`.
- The four-source link preview includes the changed pair, the old allocator
  owner and GameMemory. Against index `85f6b7f40c` (2026-10-29 15:08), all
  four preview LINKS: vector 577 -> 577, num-put 690 -> 719, wide-string
  564 -> 564, GameMemory 279 -> 279 authored bytes. The 29-byte difference
  is the already-covered twin, not a census gain.
- Strict preparation of those four sources passes 43/43 function rows,
  seven data rows, 13 literals and four named imports, with reusable receipts.
- The staged new-variant guard passes; the vector no longer appears in the
  STLport migration queue. `check_csv.py` and `git diff --check` pass.

## Outgoing audit boundary

The initial staged audit against `32a7f941eb` is INCONCLUSIVE: index
`85f6b7f40c` predates the base and four directly affected source objects
lack current receipts. Supported strict preparation passes 113/113 rows
across AptCreateAHeroDrawMapComponent.cpp, GSConfig.cpp, W3DWater.cpp and
Render2DSentenceBuildThaiBFME2.cpp, including 71 funclet bindings and two
complete constructor folds. Their sources are unchanged.

Consumer-wide selection/loss verification and scheduled census confirmation
remain separate from the bounded four-source preview. The repeated audit
gets past the direct-source receipt stage and remains INCONCLUSIVE on the
older baseline and the affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`, whose current
receipt is missing. It does not complete consumer selection/loss verification.
Carry both changed sources, their word-allocator identities and all affected
consumers into the next scheduled census. No nightly, link cycle or smoke
runner was invoked and no census gain is claimed.
