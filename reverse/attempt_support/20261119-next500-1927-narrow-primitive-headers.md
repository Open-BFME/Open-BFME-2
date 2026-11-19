# Narrow existing primitive declarations

The nine existing EA aggregate aliases keep their names, primitives and order. The representative aggregate control preserves its complete native type graph, ordinary runtime, weak bindings and COMDAT contracts. Normal full-game header gates remain mandatory. Original broader providers stay intact. Headers and this control count zero tasks.

Other source-backed families consolidate unanimous existing primitive declarations without inventing a semantic identity. Incompatible aliases stay unchanged. Win32 leaves preserve target-side compatibility declarations. The EA wchar_t spelling of WideChar must independently retain each original native unsigned-short contract.

|Type|Header|Verified direct consumers|Basis|
|---|---|---:|---|
|BOOL|`Code/GameEngine/Include/Common/ScalarTypes/Win32/BOOL.h`|4|Existing target-side Win32 compatibility declarations; no addresses or runtime definitions|
|BYTE|`Code/GameEngine/Include/Common/ScalarTypes/Win32/BYTE.h`|1|Existing target-side Win32 compatibility declarations; no addresses or runtime definitions|
|BfmeUInt32|`Code/GameEngine/Include/Common/ScalarTypes/Source/BfmeUInt32.h`|3|Unanimous existing target-source primitive declarations; no target header already defines this name. Each consumer must independently preserve its entire native type graph, ordinary runtime and binding witness. This is source consistency, not a newly recovered semantic identity.|
|Bool|`Code/GameEngine/Include/Common/ScalarTypes/Bool.h`|23|Existing EA basetype.h declaration and current source primitive contracts|
|Byte|`Code/GameEngine/Include/Common/ScalarTypes/Byte.h`|0|Existing EA basetype.h declaration and current source primitive contracts|
|Char|`Code/GameEngine/Include/Common/ScalarTypes/Char.h`|0|Existing EA basetype.h declaration and current source primitive contracts|
|DWORD|`Code/GameEngine/Include/Common/ScalarTypes/Win32/DWORD.h`|7|Existing target-side Win32 compatibility declarations; no addresses or runtime definitions|
|FeslInt64|`Code/GameEngine/Include/Common/ScalarTypes/Source/FeslInt64.h`|17|Unanimous existing target-source primitive declarations; no target header already defines this name. Each consumer must independently preserve its entire native type graph, ordinary runtime and binding witness. This is source consistency, not a newly recovered semantic identity.|
|HRESULT|`Code/GameEngine/Include/Common/ScalarTypes/Win32/HRESULT.h`|1|Existing target-side Win32 compatibility declarations; no addresses or runtime definitions|
|Int|`Code/GameEngine/Include/Common/ScalarTypes/Int.h`|33|Existing EA basetype.h declaration and current source primitive contracts|
|Int64|`Code/GameEngine/Include/Common/ScalarTypes/Int64.h`|1|Existing EA basetype.h declaration and current source primitive contracts|
|LONG|`Code/GameEngine/Include/Common/ScalarTypes/Win32/LONG.h`|1|Existing target-side Win32 compatibility declarations; no addresses or runtime definitions|
|LocomotorSurfaceTypeMask|`Code/GameEngine/Include/Common/ScalarTypes/Source/LocomotorSurfaceTypeMask.h`|4|Unanimous existing target-source primitive declarations; no target header already defines this name. Each consumer must independently preserve its entire native type graph, ordinary runtime and binding witness. This is source consistency, not a newly recovered semantic identity.|
|PEERBool|`Code/GameEngine/Include/Common/ScalarTypes/Source/PEERBool.h`|4|Unanimous existing target-source primitive declarations; no target header already defines this name. Each consumer must independently preserve its entire native type graph, ordinary runtime and binding witness. This is source consistency, not a newly recovered semantic identity.|
|Real|`Code/GameEngine/Include/Common/ScalarTypes/Real.h`|11|Existing EA basetype.h declaration and current source primitive contracts|
|Short|`Code/GameEngine/Include/Common/ScalarTypes/Short.h`|3|Existing EA basetype.h declaration and current source primitive contracts|
|UINT|`Code/GameEngine/Include/Common/ScalarTypes/Win32/UINT.h`|3|Existing target-side Win32 compatibility declarations; no addresses or runtime definitions|
|ULONG|`Code/GameEngine/Include/Common/ScalarTypes/Win32/ULONG.h`|1|Existing target-side Win32 compatibility declarations; no addresses or runtime definitions|
|UShort|`Code/GameEngine/Include/Common/ScalarTypes/Source/UShort.h`|2|Unanimous existing target-source primitive declarations; no target header already defines this name. Each consumer must independently preserve its entire native type graph, ordinary runtime and binding witness. This is source consistency, not a newly recovered semantic identity.|
|Uint|`Code/GameEngine/Include/Common/ScalarTypes/Source/Uint.h`|3|Unanimous existing target-source primitive declarations; no target header already defines this name. Each consumer must independently preserve its entire native type graph, ordinary runtime and binding witness. This is source consistency, not a newly recovered semantic identity.|
|UnsignedByte|`Code/GameEngine/Include/Common/ScalarTypes/UnsignedByte.h`|2|Existing EA basetype.h declaration and current source primitive contracts|
|UnsignedInt|`Code/GameEngine/Include/Common/ScalarTypes/UnsignedInt.h`|13|Existing EA basetype.h declaration and current source primitive contracts|
|UnsignedLong|`Code/GameEngine/Include/Common/ScalarTypes/Source/UnsignedLong.h`|1|Unanimous existing target-source primitive declarations; no target header already defines this name. Each consumer must independently preserve its entire native type graph, ordinary runtime and binding witness. This is source consistency, not a newly recovered semantic identity.|
|UnsignedShort|`Code/GameEngine/Include/Common/ScalarTypes/UnsignedShort.h`|7|Existing EA basetype.h declaration and current source primitive contracts|
|WORD|`Code/GameEngine/Include/Common/ScalarTypes/Win32/WORD.h`|1|Existing target-side Win32 compatibility declarations; no addresses or runtime definitions|
|WideChar|`Code/GameEngine/Include/Common/ScalarTypes/WideChar.h`|21|EA basetype.h typedef wchar_t WideChar; native compiler must independently prove unsigned-short identity in every consumer|
|WindowMsgData|`Code/GameEngine/Include/Common/ScalarTypes/Source/WindowMsgData.h`|7|Unanimous existing target-source primitive declarations; no target header already defines this name. Each consumer must independently preserve its entire native type graph, ordinary runtime and binding witness. This is source consistency, not a newly recovered semantic identity.|
|uint8|`Code/GameEngine/Include/Common/ScalarTypes/Source/uint8.h`|3|Unanimous existing target-source primitive declarations; no target header already defines this name. Each consumer must independently preserve its entire native type graph, ordinary runtime and binding witness. This is source consistency, not a newly recovered semantic identity.|

Aggregate control:
```json
{
  "source": "Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBoxAdjustSlider.cpp",
  "source_sha256": "3450257400148dc271bd33e8c2e71511bbe2fbcbdbb6691b528fdf95677b1d12",
  "aggregate": "Code/GameEngine/Include/Common/ScalarTypes.h",
  "aggregate_before_sha256": "9ea3375521c2e276489a72fcc140df68bfb6dab6c0631aeb7b4a5ac3d4129aee",
  "aggregate_after_sha256": "36508ad568c82faab3407fe3f51eac1bbfac7db2b1abfb7767473ceccad9af6f",
  "primitive_definitions_and_order_preserved": true,
  "native_type_graph": {
    "entire_native_type_graph_identical": true,
    "type_stream_sha256": "7e87635fc0c79a7aed9794995889578cd1b42834dc7b5d0608b7549014cbf95c"
  },
  "ordinary_runtime_and_comdat_identical": true,
  "private": "W:\\OpenBFME\\Open-BFME-2\\build\\codex-20261119-next500-1927\\aggregate-equivalence",
  "task_credit": 0
}
```
