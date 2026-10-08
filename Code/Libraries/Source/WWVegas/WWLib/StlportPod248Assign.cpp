// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /EHsc /Ireference/shims/bfmealloc
// stlport
//
// ??4BfmePod248@@QAEAAU0@ABU0@@Z @0x000C6C54 240B.
// Copy ctor 0x000C6B17/317 uses the same native248-byte member layout.
// The 76-byte copy provider is an ICF memory-copy view; its spelling does
// not establish an application WeaponTemplateSet field. Original type unknown.
// Assignment: Self-check, StringBase set at +0 and +0x6C, 19-dword POD copy, then the
// rowed container assigns. Six vector slots at +0xAC step by 0xC. Returns this.
#include "ascii_string.h"
// Declare the container assigns. Do not compile their bodies into this TU.
#define _STLP_LINK_TIME_INSTANTIATION
#include <map>
#include <vector>
#include <list>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

struct PristineBoneInfo
{
	unsigned char m_data[52];
};

struct BfmeVectorRecord000BDF17 { char m[64]; BfmeVectorRecord000BDF17(const BfmeVectorRecord000BDF17 &); ~BfmeVectorRecord000BDF17(); };
class Rva000BB491 { char m[24]; public: Rva000BB491(const Rva000BB491 &); ~Rva000BB491(); };
class Rva000BB4AC { char m[24]; public: Rva000BB4AC(const Rva000BB4AC &); ~Rva000BB4AC(); };
struct BfmeStringRecord000B950F { char m[24]; BfmeStringRecord000B950F(const BfmeStringRecord000B950F &); ~BfmeStringRecord000B950F(); };
struct BfmeFixedObject60 { char m[60]; BfmeFixedObject60(const BfmeFixedObject60 &); ~BfmeFixedObject60(); };
struct BfmePod32 { char m[32]; BfmePod32(const BfmePod32 &); ~BfmePod32(); };
// Retain the assignment providers' existing opaque spellings. Both views
// have the same STLport pointer/header layout and native payload width as
// the constructor views above; their established call bindings stay intact.
struct Gen_p64cd;
struct Rva000B419E;

// Native default construction zeros the same76-byte storage through the
// rowed opaque bulk-zero constructor0x42526. Its copy uses the existing
// memory-copy provider0x45455. These are ABI views, not application names.
class Rva0042526Member {
	unsigned int m[19];
public:
	Rva0042526Member();
};

class WeaponTemplateSetHead
{
	unsigned int w[19];
public:
	__forceinline WeaponTemplateSetHead() {
		((Rva0042526Member *)this)->Rva0042526Member::Rva0042526Member();
	}
	WeaponTemplateSetHead(const WeaponTemplateSetHead &);
};

struct BfmePod248
{
	AsciiString m_s00;
	WeaponTemplateSetHead m_pod;
	_STL::vector<BfmeVectorRecord000BDF17> m_v50;
	unsigned int m_at5C;
	unsigned int m_at60;
	unsigned char m_at64;
	unsigned char m_pad65[3];
	unsigned int m_at68;
	AsciiString m_s6C;
	unsigned int m_at70;
	_STL::list<BfmePod32> m_list;
	_STL::vector<Rva000BB491> m_v78;
	_STL::vector<Rva000BB4AC> m_v84;
	_STL::vector<BfmeStringRecord000B950F> m_v90;
	unsigned char m_at9C;
	unsigned char m_at9D;
	unsigned char m_pad9E[2];
	_STL::map<NameKeyType, PristineBoneInfo> m_map;
	_STL::vector<BfmeFixedObject60> m_arr[6];
	unsigned char m_atF4;
	unsigned char m_padF5[3];

	BfmePod248();
	BfmePod248(const BfmePod248 &rhs);
    BfmePod248 &operator=(const BfmePod248 &rhs);
};

typedef char Pod248Size[(sizeof(BfmePod248) == 0xF8) ? 1 : -1];

// Native boundary0xC6A4D..0xC6B17,202B. The leading canonical string
// supplies the native cleanup state without synthetic base classes.
BfmePod248::BfmePod248():
 m_at5C(0), m_at60(0), m_at64(0), m_at68(0), m_at70(-1),
 m_at9C(0), m_at9D(0), m_atF4(0)
{}

BfmePod248::BfmePod248(const BfmePod248 &rhs):
 m_s00(rhs.m_s00), m_pod(rhs.m_pod), m_v50(rhs.m_v50),
 m_at5C(rhs.m_at5C), m_at60(rhs.m_at60), m_at64(rhs.m_at64), m_at68(rhs.m_at68),
 m_s6C(rhs.m_s6C), m_at70(rhs.m_at70), m_list(rhs.m_list),
 m_v78(rhs.m_v78), m_v84(rhs.m_v84), m_v90(rhs.m_v90),
 m_at9C(rhs.m_at9C), m_at9D(rhs.m_at9D), m_map(rhs.m_map), m_atF4(rhs.m_atF4)
{
 for (int i=0; i<6; ++i) m_arr[i]=rhs.m_arr[i];
}


BfmePod248 &BfmePod248::operator=(const BfmePod248 &rhs)
{
	if (this != &rhs) {
		m_s00 = rhs.m_s00;
		m_pod = rhs.m_pod;
		reinterpret_cast<_STL::vector<Gen_p64cd> &>(m_v50) =
			reinterpret_cast<const _STL::vector<Gen_p64cd> &>(rhs.m_v50);
		m_at5C = rhs.m_at5C;
		m_at64 = rhs.m_at64;
		m_at68 = rhs.m_at68;
		m_at60 = rhs.m_at60;
		m_at9D = rhs.m_at9D;
		m_s6C = rhs.m_s6C;
		reinterpret_cast<_STL::list<Rva000B419E> &>(m_list) =
			reinterpret_cast<const _STL::list<Rva000B419E> &>(rhs.m_list);
		m_at70 = rhs.m_at70;
		m_map = rhs.m_map;
		m_v78 = rhs.m_v78;
		m_v90 = rhs.m_v90;
		m_v84 = rhs.m_v84;
		m_atF4 = rhs.m_atF4;
		m_at9C = rhs.m_at9C;
		for (int i = 0; i < 6; ++i)
			m_arr[i] = rhs.m_arr[i];
	}
	return *this;
}
