// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CreateAHeroData identity and 0x140-byte layout are established by the
// independently matched copy constructor and named vtable at VA C38D88.
// RvaVecAscii declares the existing 12-byte string-vector cleanup ABI at
// RVA2CC70. The global STL vector<AsciiString> destructor pin is misidentified
// as string release36410 in an unrelated baseline caller; do not reuse it here.
// WriteNamedHero4074CF opens a wide path with mode w, writes map50 entries
// as "%s = %d\n", closes the file and returns success as a bool.
#include <memory>
#include <vector>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "unicode_string.h"
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
class Xfer;
class Snapshot { public: __forceinline virtual ~Snapshot() {} virtual void crc(Xfer *); virtual const char *typeName() const; virtual void xfer(Xfer *); };
typedef _STL::map<int,int> IntegerMap;
struct TreeHintPayload001F8ACB { unsigned int value; };
bool operator<(const AsciiString &, const AsciiString &);
typedef _STL::map<AsciiString,TreeHintPayload001F8ACB> StringPayloadMap;
typedef _STL::vector<bool> BitVector;
typedef _STL::map<int,_STL::vector<unsigned int> > IntegerVectorMap;
class RvaVecAscii { AsciiString *m_begin; AsciiString *m_end; AsciiString *m_capacity; public: ~RvaVecAscii(); };
struct BfmeHeroElement005C39DE { AsciiString text; unsigned int word4, word8; BfmeHeroElement005C39DE(); BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &); };
class CreateAHeroData;
extern void __cdecl UnregisterCreateAHeroAtRva0021A624(CreateAHeroData *);
class CreateAHeroData : public Snapshot {
    unsigned int word04; UnicodeString text08; unsigned int word0C, word10;
    IntegerMap map14, map20; unsigned int word2C, word30, word34, word38;
    RvaVecAscii strings3C; unsigned char flag48; AsciiString text4C;
    StringPayloadMap map50; BitVector bits5C; unsigned char flag70, flag71;
    unsigned short pad72; IntegerVectorMap map74; BfmeHeroElement005C39DE elements80[15];
    unsigned int word134, word138, word13C;
public:
    bool WriteNamedHeroAtRva004074CF();
    virtual ~CreateAHeroData();
};
CreateAHeroData::~CreateAHeroData() { if (!text4C.isEmpty()) WriteNamedHeroAtRva004074CF(); UnregisterCreateAHeroAtRva0021A624(this); }

typedef char HeroLayoutSizeCheck[sizeof(CreateAHeroData)==0x140 ? 1 : -1];
typedef char HeroStringVectorSizeCheck[sizeof(RvaVecAscii)==12 ? 1 : -1];

// Whole-class instantiation of this tree. It reproduces operator= (retail 0x0040806A)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<AsciiString,_STL::pair<AsciiString const ,TreeHintPayload001F8ACB>,_STL::_Select1st<_STL::pair<AsciiString const ,TreeHintPayload001F8ACB> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const ,TreeHintPayload001F8ACB> > >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?j_00015d7a@@YAXXZ=??1?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@QAE@XZ")

// ?rva0021B7B6@Rva0021B7B6@@QAEXPAVINI@@PAX@Z @0x0021B7B6 234B
// Bitstring-list INI driver, same shape as the KindOf driver Rva00256499
// (System/Rva00256499Parse.cpp) and its twins. The worker is the rowed
// 0x0021AAFE single-token worker; Append, Tok, INI and the empty string
// mirror the prototype TU (undefined externals).
class INI
{
public:
	const char *rva0002DFE2(const char *seps, bool *substituted);
};

class Rva0033B84ETok
{
public:
	Rva0033B84ETok(const char *s);
	~Rva0033B84ETok();
	Rva0033B84ETok() : m_data(0) {}
	const char *str() const { return m_data ? (const char *)m_data + 8 : ""; }
	bool nextToken(Rva0033B84ETok *out, const char *seps);
	void reset();

private:
	void *m_data;
};

extern const char g_Rva0107301CEmptyString[];

__forceinline const char *GetStr0021B7B6(const Rva0033B84ETok &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

class Rva0021AAFE
{
public:
	bool rva0021AAFE(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva0021B7B6 : public Rva0021AAFE
{
public:
	void rva0021B7B6(INI *ini, void *extra);
	void rva0021B7B6Append(const char *s, Rva0033B84ETok *b);
};

void Rva0021B7B6::rva0021B7B6(INI *ini, void *extra)
{
	Rva0033B84ETok *accum = (Rva0033B84ETok *)extra;
	if (accum != 0)
		accum->reset();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			Rva0033B84ETok tmp(token);
			Rva0033B84ETok part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr0021B7B6(part);
				rva0021B7B6Append(s, accum);
				if (!rva0021AAFE(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			rva0021B7B6Append(token, accum);
			if (!rva0021AAFE(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
