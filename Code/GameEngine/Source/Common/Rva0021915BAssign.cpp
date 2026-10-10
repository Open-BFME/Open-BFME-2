// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ??4Rva0021915B@@QAEAAV0@ABV0@@Z @0x0021915B 31B
// ??RRva0021B753@@QBE_NABVRva0021915B@@0@Z @0x0021B753 34B
// Honest-address copy-assignment for an 8-byte AsciiString-plus-bool entry.
// Retail: self-check (cmp this,other; je skip), AsciiString::operator= at +0
// via pinned 0x000366F0, byte copy at +4, return *this (mov eax,esi; ret 4).
// Evidence: element stride 8 in copy_backward caller 0x002195B7 (47B loop with
// sar 3); swap callers 0x0021ACB9/0x0021BAA3/0x0021BB61/0x0021C798/0x0021C8D7/
// 0x0021D39E drive per-element *dest=*src over the same 8B layout; temp pair
// copy ctor 0x005117F6 (pair<const AsciiString,char>) and releaseBuffer
// 0x00036410 in those callers prove AsciiString at +0 plus 1-byte mapped at
// +4 (size 8 with padding). bool (not unsigned char) proven by 0x0021B753
// comparator below: only bool gives byte-exact jne-return without test/setne.
// No donor; honest Rva name (never guess template args).
// Comparator 0x0021B753: strict-weak-ordering for Rva0021915B sorting (median
// 0x0021B9A0, linear-insert 0x0021BAA3, binary-heap 0x0021BB61, lower/upper
// 0x0021C6CB and callers 0x0021BB61/0x0021C798/0x0021C8D7/0x0021E4A5). Primary
// key bool at +4 (true-first: differ returns a.flag), secondary AsciiString
// at +0 via rowed StringBase<char>::compareNoCase 0x00006A00 <0. Empty
// comparator struct (this unused, ecx dead) proven by lea ecx at every caller.

#include "ascii_string.h"


class Rva0021915B
{
public:
	Rva0021915B &operator=(const Rva0021915B &other);
	friend struct Rva0021B753;

private:
	AsciiString m_str;
	bool m_byte;
};

Rva0021915B &Rva0021915B::operator=(const Rva0021915B &other)
{
	if (this != &other) {
		m_str = other.m_str;
		m_byte = other.m_byte;
	}
	return *this;
}

struct Rva0021B753
{
	bool operator()(const Rva0021915B &a, const Rva0021915B &b) const;
};

bool Rva0021B753::operator()(const Rva0021915B &a, const Rva0021915B &b) const
{
	if (a.m_byte != b.m_byte)
		return a.m_byte;
	return ((const StringBase<char> &)a.m_str).compareNoCase((const StringBase<char> &)b.m_str) < 0;
}
