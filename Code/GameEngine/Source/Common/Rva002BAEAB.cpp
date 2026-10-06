// cl: /DNDEBUG /MD /EHsc
//
// ??1Rva002BAEAB@@QAE@XZ @0x002BAEAB 53B.
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

class RvaVec002B80CE
{
public:
	~RvaVec002B80CE();
private:
	char m_pad[12];
};

class Rva002BAEAB
{
public:
	~Rva002BAEAB();
private:
	FXParticleSystem::WindModuleInfo m_00;
	RvaVec002B80CE m_0C;
};

Rva002BAEAB::~Rva002BAEAB()
{
}

void *operator new(unsigned int size);
void operator delete(void *p);

// Anchor: new/delete calls the scalar deleting dtor directly (non-virtual,
// so devirtualization is a direct ??_G call), emitting the COMDAT for
// ??_GRva002BAEAB@@QAEPAXI@Z at 0x002BAE8F. Operator new/delete resolve to
// their rows at 0x0002FDA0/0x0002FD60.
void Rva002BAEAB_Anchor()
{
	Rva002BAEAB *p = new Rva002BAEAB;
	delete p;
}
