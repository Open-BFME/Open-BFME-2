// cl: /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/shims/bfmevector /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// BFME1 hlod.cpp supplies the method identity and the top-LOD/additional-model
// traversal. Matched HLod constructors install table RVA 0x007D6780; slot
// 0xF0 identifies retail RVA 0x0019CF50 (324 bytes through ret4 at 0x0019D091).
// Retail adds the flag +0x42 branch: prefer the first CLASSID_OBBOX child,
// otherwise stop on a hit. The existing bfme2ray shim establishes this flag's
// position from the ray-test constructor; its original name remains unknown.
// Target accesses confirm HLod offsets 0x120/0x128/0x138 and 20-byte model nodes.
// No shared layout or new callee pin is needed.
#include "rendobj.h"
#include <bfme2ray/coltest.h>
#include <htree.h>
#include "hlod.h"

bool HLodClass::Cast_Ray(RayCollisionTestClass &raytest)
{
    if (Are_Sub_Object_Transforms_Dirty()) {
        Update_Sub_Object_Transforms();
    }
    bool res = false;
    int i;
    int top = LodCount - 1;
    if (raytest._bfme_flag42) {
        for (i = 0; i < Lod[top].Count(); ++i) {
            RenderObjClass *model = Lod[top][i].Model;
            if (model->Class_ID() == CLASSID_OBBOX) {
                return model->Cast_Ray(raytest);
            }
        }
    }
    for (i = 0; i < Lod[top].Count(); ++i) {
        res |= Lod[top][i].Model->Cast_Ray(raytest);
        if (res && raytest._bfme_flag42) return true;
    }
    for (i = 0; i < AdditionalModels.Count(); ++i) {
        res |= AdditionalModels[i].Model->Cast_Ray(raytest);
        if (res && raytest._bfme_flag42) return true;
    }
    return res;
}
