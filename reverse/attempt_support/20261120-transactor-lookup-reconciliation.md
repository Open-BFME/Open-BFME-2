# Served item005: isolated Seed + Lookup reconciliation, 8/8 strict

Sicher: the attached two-source prerequisite preserves every currently rowed body in both complete source files and their joint composition. It supports a regular partial consolidation of exactly one donor. It does not finish all served item005 donors: the414B reply donor remains explicitly blocked and excluded.

## Root integration package

`transactor-lookup-only.patch` changes only:

1. `Code/Libraries/Source/Fesl/transactor.cpp`
2. `Code/GameEngine/Source/GameNetwork/FeslTransactor_lookup_rva007F9530.cpp`

No header, contract, flag, gate, alias, pin, ledger, register, claim or Git state was edited by this worker. The patch was generated against raw current worktree bytes with preserved CRLFs. `transactor-lookup-inputs.json` binds source/header SHA256s. Root holds all productive scopes centrally. The patch contains normal source reconciliation, not hand-written row/path movement.

The Gen007F0130 candidate and the3-source/9-row experimental sources are NOT part of this package. Do not apply `*-transactor-proposed.cpp` or the experimental Gen007F0130 header; only `transactor-lookup-only.patch` is proposed.

## Native measurements

All compilations used native `tu_skeleton.Verifier` with explicit unique private objects under `build/codex-thing-agent-20261120/transactor-lookup/`. No ordinary match-cache object/receipt was used or forged. Actual directives remain unchanged: seed `/GX- /GS-`, lookup `/O2 /GX- /GS-`, ordinary compiler baseline/O2. The combined native carried override is the seed's empty managed override, without editing the register. The tool already normalizes a leading duplicate baseline-O2 through `override_flags_key`; the old historical flag rejection is not the current obstacle.

| Full native source control | Rows | Result |
| --- | ---: | --- |
| Original seed |7|7/7 strict |
| Original lookup |1|1/1 strict |
| Proposed seed, including real Rva00802A10 adoption |7|7/7 strict |
| Proposed lookup |1|1/1 strict |
| Native composed Seed + Lookup |8|8/8 strict |

Every accepted row has `masked=false`, `unresolved=[]`, exact full size. The eight rows are00665A70/84B allocator,00665B80/33B release,00665BD0/55B deleting helper,00665B30/46B timeout stamp,00665C30/233B txn dispatch,00665BB0/25B fields ctor,00665B70/13B ctor and00665AD0/71B lookup. Total560 existing bytes retained; zero new authored or measured LINKED bytes.

`transactor-lookup-private-measurements.json` records complete per-row outcomes, exact object paths and effective source hashes. `transactor-lookup-code-footprints.json` compares every emitted external function: seed7->7 and lookup1->1, no added/removed/changed body, hash or relocation list. This is stronger than keeping only one primary function, but still does not replace root's current ordinary build, class/adoption verdict or link preview.

## Field and ABI matrix

Fresh CodeView was compiled from both full original and both full proposed sources, using the native class-layout compiler with an explicit private cache/output. `transactor-lookup-codeview.json` retains complete records; no synthetic stand-alone class provided layout votes. Complete current retail decodes are `transactor-retail-*.decode.log`.

| Storage | Original seed / lookup | Reconciled view and independent native evidence |
| --- | --- | --- |
| Owner visible extent |0x28 seed prefix;0x6A8 lookup prefix |Both private views now reach0x6A8. This is the last witnessed field extent, not proof of the actual allocation size; other existing operations access+6A8/+6AC. No owner object is allocated or sized by the edited bodies. |
| Owner+10 |seed padding; lookup int m_count |int m_count. Complete71B lookup compares signed index against[ebx+10] (`jge`), records begin via `lea ...,+3A8`. |
| Owner+14 |int m_14; lookup padding |Same int m_14. Complete233B txn increments/decrements it around callback dispatch. |
| Owner+18 |unsigned m_watermark; lookup padding |Same unsigned watermark.46B stamp performs native unsigned minimum comparison and stores it. |
| Owner+20 |void* m_20; lookup padding |Preserved unchanged; txn passes it as vslot4's first four-byte argument. |
| Owner+24 |Rva007F96C0Hub* m_24; lookup padding |Same exact pointer type, renamed m_hub. Complete txn loads+24 then calls vslot4; reply and710B handler independently locate the hub at the same owner+24. The existing descriptive hub role is retained without claiming a real EA class identity. |
| Owner+28..+3A8 |lookup padding |Padding remains. Read-only handler evidence separately proves32 request slots of0x1C beginning+28, ending+3A8; this package does not invent named members for them. |
| Owner+3A8 |lookup record[32]; seed no typed view |Same32 records, each0x18; complete lookup advances by0x18 and bounds by count.84B seed allocator independently writes the first active byte at the same pool base/stride. |
| Record+00 |char m_00 / char m_active |char m_active, byte-compare in lookup. No code in the seed accessed m_00 by name. |
| Record+01..+04 |char padding[3] |Preserved padding. |
| Record+04..+10 |seed3 opaque4B fields; lookup12B key |Existing Rva007F9A40Key m_key. Actual complete matches callee0065D0B0/187B is in `Common/SmallGaps/Rva007F9A40GetOrCreateSlot.cpp`: strcmp word0, int word8, strcmp word4. The lookup passes exactly record+4 as const key. Its source key fields and method name are retained. |
| Record+10 |cdecl function pointer / void* |Existing typed fn from seed. Complete txn pushes context and message, indirect-calls[record+10], then performs caller cleanup8. No invented callback alias/pin. |
| Record+14 |void* ctx / void* |Existing ctx from seed. Full txn loads[record+14] as the callback context. |

Record CodeView is24B before/after in both files. Key is12B. New owner field positions are identical in the two proposed TUs: count10, depth14, watermark18, context20, hub24, records3A8. The original seed's first20-byte padding simply becomes16-byte padding plus the lookup's already witnessed count. Baseless/nonpolymorphic owner and record layouts stay baseless/nonpolymorphic; no fabricated vtable or guessed full class name is introduced.

The shared hub definition itself is unchanged in this isolated package: existing Rva007F96C0Hub vslots0..4, with v4 returning the existing object pointer and taking(void*,message*). No reply v8 or handler object is copied into this source merely to make it compile. Full9-slot reconciliation belongs to the excluded reply follow-up, with its independent evidence.

## Actual Rva00802A10 prerequisite

The seed's sole `adopt_first` row is handled by replacing its empty method-only `class Rva00802A10 { public: void clear(); };` with the existing canonical `Code/GameEngine/Include/GameNetwork/Rva00802A10.h`. That header currently needs `class Rva00802A10Elem;` before inclusion; the prerequisite puts that declaration in the seed, without changing the header.

The seed only declares the related forwarding owner and clear method; it emits no Rva00802A10 constructor/vtable or additional code. All seven actual emitted functions remain byte/relocation-identical. Thus this does not introduce a SurfaceClass-like default-constructor COMDAT choice. Root should run ordinary `header_adopt_lane.py accept --class Rva00802A10 Code/Libraries/Source/Fesl/transactor.cpp` after applying the source prerequisite; no queue row is retired by this worker.

## Reply remains a separate blocker

The private9-row composition used physically supported shared views, canonical Message data fields, and an experimental Gen007F0130 field/header shape solely to locate the next obstruction. It kept the414B extent and all calls resolved but differs at exactly5 non-relocation positions+6E..+72. Current retail spells `mov ebp,eax; mov eax,[edi+14]; push eax`; the canonical direct-field source instead reloads intoEDX before movingEAX toEBP. No more old flag/alias/volatile variants were tested.

There is also a concrete normal generator-admission limitation. The current Gen007F0130 contract records14 views:13 empty1B allocation-only views and one12B reply view. It explicitly lists+4/+8 as outliers and generates pad4[8]. Adding physically witnessed fields cannot simply hand-edit that generated header. Pure invocation of the actual native admission `_elide_header` on the UNCHANGED header refuses both its original contract and a hypothetical expanded contract with `canonical declaration has an unsupported scope, alias, intrinsic or type role`; its static operator-new declaration is outside the current narrow native admission. The existing array padding is also outside that admission's primitive/pointer-only input grammar. `transactor-reply-generator-refusal.json` retains the actual refusal. This is a private native parser-path reproduction, not a claim that the side-effecting full registered-generation CLI was run. No generator/header/gate/contract change is proposed here.

The earlier speculation that the first refusal would be assertion mismatch was superseded by this measured earlier lexical refusal. Updating the contract alone would not make the current baseline a supported native regeneration input. Leave this as evidence and preserve all productive canonical files.

## Mixed files and root completion boundary

The latest normal plan reports two mixed sources: InlineDtorDeletingDtors2.cpp has26 foreign rows; stlport_basic_ios_init.cpp has12. Their transactor-related7/31B destructor and10B STL member rows do not authorize absorbing all their other-TU bodies. They remain outside this patch and outside the proposed partial merge. No hand split or manual row move is suggested.

Root can verify/stage the two-source prerequisite as its own change, run normal header acceptance for the actual seed adoption, then let regular tu_skeleton dry-run/merge select only the truly accepted donor. Run the normal complete-TU build and declared-unmatched check plus current link guard; only the native merger may move rows/register keys and remove the lookup donor. With that actual native outcome, report exactly1 file removed; the original served2-donor item is not complete while reply remains unabsorbed.

## Root normal prerequisite checks

The two ordinary source builds pass8/8 rows and6 literals. Native header
acceptance for Rva00802A10 passes the seed and retires exactly its one header
queue row. Shared headers, original flags and the reply source remain
unchanged. Full served-item completion is still open pending native merger
results and the excluded reply blocker.

## Root native partial merge and consumer audit

The normal tu_skeleton merge accepts exactly the seed and lookup and removes
FeslTransactor_lookup_rva007F9530.cpp. All8 rows pass the ordinary merged-TU
build with6 literals; declared-unmatched reports no remaining definition.
The reply donor and both mixed files stay. Only the native merger repoints
the existing row, its map source column and existing flag bookkeeping.

This batch has one absorbed source path. The exact old-path/basename audit
finds two intentionally retained references: the native merger's '// ----
from' provenance comment, and the previous census's reverse/link_status.csv
measurement. Neither is an active source include/tool input requiring a
rewritten path. The measured census is preserved; link_check --update-index
refreshes the live provider index after this commit. No other old-path
consumer appears in Code, tools, hooks, workflows or CSV/TSV registers.

The merger's normal link guard preserves census-linked source bytes. This
is one removed fragment, not completion of the original two-donor item,
new linked-byte coverage, a full-image link or runtime verification.
