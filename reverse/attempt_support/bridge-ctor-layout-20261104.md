# Bridge constructor consolidation prerequisite, 2026-11-04

Inspected revision: 96e492564922. Scope: W3DBridgeBuffer.cpp and
W3DBridgeCtor.cpp under Code/GameEngineDevice/Source/W3DDevice/GameClient/.
Normal picker file claims and class:W3DBridge held by yasinschroeder-codex3.

The native dry merge initially accepted no donor: the destination padded over
members initialized by the constructor (first reported missing m_numPolygons).
The existing constructor at RVA 0x000DD97F supplies the scalar, count and
three Vector4[3] matrix members; replace only the destination padding at those
same offsets. Preserve the 0x114 stride, texture at +0x34, meshes at +0x38,
+0x7C/+0xB8, visibility +0x104, string +0x108 and enabled byte +0x110.
Names are retained from that verified target reconstruction, with its recorded
Zero Hour/BFME1 donor provenance; no new original-source identity is asserted.
The registered W3DBridge header remains a separate adoption prerequisite:
its AssetReference member differs from these existing TextureRef views.

The native tu_views tool shares TextureRef's existing null constructor between
the two sources. Its separate TextureClass trial failed compilation and was
restored; W3DBridgeLoad.cpp is unchanged. No new class, function body, pin,
alias, compiler flag or debt retirement is introduced.

Verification:

- Normal build and strict-current preparation: 34/34 function/EH rows exact,
  five float literals; frozen-source check passes.
- EH verifier: 8/8 EXACT. allowed_symbols: 87 references, zero wrong bindings.
- data_check: two sources, zero findings or findings outside the baseline.
- Destination object before/after layout expansion: identical 52 COMDAT
  byte/relocation digests and sizes, 16 exclusive definitions, 33 undefined
  names and zero weak aliases (read-only link_census COFF inspection).
- Normal native dry merge now accepts the destination plus W3DBridgeCtor.cpp,
  all 34 rows, with the census-linked-unit guard passing. It previously
  accepted no donors. No source move has yet been applied in this commit.

The evidence planner was run for the GameClient directory. It distinguishes
retail original-path facts, donor hints, provisional alternatives and stale
committed map warnings; tu_skeleton rebuilds the current map in memory.
Remaining donors: GetModelVerticesFixed fails Vector3 declaration order;
Load fails duplicate RefCountPtr/method-view composition. The two mixed files
remain outside the merge. No census, full-image link or runtime gain claimed.
Local logs: build/codex3-bridge-{dry,after-dry,views-apply,prereq-build,
prereq-current}.log. The source-path audit will accompany the actual merge.
