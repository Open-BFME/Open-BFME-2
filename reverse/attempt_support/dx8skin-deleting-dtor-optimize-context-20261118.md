# DX8SkinClearVisibleList.cpp: `??_G?$DynamicVectorClass@VVector3@@@@UAEPAXI@Z` shape (2026-11-18)

Link blocker (1,613 B): the unit's copy is the 30-byte speed shape (`add esp,4`); the first copy
in link order (FXShaderRendererSkin.cpp) and retail's vtable 0x00BCEFDC slot 0 (0x000F28A7,
rowed under the Curve3DClass::KeyClass spelling in curve.cpp) are the 28-byte size shape (`pop ecx`).

Cause: 3f9edfb49d and 9317f5872f retired the `#pragma optimize("s", on)` / `("", on)` pair around
`#include "../WWLib/RefCountData.h"` as redundant. All 10 rows still match, but the unrowed
deleting destructor changed shape.

Measured rule (VC7.1, throwaway builds, each 10/10 rows matched):

| variant | `??_G` |
|---|---|
| pair around `#include "../WWLib/RefCountData.h"` (`s` or `gsy`) | 28 |
| `s` pair around the donor `refcount.h` placed ahead of RefCountData.h | 28 |
| adjacent pair with nothing between (three positions), or a lone `("", on)` | 30 |
| class defined in the default state, only `Delete_This`'s body in the pair | 30 |
| `#include "Line3DCompileView.h"` (its anchor struct closes before its `gsy` line) | 30 |
| `extern template class DynamicVectorClass<Vector3>;` before or after the specializations | 30, still emitted |

So the pending inline destructor specialization (`template <> inline
DynamicVectorClass<Vector3>::~DynamicVectorClass() {}`) is compiled at the closing brace of the
next class definition, and the deleting destructor its vtable reference creates takes the optimize
state in force at that brace. rendobj.h records the same rule for in-class bodies.

The unit builds /O2 and holds no size block, and it must emit the table (Render expands the
constructor inline), so no shape without a directive exists here. Repair: re-admit the retired pair
through the hatch register (precedent cfbcc23bab), exactly where it stood. rawfile.cpp's
`??_GFileClass` (LINK-691 residue) is the same case.

## The retail-proof route (2026-11-19): blocked on the VectorClass<Vector3> table's address

Tried instead of a directive: prove FXShaderRendererSkin.cpp's first copy retail, so this unit's
30-byte copy is discarded without losing (retail-truth-3/4). Nothing kept; both sources and the
ledger are as before.

What works. With `template<class T> inline VectorClass<T>::~VectorClass() { VectorClass<T>::Clear(); }`
and `template<class T> DynamicVectorClass<T>::~DynamicVectorClass() {}` added to
FXShaderRendererSkin.cpp's own class views (/O1; 10/10 rows still match), its object emits

| name | size | retail (relocations masked) |
|---|---|---|
| `??1?$DynamicVectorClass@VVector3@@@@UAE@XZ` | 11 | equal to 0x000F1D19 |
| `??_G?$DynamicVectorClass@VVector3@@@@UAEPAXI@Z` | 28 | equal to 0x000F28A7 |
| `??1?$VectorClass@VVector3@@@@UAE@XZ` | 11 | equal to 0x000F1D19 |
| `??_G?$VectorClass@VVector3@@@@UAEPAXI@Z` | 34 | equal to 0x000F1CF7 |

and `add_match.py --icf-owner` admits all three unrowed names as fold aliases of curve.cpp's
`KeyClass` rows (0x000F1D19 twice, 0x000F28A7). With those rows `??_G?$DynamicVectorClass@VVector3@@`
is proven and stops blocking DX8SkinClearVisibleList.cpp.

Why it does not land. The two 11-byte destructors store the `VectorClass<Vector3>` table
(DIR32 to `??_7?$VectorClass@VVector3@@@@6B@`, retail 0x007CEFAC). That name has a
`data_ledger.csv` line but no matched `data_rows.csv` row, so the census cannot place the
relocation and both copies stay `unknown`:

- `??1?$DynamicVectorClass@VVector3@@`: this unit's implicit 5-byte copy (`jmp` to the base
  destructor) differs from the unproven kept one and loses. An explicit-specialization
  declaration does not remove it: the class template declares no destructor, so cl ignores the
  declaration and still synthesizes the implicit one, with the table and `??_G`.
- `??1?$VectorClass@VVector3@@`: FXShaderRendererSkin.obj becomes the first definer, ahead of
  pointgr.cpp, Rva007B7280Siblings.cpp and Rva007B73C0.cpp, whose /O2 copies (45 bytes, `Clear`
  expanded) then lose: `link_check.py` over the six units touching these names goes
  25,636 -> 1,218 linked bytes (pointgr.cpp alone 24,113). The 11-byte derived destructor cannot be
  had without it: storing the base table makes cl emit that table and its virtual destructor.

Proving the table through the object's own definition (`RetailTruth._defined_at`) needs every slot
placed: slots 1, 4 and 5 (0x000F1C16, 0x000F0DC5, 0x000F0E20) are rowed only under the
`TCBSpline3DClass::TCBClass` spellings, and `?ID@?$VectorClass@VVector3@@@@UAEHPBVVector3@@@Z` is
rowed at 0x001298B0 (pointgr.cpp), not at slot 5.

Unblocks it: a matched `data_rows.csv` row for `??_7?$VectorClass@VVector3@@@@6B@` at 0x007CEFAC
(the data lane's two-voter admission; the same row LINK-015 and the 0x007CEFAC vtable-bridge item
wait on). Then the three alias rows above and the two template destructors land as measured, with
pointgr.cpp's copies standing behind a proven first copy. Until then the pragma pair is the only
repair of this unit.
