// cl: /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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
