### VslotSmallBodiesAG_Rva00131CF2 linking prerequisites (2026-10-31)

VslotSmallBodiesAG_Rva00131CF2.cpp (10 matched functions, 264 bytes) does not link due to 7 unresolved symbols:
1. `?rva00130FCE@Rva00130FCE@@QAE_NXZ` (0x00130FCE): rowed in `BfmeConv1341.cpp` as `?bfmeGoURB@BfmeThingURB@@QAEHXZ` (returns int, whereas slots 0x00131CF2 and 0x00151415 return bool; compiling a direct call to `bfmeGoURB` produces a call `e8` rather than the target tail-jump `e9 c7 f2 ff ff`).
2. `?rva0023C7F5@Rva0023C7F5@@QAEHMH@Z` (0x0023C7F5): rowed in `Rva0023C7F5Get.cpp` as `__stdcall ?Rva0023C7F5Get@@YGHHH@Z`, whereas 0x0023DAF7 calls it `thiscall` on member `+0x08`.
3. `?m@Gen_003bcb40@@QAEXH@Z` & `?buildFieldParse@Rva005C4352Base@@QAEXAAVMultiIniFieldParse@@@Z` (0x0047A69C): alias pins for the shared 3-byte `ret 4` empty base function (owned by `EmissionInfoCopyCtors.cpp` and `GameEngineInitFolded.cpp`).
4. `?g_rva005C4352FieldParse@@3QBUFieldParse@@B`, `?g_rva005C4553FieldParse@@3QBUFieldParse@@B`, `?g_rva005C47A8FieldParse@@3QBUFieldParse@@B`: data tables at 0x00874540, 0x00874630, 0x00874704 in `.rdata` which are unowned in `reverse/data_ledger.csv`.
Recorded `blocked` in `reverse/re_attempts.log`.
