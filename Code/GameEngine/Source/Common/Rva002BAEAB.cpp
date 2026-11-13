// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva003C2F40Owner@@QAE@XZ @0x002BAEAB 53B.
// Non-virtual dtor over WindModuleInfo member at +0 and RvaVec member
// at +0xC; empty body with EH states for the two calls.
// Evidence: unlock lane; member callee pinned 0x002B80CE; base callee
// rowed WindModuleInfo 0x0049B47C (ICF-shared 7B virtual dtor); caller
// at 0x002BAE92; unblocks 0x002BAE8F; same 2-call EH shape as rowed
// Rva002B82D5 dtor at 0x002B82D5.
namespace FXParticleSystem {
class WindModuleInfo
{
public:
	WindModuleInfo();
	virtual ~WindModuleInfo();
private:
	char m_pad08[8];
};
}

#include "../../Include/Common/RvaVec002B80CE.h"

class Rva003C2F40Owner
{
public:
	~Rva003C2F40Owner();
private:
	FXParticleSystem::WindModuleInfo m_00;
	RvaVec002B80CE m_0C;
};

Rva003C2F40Owner::~Rva003C2F40Owner()
{
}

#include <new>

// Anchor: delete calls the scalar deleting dtor directly (non-virtual,
// so devirtualization is a direct ??_G call), emitting the COMDAT for
// ??_GRva003C2F40Owner@@QAEPAXI@Z at 0x002BAE8F. Operator delete resolves to
// its row at 0x0002FD60. No new-expression: an implicit default constructor
// here would emit a second ??0Rva003C2F40Owner@@QAE@XZ COMDAT beside the
// rowed constructor at 0x002BAE57 (Rva003C2F40TreeCtor.cpp).
void Rva002BAEAB_Anchor(Rva003C2F40Owner *p)
{
	delete p;
}
