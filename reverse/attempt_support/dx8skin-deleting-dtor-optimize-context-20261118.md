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
