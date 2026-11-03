# F600C canonical Pathfinder primary-base call-shape trial

Verdict: PASS, standalone105B function/provider identity. Starting from the previous exact canonical-PathfindCell candidate, replace only the private Pathfinder declaration with canonical AIPathfind.h, adapt the EXISTING Rva002F52A7Shape typedef's owning class to the real primary PathfindServicesInterface, and express the member-pointer conversion on that primary base explicitly.

The exact canonical CheckForAdjust declaration is bool(Object *, const LocomotorSet &, bool, int, int, PathfindLayerEnum, int, bool, Coord3D *, const Coord3D *, float, int *, int). Canonical Pathfinder publicly derives PathfindServicesInterface first and Snapshot second. The candidate uses a standard static_cast of &Pathfinder::CheckForAdjust to that exact signature on PathfindServicesInterface, then the existing reinterpret_cast to the original integer/byte call-shape typedef. The receiver is static_cast<PathfindServicesInterface *>((Pathfinder *)query). It leaves all argument expressions, field spellings/layout, callback Info view, return/control flow, old call-shape argument types and source compiler flags unchanged. No new helper body, type name, pin, alias, pragma or marker is added.

Three bounded sanctioned private Verifier trials, all from one captured scratch control:

| Variant | Native105B row | Emitted size | External definitions | EH |
|---|---|---:|---:|---|
| Prior exact Cell-header control | exact | 105 | 1 | none |
| Naive canonical Pathfinder include, old member-pointer shape | fails bytes | 119 | 1 | none |
| Explicit canonical primary-base member-pointer conversion and receiver | exact | 105 | 1 | none |

For the successful primary-base candidate, the sole ordinary external definition `?cellCallback@Rva002F600CInfo@@QAEHPAVPathfindCell@@0HH@Z` has exactly the same entire E.Obj section bytes and ordered symbolic relocation list as control. Added/removed/changed provider lists are all empty. The comparison uses BSS-aware E.Obj section.data; no object-header/BSS false difference. The naive negative changes this provider's bytes, confirming a real canonical-MI call-shape issue rather than a preexisting mismatch. None emits an EH graph. This trial ran only tu_skeleton.Verifier(source).matched; no normal build or shared cache write.

Control text SHA256: `a2f594f148cf5a397111590e2ef9fb2056a9ddda3cced32e327605ac7da983e7`.

Candidate: primary-base.cpp, complete scratch source without extra asserts. Supporting control.cpp / naive-canonical.cpp and all three copied private objects accompany proof.json, which contains exact provider bytes/relocations and all verdicts. Harness: ../core-header-proof/f600c-primary-base-probe.py. Main should apply the intended local edits to its current claimed public source and then run ordinary verification/header acceptance; do not overwrite newer source wholesale from this snapshot.

Scope limits: retaining the existing integer/byte ABI view is not recovery of semantic callee parameter types. No final TU composition, resolved Rva002F600CInfo competing view, fresh selected-provider census or image linkage is asserted. The current seed's unused4B Info prefix remains main's separate reconciliation. No tracked source/ledger edit, claim, network operation, check edit or normal build occurred. Tracked reads stopped.
