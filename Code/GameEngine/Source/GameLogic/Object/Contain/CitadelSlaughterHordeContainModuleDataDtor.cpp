// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// stlport
//
// ??1CitadelSlaughterHordeContainModuleData@@UAE@XZ, retail 0x004811E6, 74 bytes.
// Citadel slaughter-horde ModuleData dtor: stores vtable 0x00C48E40 (DIR32,
// pin ??_7CitadelSlaughterHordeContainModuleData at 0x00C48E40 whose slot0 is
// the audited scalar-deleting dtor at 0x004811CA calling here), destroys the
// +0x100 AsciiString vector through the rowed 0x002CC70 dtor (EH state 1),
// the +0xFC filter member through the rowed 0x00360D26 dtor (EH state 0),
// then calls the rowed SlaughterHordeContainModuleData base dtor at
// 0x004810D5. Layout from the rowed ctor at 0x0048112F (base 0x0048104D size
// 0xEC, StatusForRingEntry bitset at +0xEC trivial, ObjectToDestroy at +0xFC
// via 0x003623E5 pin, Upgrade vector at +0x100 via 0x00211E58, FX null at
// +0x10C, size 0x110 via factory 0x0024C100). Same EH 1/0/-1 shape as the
// rowed Garrison family; direct-Slaughter precedent unblocked by 0x004810D5.
#include <vector>

#include "ascii_string.h"

namespace _STL
{

template <>
vector<AsciiString, allocator<AsciiString> >::~vector();

}

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	int m_x;
};

class SlaughterHordeContainModuleData
{
public:
	virtual ~SlaughterHordeContainModuleData();

private:
	unsigned char m_pad[0xEC - 4];
};

class __declspec(novtable) CitadelSlaughterHordeContainModuleData : public SlaughterHordeContainModuleData
{
public:
	virtual ~CitadelSlaughterHordeContainModuleData();

private:
	unsigned char m_padEC[0xFC - 0xEC];
	Rva00360D26Member m_filterFC;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_vec100;
	void *m_fx10C;
};

CitadelSlaughterHordeContainModuleData::~CitadelSlaughterHordeContainModuleData()
{
}
