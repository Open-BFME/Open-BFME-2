// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0AIUpgradeScienceBuilder@@QAE@PAX@Z @0x00597693 128B: ctor with EH prolog building Rva00506B1B at +0xc and three Vector_base<BfmeE16> at +0x18/+0x24/+0x30 via rowed 0x00506B1B and 0x00211E58; caller 0x004EC4B7
// Native FuncInfo9532CC has one state:8B cleanup79D3F1 destroys the primary
// base at this through the complete7B destructor4EA016. The C62888 table has
// two pure callbacks then the deleting destructor4EA01D in slot2. Derived
// C70C24 slots0/1 are Register597C58 and UnRegister59771B; slot2 is the
// deleting callback597FA9. The complete25B base ctor4E9FFD initializes the
// same two scalar fields from arguments; this owner supplies1 and2.
// The secondary base's C63F9C table has its deleting destructor in slot0.
// Unused method identities and the empty-vector payloads remain unspecified.
#include <vector>

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"

class Object;

#include "../../../../Include/Common/BaseA.h"

class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual ~Rva00506B1B();
	virtual void rva00597fc5() = 0;
	virtual void shutdown() = 0;
	bool m_04;
};

class AIUpgradeScienceBuilder : public BaseA, public Rva00506B1B
{
public:
    virtual void Register(Object *, void *);
    virtual void UnRegister(Object *);
    virtual ~AIUpgradeScienceBuilder();
    virtual void rva00597fc5();
    virtual void shutdown();
	AIUpgradeScienceBuilder(void *p);
private:
	void *m_14;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_vec18;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_vec24;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_vec30;
	int m_3c;
};

AIUpgradeScienceBuilder::AIUpgradeScienceBuilder(void *p)
	: BaseA(1, 2)
	, Rva00506B1B()
	, m_14(p)
	, m_vec18(_STL::allocator<BfmeE16>())
	, m_vec24(_STL::allocator<BfmeE16>())
	, m_vec30(_STL::allocator<BfmeE16>())
	, m_3c(0)
{
}
