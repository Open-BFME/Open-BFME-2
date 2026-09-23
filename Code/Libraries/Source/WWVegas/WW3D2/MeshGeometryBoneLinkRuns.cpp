// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfmerendobj /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
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
#include "sharebuf.h"

class MeshGeometryClass
{
public:
    virtual ~MeshGeometryClass();
private:
    unsigned char m_before_links[0x50];
    ShareBufferClass<unsigned short> *BoneLinkRuns; // target +0x54
protected:
    unsigned short *get_buffer54(int count);
};

// Target 16A170 lazily allocates the requested element count at +0x54.
// A zero count only queries the current array. This is a local ABI view.
unsigned short *MeshGeometryClass::get_buffer54(int count)
{
    if (count && !BoneLinkRuns) {
        BoneLinkRuns = NEW_REF(ShareBufferClass<unsigned short>,
            (count, 0));
    }
    if (BoneLinkRuns) {
        return BoneLinkRuns->Get_Array();
    }
    return NULL;
}
