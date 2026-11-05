# Camera timestep consolidation

Inspected source base: `ed73303ad902043fa9b051d047057f993242acbd`.
Prerequisites: canonical list-header adoption `b336831c6c` and destination
list-access reconciliation `ed73303ad9`, each separately byte-verified.

`tu_skeleton.py --merge` absorbed
`Code/GameEngine/Source/Common/Rva00065E3CMethod.cpp` into
`Code/GameEngineDevice/Source/W3DDevice/GameClient/camerashakesystem.cpp`.
The current in-memory TU assignment approved the timestep body; the inline
constructor and its EH rows follow their owner. Four functions.csv and four
tu_map.csv source cells moved. The TU map was not regenerated. The mixed
`camerashakesystem_shaker.cpp` remains separate. Source files decrease by one;
all 17 rows survive. Placeholder identities remain cleanup work.

Verification:

- Destination `./build.sh`: 17/17 rows exact; the three renamed compiler
  funclet labels resolve through their parent EH data to the existing RVAs.
- Destination plus affected `W3DCamTransform.cpp`: 20/20 rows exact, two
  string literals and 21 compiler float literals verified.
- `link_check.py --prepare-current` on those two explicit sources passes
  with strict reusable receipts; no census, index or status was written.
- Frozen-file check: all definitions matched. CSV check passes.
- `tu_ownership.py --staged` and staged whitespace check pass.
- Header adoption accepts the destination; refreshed MS-header queues have
  no local-header findings. No remaining header, code-identity, data-debt or
  hatch key names the absorbed source, so no debt transfer or retirement is
  hidden in the deletion. The earlier prerequisite retired its one header
  queue row through `header_adopt_lane.py accept`.
- The merge engine's census-linked guard accepts both original sources.
  Ordinary destination preview is LINKS, 282 -> 453 bytes: 171 bytes moved
  from the fragment, not a new headline gain.

Provider/consumer qualification: manual `link_batch_audit.py` on the staged
tree remains INCONCLUSIVE. Index `c95fcfcfcd` predates the outgoing source
base. After strict preparation resolves the two initially missing scoped
receipts, the audit reaches an unchanged shared-list consumer lacking a
current receipt:
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`.
Thus whole-batch selected-provider and consumer closure is unverified;
include this merge and its shared-list consumers in the next scheduled
census/current-index audit. No linking or ownership headline gain is claimed.

## Tooling compatibility audit

Fetched origin/master `0d6981621bf445ca01a74792a2ce06bef80de61e` before
auditing the pending range and staged merge. This is the batch's only source
path removal. Combined old-path/basename searches covered tools, hooks,
workflows, Code, reverse and docs. No active include, tool selector, build
configuration, debt/header queue or fold-proof owner requires updating.
The merge engine repointed the active function ledger and TU-map source
columns. Old mentions intentionally remain in the historical census
`reverse/link_status.csv`, attempt log, hashed naming votes, prior evidence
and destination provenance comments. They do not select a current provider.
The historical deleted-row destructor entry refers to the surviving shaker
file, not this fragment. Fresh destination builds and strict receipts verify
the replacement object rather than reusing the deleted source's object.
