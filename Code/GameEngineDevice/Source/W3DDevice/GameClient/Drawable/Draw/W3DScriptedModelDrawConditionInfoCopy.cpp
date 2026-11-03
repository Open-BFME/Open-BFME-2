// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0BfmePod252@@QAE@ABU0@@Z, retail 0x000C254B..0x000C27B0 (613 bytes, EH,
// RET 4). Copy constructor of the 252-byte scripted-model condition-state
// record (the element of W3DScriptedModelDrawModuleData's state vector):
// _Construct<BfmePod252> 0x000C3717 calls it, and WorldBuilder's twin
// (0x0091F7E0) is the same unnamed copy constructor. The record name is the
// existing pin's placeholder; the member layout is the one the rowed
// assignment 0x000C27B0 and destructor 0x000C2980 already prove.
//
// Target evidence: members are copy-constructed in declaration order except
// the model list (+0x4C) and the four string vectors at +0x84..+0xA8 and the
// word vector at +0xD0, which are default-constructed (the folded 29-byte
// _Vector_base(const allocator &) at 0x00211E58) and assigned in the body;
// the shadow-info pointer at +0xDC is nulled and deep-copied (new 0x28,
// ctor 0x00079514, assignment 0x0009A41B); the model list is cleared and
// refilled element by element with push_back, as the assignment does.
#include "ascii_string.h"
#include <vector>
#include <list>

#include "../../../../../../GameEngine/Include/Common/WeaponTemplateSetHead.h"

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo() throw();												// 0x00079514
		ShadowTypeInfo &operator=(const ShadowTypeInfo &that);		// 0x0009A41B
		char m_data[0x28];
	};
};

struct BfmeStringRecord000B94D2 { char _pad[8]; };
struct BfmePod32 { int a[8]; };
class Rva000BB491 { public: char _pad[0xc]; };
class Rva000BB4AC { public: char _pad[0xc]; };
struct Rva000BC20DWords { unsigned words[6]; };

// Rowed members this body calls; declared only so the calls bind to them.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> > &);
template <> vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> > &);
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString *, AsciiString *);
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString &);
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> vector<BfmeStringRecord000B94D2, allocator<BfmeStringRecord000B94D2> >::vector(const vector<BfmeStringRecord000B94D2, allocator<BfmeStringRecord000B94D2> > &);
template <> vector<BfmeStringRecord000B94D2, allocator<BfmeStringRecord000B94D2> >::~vector();
template <> list<BfmePod32, allocator<BfmePod32> >::list(const list<BfmePod32, allocator<BfmePod32> > &);
template <> list<BfmePod32, allocator<BfmePod32> >::~list();
template <> vector<Rva000BB491, allocator<Rva000BB491> >::vector(const vector<Rva000BB491, allocator<Rva000BB491> > &);
template <> vector<Rva000BB491, allocator<Rva000BB491> >::~vector();
template <> vector<Rva000BB4AC, allocator<Rva000BB4AC> >::vector(const vector<Rva000BB4AC, allocator<Rva000BB4AC> > &);
template <> vector<Rva000BB4AC, allocator<Rva000BB4AC> >::~vector();
template <> vector<Rva000BC20DWords, allocator<Rva000BC20DWords> > &vector<Rva000BC20DWords, allocator<Rva000BC20DWords> >::operator=(const vector<Rva000BC20DWords, allocator<Rva000BC20DWords> > &);
}

struct BfmePod252
{
	BfmePod252(const BfmePod252 &that);

	WeaponTemplateSetHead m_flags;								// +0x00
	_STL::vector<AsciiString> m_4c;								// +0x4C
	AsciiString m_58;											// +0x58
	AsciiString m_5c;											// +0x5C
	AsciiString m_60;											// +0x60
	_STL::vector<BfmeStringRecord000B94D2> m_64;				// +0x64
	AsciiString m_70;											// +0x70
	AsciiString m_74;											// +0x74
	_STL::vector<AsciiString> m_78;								// +0x78
	_STL::vector<AsciiString> m_84;								// +0x84
	_STL::vector<AsciiString> m_90;								// +0x90
	_STL::vector<AsciiString> m_9c;								// +0x9C
	_STL::vector<AsciiString> m_a8;								// +0xA8
	_STL::list<BfmePod32> m_b4;									// +0xB4
	_STL::vector<Rva000BB491> m_b8;								// +0xB8
	_STL::vector<Rva000BB4AC> m_c4;								// +0xC4
	_STL::vector<Rva000BC20DWords> m_d0;						// +0xD0
	Shadow::ShadowTypeInfo *m_dc;								// +0xDC
	int m_e0;
	int m_e4;
	int m_e8;
	int m_ec;
	int m_f0;
	unsigned char m_f4;
	unsigned char m_f5;
};

BfmePod252::BfmePod252(const BfmePod252 &that)
	: m_flags(that.m_flags),
	  m_58(that.m_58),
	  m_5c(that.m_5c),
	  m_60(that.m_60),
	  m_64(that.m_64),
	  m_70(that.m_70),
	  m_74(that.m_74),
	  m_78(that.m_78),
	  m_b4(that.m_b4),
	  m_b8(that.m_b8),
	  m_c4(that.m_c4),
	  m_dc(0),
	  m_e0(that.m_e0),
	  m_e4(that.m_e4),
	  m_e8(that.m_e8),
	  m_ec(that.m_ec),
	  m_f0(that.m_f0),
	  m_f4(that.m_f4)
{
	if (that.m_dc != 0) {
		m_dc = new Shadow::ShadowTypeInfo;
		*m_dc = *that.m_dc;
	}
	m_84 = that.m_84;
	m_90 = that.m_90;
	m_9c = that.m_9c;
	m_a8 = that.m_a8;
	m_d0 = that.m_d0;
	m_f5 = that.m_f5;
	_STL::vector<AsciiString> *models = &m_4c;
	models->erase(models->begin(), models->end());
	for (int i = 0; i < (int)that.m_4c.size(); ++i)
		m_4c.push_back(that.m_4c[i]);
}
