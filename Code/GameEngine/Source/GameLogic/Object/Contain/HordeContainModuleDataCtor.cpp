// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_CRTIMP= /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0HordeContainModuleData@@QAE@XZ @0x00475C9A 492B.
// Pinned name; sole raw caller friend_newModuleData at 0x0024B92B (news 0x274)
// plus derived AODHordeContainModuleData ctor at 0x0047A2E4; vtable 0x00C457B0
// (slot0 deleting dtor at 0x00475E86); INI table 0x00C45530 (40 entries from
// +0x18C to +0x270); donor BFME1 HordeUpdateModuleData trivial plus
// ProductionUpdateModuleDataCtor precedent for STL/EH/SSE ModuleData shape;
// globals VA 0x00DBA4E4 (int 5 -> 2/15/25) and float literals 3.0/5.0/0.5/
// 60.0/360.0 (DIR32-masked like AOD precedent).

#include <vector>
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}
#include <set>

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

#include "ascii_string.h"

extern int BfmeLogicFramesPerSecond;

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::~_Rb_tree(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

struct Vec2
{
	Vec2() : x(0.0f), y(0.0f) {}
	float x;
	float y;
};

namespace _STL
{

template <>
_Vector_base<BfmeE16, allocator<BfmeE16> >::_Vector_base(
	const allocator<BfmeE16> &storage) throw();

template <>
_List_base<int, allocator<int> >::_List_base(
	const allocator<int> &storage);

template <>
set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();

}

#include "../../../../Include/GameLogic/Module/TransportContainModuleData.h"

class HordeContainModuleData : public TransportContainModuleData
{
public:
	HordeContainModuleData();
	virtual ~HordeContainModuleData();	// rowed 0x00475942 (HordeContainModuleDataDtor.cpp)

private:
	_STL::vector<BfmeE16> m_vec18C;
	_STL::vector<BfmeE16> m_vec198;
	_STL::vector<BfmeE16> m_vec1A4;
	AsciiString m_s1B0;
	_STL::list<int> m_list1B4;
	_STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > m_set1B8;
	_STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > m_set1C4;
	Vec2 m_v1D0;
	bool m_b1D8;
	int m_i1DC;
	int m_i1E0;
	float m_f1E4;
	float m_f1E8;
	float m_f1EC;
	float m_f1F0;
	_STL::vector<BfmeE16> m_vec1F4;
	Vec2 m_v200;
	int m_i208;
	_STL::vector<BfmeE16> m_vec20C;
	_STL::vector<BfmeE16> m_vec218;
	_STL::vector<BfmeE16> m_vec224;
	bool m_b230;
	int m_i234;
	bool m_b238;
	AsciiString m_s23C;
	bool m_b240;
	float m_f244;
	int m_i248;
	bool m_b24C;
	int m_i250;
	bool m_b254;
	bool m_b255;
	int m_i258;
	float m_f25C;
	int m_i260;
	int m_i264;
	int m_i268;
	float m_f26C;
	float m_f270;
};

HordeContainModuleData::HordeContainModuleData()
	: TransportContainModuleData()
	, m_b1D8(true)
	, m_i1DC(BfmeLogicFramesPerSecond / 2)
	, m_i1E0(BfmeLogicFramesPerSecond * 3)
	, m_f1E4(3.0f)
	, m_f1E8(5.0f)
	, m_f1EC(0.5f)
	, m_f1F0(0.0f)
	, m_i208(0)
	, m_b230(false)
	, m_i234(-1)
	, m_b238(false)
	, m_f244(60.0f)
	, m_i248(-1)
	, m_b24C(false)
	, m_i250(0)
	, m_b254(false)
	, m_b255(false)
	, m_i258(0)
	, m_f25C(360.0f)
	, m_i260(0)
{
	m_b240 = true;
	m_i264 = BfmeLogicFramesPerSecond * 5;
	m_i268 = 0;
	m_f26C = 0.0f;
	m_f270 = 0.0f;
}
