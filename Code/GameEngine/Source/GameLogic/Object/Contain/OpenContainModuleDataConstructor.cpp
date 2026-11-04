// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// stlport
// ??0OpenContainModuleData@@QAE@XZ, retail 0x00465124..0x00465221 (253
// bytes, EH): the constructor whose table 0x00C43658 the rowed destructor
// 0x00257481 (Rva00465124BaseDtor.cpp) and scalar deleting destructor
// 0x00465221 belong to. Over Snapshot it builds the die-mux data at +8
// (rowed init 0x000CE534), two null release handles at +0x38/+0x3C, the
// +0x40/+0x44 members (rowed 0x003623E5), the +0x48 list (base constructor
// 0x000B92D2), the +0x4C set (0x00463D59), the cleared 128-bit set at +0x58
// (rowed reset 0x0024CA24) and the +0x88 string vector (base constructor
// 0x00211E58); then the body sets its fields (-1000 at +0x68, -1 at +0x70,
// the +0x7D..+0x84 flags) and empties the string vector before +0x94 = 100.
// The unwind map destroys them in reverse (list copy 0x00257464, set copy
// 0x00256641). Field identities beyond the cited callees are not recovered.
#include <bitset>
#include <list>
#include <set>
#include <vector>
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "../../../../Include/Common/BfmeModuleData.h"
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@URva00463D59Element@@U1@U?$_Identity@URva00463D59Element@@@_STL@@U?$less@URv:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00463D59Element;
namespace _STL { template <> _Rb_tree<Rva00463D59Element,Rva00463D59Element,_Identity<Rva00463D59Element>,less<Rva00463D59Element>,allocator<Rva00463D59Element> >::~_Rb_tree(); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@URva00463D59Element@@V?$allocator@URva00463D59Element@@@_STL@@@_STL@@QA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00463D59Element;
namespace _STL { template <> _Rb_tree_base<Rva00463D59Element,allocator<Rva00463D59Element> >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@URva00463D59Element@@U1@U?$_Identity@URva00463D59Element@@@_STL@@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00463D59Element;
namespace _STL { template <> void _Rb_tree<Rva00463D59Element,Rva00463D59Element,_Identity<Rva00463D59Element>,less<Rva00463D59Element>,allocator<Rva00463D59Element> >::_M_erase(_Rb_tree_node<Rva00463D59Element> *); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@URva00463D59Element@@@_STL@@@_STL@@QBEXPAU?$_Rb_t:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00463D59Element;
namespace _STL { template <> void allocator<_Rb_tree_node<Rva00463D59Element> >::deallocate(_Rb_tree_node<Rva00463D59Element> *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??1?$_List_base@UBfmePod32@@V?$allocator@UBfmePod32@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod32;
namespace _STL { template <> _List_base<BfmePod32,allocator<BfmePod32> >::~_List_base(); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> _Vector_base<AsciiString,allocator<AsciiString> >::~_Vector_base(); }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@VAsciiString@@@_STL@@QBEXPAVAsciiString@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class AsciiString;
namespace _STL { template <> void allocator<AsciiString>::deallocate(AsciiString *, size_t) const; }

struct BfmePod32 { int m_data[8]; };
// Retail folds this list destructor to the rowed whole-body wrapper at 207F08.
namespace _STL { template <> list<BfmePod32, allocator<BfmePod32> >::~list(); }
struct Rva00463D59Element { int m_a; int m_b; };
inline bool operator<(const Rva00463D59Element &a, const Rva00463D59Element &b) { return a.m_a < b.m_a; }

namespace _STL {
template<> _List_base<BfmePod32, allocator<BfmePod32> >::_List_base(const allocator<BfmePod32> &a);
template<> set<Rva00463D59Element, less<Rva00463D59Element>, allocator<Rva00463D59Element> >::set();
template<> __declspec(nothrow) bitset<128> &bitset<128>::reset();
template<> __declspec(nothrow) _Vector_base<AsciiString, allocator<AsciiString> >::_Vector_base(const allocator<AsciiString> &a);
template<> vector<AsciiString, allocator<AsciiString> >::~vector();
template<> vector<AsciiString, allocator<AsciiString> >::iterator vector<AsciiString, allocator<AsciiString> >::erase(iterator first, iterator last);
}

#include "../../../../Include/GameLogic/Module/DieMuxData.h"

#include "../../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

struct Rva0010F149Handle
{
	Rva0010F149Handle() : m_ptr(0) {}
	~Rva0010F149Handle() { if (m_ptr) m_ptr->Release_Ref(); }
	OpaqueRefCounted *m_ptr;
};

class Rva00360D26Member
{
public:
	Rva00360D26Member();
	~Rva00360D26Member();
private:
	int m_x;
};

struct Rva00257464
{
	__forceinline Rva00257464() {}
	~Rva00257464();
	_STL::list<BfmePod32> m_list;
};

// Native construction at 463D59 and teardown at 256461 share the
// set storage at +4C. The element semantics remain address-derived.
class Rva00255CD1
{
public:
	__forceinline Rva00255CD1()
	{
		typedef _STL::set<Rva00463D59Element> Set;
		((Set *)this)->_STL::set<Rva00463D59Element>::set();
	}
	~Rva00255CD1();
private:
	union
	{
		void *m_alignment;
		unsigned char m_storage[sizeof(_STL::set<Rva00463D59Element>)];
	};
};
struct Rva00256641
{
	__forceinline Rva00256641() {}
	~Rva00256641() {}
	Rva00255CD1 m_set;
};

struct Rva0024CA24Bits
{
	Rva0024CA24Bits() { ((_STL::bitset<128> *)this)->reset(); }
	unsigned int m_words[4];
};

// Native C43658 has the shared 31-slot interface with a true slot 8.
class OpenContainModuleData : public ModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();
	virtual bool slot08() const { return true; }
private:
	int m_04;
	DieMuxData m_dieMuxData;			// +0x08
	Rva0010F149Handle m_ref38;			// +0x38
	Rva0010F149Handle m_ref3C;			// +0x3C
	Rva00360D26Member m_member40;			// +0x40
	Rva00360D26Member m_member44;			// +0x44
	Rva00257464 m_list48;				// +0x48
	Rva00256641 m_set4C;				// +0x4C
	Rva0024CA24Bits m_bits58;			// +0x58
	float m_passengersTestCollisionHeight;
	float m_damagePercentToUnits;
	int m_containMax;
	int m_numberOfExitPaths;
	int m_doorOpenTime;
	bool m_allowOwnPlayerInsideOverride;
	bool m_allowAlliesInside;
	bool m_allowEnemiesInside;
	bool m_allowNeutralInside;
	bool m_showPips;
	bool m_collidePickup;
	bool m_ejectPassengersOnDeath;
	bool m_killPassengersOnDeath;
	bool m_enabled;
	bool m_passengersInTurret;
	bool m_86;
	_STL::vector<AsciiString> m_vec88;		// +0x88
	int m_modifierRequiredTime;
};

OpenContainModuleData::OpenContainModuleData()
{
	m_containMax = -1;
	m_passengersTestCollisionHeight = -1000.0f;
	m_passengersInTurret = false;
	m_numberOfExitPaths = 1;
	m_damagePercentToUnits = 0.0f;
	m_doorOpenTime = 1;
	m_allowOwnPlayerInsideOverride = false;
	m_allowAlliesInside = true;
	m_allowEnemiesInside = true;
	m_allowNeutralInside = true;
	m_showPips = true;
	m_collidePickup = true;
	m_ejectPassengersOnDeath = true;
	m_killPassengersOnDeath = false;
	m_enabled = true;
	m_86 = false;
	m_vec88.clear();
	m_modifierRequiredTime = 100;
}
