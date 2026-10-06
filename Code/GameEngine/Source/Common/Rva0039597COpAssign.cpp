// cl: /MD /Ireference/shims/bfme2_ascii
//
// ?rva0039597C@Rva0039597C@@QAEAAV1@ABV1@@Z, retail 0x0039597C, 39 bytes.
// Copy-assignment over two AsciiStrings plus int at +8, returning *this.
// Calls rowed StringBase<char>::set at 0x000366F0 twice (inlined through
// shared AsciiString::operator=), then int copy, then return *this via mov
// eax,esi. Prev allocator/StringRecordCopyBFME2 and next CastleMemberBehavior
// share the 00395xxx page; AsciiString via shared header (str/set inline
// through StringBase, literals link).
#include "ascii_string.h"

class Rva0039597C
{
public:
	Rva0039597C &rva0039597C(const Rva0039597C &other);
private:
	AsciiString m_00;
	AsciiString m_04;
	int m_08;
};
Rva0039597C &Rva0039597C::rva0039597C(const Rva0039597C &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	return *this;
}

// ?Rva00395D45Copy@@YAPAVRva0039597C@@PAV1@00@Z, retail 0x00395D45, 50 bytes.
// Chain from 0x0039597C: array copy of 0x0C-sized Rva0039597C via rowed
// copy-assign. Count from pointer difference (sub+cdq+idiv 12), EBP frame,
// dec/jne loop advancing both ends by 0x0C, returns advanced dest.
Rva0039597C *Rva00395D45Copy(Rva0039597C *first, Rva0039597C *last, Rva0039597C *dest)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (; n > 0; --n)
	{
		dest->rva0039597C(*first);
		++first;
		++dest;
	}
	return dest;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva00395D45CopyAux@@YAPAVRva0039597C@@PAV1@00PADH@Z=?Rva00395D45Copy@@YAPAVRva0039597C@@PAV1@00@Z")
