// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// SiegeDockingBehavior's two dock-point accessors, retail 0x004598F2 and
// 0x0045992F (61 bytes each): by index, a copy of the +0x08 or +0x14 position
// of an entry in the +0x24 entry vector, or the Object's position (+0x38 of
// the +0x08 Object) when the index is out of range. Target facts: HordeContain
// slot 130 (0x00469967) calls both on the module it finds under the
// "SiegeDockingBehavior" key, and the +0x24 vector and entry offsets are the
// ones SiegeDockingBehavior::xfer (0x0045A02F) walks. Donor: BFME 1's
// Rva002060B0TripleCopy.cpp and Rva00206100Point.cpp (retail 0x002060B0,
// 0x00206100) have this shape; the returned triple's copy constructor is
// carried from them and reproduces retail's fld/fstp first word. The method
// and point names are address-derived.

#include <vector>

struct Rva004598F2Point
{
	Rva004598F2Point() {}
	Rva004598F2Point(const Rva004598F2Point &other) : x(other.x), y(other.y), z(other.z) {}
	float x;
	float y;
	float z;
};

class Object
{
public:
	const Rva004598F2Point *getPosition() const { return &m_cachedPos; }
private:
	unsigned char m_pad00[0x38];
	Rva004598F2Point m_cachedPos; // +0x38
};

struct SiegeDockEntry
{
	int m_int00;
	int m_enum04;
	Rva004598F2Point m_coord08; // +0x08
	Rva004598F2Point m_coord14; // +0x14
	int m_objectID20;
};

class SiegeDockingBehavior
{
public:
	Rva004598F2Point rva004598F2(int index);
	Rva004598F2Point rva0045992F(int index);
	Object *getObject() const { return m_object; }
private:
	void *m_vtbl;
	const void *m_moduleData;
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	_STL::vector<SiegeDockEntry *> m_entries; // +0x24
};

// ?rva004598F2@SiegeDockingBehavior@@QAE?AURva004598F2Point@@H@Z @0x004598F2
Rva004598F2Point SiegeDockingBehavior::rva004598F2(int index)
{
	if (index >= 0 && index < m_entries.size())
		return m_entries[index]->m_coord08;
	return *getObject()->getPosition();
}

// ?rva0045992F@SiegeDockingBehavior@@QAE?AURva004598F2Point@@H@Z @0x0045992F
Rva004598F2Point SiegeDockingBehavior::rva0045992F(int index)
{
	if (index >= 0 && index < m_entries.size())
		return m_entries[index]->m_coord14;
	return *getObject()->getPosition();
}
