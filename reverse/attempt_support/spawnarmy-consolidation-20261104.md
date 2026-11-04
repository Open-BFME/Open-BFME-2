# SpawnArmy consolidation, 2026-11-04, codex5

Inspected revision: `5001bb6e79`. Census index: `5a13f2cd61`,
2026-11-04 02:25. These are local checks, not a new census or real-link run.

The current-map merge planner approves the 34-byte body at `0x004E2CD5`
for `Code/Libraries/Source/WWVegas/WWLib/SpawnArmy.cpp` by provisional
range evidence `C=0x004E265F..0x004E2CF7`. This does not establish the
original retail filename. The naming evidence planner instead groups the
seed with LivingWorldCampaignObjects for investigation; that suggestion
does not authorize moving the seed's other rows there.

Prerequisites and applied move:

- The contains helper only passes `StringBase<char>` pointers/references.
  Replacing its private class body with a forward declaration keeps its
  34 bytes exact and permits composition with the seed's string header.
- At `0x004E18A2`, retail's conditional tail call targets `0x00050ED3`.
  The seed now uses canonical `OpaqueRefCounted::Release_Ref` directly.
  The link-wide PoolMember alias and pin remain for other consumers.
- `tu_skeleton.py --merge` accepts the seed and the contains donor,
  deletes `Common/Rva004E2CD5Contains.cpp`, and repoints exactly its one
  function row and TU-map source cell. No regenerated map is committed;
  the tool rebuilt the stale map in memory from current inputs.

Verification and path audit:

- `./build.sh SpawnArmy.cpp`: 68/68 code rows and seven data rows exact;
  seven string literals verified. Frozen-file check passes.
- Code identity: 68 rows, zero new findings (shadow). Data identity:
  zero findings. CSV integrity passes with 99,433 function rows unchanged.
- Link previews: seed 2,774 bytes plus donor 34 bytes before;
  merged seed 2,808 bytes after. Both original units linked in the index.
  The merge's link guard accepted this composition. No linking gain claimed.
- No removed-source keys occur in the header, Microsoft-header, identity,
  data, flags, gate or hatch registers. Header transfer preserves the
  seed's existing adoption debts. The owning Microsoft-header scan refreshed
  the destination and found zero local Microsoft-name definitions; neither
  queue changed. The merge's hatch update leaves its register unchanged.
- Old-path and basename search covered Code, tools, hooks, workflows,
  reverse, docs and build.sh. Remaining references are the seed's provenance
  comments and census-generated `reverse/link_status.csv`; no active path
  consumer needs updating. Source files decrease by one (18,494 to 18,493
  in this checkout's tracked index).
- Batch audit against the staged tree is **INCONCLUSIVE**: the census base
  predates HEAD, and strict current receipts are missing for SpawnArmy.cpp
  and its direct contains-helper consumer Common/Glo012F1024Item.cpp.
  Carry both into the next scheduled census. The per-unit preview above
  does not establish a clean outgoing batch or verified downstream consumers.

Remaining merge prerequisites (no edits to these rejected donors):

- `Rva004E20ABEqual.cpp`: composition would select non-retail
  `?compare@AsciiString@@QBEHABV1@@Z`, breaking another unit's selected copy.
- `Rva004E35D5Notify.cpp`: composition introduces unresolved
  `??$?MD@@YA_NABV?$StringBase@D@@0@Z` and a wrong first
  `less<AsciiString>::operator()` COMDAT.
- Resolve those declaration/inline-overload bindings before retrying their
  merges; preserve the existing standalone linked units meanwhile.
- The other 17 donors still fail compilation or byte checks. In particular,
  the supported view planner refuses Rva004E32F2: the seed's eight-byte
  `m_head0C` at +4 overlaps the constructor donor's four-byte `m_04`.
  Reconcile that view using target layout evidence before another attempt.
