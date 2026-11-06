> Recovery publication: historical investigation from e61985373425. Recovered against `8bb483ac9115`; original commands and results below were not rerun during recovery. All original fleet claims were released. These are prerequisites/attempt evidence, not a completed repair or runtime result.

# ParticleEmitter TU consolidation: current header boundaries

Inspected revision: `f15737ff46b`. Worker: `codex-fleet-20261106-c02-seat2`, shard `4/30`.
Status: blocked; no game source, ledger source path or register key changed.

The default claimed picker selected `Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp`, with the complete donors `ParticleEmitterGetTexture.cpp` and `ParticleEmitterRva001A1500.cpp`. The prior blocked attempt was `627efb64099` on 2026-10-31. The subsequent seed header adoption, nine-file merge and November 4 string-header repair changed inputs, so this was a fresh trial rather than an unchanged repeat.

`check_csv.py` passed: 99,515 function rows, 9,320 symbol rows and 2,272 data rows. The declared-unmatched audit ended with `All defined functions are already matched`; it also noted 43 seed rows and 12 existing unclaimed-definition annotations. Those existing annotations were not changed or claimed retired. The native plan rebuilt TU assignments in memory: 87 approved rows, the seed plus two candidate donors, four mixed sources retained. The committed TU map was not regenerated or staged. Existing owners at 0x001A0D10/33B and 0x001A1500/26B were inspected; no body or row was added.

## Commands and result

- `python3 tools/next_work.py --claim --shard 4/30`
- `python3 tools/name_lane.py consolidate --under Code/Libraries/Source/WWVegas/WW3D2/`
- `python3 tools/tu_skeleton.py --plan Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp`
- `python3 tools/find_declared_unmatched.py Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp Code/Libraries/Source/WWVegas/WW3D2/ParticleEmitterGetTexture.cpp Code/Libraries/Source/WWVegas/WW3D2/ParticleEmitterRva001A1500.cpp`
- Through the shared two-slot scheduler: `python3 tools/tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp --dry-run`

The trial used the brief's compiler PATH, `BFME_VM_WINEPREFIX=/home/bfme/.wine-pdb`, `BUILD_POOL=1`, and stable worker owner/namespace. It completed normally with exit 2: zero donors accepted, zero source files removed, zero rows moved. The native report follows. Its census-linked input list is dated evidence, not a current whole-image link result.

```text
Waiting for a shared verification slot; keep polling this process.
Acquired shared verification slot 1/2.
tu: Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp
approved: 87
mixed: {'Code/GameEngine/Source/Common/ConstIntGetters.cpp': 40, 'Code/Libraries/Source/WWVegas/WW3D2/particle_emitter_build_definition.cpp': 4, 'Code/Libraries/Source/WWVegas/WW3D2/particle_emitter_create_from_definition.cpp': 17, 'Code/Libraries/Source/WWVegas/WW3D2/particle_emitter_destructor.cpp': 1}
refused: {}
accepted: []
rejected: {'Code/Libraries/Source/WWVegas/WW3D2/ParticleEmitterGetTexture.cpp': "compile: Code\\Libraries\\Source\\WWVegas\\WW3D2\\.part_emt.42e2d0d74e2ac78d.tu_skeleton.cpp(1224) : error C2556: 'BFME2ParticleTextureHandle ParticleEmitterClass::Get_Texture(void) const' : overloaded function differs only by return type from 'TextureClass *ParticleEmitterClass::Get_Texture(void) const' | Code\\L", 'Code/Libraries/Source/WWVegas/WW3D2/ParticleEmitterRva001A1500.cpp': "compile: Code\\Libraries\\Source\\WWVegas\\WW3D2\\.part_emt.7ec1266628a4aa33.tu_skeleton.cpp(1358) : error C2039: 'rva001A1500' : is not a member of 'ParticleEmitterClass' | Code\\Libraries\\Source\\WWVegas\\WW3D2\\.part_emt.7ec1266628a4aa33.tu_skeleton.cpp(1360) : error C2065: 'Buffer' : undeclared identifier | Code\\"}
link_guard: census-linked: Code/Libraries/Source/WWVegas/WW3D2/ParticleEmitterGetTexture.cpp, Code/Libraries/Source/WWVegas/WW3D2/ParticleEmitterRva001A1500.cpp, Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp
blocked: no verified merge of two or more donors
reconcile_classes: ['ParticleBufferClass', 'ParticleEmitterClass']
reconcile: python3 tools/tu_views.py Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp --dry-run, then without --dry-run: the donors declare their own views of ParticleBufferClass, ParticleEmitterClass (docs/consolidation.md, "Workflow per TU", step 4)
```

## Remaining prerequisites and audit limits

`ParticleEmitterGetTexture.cpp` owns the existing handle-returning function. The seed's `reference/shims/bfme2_part_emt/part_emt.h` instead declares an inline `TextureClass* Get_Texture()` extracting `Buffer->Get_Texture().Ptr`; the isolated donor returns `BFME2ParticleTextureHandle`. Reconcile the real texture-handle ABI and the affected declarations/providers before merging. Return-only overload edits or a second owner would not resolve this boundary.

`ParticleEmitterRva001A1500.cpp` defines a private render-slot view, forwarding slot 82 (+0x148) to the buffer at +0x12C. The seed uses the full RenderObjClass hierarchy and has no `ParticleEmitterClass::rva001A1500` declaration. Its actual virtual owner/slot and canonical declaration need evidence and the supported naming/reconciliation path before a native merge. This pass added no aliases, pins, virtual-signature respells or hatch.

The planner snapshot for this target is attached as `.planner.json`. Its initial system Python lacked Capstone, so its owner-level retail instruction references are explicitly unverified; it is investigation context, not routing approval. The merge tool's current in-memory approved map and native byte/link guards remain authoritative. The four mixed sources were not split or changed.

No path moved, no protected key retired, and no source/provider change was published. There is consequently no successful merge byte/EH/data/provider/consumer audit to claim. The copied published link index is the dated `47fd56b879` index (2026-11-06 05:39 UTC); neither it nor the guard's input list proves current full selection, real linking, menu/skirmish/save-load or retail CRC equivalence. No restricted measurement or smoke runner was started.

## Runtime assessment of the original trial

The original scheduler process waited roughly 109 minutes before acquiring a slot. At **2026-11-06 12:46:42 UTC**, its tu_skeleton child had run **47m49s**; the current candidate `8851ec4f884d5876` compiler wrapper had run only about one minute. Distinct earlier generated candidates (`831e75b35b78ee5e`, `949c19668e67fb19`, `7ec1266628a4aa33`) and five successful object/dependency pairs demonstrated progress. The newest successful pair at that check was written at 12:36 UTC; the search's final verdict remained pending then. Overall trial age was not one compiler invocation's age.

The original process's `BFME_COMPILE_TIMEOUT` was checked and was unset. `tu_skeleton.py` therefore used its existing **600-second per-candidate** limit through `try_compile_source`; timeout status 124 is a refused candidate, never accepted. Search has distinct composition/order/flag trials and memoization, but no overall wall-clock deadline. The original process was polled to completion, never restarted or duplicated.

A read-only guest process check around 12:48 UTC found exactly two cl.exe processes: the current seat2 candidate and another worker's live StagingRoomGameInfo job. There were no older seat2 compiler orphans in that snapshot. Dispatch separately observed the current candidate waiting in `p9_client_rpc`, supporting shared filesystem wait rather than a single 47-minute compiler spin. This was a bounded observation, not proof of general timeout cleanup correctness. No runtime was restarted or stopped and no other worker's process was changed. Failed candidate counts and timeout counts were not exposed by the final report; none are inferred from elapsed time.
