### LINK-125: AptSkirmish callbacks bind a second Apt manager global

**2026-10-28 follow-up, base `f4d813d60d`, index `d92e7e6635`:**
The served unresolved lead is stale: b46f564676 already switched the consumer
back to the current TheMessageStream data-row owner, and ordinary preview
retains LINKS for 4,008 authored bytes. The existing pinned GameMessage helper
at 0x0030F936 now has a verified whole-body ICF row, retiring its pin and
present-unmatched marker. All 55 source rows and 11 EH graphs remain exact;
strict preparation also verifies the MessageStream owner (73 cohort rows and
one data row). The direct-call simplification trial changed branch layout and
was reverted. This is hatch retirement, with no census gain claimed. The after-preview remains
LINKS; its extra 19 authored bytes count the existing fold, not new coverage.
The outgoing audit is INCONCLUSIVE because the index predates the base and
Common/0CreateAHeroManager21FE49.cpp lacks a current affected-consumer receipt.
Carry this fold/provider scope into the next scheduled census.
[Evidence and remaining verification](../../reverse/attempt_support/apt-skirmish-fold-debt-20261028-codex.md).

Status: Cleared for this consumer's data bindings. Updated: 2026-10-27;
inspected revision: 2eab7a67c3; ordinary-preview index: 73061d9452.

`AptSkirmishCallbacks.cpp` used `TheRva00222A8BTarget` for the Apt manager
at RVA 0x009FE4CC. It now declares the ledger owner
`BfmeAptWindowManager *g_bfmeAptWindowManager` and casts at each call site.
The fresh-object retirement verdict also exposed `TheMessageStream` at
0x00A00950: the explicit `data_rows.csv` owner overrides the provisional
`data_ledger.csv` spelling there and names `MessageStreamSubsystem`. Both
message appends now use that owner.

Verification: all 54 rows byte-match; frozen-file and data checks pass with
zero data findings. `repair_queue.py retire data` retires the one registered
key through its own fresh-object verdict. The ordinary link preview retains
LINKS, 4,008 -> 4,008 bytes. This is debt retirement, with no linked-byte or
image-ownership gain claimed.

Remaining: other consumers and the two MessageStream definitions retain their
existing ownership work. The separate `Rva005F2FEFApt.cpp` debt remains blocked
by its previously recorded compiler-guard ownership findings at 0x00A068D8/E0;
its 43 rows still match, and no source or register change was made for it.
Census confirmation of this edit remains pending.

**2026-10-27 merge-prep follow-up (no commits possible under the standing rules):**
- motchan AdaptiveDelta donors (0x00195F60 ctor, 0x00195FF0 Load_W3D): both bodies need the retail 0x1C layout (`DataByteCount` at +0x10, no caches), but motchan.cpp compiles against the BFME1 `AdaptiveDeltaMotionChannelClass` in the vendored `game/Libraries/Source/WWVegas/WW3D2/motchan.h` (0x24 bytes; `Get_Channel_Memory_Usage` already reads +0x10 through `_bfme_adm_scale2`). Reconciling means editing that vendored header or adding a project shim header for motchan.cpp that overrides it; the `reference/shims/bfmehrawanim/motchan.h` shim has the same BFME1 layout. The `<new>` collision in AdaptiveDeltaLoadW3D.cpp disappears only together with that layout change, since the body's `new unsigned long[numInts + 1]` must stay on the array allocator.
- udp donors (0x00594976, 0x00594A06, 0x00594B2E): the ZH bodies (`SetBlocking`, `GetStatus`, `AllowBroadcasts`, GeneralsMD udp.cpp:210/330/504) are the obvious names, but `rename.py function --basis canonical:zh` refuses: name_evidence has no zh-body placement at these RVAs (the ZH sweep, 27,011 records, places the UDP COMDATs elsewhere or not at all), and `inferred` needs a two-agent agreement record. udp.cpp's `/alternatename` for GetStatus already reflects the same gap. Not renamed.
- matpass: the two flag-override donors (MaterialPassClassDestructor `/G7`, MaterialPassInstallMaterials `/O2 /G7 /arch:SSE`) disagree with matpass.cpp's flags, so they cannot share the TU without a per-function optimize pragma; the ctor thunk's placeholder fields `m_28/m_2c/m_30/m_34` (8 stage wrappers then four fields) have no counterpart in the ZH `MaterialPassClass` layout matpass.cpp includes; the two Rva0013EE* donors have no baseline match.

2026-11-01 material-pass follow-up (`5aaa45b`): the
[native-lifetime and compiler-profile proof](../../reverse/attempt_support/matpass-consolidation-20261101/readme.md)
maps those tail offsets to shader/material/enable/cull fields, but confirms
that the pristine header's raw texture pointers lack native's eight owning
wrapper lifetimes. G7 fixes the getter's INC/ADD mismatch and preserves two
seed rows, while breaking its existing 39-byte Set_Material row. Mechanical
view reconciliation passes 13 strict rows but enables no merge; all source
trials are restored. Native class/lifetime and coherent profile recovery remain
prerequisites. The earlier pragma suggestion is not used; no hatch, row, source
move or census gain is introduced.

**SelectionXlat declaration prerequisites (2026-11-01, `085274ce70`):**
[The scoped ABI and alias repair](../../reverse/attempt_support/selection-tu-prerequisites-20261101/readme.md)
aligns the wrapper's private header spelling with its existing public native
provider and removes a collision between integer-map and boolean-hash-map
aliases. All 17 cohort rows verify, 72 changed-source code definitions and their
relocations remain identical, and four previews retain all 634 authored bytes.
The supported dry run now accepts the callback wrapper into the seed. Applying
the merge requires the whole TU input scope, whose large translation donor is
reserved by another worker; no claim check is bypassed. The boolean-map donor
compiles but still fails bytes; constructor and include/view prerequisites also
remain. The seed's existing shadow 42FFC0 constructor-identity finding is
unchanged. No source-file reduction, linked gain or census clearance is claimed.

The subsequent allocator-lifetime prerequisite removes the boolean donor's
declaration-only empty allocator destructor. Its 63-byte body stays exact; the
previous merge failure was the seed's 42FFC0 constructor growing 64 -> 72 bytes.
The supported dry run now accepts both small donors with the seed and keeps the
link guard clean. Their absorption remains pending the whole-TU reservation;
no source-file reduction is credited before application.

**Browser GUID ownership repair (2026-11-01, control `821bd9d380`):**
[The paired COM proof](../../reverse/attempt_support/browser-guid-ownership-20261101/readme.md)
binds both CreateInstance copies to the existing IUnknown and browser IID
owners. All eight rows and the initialization EH graph remain exact; all 27
external code definitions retain their raw bytes, with only GUID relocation
names changing. The 141-byte copies now agree symbolically and both units
retain LINKS, 912 -> 912 authored bytes against `0d24c60eef`. The owning data
tool retires the initialization unit's one wrong-name key. Earlier one-sided
trials are superseded only for this paired scope. No new global, pin, code row,
census gain or image-ownership receipt is claimed; wider consumer audit remains
the publication boundary.
