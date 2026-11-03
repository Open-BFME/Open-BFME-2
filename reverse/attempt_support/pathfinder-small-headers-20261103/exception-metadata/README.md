# XferException natural-throw metadata closure

Verdict: the private canonical `throw XferException(0,0)` trial has exact native compiler metadata and a closed, existing symbolic provider graph within the inspected scope. No new pin, alias, guessed owner or metadata row is needed. This packet does not claim a fresh whole-image link result.

Parent's private trial evidence: all 83 source ledger rows and all 3 owning EH checks pass. Ordinary external definitions rise 205 -> 209, solely the four compiler exception metadata definitions below. The only changed old definition is `Rva002E7FEDGet`; its full 88 raw bytes are identical between control and trial.

| Emitted symbol / role | Native RVA | Size | Native symbolic bindings |
|---|---:|---:|---|
| `??_R0?AVXferException@@@8` / TypeDescriptor | 9B3F80 | 28 | +0 -> `??_7type_info@@6B@`, native RVA87C730 |
| `__CT??_R0?AVXferException@@@8??0XferException@@QAE@ABV0@@Z8` / CatchableType | 8FFCF4 | 28 | +4 -> TypeDescriptor; +24 -> copy constructor588C5 |
| `__CTA1?AVXferException@@` / CatchableTypeArray | 8FFD10 | 8 | +4 -> CatchableType; count1 |
| `__TI1?AVXferException@@` / ThrowInfo | 8FFD18 | 16 | +4 -> destructor2BD30; +12 -> CatchableTypeArray |

Every nonrelocation byte is equal to retail; every relocation is DIR32 with zero object addend and the native operand points to the stated exact target. The native graph uses VA CFFD18/CFFD10/CFFCF4/DB3F80. Each of these four definitions also has exactly the same raw bytes and symbolic relocations as the existing normal cached `Code/GameEngine/Source/Common/System/Xfer.cpp` provider. They are ordinary duplicate compiler COMDATs, rather than four new unique implementations.

The TypeDescriptor dependency is concretely closed: current cached `Code/Libraries/Source/CRT/TypeInfoCopyConstructor.cpp` provides the `type_info` vtable, a 4-byte DIR32 slot to `??_Etype_info@@UAEPAXI@Z`. Retail RVA87C730 holds VA A29048, matching the 75-byte vector deleting destructor row at RVA629048 owned by that same source. No extra vtable pin is introduced.

The copy constructor588C5/21B, variadic constructor60C36E/85B, and destructor2BD30/9B are matched rows in `Code/GameEngine/Source/Common/System/XferException.cpp`. The variadic constructor is cdecl (`QAA`), reproducing the original three-push stack/cleanup ABI. In `Rva002E7FEDGet` the offset43 REL32 changes from `_bfmeFormatText` to that canonical constructor; its native target is60C36E. Offset51 DIR32 changes from `g_guardTargetTypeThrowInfo` to `__TI1?AVXferException@@`; its native operand is VA CFFD18. Offset60 REL32 remains `__CxxThrowException@8`, native629094. Weak aliases/directives are unchanged. Removed undefined keys are the two superseded raw declarations; added undefined keys are the canonical constructor, copy constructor, destructor and type_info vtable, all with the existing providers above.

Limits: no matching `reverse/data_rows.csv` owner rows were found for these four compiler metadata definitions. The data ledger identifies ThrowInfo RVA8FFD18 with canonical symbol and existing raw aliases. The published index is dated 2026-11-02 08:35, commit984a4cdc4d / census357ce2a88f: it has99 existing copies of each metadata COMDAT, all with the same respective digest, but their index verdict is None; that fact is not a retail-placement verdict. Native comparisons and the current cached-provider comparison provide the scoped proof independently. Parent must still apply the candidate to the currently owned source and run ordinary final source/EH/header/link gates; this audit does not override those gates or establish selected addresses in a new full image.

Evidence: `proof.json` (specific native bytes, graph, row bindings and index facts), `closure.json` (undefined and directive delta), `type-info-closure.json` (existing vtable dependency and metadata-provider byte/reloc identity). Read-only extraction scripts are beside those files. No compilation, shared cache write, Code edit, ledger edit, network operation or claim was performed by this audit.

Tracked reads stopped after this report.
