// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?Rva000696C0Distance@@YAHABURva000696C0Iterator@@0@Z
// retail 0x002174CF, 16 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/SixteenByteIteratorArithmetic.cpp
// (reference/open-bfme-1). The donor body recompiled /Os is byte-identical to
// retail once relocations are masked (unique masked placement on unclaimed
// .text). Only the placed body is defined here; the donor's other eleven
// definitions are omitted.
//
// WHAT THE BYTES SHOW.  Nothing in ecx on entry and a plain `ret`: __cdecl,
// caller-cleaned.  The argument that names an iterator is dereferenced once
// before use (`mov eax,[eax]`), so the iterator arrives BY ADDRESS -- by
// reference -- and its whole representation is the single pointer at offset 0.
//
// `sar eax,4` on a pointer difference: the element is SIXTEEN BYTES wide.
//
// THE ARGUMENT ORDER IS A SIGNATURE FACT, not scheduling noise.  distance reads
// its SECOND argument first and subtracts the first from it, so it returns
// `last - first`.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the container this
// iterates, so the name is address-derived and disclaims identity.

struct Rva000696C0Element
{
	int m_word0;
	int m_word1;
	int m_word2;
	int m_word3;
};

struct Rva000696C0Iterator
{
	Rva000696C0Element *m_current;
};

int Rva000696C0Distance( const Rva000696C0Iterator &first, const Rva000696C0Iterator &last );

int Rva000696C0Distance( const Rva000696C0Iterator &first, const Rva000696C0Iterator &last )
{
	return last.m_current - first.m_current;
}