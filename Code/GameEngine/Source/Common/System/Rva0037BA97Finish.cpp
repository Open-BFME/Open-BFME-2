// cl: /EHsc /MD
// ?Rva0037BA97Init@@YA?AUTriple12@@PBUPair8@@H@Z @0x0037BA97 43B
// Value-returning (struct-return) Triple12 builder: loads the two ints of the
// Pair8 source, stores them plus the third argument into a stack temporary and
// copies it through the hidden return pointer. Evidence: exact 43-byte match;
// the target's `mov eax,[ebp+8]` / `mov edi,eax` pair is the hidden
// struct-return pointer, which a void dest-pointer signature cannot produce
// (that shape is 41B and pushes esi/edi before the tmp.b store). The banked
// void `...YAXPAUTriple12...` body was the 41B near miss. Neighbour
// Rva0037BA48Get (0x0037BA48) uses the same /O1 /EHsc struct-return recipe.
struct Pair8
{
	int a;
	int b;
};

struct Triple12
{
	int a;
	int b;
	int c;
};

// Select-any like the Rva0037D96B.cpp copy (this retail body comes first in link
// order, so it is the copy the link keeps); the anchor keeps the body emitted.
inline Triple12 __cdecl Rva0037BA97Init(const Pair8 *src, int c)
{
	Triple12 resultTriple;
	resultTriple.a = src->a;
	resultTriple.b = src->b;
	resultTriple.c = c;
	return resultTriple;
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva0037BA97Init@@YAXPBUPair8@@H@Z absent-from-retail
void bfmeEmitRva0037BA97Init(const Pair8 *src, int c)
{
	Rva0037BA97Init(src, c);
}

class AsciiString;
#include "../../../Include/Common/AsciiStringRef.h"
#include "../../../Include/Common/AsciiStringRefWithChar.h"
// Aggregate like Triple12 above (no user constructor), so the operator
// below builds it with plain stores and no EH registration.
struct Rva0002C9C2
{
	AsciiStringRefWithChar m_first;
	AsciiStringRef m_second;
};

// ICF-folded twin of Rva0037BA97Init above (same 43 bytes at 0x0037BA97):
// the narrow string+char concat node stores the same three dwords (two
// from the ref-with-char source, one from the string side) through the
// hidden return pointer with the same shape.
inline Rva0002C9C2 __cdecl operator+(const AsciiStringRefWithChar &left, const AsciiString &right)
{
	Rva0002C9C2 tmp;
	tmp.m_first = left;
	tmp.m_second.m_string = &right;
	return tmp;
}

// ?bfmeEmitRva0002C9C2Add@@YAXABUAsciiStringRefWithChar@@ABVAsciiString@@@Z absent-from-retail
void bfmeEmitRva0002C9C2Add(const AsciiStringRefWithChar &left, const AsciiString &right)
{
	operator+(left, right);
}
