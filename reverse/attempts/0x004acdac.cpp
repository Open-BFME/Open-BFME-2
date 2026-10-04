// ?rva004ACDAC@Rva004ACDACFilter@@UAE_NPAVObject@@@Z
// partial score=0.8 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva004ACDAC@Rva004ACDACFilter@@UAE_NPAVObject@@@Z, retail 0x004ACDAC, 101
// bytes: slot 1 of the vtable 0x00C54EB4 that RousingSpeechUpdate's code
// builds on the stack and in 0x004ACD5B (a float at +8, a Coord3D pointer at
// +0x0C; slot 0 is the matched deleting body 0x00395A19), the partition-filter
// shape: true when the Object's position (+0x38) lies farther from the
// centre than the radius, measured in x/y (rowed Coord3D::GetLength2D on the
// difference). Names by address.
struct Coord3D
{
	float GetLength2D() const;
	float x;
	float y;
	float z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_pos; // +0x38
};

class Rva004ACDACFilter
{
public:
	virtual void *slot0(unsigned int flags);
	virtual bool rva004ACDAC(Object *other);
private:
	int m_04; // +0x04
	float m_radius; // +0x08
	const Coord3D *m_center; // +0x0C
};

bool Rva004ACDACFilter::rva004ACDAC(Object *other)
{
	Coord3D diff;
	diff.x = other->getPosition()->x - m_center->x;
	diff.y = other->getPosition()->y - m_center->y;
	diff.z = other->getPosition()->z - m_center->z;
	if (diff.GetLength2D() > m_radius)
		return true;
	return false;
}
