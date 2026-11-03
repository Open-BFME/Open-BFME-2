// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??1HordeContainModuleData@@UAE@XZ, retail 0x00475942..0x00475BDD (667
// bytes, EH): table 0x00C457B0 (constructor 0x00475C9A in
// HordeContainModuleDataCtor.cpp, slot-0 scalar deleting destructor
// 0x00475E86). It deletes and empties its three owned-record vectors at
// +0x18C/+0x198/+0x1A4 (record destructors rowed 0x004703E0, 0x00469D86 and
// 0x00469DCE; range erase 0x0031BD55), clears the +0x1B4 list and the two
// name sets, empties the +0x1F4 and +0x218 string vectors, deletes and
// empties the +0x20C owned strings, empties the +0x224 string vector and
// ::deletes its +0x258 object. Retail's unwind map then destroys the
// members in reverse and TransportContainModuleData (rowed 0x004684F1). The
// sets' wrapper unwind copy is the 5-byte thunk 0x00073116 (set destructor
// 0x000730DE); the list's is 0x00200667. Members past the cited offsets
// keep the constructor view's placeholders.
#include <list>
#include <vector>
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);

struct Rva004FA1FObserver;
class Rva004703E0;
class Rva00469D86;
class Rva0046AA69Record;
namespace _STL {
template<> void _List_base<Rva004FA1FObserver *, allocator<Rva004FA1FObserver *> >::clear();
template<> _List_base<Rva004FA1FObserver *, allocator<Rva004FA1FObserver *> >::~_List_base();
template<> vector<AsciiString, allocator<AsciiString> >::~vector();
template<> vector<AsciiString, allocator<AsciiString> >::iterator vector<AsciiString, allocator<AsciiString> >::erase(iterator first, iterator last);
// The four owned-pointer vectors carry their record types (retail unwinds each through the
// shared 14-byte body 0x0007FAB3); only their range erase is reached through vector<void *>.
template<> inline _Vector_base<Rva004703E0 *, allocator<Rva004703E0 *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
template<> inline _Vector_base<Rva00469D86 *, allocator<Rva00469D86 *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
template<> inline _Vector_base<Rva0046AA69Record *, allocator<Rva0046AA69Record *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
template<> inline _Vector_base<AsciiString *, allocator<AsciiString *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
template<> vector<void *>::iterator vector<void *>::erase(iterator first, iterator last);
template <> __declspec(dllimport) __forceinline void **vector<void *>::begin() { return _M_start; }
template <> __declspec(dllimport) __forceinline void **vector<void *>::end() { return _M_finish; }
}

class TransportContainModuleData
{
public:
	virtual ~TransportContainModuleData();
private:
	unsigned char m_pad04[0x18C - 4];
};

class Rva004703E0 { public: ~Rva004703E0(); };
class Rva00469D86 { public: ~Rva00469D86(); };
class Rva0046AA69Record { public: ~Rva0046AA69Record(); };

struct Rva00200667
{
	~Rva00200667() {}
	_STL::list<Rva004FA1FObserver *> m_list;
};

#include "../../../../Include/Common/Rva00072FE6.h"

struct Rva00073116
{
	~Rva00073116() {}
	Rva00072FE6 m_set;
};

class HordeContainOwned
{
public:
	virtual ~HordeContainOwned();
};

class HordeContainModuleData : public TransportContainModuleData
{
public:
	HordeContainModuleData();
	virtual ~HordeContainModuleData();
private:
	_STL::vector<Rva004703E0 *> m_vec18C;
	_STL::vector<Rva00469D86 *> m_vec198;
	_STL::vector<Rva0046AA69Record *> m_vec1A4;
	AsciiString m_s1B0;
	Rva00200667 m_list1B4;
	Rva00073116 m_set1B8;
	Rva00073116 m_set1C4;
	unsigned char m_pad1D0[0x1F4 - 0x1D0];
	_STL::vector<AsciiString> m_vec1F4;
	unsigned char m_pad200[0x20C - 0x200];
	_STL::vector<AsciiString *> m_vec20C;
	_STL::vector<AsciiString> m_vec218;
	_STL::vector<AsciiString> m_vec224;
	unsigned char m_pad230[0x23C - 0x230];
	AsciiString m_s23C;
	unsigned char m_pad240[0x258 - 0x240];
	HordeContainOwned *m_meleeBehavior;
	unsigned char m_pad25C[0x274 - 0x25C];
};

HordeContainModuleData::~HordeContainModuleData()
{
	unsigned int i;
	for (i = 0; i < m_vec18C.size(); ++i)
		delete m_vec18C[i];
	_STL::vector<void *> &v18C = reinterpret_cast<_STL::vector<void *> &>(m_vec18C);
	v18C.erase(v18C.begin(), v18C.end());
	for (i = 0; i < m_vec198.size(); ++i)
		delete m_vec198[i];
	_STL::vector<void *> &v198 = reinterpret_cast<_STL::vector<void *> &>(m_vec198);
	v198.erase(v198.begin(), v198.end());
	for (i = 0; i < m_vec1A4.size(); ++i)
		delete m_vec1A4[i];
	_STL::vector<void *> &v1A4 = reinterpret_cast<_STL::vector<void *> &>(m_vec1A4);
	v1A4.erase(v1A4.begin(), v1A4.end());

	m_list1B4.m_list.clear();
	m_set1B8.m_set.rva00072FE6();
	m_set1C4.m_set.rva00072FE6();
	m_vec1F4.clear();
	m_vec218.clear();

	for (i = 0; i < m_vec20C.size(); ++i)
		delete m_vec20C[i];
	_STL::vector<void *> &v20C = reinterpret_cast<_STL::vector<void *> &>(m_vec20C);
	v20C.erase(v20C.begin(), v20C.end());
	m_vec224.clear();

	::delete m_meleeBehavior;
}
