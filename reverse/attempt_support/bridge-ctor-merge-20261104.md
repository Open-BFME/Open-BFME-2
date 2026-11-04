# Bridge constructor consolidation, 2026-11-04

The native `tu_skeleton.py --merge` absorbed
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeCtor.cpp` into
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp` after
the separately verified [layout prerequisite](bridge-ctor-layout-20261104.md).
The result removes one source file and retains 34 matched rows, 34 distinct
RVAs and 4,056 ledger bytes. No new match, linking gain or debt retirement is
claimed.

The merge repointed four function rows, including the TextureRef destructor's
existing fold-proof, three TU-map source cells and one header-queue source and
accept command. TU assignments and approval evidence were not regenerated.
The header diagnostic and all four covered RVAs survive unchanged at the new
path; canonical W3DBridge adoption remains outstanding. No pin, alias or hatch
was removed or added. The inspected constructor has no local or parameter
bindings requiring scoped naming.

The first commit-message check refused the vanished donor's W3DBridge key:
the destination already holds that class key, so its set-based transfer check
cannot see an added key. The merge commit uses the documented per-key
`Debt-Retired:` source-accounting trailer for this already-held-key case
(`docs/consolidation.md`); both header rows and their diagnostics remain in the
queue. This does not accept canonical-header adoption or remove class debt.

## Verification

- `./build.sh` on the final destination: 34/34 exact; five compiler float
  literals verified. Existing funclet label renumbering is checked against
  exact parent EH graphs.
- `eh_verify.py`: eight EH rows exact, none missing.
- `allowed_symbols.py --source`: 87 references, zero wrong bindings.
- `data_check.py`: one source, zero findings outside or inside its baseline.
- `check_csv.py` and `find_declared_unmatched.py`: pass; the destination's
  existing one unclaimed definition remains unchanged.
- `link_check.py --prepare-current`: final destination has strict reusable
  receipts and passes the same normal byte gates. Census/index/status unchanged.
- Native merge guard: preserves its census-linked scope comprising the
  destination, constructor, GetModelVerticesFixed and Load units.
- Refreshed the scoped consolidation planner after the move;
  `name_lane.py consolidate --check build/consolidation` passes.

## Path consumers and bounded link evidence

Audited the constructor path and basename across the outgoing prerequisite and
merge, including tools, hooks, workflows, source/header includes, configurations,
registries and documentation. No active tooling/include consumer needs a path
change. The native merger transfers active ledger/header rows. Remaining old
path mentions are the source provenance marker, historical attempts and obstacle
history, and the census-owned `reverse/link_status.csv` snapshot; these are
intentionally retained. The source's TextureRef comment now describes the
retained constructor spelling without claiming two surviving units.

The staged-tree batch audit used tree
`d4f52052f05c9c1812ba4c0c48c8f24a74b4c0b2`. Its older census index at
`2f0cb97f52` makes results provisional. The first missing receipt,
`Rva0011C0F0Finish.cpp`, was refreshed through `--prepare-current` (6/6 rows
exact). Repeating the audit against observed origin base
`beace82b7c4057ef6016cf10923d65250d9ffc6e` remains **INCONCLUSIVE**: affected
consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
current receipt. Carry that consumer into the next census; broad link closure
and runtime are unverified. No census or headline linking figure was updated.

Remaining donor blockers are Vector3 declaration ordering in
GetModelVerticesFixed and RefCountPtr/model-view reconciliation in Load. Mixed
DrawBridges and TerrainLogic sources were not split or moved.
