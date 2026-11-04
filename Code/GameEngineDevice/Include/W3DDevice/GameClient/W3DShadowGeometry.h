// Target facts (BFME 2 1.06; code addresses are RVAs, tables are VAs): Load_Geom 0x000F27D3 allocates 0x209C bytes at 0x000F27E2 and calls the constructor 0x000F1E48 at 0x000F27FD. The constructor stores count +4 = 1, HashableClass table 0x00BCEF94 at +8 and link +0xC = 0, then the geometry tables 0x00BCEFFC at +0 and 0x00BCEFF4 at +8. The destructor 0x000F1F00 restores those geometry tables before cleanup, then base tables 0x00BCEF94 at +8 and 0x00BC650C at +0. RefCountClass constructor and destructor 0x00072882/0x00072892 and HashableClass constructor and destructor 0x000EF9C2/0x000EF9CF prove the two eight-byte bases.
// The primary table 0x00BCEFFC holds the inherited Delete_This 0x0006CE57 and the deleting destructor 0x000F1EE4, and VA 0x00BCF004 is zero; the secondary table 0x00BCEFF4 holds the this-minus-eight destructor thunk 0x000F1EBA and Get_Key 0x000F1EC2 and ends where the primary table starts. Get_Key reads secondary this+8 (complete this+0x10) and returns buffer+8 or VA 0x00BBAC1C; Load_Geom 0x000F2813/0x000F2818 passes complete this+0x10 to StringBase<char>::set 0x000055F5, and the destructor releases it through 0x00036410 at 0x000F1F41, so +0x10 is a four-byte AsciiString.
// The constructor zeros +0x10, passes mesh constructor 0x000EFD4B, destructor 0x000F11C0, count 160 and stride 0x34 for +0x14 to the array constructor iterator (0x000F1E80..0x000F1E99) and zeros +0x2094/+0x2098 at 0x000F1EA1/0x000F1EA7; initFromMesh 0x000F1018 updates those counts and initFromHLOD 0x000F1F60 clears them. Donor names only: Zero Hour GeneralsMD W3DVolumetricShadow.cpp declares the class, its members and accessors; BFME 2's string member and three-argument initFromMesh come from retail.

#ifndef BFME2_W3DSHADOWGEOMETRY_H
#define BFME2_W3DSHADOWGEOMETRY_H

#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/HashableClass.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "W3DShadowGeometryMesh.h"

class RenderObjClass;

class W3DShadowGeometry : public RefCountClass, public HashableClass
{
public:
    W3DShadowGeometry();
    virtual ~W3DShadowGeometry();
    virtual const char *Get_Key();

    int initFromHLOD(RenderObjClass *object);
    int initFromMesh(RenderObjClass *object, int meshIndex, W3DShadowGeometry *parent);

    const char *Get_Name() const { return m_namebuf.str(); }
    void Set_Name(const char *name) { m_namebuf.set(name); }
    int getMeshCount() { return m_meshCount; }
    W3DShadowGeometryMesh *getMesh(int index) { return &m_meshList[index]; }
    int GetNumTotalVertex() { return m_numTotalsVerts; }

    AsciiString m_namebuf;
    W3DShadowGeometryMesh m_meshList[160];
    int m_meshCount;
    int m_numTotalsVerts;
};

typedef char W3DShadowGeometry_size_209C[(sizeof(W3DShadowGeometry) == 0x209C) ? 1 : -1];

#endif
