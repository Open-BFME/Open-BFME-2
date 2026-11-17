# MonsterDock native table proof

This frozen snapshot inspects existing objects; no reviewer compilation, link or runtime was launched.

Native table `00851DA8`: **31/31** body/relocation comparisons exact, 124-byte source table. Monster differs from common ModuleData table `0084ED70` only at slot0.

Both seven-byte ModuleData/Dock cleanup folds match `0049B47C`: **True**. Parent current ctor+dtor owning predicate: **True**; that is not a real-link result.

| Slot | Resolved source binding | Native RVA | Extent | Masked bytes / relocations |
|---:|---|---:|---:|---|
| 0 | `??_GMonsterDockUpdateModuleData@@UAEPAXI@Z` | `0x004A1552` | 28 | True / True |
| 1 | `?loadPostProcess@ModuleData@@UAEXXZ` | `0x000B3FD0` | 1 | True / True |
| 2 | `?GetSnapshotName@ModuleData@@UBEPBDXZ` | `0x00065212` | 6 | True / True |
| 3 | `?xfer@ModuleData@@UAEXPAVXfer@@@Z` | `0x0047A69C` | 3 | True / True |
| 4 | `?isAiModuleData@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 5 | `?slot05@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 6 | `?slot06@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 7 | `?slot07@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 8 | `?slot08@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 9 | `?slot09@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 10 | `?slot10@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 11 | `?slot11@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 12 | `?slot12@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 13 | `?slot13@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 14 | `?slot14@ModuleData@@UBE?AVAsciiString@@H@Z` | `0x000B69A1` | 28 | True / True |
| 15 | `?slot15@ModuleData@@UBE_NXZ` | `0x0047A699` | 3 | True / True |
| 16 | `?slot16@ModuleData@@UBEPBXXZ` | `0x000D43D0` | 3 | True / True |
| 17 | `?slot17@ModuleData@@UBEPBXXZ` | `0x000D43D0` | 3 | True / True |
| 18 | `?getAsW3DModelDrawModuleData@ModuleData@@UBEPBVW3DModelDrawModuleData@@XZ` | `0x000D43D0` | 3 | True / True |
| 19 | `?getAsW3DPropDrawModuleData@ModuleData@@UBEPBVW3DPropDrawModuleData@@XZ` | `0x000D43D0` | 3 | True / True |
| 20 | `?slot20@ModuleData@@UBEPBXXZ` | `0x000D43D0` | 3 | True / True |
| 21 | `?getHordeModuleData@ModuleData@@UBEPBVHordeModuleData@@XZ` | `0x000D43D0` | 3 | True / True |
| 22 | `?getMinimumRequiredGameLOD@ModuleData@@UBEHXZ` | `0x000D43D0` | 3 | True / True |
| 23 | `?slot23@ModuleData@@UBEPBXXZ` | `0x000D43D0` | 3 | True / True |
| 24 | `?slot24@ModuleData@@UBEPBXXZ` | `0x000D43D0` | 3 | True / True |
| 25 | `?slot25@ModuleData@@UBEPBXXZ` | `0x000D43D0` | 3 | True / True |
| 26 | `?slot26@ModuleData@@UBEPBXXZ` | `0x000D43D0` | 3 | True / True |
| 27 | `?slot27@ModuleData@@UBEPBXXZ` | `0x000D43D0` | 3 | True / True |
| 28 | `?slot28@ModuleData@@UBEPBXXZ` | `0x000D43D0` | 3 | True / True |
| 29 | `?slot29@ModuleData@@UBEPBXXZ` | `0x000D43D0` | 3 | True / True |
| 30 | `?slot30@ModuleData@@UBE_NXZ` | `0x0050B5C6` | 3 | True / True |

Slots 2/14 are owned by `Common/SubsystemNameGetters.cpp` and `Common/Rva000B69A1.cpp`. Their current objects, full bytes, string/data references and code-callee records are in the JSON. Slot0 is weak E -> local G (SEARCH_LIBRARY=2). G is 28 bytes with REL32 calls to the existing Monster complete destructor and operator delete.

Both `ModuleData::~ModuleData` and `DockUpdateModuleData::~DockUpdateModuleData` are 7-byte ANY COMDATs with one DIR32 relocation to `??_7Snapshot@@6B@` (native `007BB554`); neither is a 5-byte tail-jump.

Layout: ModuleData is 8 bytes; Dock is 16 bytes with DWORD+8=0 and byte+C=1; Monster is 24 bytes with filter+10 and zero DWORD+14. The factory allocation and native constructor/unwind bytes are recorded.

## Reproduce

JSON includes SHA256 of every input, current dependency-receipt results, exact object/native byte offsets and extents, all COFF relocation fields, weak-default metadata, and the precise function/data/literal bindings used. The COFF parser itself is hashed. Recheck hashes before reusing the verdict. A frozen-byte recheck from the worktree root:

```python
from pathlib import Path
import hashlib,json
r=Path.cwd()
p=json.loads((r/'reverse/attempt_support/monster-dock-native-prefix-20261117-root20-native.json').read_text())
for name,x in p['inputs'].items():
    assert hashlib.sha256((r/name).read_bytes()).hexdigest()==x['sha256'],name
for x in p['slots']+list(p['cleanup_folds'].values()):
    size=x['extent']
    a=bytearray((r/x['object']).read_bytes()[x['object_file_offset']:][:size])
    b=bytearray((r/p['retail_image']).read_bytes()[x['native_file_offset']:][:size])
    assert a.hex()==x['object_bytes_hex'] and b.hex()==x['native_bytes_hex']
    for z in x['relocations']:
        k=z['offset'];a[k:k+4]=b[k:k+4]=bytes(4)
        assert z['equal'],(x['symbol'],z)
    assert a==b,x['symbol']
```

Independently reproduce semantic relocations with the recorded rules: REL32 target is native instruction-next RVA plus displacement, and must equal the exact matched-symbol row plus object addend; DIR32 targets use Snapshot table identity, a full terminated local string, or registered data-symbol RVA plus addend. The snippet checks frozen bytes and recorded verdicts; those explicit records support the independent relocation check.

## Input SHA256

| Input | SHA256 |
|---|---|
| `Code/GameEngine/Source/GameLogic/Object/Update/MonsterDockUpdateModuleDataCtor.cpp` | `c81891901042186308a946748d7a0a665e3e8a324b8e338d08c8309b886302ad` |
| `Code/GameEngine/Include/GameLogic/Module/DockUpdateModuleData.h` | `94c7c79276d04c15bf327d83152500902435f44fc801680d9be21ce681e7d415` |
| `Code/GameEngine/Include/Common/ModuleData.h` | `3abdc2564c8dce950a23d2452f4916b7b1bcb4ca6227fd0935494c5656e1e044` |
| `reference/shims/moduledata/Common/Snapshot.h` | `966b0ec30c8d777caa46df85bfc0f9013baeed17f8cc2cd1a1c4295172cf2206` |
| `Code/GameEngine/Include/GameLogic/Module/Rva003623E5Member.h` | `e6d0cff81b2ad54c5b3d6c70c6b4e8c262ce29dc713579f72acff838e8d00e46` |
| `tools/link_cycle.py` | `cf13cc812a48572626558cfff005dbb550ba1f2276748572af9ad64a1538fa9a` |
| `baselines/bfme2/workshop-vanilla-1.06/files/game.dat` | `f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640` |
| `build/match/^code_^game^engine_^source_^game^logic_^object_^update_^monster^dock^update^module^data^ctor.obj` | `50a782d47c4c7043e5ae98f483d690eb18cc6e62c791ea78ff13235bd284efc7` |
| `build/match/^code_^game^engine_^source_^game^logic_^object_^update_^monster^dock^update^module^data^ctor.deps.json` | `9c036facd8e9334bf87ea15361aeddae80677d81b78199af7911e0992badc383` |
| `build/match/^code_^game^engine_^source_^common_^subsystem^name^getters.obj` | `2209b2721a107443019df5e97528c42e127108450950dda942fff21b970477d1` |
| `Code/GameEngine/Source/Common/SubsystemNameGetters.cpp` | `ad073361268dd57c8fe63cd46ee837c958a465f205095ee64b4e3a6f1b3b12a6` |
| `build/match/^code_^game^engine_^source_^common_^subsystem^name^getters.deps.json` | `7679edd9ed9c1cd85ff24f16beae015ceda2d2a6bf7fe7915afec2d9f21c1112` |
| `build/match/^code_^game^engine_^source_^common_^rva000^b69^a1.obj` | `4bf541e81c8f7e644037dea383396d9ee958c5191abcef9411e6483e30e99ffe` |
| `Code/GameEngine/Source/Common/Rva000B69A1.cpp` | `9d4c8c3ec20ab3315a291bb7ec73cb806078a7c0c229d5b7c4a8e8abf7de47a0` |
| `build/match/^code_^game^engine_^source_^common_^rva000^b69^a1.deps.json` | `0ca2ff0957eda4c98047d6d11789b175802466fd5740c2aa4cd4d3bad576421c` |
| `build/match/^code_^game^engine_^source_^game^logic_^object_^update_^monster^dock^update^module^data^dtor.obj` | `c51c5e6160e3bcaa4cc8ca6b3e3e001a09e326cac2549c725949db97ff8fbdde` |
| `Code/GameEngine/Source/GameLogic/Object/Update/MonsterDockUpdateModuleDataDtor.cpp` | `5cea7f473e97f623bfeb631148c3bb17c8ceaa97c025427209e00b69edac38eb` |
| `build/match/^code_^game^engine_^source_^game^logic_^object_^update_^monster^dock^update^module^data^dtor.deps.json` | `c39e22478dd514e78f60c89dd7ba9080f58344ce7ec2e089376e4105a4cc30ee` |
| `build/root-monster-dock-20261117/owning-table-predicate.json` | `52930be03ba1718bddac07962b07e0981be411a0a57906bced88257ecab0b28e` |
| `reverse/class_contracts/DockUpdateModuleData.json` | `8f18d00b0e024c34efbeeb8b02396711e7ea805ce1a3fa4ba4bb109592edd520` |

Existing class-contract metadata remains an opaque-view snapshot; no metadata rewrite is claimed. Constructor live31-slot tables and final Snapshot teardown are separate phases. Global provider selection, wider acceptance and published runtime progress remain separate checks.

Slot14 data relocation agrees with the registered TheEmptyString RVA 0x009E0878; that data_ledger row is provisional. This establishes the inspected reference, not a unique global definition or whole-link data-provider result.
