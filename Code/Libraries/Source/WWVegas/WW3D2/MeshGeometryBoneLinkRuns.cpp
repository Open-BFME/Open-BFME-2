// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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
// Reference pattern: BFME1 MeshGeometry get_bone_links and ShareBuffer.
// Target reader 16B1A0 calls 16A170 with twice the number of consecutive
// equal four-word influence tuples,
// then writes uint16 pairs: first bone index and run length. The original
// member/accessor names are unknown; get_buffer54 describes the target slot.
#include "always.h"
// Retail's out-of-line RefCountClass deleting dtor is the /O1 form hlod.cpp
// emits; compile refcount.h for size before sharebuf.h pulls it in.
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
#include "sharebuf.h"

// Retail's ShareBufferClass<unsigned short> destructor is the explicit
// specialization MeshGeometryShareBufferInstantiations.cpp emits (0x00169DE0);
// the primary template's copy here is not retail's and must not be emitted.
template <> ShareBufferClass<unsigned short>::~ShareBufferClass();

// Keep the reference RefCountClass inline definitions and the canonical list base.
#define BFME2_WWLIB_REFCOUNTDATA_H
#include "../WWLib/MultiListObjectClass.h"
#define MULTILIST_H
#include "MeshGeometryClass.h"

// Target 16A170 lazily allocates the requested element count at +0x54.
// A zero count only queries the current array.
unsigned short *MeshGeometryClass::get_buffer54(int count)
{
    if (count && !slot54) {
        slot54 = NEW_REF(ShareBufferClass<unsigned short>,
            (count, 0));
    }
    if (slot54) {
        return slot54->Get_Array();
    }
    return NULL;
}
