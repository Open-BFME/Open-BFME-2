// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004E5012@@QAE@ABV0@@Z @0x004E5012 (116B)
// Copy ctor with Pod12 pair at +0/+0xC via movsd, ints at +0x18/+0x24/+0x28/+0x2C/+0x30,
// pad at +0x1C/+0x20 untouched, lists int at +0x34 Pod8 at +0x38 via default empty allocator.
// Neighbours stlport_pod_list_bodies Pod60. Evidence unlock lane caller 0x004E5317.
#include <list>

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}
struct Pod12_004E5012 { int a[3]; };
struct BfmePod8 { int a[2]; };
class Rva004E5012 {
public:
	Rva004E5012(const Rva004E5012 &that);
private:
	Pod12_004E5012 m_00;
	Pod12_004E5012 m_0C;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	_STL::list<int, _STL::allocator<int> > m_34;
	_STL::list<BfmePod8, _STL::allocator<BfmePod8> > m_38;
};
Rva004E5012::Rva004E5012(const Rva004E5012 &that)
	: m_18(that.m_18)
	, m_24(that.m_24)
	, m_28(that.m_28)
	, m_2C(that.m_2C)
	, m_30(that.m_30)
	, m_34(_STL::allocator<int>())
	, m_38(_STL::allocator<BfmePod8>())
{
	m_00 = that.m_00;
	m_0C = that.m_0C;
}
