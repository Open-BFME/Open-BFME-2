// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
//
// ??1ObjectSMCHelper@@UAE@XZ retail 0x004DE767 91 bytes.
// ObjectSMCHelper public virtual destructor over opaque base 0x004DF7C2.
// Restores three vtable slots at +0x00 +0x0C +0x10 then clears list at +0x20
// through rowed _List_base clear 0x0023DAA5 then destroys it through rowed
// _List_base dtor 0x004EC395 then calls base dtor.
// Donor BFME1 ObjectSMCHelper cpp plus ZH empty dtor.
// Identity via deleting wrapper 0x00292894 slot0 vtable 0x00BFC088
// and pool key 0x00292849 with ObjectSMCHelper string.
// Layout from donor ObjectHelper plus list timers at 0x20.
// Shape follows ProductionUpdateModuleDataDtor list plus GameWindowManager EHs precedent.

#include <list>

namespace _STL
{
template<> _List_base<int, allocator<int> >::~_List_base();
}

class Rva0024A797
{
public:
	virtual ~Rva0024A797();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class Rva004DF7C2_B2
{
public:
	virtual void f2();
};

class Rva004DF7C2 : public Rva0024A797, public MiBase1, public Rva004DF7C2_B2
{
public:
	virtual ~Rva004DF7C2();
};

class ObjectSMCHelper : public Rva004DF7C2
{
public:
	virtual ~ObjectSMCHelper();

private:
	unsigned char m_pad14_20[0x20 - 0x14];
	_STL::_List_base<int, _STL::allocator<int> > m_timers;
};

ObjectSMCHelper::~ObjectSMCHelper()
{
	m_timers.clear();
}
