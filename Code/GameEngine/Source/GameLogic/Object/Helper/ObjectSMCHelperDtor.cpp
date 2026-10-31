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

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

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

enum UpdateSleepTime { UPDATE_SLEEP_INVALID = 0 };

// The update interface at +0x10: retail's ObjectSMCHelper table there (0x00BFC07C)
// holds ObjectSMCHelper::update (rowed) in slot 0.
class Rva004DF7C2_B2
{
public:
	virtual UpdateSleepTime update() = 0;
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
	virtual UpdateSleepTime update();

private:
	unsigned char m_pad14_20[0x20 - 0x14];
	_STL::list<int> m_timers;
};

ObjectSMCHelper::~ObjectSMCHelper()
{
	m_timers.clear();
}
