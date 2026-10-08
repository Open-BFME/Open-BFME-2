// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport __uninitialized_fill_n<T> helpers (37 bytes), same-shape siblings
// of the rowed fill_n at 0x000B97E9. Each body null-guards the count, then
// constructs each element out-of-line through T's own rowed _Construct
// (declared-only specialization below, resolving through that row), striding
// by sizeof(T). Each T is declared minimally at its retail stride (8 bytes)
// with the struct/class-ness of its rowed copy ctor; no member is touched.

#include <memory>
#include <vector>

#include "ascii_string.h"

struct NoCaseTreeValue4
{
	char m_body[4];
};

// Target push_back 0x0039A48E proves an 8-byte element stride; its application
// layout is otherwise kept address-derived.
struct Rva0039A48EElement
{
	int a[2];
};

struct TreeKey00242F5E
{
public:
	TreeKey00242F5E();
	TreeKey00242F5E(const TreeKey00242F5E &other);
	char m_body[8];
};

struct BfmeStringRecord005DDD40
{
public:
	BfmeStringRecord005DDD40();
	BfmeStringRecord005DDD40(const BfmeStringRecord005DDD40 &other);
	char m_body[8];
};

struct Rva0048130E
{
public:
	Rva0048130E();
	Rva0048130E(const Rva0048130E &other);
	char m_body[8];
};

class Rva002390CB
{
public:
	Rva002390CB();
	Rva002390CB(const Rva002390CB &other);

private:
	char m_pad[8];
};

class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry();
	Rva0040CB11Entry(const Rva0040CB11Entry &other);

private:
	char m_pad[8];
};

// Sixteen-byte string record at 0x002199C8: same 37-byte fill_n shape,
// striding 0x10 per element through its own rowed _Construct at 0x0021A95D.
// Layout matches the 0x002199C8 copy ctor (three AsciiStrings plus a word).
struct BfmeStringRecord002199C8
{
public:
	BfmeStringRecord002199C8();
	BfmeStringRecord002199C8(const BfmeStringRecord002199C8 &other);
	char m_body[16];
};

// Twenty-byte string record at 0x00219A68: same 37-byte fill_n shape,
// striding 0x14 per element through its own rowed _Construct at 0x0021A98A.
// Layout matches the 0x00219A68 copy ctor (word plus two AsciiStrings plus two words).
struct BfmeStringRecord00219A68
{
public:
	BfmeStringRecord00219A68();
	BfmeStringRecord00219A68(const BfmeStringRecord00219A68 &other);
	char m_body[20];
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> FillNoCasePair;
typedef _STL::pair<const AsciiString, char> FillPairC;

namespace _STL {
template<> void _Construct<TreeKey00242F5E, TreeKey00242F5E>(TreeKey00242F5E *, const TreeKey00242F5E &);
template<> void _Construct<FillNoCasePair, FillNoCasePair>(FillNoCasePair *, const FillNoCasePair &);
template<> __declspec(nothrow) void _Construct<Rva0039A48EElement, Rva0039A48EElement>(Rva0039A48EElement *, const Rva0039A48EElement &);
template<> void _Construct<FillPairC, FillPairC>(FillPairC *, const FillPairC &);
template<> void _Construct<BfmeStringRecord005DDD40, BfmeStringRecord005DDD40>(BfmeStringRecord005DDD40 *, const BfmeStringRecord005DDD40 &);
template<> void _Construct<Rva0048130E, Rva0048130E>(Rva0048130E *, const Rva0048130E &);
template<> void _Construct<Rva002390CB, Rva002390CB>(Rva002390CB *, const Rva002390CB &);
template<> void _Construct<AsciiString, AsciiString>(AsciiString *, const AsciiString &);
template<> void _Construct<Rva0040CB11Entry, Rva0040CB11Entry>(Rva0040CB11Entry *, const Rva0040CB11Entry &);
template<> void _Construct<BfmeStringRecord002199C8, BfmeStringRecord002199C8>(BfmeStringRecord002199C8 *, const BfmeStringRecord002199C8 &);
template<> void _Construct<BfmeStringRecord00219A68, BfmeStringRecord00219A68>(BfmeStringRecord00219A68 *, const BfmeStringRecord00219A68 &);
// The retail allocate for this 20-byte record is the /G7 imul copy kept by the
// G7 growth TU; declare it so this /O1 TU does not emit the lea+shl copy.
template<> BfmeStringRecord00219A68 *allocator<BfmeStringRecord00219A68>::allocate(unsigned int, const void *) const;
}

template _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> >::vector(unsigned int, const TreeKey00242F5E &, const _STL::allocator<TreeKey00242F5E> &);
template _STL::vector<FillNoCasePair, _STL::allocator<FillNoCasePair> >::vector(unsigned int, const FillNoCasePair &, const _STL::allocator<FillNoCasePair> &);
template _STL::vector<FillPairC, _STL::allocator<FillPairC> >::vector(unsigned int, const FillPairC &, const _STL::allocator<FillPairC> &);
template _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> >::vector(unsigned int, const BfmeStringRecord005DDD40 &, const _STL::allocator<BfmeStringRecord005DDD40> &);
template _STL::vector<Rva0048130E, _STL::allocator<Rva0048130E> >::vector(unsigned int, const Rva0048130E &, const _STL::allocator<Rva0048130E> &);
template _STL::vector<Rva002390CB, _STL::allocator<Rva002390CB> >::vector(unsigned int, const Rva002390CB &, const _STL::allocator<Rva002390CB> &);
template _STL::vector<AsciiString, _STL::allocator<AsciiString> >::vector(unsigned int, const AsciiString &, const _STL::allocator<AsciiString> &);
template _STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> >::vector(unsigned int, const Rva0040CB11Entry &, const _STL::allocator<Rva0040CB11Entry> &);
template _STL::vector<BfmeStringRecord002199C8, _STL::allocator<BfmeStringRecord002199C8> >::vector(unsigned int, const BfmeStringRecord002199C8 &, const _STL::allocator<BfmeStringRecord002199C8> &);
template _STL::vector<BfmeStringRecord00219A68, _STL::allocator<BfmeStringRecord00219A68> >::vector(unsigned int, const BfmeStringRecord00219A68 &, const _STL::allocator<BfmeStringRecord00219A68> &);

// Target _M_insert_overflow 0x00399EBE calls the 37-byte fill worker at
// 0x003961F0; the worker calls the _Construct placement at 0x00396170.
template Rva0039A48EElement *_STL::__uninitialized_fill_n<Rva0039A48EElement *, unsigned int, Rva0039A48EElement>(Rva0039A48EElement *, unsigned int, const Rva0039A48EElement &, const _STL::__false_type &);

// Retail 0x005DE088 (27B): public _STL::uninitialized_fill_n for
// BfmeStringRecord005DDD40, forwarding first/n/value to the rowed 4-arg
// __uninitialized_fill_n 0x005DDDA5 with a false_type tag temporary.
// Unlock lane: caller is 0x005DE6EA in 0x005DE651/260.
template BfmeStringRecord005DDD40 *_STL::uninitialized_fill_n(BfmeStringRecord005DDD40 *, unsigned int, const BfmeStringRecord005DDD40 &);

// ?rva0049DD83@Rva0049DD83@@QAEXPAVINI@@PAX@Z @0x0049DD83 234B
// Bitstring-list INI driver, same shape as the KindOf driver Rva00256499
// (System/Rva00256499Parse.cpp) and its twins. The worker is the rowed
// 0x0049D67F single-token worker; Append, Tok, INI and the empty string
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


__forceinline const char *GetStr0049DD83(const Rva0033B84ETok &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

class Rva0049D67F
{
public:
	bool rva0049D67F(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva0049DD83 : public Rva0049D67F
{
public:
	void rva0049DD83(INI *ini, void *extra);
	void rva0049DD83Append(const char *s, Rva0033B84ETok *b);
};

void Rva0049DD83::rva0049DD83(INI *ini, void *extra)
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
				const char *s = GetStr0049DD83(part);
				rva0049DD83Append(s, accum);
				if (!rva0049D67F(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			rva0049DD83Append(token, accum);
			if (!rva0049D67F(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
