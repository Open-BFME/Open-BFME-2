// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPAE@Z
// partial score=0.8182 date=2026-10-05
// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPAE@Z
// partial score=0.92 date=2026-10-01
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPAE@Z @0x00218468 278B: font substitution adjust with interpolation.
// Evidence: tree at this+0x20 via rowed _M_find 0x001F8437; vector first/last at +0/+4 with ~0x0f empty test; rowed Gen00473A40 upper bound 0x0021764D with (int)*size; both name assigns via rowed StringBase::set 0x000366F0; SSE lerp; flags bits 1/2 to style. BFME1 donor game/GameEngine/Source/GameClient/GUI/FontLibraryBFMEAdjustFont.cpp (tree +0x1C, same lerp, same Gen layout).
// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPAE@Z @0x00218468 present-unmatched
#include <map>

#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

struct Gen00473A40Elem
{
	int m_inputSize;
	int m_outputSize;
	int m_flags;
	AsciiString m_name;
};

struct Gen00473A40Less
{
	bool operator()(const int &value, const Gen00473A40Elem &elem) const;
	unsigned char m_pad0x00;
};

Gen00473A40Elem *Gen00473A40(Gen00473A40Elem *first, Gen00473A40Elem *last, const int &value, Gen00473A40Less, int *);

struct FontSubVector
{
	Gen00473A40Elem *m_first;
	Gen00473A40Elem *m_last;
	char *m_end;
};

class FontLibrary
{
public:
	void rva00218468(AsciiString *name, float *size, unsigned char *style);
private:
	char m_pad[0x20];
	_STL::map<AsciiString, AsciiString> m_substitution;
};

void FontLibrary::rva00218468(AsciiString *name, float *size, unsigned char *style)
{
	_STL::map<AsciiString, AsciiString>::iterator node = m_substitution.find(*name);
	if (node == m_substitution.end())
		return;
	FontSubVector *list = *(FontSubVector **)&node->second;
	if (list == 0)
		return;
	float *sizePtr = size;
	Gen00473A40Elem *first = list->m_first;
	Gen00473A40Elem *last = list->m_last;
	if ((((char *)last - (char *)first) & ~0x0f) == 0)
		return;
	Gen00473A40Less less;
	less.m_pad0x00 = 0;
	Gen00473A40Elem *next = Gen00473A40(first, last, (int)*sizePtr, less, 0);
	Gen00473A40Elem *previous;
	int flags;
	if (next != last && next != first)
	{
		previous = next - 1;
		if (previous->m_name.getLength() != 0)
			*name = previous->m_name;
		flags = previous->m_flags;
		*sizePtr = (float)previous->m_outputSize + (*sizePtr - (float)previous->m_inputSize) * ((float)next->m_outputSize - (float)previous->m_outputSize) / ((float)next->m_inputSize - (float)previous->m_inputSize);
	}
	else
	{
		previous = first;
		if (next == last)
			previous = last - 1;
		if (previous->m_name.getLength() != 0)
			*name = previous->m_name;
		flags = previous->m_flags;
		*sizePtr = (float)previous->m_outputSize;
	}
	if (flags & 1)
		*style = 1;
	else if (flags & 2)
		*style = 0;
}
