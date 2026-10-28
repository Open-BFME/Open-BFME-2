# Slot-nine filter ownership prerequisite

Inspected `ee6402fcd2` on 2026-10-28. No game source or ledger changed.

`./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/Rva000FDCD7Get.cpp`
passes its one 26-byte row at `0x000FDCD7`. `find_declared_unmatched.py`
reports all definitions matched. The ordinary `link_check.py` index fetched
at `d92e7e6635` (2026-10-28 15:58) reports one unresolved symbol:
`?g_00DB5BD4@@3VRva000FDCD7Filter@@A`. This is a prediction, not a new census.

Target facts: the body calls `W3DShaderManager::canRenderToTexture`, then
stores VA `0x00DB5BD4` in slot nine of `W3DFilters` when that succeeds. Its
current source declares an incomplete filter class and an external object;
it supplies no storage or initialized vtable for that object.

The inferred `reverse/data_ledger.csv` interval at RVA `0x009B5B88` is 144
bytes and unowned. It is not the matched data register: the corresponding
entry in `reverse/data_rows.csv` owns only four bytes under
`BfmeScreenTransitionSwapCounter`, from `ScreenFilterRva000FC63DSet.cpp`.
The surrounding inferred interval therefore proves neither the filter's
extent nor its initialized contents. LINK-007's 2026-10-26 filter-root audit
already records this distinction; LINK-020's older split-only advice was stale.

Next work requires independent evidence for the complete filter object and
its initialized virtual table, followed by ordinary data ownership and link
verification. No artificial storage, alias or duplicate global was added.
