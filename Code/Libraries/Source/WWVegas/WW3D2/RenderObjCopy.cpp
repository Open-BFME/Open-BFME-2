// cl: /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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

// rendobj.h: this unit inlines RenderObjClass::Set_Hidden (a qualified or
// in-constructor call), so it needs the bit setters' bodies.
#define BFME_RO_DEFINE_VISIBILITY
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
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
#pragma optimize("s", on)
// multilist.h's inline members are retail's size-optimised bodies: compile
// them for size (as hlod.cpp/decalsys.cpp do) so this unit's copies match.
#include "refcount.h"
#include "multilist.h"
// Matrix3D uses the same size-optimized copy as its retail provider.
#include "matrix3d.h"
#pragma optimize("", on)
#include "rendobj.h"
#include "aabox.h"

typedef char RenderObjSizeMatchesRetail[(sizeof(RenderObjClass) == 0xC4) ? 1 : -1];

// Retail copies each opaque field without assigning it an application meaning.
// The copy starts detached from its scene/container and preserves the indexed
// factors after copying the 32 opaque bytes at 0x9C.
RenderObjClass::RenderObjClass(const RenderObjClass &src) :
    Bits(src.Bits),
    _bfme_unk_14(src._bfme_unk_14),
    Transform(src.Transform),
    ObjectScale(1.0f),
    CachedBoundingSphere(src.CachedBoundingSphere),
    CachedBoundingBox(src.CachedBoundingBox),
    IsTransformIdentity(src.IsTransformIdentity),
    Scene(NULL), Container(NULL), User_Data(NULL),
    _bfme_float_84(src._bfme_float_84),
    _bfme_unk_88(0), _bfme_unk_8c(-1),
    _bfme_unk_98(src._bfme_unk_98),
    _bfme_unk_bc(src._bfme_unk_bc), _bfme_unk_bd(src._bfme_unk_bd),
    _bfme_unk_c0(src._bfme_unk_c0)
{
    Set_Hidden(src.Is_Hidden());
    for (int i = 0; i < 32; ++i) {
        _bfme_opaque_9c[i] = src._bfme_opaque_9c[i];
    }
    for (int i = 0; i < 2; ++i) {
        _bfme_indexed_factors[i] = src._bfme_indexed_factors[i];
    }
}

// RenderObjClass::Set_ObjectScale, the header inline virtual (slot 93): the
// copy every RenderObjClass-derived vtable points at is the /arch:SSE body at
// 0x0006CEBF. The anchor below only makes this SSE unit emit it (qualified
// call with inlining disabled); it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRenderObjScaleAnchor@@YAXPAVRenderObjClass@@M@Z absent-from-retail
void _bfmeRenderObjScaleAnchor(RenderObjClass *renderObj, float scale)
{
    renderObj->RenderObjClass::Set_ObjectScale(scale);
}
#pragma inline_depth()
