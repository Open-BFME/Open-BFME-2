# UnitRevivalEntry pre-existing shadow identity finding

2026-11-04, follow-up to the header adoption published as `2a64e75991`.
The commit hook passed but reported one outside-register shadow finding in
`UnitRevivalTrackerRva0037F2C0Finish.cpp`: the row at 0x0037F2C0 references
vector<UnitRevivalEntry>::push_back, bound by symbols.csv to 0x002E2D10.

To distinguish a new regression from existing debt, temporarily restored this
source from the adoption commit's original parent (`9c3bffffe2^`), verified it
with normal `./build.sh`, and ran `allowed_symbols.py --source` on it. Then
restored the adopted source in a finally block and verified it again with
normal `./build.sh`. No direct build.compile_source invocation was used.
Ran the same identity scan on the adopted source and compared the entire
source-scoped refs.tsv with cmp: identical (exit 0). Both scans report:

```text
references: 5
  owner      3
  eh         1
  wrong      1
rows with a wrong binding: 1
  wrong/unknown: 1
```

The identical non-owner reference record is:

```text
source	row	row_rva	offset	kind	symbol	target	class	detail
Code/GameEngine/Source/Common/RTS/UnitRevivalTrackerRva0037F2C0Finish.cpp	?rva0037F2C0@Rva0037F2C0@@QAEHPAVObject@@_N@Z	0x0037F2C0	59	REL32	?push_back@?$vector@VUnitRevivalEntry@@V?$allocator@VUnitRevivalEntry@@@_STL@@@_STL@@QAEXABVUnitRevivalEntry@@@Z	0x002E2D10	wrong	unknown
```

`wrong/unknown` is this classifier's unverified-kept-copy result; it is not a
proof that these edits select different bytes. The finding predates adoption.
No code-identity register entry was added or retired. Existing ordinary link
preview still preserves 423 bytes; no new census or real-link claim is made.
Remaining identity check: establish the kept push_back copy's retail equivalence
or bind the call to the existing 0x002E2D10 owner through its real declaration.
