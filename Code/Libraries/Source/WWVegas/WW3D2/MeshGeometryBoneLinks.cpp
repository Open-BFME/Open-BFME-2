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
// Donor: BFME1 WW3D2/meshgeometry.h, get_bone_links.
#include "always.h"
#include "sharebuf.h"

class MeshGeometryClass
{
public:
    virtual ~MeshGeometryClass();
private:
    unsigned char m_before_count[0x24];
    int VertexCount; // target +0x28
    unsigned char m_before_links[0x50 - 0x2C];
    ShareBufferClass<unsigned short> *VertexBoneLink; // target +0x50
protected:
    unsigned short *get_bone_links(bool create);
};

// Target evidence: getter and reader both use VertexBoneLink at +0x50;
// four 16-bit links are allocated per vertex. This is a local ABI view.
unsigned short *MeshGeometryClass::get_bone_links(bool create)
{
    if (create && !VertexBoneLink) {
        VertexBoneLink = NEW_REF(ShareBufferClass<unsigned short>,
            (VertexCount * 4,
             "MeshGeometryClass::VertexBoneLink"));
    }
    if (VertexBoneLink) {
        return VertexBoneLink->Get_Array();
    }
    return NULL;
}
