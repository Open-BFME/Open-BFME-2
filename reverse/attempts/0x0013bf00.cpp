// ??0RenderObjClass@@QAE@XZ
// partial score=0.8358778625954199 date=2026-09-07
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

// Partial: complete retail extent is 262 bytes at RVA 0x13BF00.
// Current output is 257 bytes and agrees through offset 0xD2. The compiler
// shares the two -1 stores in ECX and moves the float-zero store after them;
// retail uses immediate -1 stores after the float-zero store.
// Requires the scoped C4 RenderObj layout committed with RenderObjBounds/Copy.
// 24 tail orders and /G6 /Ob1 /Op reproduce the same obstacle; /O1 and /Og-
// lose the previously exact prefix. No field volatility or type is invented.
RenderObjClass::RenderObjClass(void) :
    Bits(DEFAULT_BITS), _bfme_unk_14(1), Transform(1), ObjectScale(1.0f),
    CachedBoundingSphere(Vector3(0, 0, 0), 1.0f),
    CachedBoundingBox(Vector3(0, 0, 0), Vector3(1, 1, 1)),
    IsTransformIdentity(false), Scene(NULL), Container(NULL), User_Data(NULL),
    _bfme_unk_88(0), _bfme_unk_bc(false), _bfme_unk_c0(NULL)
{
    _bfme_opaque_9c[0] = 0;
    _bfme_float_84 = 0.0f;
    _bfme_unk_8c = -1;
    _bfme_unk_98 = -1;
    _bfme_unk_bd = true;
    for (int i = 0; i < 2; ++i) {
        _bfme_indexed_factors[i] = 1.0f;
    }
}
