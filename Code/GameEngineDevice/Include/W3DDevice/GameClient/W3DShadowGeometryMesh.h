// Target facts (BFME 2 1.06, addresses are RVAs unless marked VA):
// 0x000EFD4B initializes dwords +00/+04/+08/+10/+14/+18/+1C/+20/+24/+28/+2C
// and byte +30 to zero, and dword +0C to -1. It calls no base constructor
// and stores no vptr. 0x000F11C0 destroys the same record without a vptr
// store; its indirect calls at 0x000F11F7/0x000F120A dispatch through the
// buffer pointers at +00/+04, not through the mesh. This class has no
// virtual functions or base subobjects; its destructor is nonvirtual.
// 0x000F1E80..0x000F1E99 passes destructor 0x000F11C0, constructor
// 0x000EFD4B, count 160, stride 0x34 and geometry+0x14 to the array
// constructor iterator. 0x000F1F1E..0x000F1F35 uses the same destructor,
// count and stride. sizeof is 0x34; the geometry's tables at VA 0x00BCEFFC
// and VA 0x00BCEFF4 belong to its enclosing object, not these records.
// initFromMesh 0x000F1018 indexes records by 0x34 at 0x000F102B and
// writes the render-object index +0C (0x000F1036), skin flag +30
// (0x000F1053), vertex count +18 (0x000F105F), vertex buffer +04
// (0x000F106C), vertex data +08 (0x000F1072), polygon count +1C
// (0x000F1078), index buffer +00 (0x000F108B), unsigned-short vertex map
// +20 (0x000F117C), unique count +14 (0x000F118A) and geometry pointer
// +2C (0x000F1195). The flag is model bit 0x400 at 0x000F104D..0x000F1053.
// GetPolygonIndex 0x000F0FCD reads +00, buffer+0C and the +20 map with
// six-byte triangles and two-byte indices. buildPolygonNormals 0x000F28C3
// reads normals +10, flag +30 and count +1C, constructs twelve-byte normals,
// calls buildPolygonNormal 0x000F1D24 at 0x000F2940 and stores +10 at
// 0x000F2952. allocateNeighbors 0x000EFD77 allocates 22-byte records and
// writes +24/+28; deleteNeighbors 0x000EFDA0 clears them. GetPolyNeighbor
// 0x000F2CFC checks +24/+28 and indexes by 22; buildPolygonNeighbors is
// 0x000F2963. These rowed methods and both special members stay out of line.
// buildPolygonNormal 0x000F1D24 and constructVolume 0x000EFDF6 index the
// normals at +10 and vertices at +08 as twelve-byte Vector3 records.
// The normal-building call at 0x000F2940 has no intervening EH-state
// transition after the array construction; its declaration is nonthrowing.
// Donor facts: Zero Hour GeneralsMD W3DVolumetricShadow.cpp, class
// W3DShadowGeometryMesh, names the three accessors and the members below
// except m_00/m_04/m_18/m_30. Only those names and accessor
// operations are shared; BFME 2's offsets, buffer ownership, extra count
// and skin flag are established by the retail instructions above.

#pragma once

class Vector3;
class W3DShadowGeometry;
struct PolyNeighbor;

class W3DShadowGeometryMesh
{
    friend class W3DShadowGeometry;
    friend class W3DVolumetricShadow;

public:
    W3DShadowGeometryMesh();
    ~W3DShadowGeometryMesh();

    const Vector3 &GetPolygonNormal(long index) const
    {
        return *reinterpret_cast<const Vector3 *>(reinterpret_cast<const char *>(m_polygonNormals) + index * 12);
    }
    int GetNumPolygon() const { return m_numPolygons; }
    const Vector3 &GetVertex(int index) const
    {
        return *reinterpret_cast<const Vector3 *>(reinterpret_cast<const char *>(m_verts) + index * 12);
    }
    void buildPolygonNeighbors();
    void buildPolygonNormals();

protected:
    Vector3 *buildPolygonNormal(long index, Vector3 *normal) const throw();
    bool allocateNeighbors(int count);
    void deleteNeighbors();
    PolyNeighbor *GetPolyNeighbor(int index);
    void GetPolygonIndex(long index, short *indices) const;

    void *m_00;
    void *m_04;
    const Vector3 *m_verts;
    int m_meshRobjIndex;
    Vector3 *m_polygonNormals;
    int m_numVerts;
    int m_18;
    int m_numPolygons;
    unsigned short *m_parentVerts;
    PolyNeighbor *m_polyNeighbors;
    int m_numPolyNeighbors;
    W3DShadowGeometry *m_parentGeometry;
    bool m_30;
};
