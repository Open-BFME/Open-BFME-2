// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1Rva00597BD4@@UAE@XZ, retail 0x00597BD4..0x00597C54 (132 bytes, EH). The
// skirmish AI upgrade-science builder wrapper (vtable 0x00C70C24 and, at
// +0x0C, the AIUpgradeScienceBuilder object with its own vtable 0x00C70C18):
// the destructor shuts the builder down (rowed shutdown 0x00597B32), frees
// its three vectors at +0x18 / +0x24 / +0x30, restores the builder base
// (0x00506B28) and the first base (0x004EA016) goes last. Class name
// address-derived.
#include <vector>

enum ObjectID { INVALID_ID = 0 };

class Gen_uwm_004ea016
{
public:
	virtual void slot00();
	~Gen_uwm_004ea016() {}
private:
	char m_pad[8];
};

class Rva00598CFDBase
{
public:
	virtual ~Rva00598CFDBase();
};

class AIUpgradeScienceBuilder
{
public:
	void shutdown();
};

class Rva00597BD4 : public Gen_uwm_004ea016, public Rva00598CFDBase
{
public:
	virtual ~Rva00597BD4();
private:
	char m_pad10[0x18 - 0x10];
	_STL::vector<ObjectID> m_vec18;
	_STL::vector<ObjectID> m_vec24;
	_STL::vector<ObjectID> m_vec30;
};

Rva00597BD4::~Rva00597BD4()
{
	((AIUpgradeScienceBuilder *)static_cast<Rva00598CFDBase *>(this))->shutdown();
}
