# Carryover parent migration — bounded handoff

No tracked source/tool/ledger edits, normal/shared compilation, claims or
network were performed. Root owns application and publication. The private
proofs use Verifier with local rows/symbol maps only.

## Ready ordinary source prerequisite

Apply `seed-order-qualified.raw.cpp` to the existing
`Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp`, normal
verify, and commit this reconciliation separately before header adoption:

1. Move the existing explicit `_Destroy<Rva001ED0DE>` instantiation after the
   complete Rva001ED0DE declaration. The current owning layout probe truncates
   the source at the earlier CarryoverUnit view; previously it retained the
   instantiation but dropped the class definition, producing C2027 in
   `_construct.h`. This changes ordinary declaration ordering, not the check.
2. Qualify the one quantity member access as
   `carryovers[i].CarryoverUnit::m_quantity = 1;`. It names its actual declaring
   class without materializing a pointer/reference, and the existing owning
   scoped renamer can prove it. A local reference was rejected as a candidate
   because it added one byte in beginCampaign; it is not recommended.

`qualified-ordering-proof.json` proves **47/47 old rows, all73 complete external
code definitions and14 data definitions unchanged**, with seven EXACT EH
graphs. No definition/name/relocation is added or lost. The owning layout
prefix now compiles. `raw-candidate-proof.json` attests that the raw candidate
preserves the original BOM/line endings and matches the privately verified
text; source remains unchanged.

## Owning header workflow

After the prerequisite normal commit, use the supported source-filtered trial:

```
python3 tools/header_adopt_lane.py adopt --class CarryoverUnit --header Code/GameEngine/Include/GameLogic/CarryoverUnit.h Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp
```

Then the same command with `--apply`, followed by:

```
python3 tools/header_adopt_lane.py accept --class CarryoverUnit Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp
```

Root has refreshed86 conservative `resize` witnesses (2502 rows/49 data), so
the earlier broad stale/missing-object fallback is cleared. Do not manufacture
receipts or remove the dependency checks. Re-run the owning discovery normally;
keep any new real consumer constraints.

The private canonical candidate is
`seed-order-qualified-canonical.raw.cpp`. This is evidence for the owning
operation, not an instruction to apply the header swap manually. It removes the
old struct, includes the canonical class and maps quantity+90 to m_90. It adds
no private canonical view or opaque-field copy.

Exactly two ledger names change through the owning tool:

- resize1EC9BD/112B: `?resize@Rva001EC9BDVector@@QAEXIUCarryoverUnit@@@Z`
  becomes `?resize@Rva001EC9BDVector@@QAEXIVCarryoverUnit@@@Z`.
- Its10B `__ehhandler$` name changes with the same parent spelling.

Four incidental vector accessors also change U→V names; after that same
class-key rebinding, **all73 external code and14 data definitions remain
identical**, with seven EXACT EH graphs and no added/lost provider. Native
Snapshot retains its existing selected four-slot profile and storage; the
canonical header adds no new fifth crc slot, table or field.

One private row lookup remains76A670/8B because its global parent row is still
the original U spelling during a private local-row probe. The EXACT new resize
EH graph independently places actual compiler label `$L10975` at76A670.
Normal owning application supplies globally renamed rows and normal funclet
resolution; root must verify the row and metadata normally. If it refuses,
bank that concrete refusal rather than editing/bypassing the check. No tombstone
is needed for a same-address/same-size owning class-key rename; preserve the
generated funclet's actual parent/EH provenance through its owning tools.

## Actual parent/overflow placement and next concrete gain

Fresh in-memory evidence in the preceding helper packet explicitly approves
fill1EBEAB/286B and overflow1EBD3B/191B to this LinearCampaignManager TU;
76A5CC/11B and76A5D7/10B follow fill's parent. Refresh that mapping again after
relevant inputs change before admitting/moving these rows. The old WWLib
one-function files are not approved landing homes for new typed parent rows.

Once seed adoption passes, privately instantiate/implement the real
vector<CarryoverUnit> parent in the approved seed using the already admitted
typed assignment, Construct, fill, backward and uninitialized providers.
Keep the old differently typed owners and callers initially. Check complete
286B parent, its entire EH graph, the191B overflow and every extra allocation/
clear/destruction helper; declaration-only suppression of an unverified helper
is not a repair. Native overflow still requires allocate1EAEBD/31B,
clear1EB9C8/30B and range destruction1EAF5E/29B; they are current existing
providers, not permission to hand-pin new typed names. Seed compiler/profile
compatibility remains to be measured, not inferred from the small source.

An independently proved typed parent can be admitted with `add_match
--icf-owner` directly in the approved seed, retaining the original row in its
old source. This adds an actual provider without a blanket class rename into
the already canonical CarryoverUnit name. A subsequent supported TU merge
must still use `tu_skeleton.py`; reconcile old declaration-only specialization
and profile conflicts first in verified source commits, never hand-merge a
split file. The immediate smaller debt gain is accepting the seed's header
queue entry; link-byte gains require the ordinary affected-consumer preview
and eventual census.

## Retirement after consumers migrate

The historical ArmySummary cleanup is already complete and its old approval
is not a new approval for this family. Its useful sequence was provider
coexistence first, caller migration second, exact obsolete-row/pin retirement
last. No global placeholder→existing-class rename is needed here.

Current old-element consumers are the seed's resize and the5B insert owner in
WWLib/StlportVectorClearForwarders.cpp, plus the old fill source itself. After
verified typed callers replace them, audit actual outside references again.
Only then prepare an exact byte-preserving `ledger_io.rewrite` plan for the
superseded real function rows, with `deleted_rows.csv` tombstones for removed
claims, appropriate register retirement and the owning hatch update for the
seven unused element pins. Existing placeholders are not deleted by
`add_match --replace-rva`; it correctly refuses real non-scaffold rows. Never
relabel them as scaffolds to bypass that refusal. Retained providers and the
original raw CSV records/terminators must stay unchanged.

No proposed parent edit has been applied. Ready source prerequisite and
canonical proof are bounded, independent evidence; the remaining normal
ownership/link/funclet checks still decide what may land.
