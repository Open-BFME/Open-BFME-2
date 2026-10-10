// cl: /Ireference/shims/bfme2_ascii /Oy- /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002B0E55@Rva002B0E55@@QAEXPBUOther002B0E55@@PBVAsciiString@@@Z @0x002B0E55 138B: remove matching 0x24 record from vector at +0x3B0.
// Evidence: callers at 0x004B5A96 0x004B5AF1; neighbors GeometryInfoCopyConstructor plus StlportVectorGrowthFootprints; rowed StringBase compare plus Rva002AAC9EEqual plus Rva002ADD75Equal plus rva002AABEE plus the record vector erase at 0x2B0CB0 (its tail dtor is 0x2AF1EC and its copy loop assigns through 0x2AF505: not GeometryShape); stride 0x24 with name at +0 plus level at +4 plus float range at +8 plus ascii range at +0x14; arg ranges at +0x11C plus +0x130; erase path exits loop.
#include <vector>
#include "ascii_string.h"

struct Rva002AAC9ERange
{
	float const *m_begin;
	float const *m_end;
};

struct AsciiRange002ADD75
{
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
};

int __cdecl Rva002AAC9EEqual(Rva002AAC9ERange const *a, Rva002AAC9ERange const *b);
int __cdecl Rva002ADD75Equal(AsciiRange002ADD75 const *a, AsciiRange002ADD75 const *b);

class Rva002AABEE
{
public:
	void rva002AABEE();
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva002AF6C5Element
{
	~Rva002AF6C5Element();
	Rva002AF6C5Element &operator=(const Rva002AF6C5Element &other);

	unsigned char m_pad[0x24];
};

struct Elem002B0E55
{
	AsciiString m_name;
	unsigned m_level;
	_STL::vector<float> m_floats;
	_STL::vector<AsciiString> m_strings;
	float m_value;
};

struct Other002B0E55
{
	char m_pad00[0x11C];
	Rva002AAC9ERange m_range1;
	char m_pad124[0x130 - 0x124];
	AsciiRange002ADD75 m_range2;
};

class Rva002B0E55
{
public:
	void rva002B0E55(const Other002B0E55 *other, const AsciiString *name);
private:
	char m_pad00[0x3B0];
	_STL::vector<Rva002AF6C5Element> m_vec;
};

void Rva002B0E55::rva002B0E55(const Other002B0E55 *other, const AsciiString *name)
{
	_STL::vector<Rva002AF6C5Element> *vec = &m_vec;
	Elem002B0E55 *esi = (Elem002B0E55 *)m_vec.begin();
	if (esi == (Elem002B0E55 *)m_vec.end())
		return;
	for (;;) {
		if (esi->m_name.compare(*name) != 0)
			goto next;
		if ((unsigned char)Rva002AAC9EEqual((Rva002AAC9ERange *)&esi->m_floats, &other->m_range1) == 0)
			goto next;
		if ((unsigned char)Rva002ADD75Equal((AsciiRange002ADD75 *)&esi->m_strings, &other->m_range2) == 0)
			goto next;
		if (esi->m_level == 1) {
			vec->erase((Rva002AF6C5Element *)esi);
			return;
		}
		esi->m_level--;
		((Rva002AABEE *)esi)->rva002AABEE();
next:
		esi = (Elem002B0E55 *)((char *)esi + 0x24);
		if (esi == (Elem002B0E55 *)m_vec.end())
			return;
	}
}
