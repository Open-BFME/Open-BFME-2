// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva0021B9A0Median@@YAABVRva0021915B@@ABV1@00URva0021B753@@@Z @0x0021B9A0 101B
// __median for 8-byte AsciiString-plus-bool entries with empty comparator
// Rva0021B753 (rowed 0x0021B753). Returns median of three const refs.
// Callees rowed: comparator 0x0021B753 (5 calls). Callers 0x0021F065.
// Evidence: same branch shape as STL __median with custom comparator; true-first
// bool primary plus nocase secondary proven by 0x0021B753; empty comp (lea ecx
// dead) proven by callers passing comp by value at [ebp+0x14].

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

struct Rva0021B753
{
	bool operator()(const Rva0021915B &a, const Rva0021915B &b) const;
};

const Rva0021915B &__cdecl Rva0021B9A0Median(const Rva0021915B &a, const Rva0021915B &b, const Rva0021915B &c, Rva0021B753 comp);

const Rva0021915B &__cdecl Rva0021B9A0Median(const Rva0021915B &a, const Rva0021915B &b, const Rva0021915B &c, Rva0021B753 comp)
{
	if (comp(a, b)) {
		if (comp(b, c))
			return b;
		else if (comp(a, c))
			return c;
		else
			return a;
	} else {
		if (comp(a, c))
			return a;
		else if (comp(b, c))
			return c;
		else
			return b;
	}
}
