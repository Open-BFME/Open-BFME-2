// cl: /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
//
// ??1Rva002AE5EB@@UAE@XZ, retail 0x002AE627, 48 bytes.
// ModuleData dtor: destroys the vector at +0x20 through the rowed vector
// Rva002A73B8 dtor at 0x002AE486 (state 0) then restores the Snapshot base
// vtable 0x00BBB554. Empty derived body with EH prolog, no base call since
// Snapshot dtor is inline. Shape follows CreateObjectDieModuleDataDtor and
// PillageModuleDataDtor (TU-local Snapshot with inline BBB554-restoring dtor,
// novtable derived, empty body). Called at 0x002AF541 and 0x002B13D1 plus
// Unwind funclets. Owner identity unproven, honest Rva name.

#include <vector>

class Xfer;

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"


// 12-byte element, as Rva002A73B8Dtor.cpp and StlportVectorDtorFamily.cpp (the
// retail _Destroy loop steps by 0x0C) lay it out.
class Rva002A73B8
{
public:
	~Rva002A73B8();
private:
	char m_pad[0xC];
};

class __declspec(novtable) Rva002AE5EB : public Snapshot
{
public:
	virtual ~Rva002AE5EB();
private:
	unsigned char m_pad04[0x20 - 4]; // +0x04..+0x1F
	_STL::vector<Rva002A73B8> m_vec20; // +0x20
};

Rva002AE5EB::~Rva002AE5EB()
{
}
