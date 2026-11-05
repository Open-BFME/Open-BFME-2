# Save-game record header adoption

Inspected revision: `ed9b9b320f`; worker: `yasinschroeder-codexb5`.

Five units now include the existing registered
`Code/GameEngine/Include/GameClient/TreeHintOpaque0043671B.h`, removing their
private definitions of the outer record and its `BfmeSubobject0022CE19` member:

- `Code/GameEngine/Source/Common/GameEngineExecuteRva0022D290.cpp`
- `Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB06.cpp`
- `Code/GameEngine/Source/Common/System/SaveGame/GameStateLoadGame.cpp`
- `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptSaveLoad.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/stlport_list_treehintopaque_00436e3b.cpp`

The two load-game consumers reference the canonical fields at the same offsets.
The list unit explicitly defines the already-rowed assignment operator at
RVA `0x00401F76`: UnicodeString assignment, owning subobject assignment, then the
two trailing words. Merely swapping the declaration loses the former implicit
operator body; the explicit definition byte-verifies all 57 bytes. The shared
headers, identities, pins, aliases and ledger rows are unchanged.

## Verification

- `python3 tools/check_csv.py`: passes before work.
- `find_declared_unmatched.py`: passes for all five files before and after edits.
- Scoped `./build.sh` runs: 32/32 rows across execute/deleting-dtor/list units,
  15/15 load-game rows and 60/60 AptSaveLoad rows pass (107 rows total).
  Data, string, float and import checks also pass; compiler-renumbered funclets
  verify through their parent EH data.
- `header_adopt_lane.py accept --class TreeHintOpaque0043671B` passes for each
  of the five files and itself retires exactly their five header-queue entries.
- Combined ordinary link preview: 5/5 LINKS, 7,006 -> 7,006 authored bytes,
  using the published index at `c95fcfcfcd`, 2026-11-05 05:17. This preserves
  preview linking; it is not a census measurement or a headline linking gain.
- `git diff --check`: passes.

## Remaining cohort

Nine queued consumers remain unchanged. Their automated adoption trials refuse
partial layouts: the copy provider and two AptSaveLoad destructor units expose
individual fields hidden by the canonical subobject's opaque storage; four
multiplayer/LAN units expose slots/digest within the outer record's nested
storage. They need source-local access views with independently established
offsets, or evidence-backed recovery of the nested layout. The two other
MpGameSetupSlots units report C1083 during layout probing; diagnose the exact
missing include before treating those as structural adoption failures. No
nonmatching reconstruction remains in Code/.

The source transformer also conservatively refuses the execute macro's line
splices and field-name collisions in the load-game consumers. The direct edits
above preserve unrelated names/macros and pass the normal acceptance gate.
AptSaveLoad's layout-probe C1083 did not recur in its ordinary build or acceptance.

## Combined link preview

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/GameEngineExecuteRva0022D290.cpp: LINKS  LINKED 1,395 -> 1,395 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 1,395)
Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB06.cpp: LINKS  LINKED 820 -> 820 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 820)
Code/GameEngine/Source/Common/System/SaveGame/GameStateLoadGame.cpp: LINKS  LINKED 1,169 -> 1,169 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 1,169)
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptSaveLoad.cpp: LINKS  LINKED 3,390 -> 3,390 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 3,390)
  diagnostic  ?deallocate@?$allocator@U?$_List_node@UTreeHintOpaque0043671B@@@_STL@@@_STL@@QBEXPAU?$_List_node@UTreeHintOpaque0043671B@@@2@I@Z  (codegen-like: 21 bytes against the majority copy's 20; unreferenced, not a blocker)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAU?$_List_node@UTreeHintOpaque0043671B@@@_STL@@U12@V?$allocator@U?$_List_node@UTreeHintOpaque0043671B@@@_STL@@@2@@_STL@@QAEXPAU?$_List_node@UTreeHintOpaque0043671B@@@2@I@Z  (codegen-like: 21 bytes against the majority copy's 20; unreferenced, not a blocker)
Code/Libraries/Source/WWVegas/WWLib/stlport_list_treehintopaque_00436e3b.cpp: LINKS  LINKED 232 -> 232 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 232)
link_check: 5 of 5 link cleanly; LINKED 7,006 -> 7,006 bytes (5.6s)
```
