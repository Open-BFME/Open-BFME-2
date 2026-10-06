// cl: /DNDEBUG /MD /EHsc
// ?rva0028B35B@Object@@QBE_NPBV1@@Z, retail 0x0028B35B, 50 bytes.
// Object geometry intersect test via GeometryInfo::bfmeIntersects.
// Evidence: same +0x38 +0x44 +0xa8 layout as BFME1 ObjectGeometry.cpp
// bfmeGeometryIntersects; rowed/pinned bfmeIntersects 0x006BEB80
// ?bfmeIntersects@GeometryInfo@@QBE_NABUCoord3D@@MABV1@0M@Z; callers
// 0x0028C0EA 0x004C601C; neighbours ObjectRva0028B31A/0028B38D.
struct Coord3D
{
	float x;
	float y;
	float z;
};
class GeometryInfo
{
public:
	bool bfmeIntersects(const Coord3D &, float, const GeometryInfo &, const Coord3D &, float) const;
};
class Object
{
public:
	bool rva0028B35B(const Object *other) const;
private:
	char m_pad0[0x38];
	Coord3D m_position; // +0x38
	float m_orientation; // +0x44
	char m_pad1[0xa8 - 0x48];
	GeometryInfo m_geometryInfo; // +0xa8
};
bool Object::rva0028B35B(const Object *other) const
{
	float otherAngle = other->m_orientation;
	float thisAngle = m_orientation;
	return m_geometryInfo.bfmeIntersects(m_position, thisAngle, other->m_geometryInfo, other->m_position, otherAngle);
}
