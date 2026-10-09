// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPA_N@Z
// partial score=0.94 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Clean BFME1 FontLibraryBFMEAdjustFont.cpp at575ba2b04; donor supplies size/style interpolation.
// Native218468..21857E and styled font caller21857E establish table20 and records16.
// Function purpose follows source and target operations; original method name unknown.
#include <map>
#include "ascii_string.h"
namespace _STL {template<>struct less<AsciiString>{bool operator()(const AsciiString&a,const AsciiString&b)const{return a<b;}};}
struct Rva004779C0Vector
{
	char *m_first;
	char *m_last;
	char *m_end;
};

struct Rva00475680Node
{
	int m_color;
	Rva00475680Node *m_parent;
	Rva00475680Node *m_left;
	Rva00475680Node *m_right;
	AsciiString m_key;
	Rva004779C0Vector *m_value;
};

class Rva00475680Tree
{
public:
	Rva00475680Node *find(const AsciiString &key) const { return reinterpret_cast<Rva00475680Node *>(reinterpret_cast<const _STL::map<AsciiString,AsciiString> *>(this)->find(key)._M_node); }

	Rva00475680Node *m_header;
};

struct Gen00473A40Elem
{
	int m_inputSize;
	int m_outputSize;
	int m_flags;
	AsciiString m_name;
};

// STLport's __upper_bound takes its comparator BY VALUE, and retail hands it a
// 4-byte stack slot whose first byte it zeroes (`mov byte ptr [esp+0x10],0` at
// +0x43) before pushing the whole dword.  A real one-byte member assigned zero
// reproduces that exactly.  An EMPTY functor does not: value-initialising
// `Gen00473A40Less()` elides the store and the body comes out 259 bytes, which
// is why the earlier revision forced the byte with `*(unsigned char *)&less = 0`
// through a cast into an empty struct.  What the byte MEANS is still unknown --
// no member of this comparator is read here -- so it is spelled by its offset
// rather than given an invented name.
struct Gen00473A40Less
{
	bool operator()(const int &value, const Gen00473A40Elem &elem) const;

	
};

Gen00473A40Elem *Gen00473A40(Gen00473A40Elem *first,
	Gen00473A40Elem *last, const int &value, Gen00473A40Less,
	int *);

class FontLibrary
{
public:
	void rva00218468(AsciiString *name, float *size,
		bool *style);

	// Nothing before the tree is read here.  The landed sibling
	// FontLibraryBFME.cpp spells the real prefix (subsystem vtable, font list,
	// two STLport maps); this body witnesses none of it, so it stays a pad.
	char m_pad0x00[0x20];
	Rva00475680Tree m_fontSubstitution;
};

// ?rva00218468@FontLibrary@@QAEXPAVAsciiString@@PAMPAE@Z
void FontLibrary::rva00218468(AsciiString *name,
	float *size, bool *style)
{
	Rva00475680Tree *tree = &m_fontSubstitution;
	Rva00475680Node *node = tree->find(*name);
	if (node == tree->m_header)
		return;

	Rva004779C0Vector *list = node->m_value;
	if (list == 0)
		return;

	Gen00473A40Elem *first = (Gen00473A40Elem *)list->m_first;
	Gen00473A40Elem *last = (Gen00473A40Elem *)list->m_last;
	if ((((char *)last - (char *)first) & ~0x0f) == 0)
		return;

	
	Gen00473A40Elem *next = Gen00473A40(first, last, (int)*size,
		Gen00473A40Less(), 0);
	Gen00473A40Elem *previous;
	int flags;

	if (next != last && next != first)
	{
		previous = next - 1;
		if (previous->m_name.getLength() != 0)
			*name = previous->m_name;

		flags = previous->m_flags;
		*size = (float)previous->m_outputSize +
			(*size - (float)previous->m_inputSize) *
				((float)next->m_outputSize -
					(float)previous->m_outputSize) /
				((float)next->m_inputSize -
					(float)previous->m_inputSize);
	}
	else
	{
		previous = first;
		if (next == last)
			previous = last - 1;

		if (previous->m_name.getLength() != 0)
			((StringBase<char> *)name)->set(
				*(const StringBase<char> *)&previous->m_name);
		flags = previous->m_flags;
		*size = (float)previous->m_outputSize;
	}

	if (flags & 1)
		*style = 1;
	else if (flags & 2)
		*style = 0;
}
