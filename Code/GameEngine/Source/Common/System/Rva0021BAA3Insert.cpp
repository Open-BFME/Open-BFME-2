// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?Rva0021BAA3Insert@@YAXPAVRva0021915B@@V1@URva0021B753@@@Z @0x0021BAA3 89B
// __unguarded_linear_insert for 8-byte AsciiString-plus-bool entries with empty
// comparator Rva0021B753 (rowed 0x0021B753). Shifts while comp(val next) then
// stores val. Callees rowed: assign 0x0021915B, comparator 0x0021B753,
// releaseBuffer 0x00036410, EH_prolog. Callers 0x0021C798/0x0021C811.
// Evidence: same loop as Rva005B6324Insert 47B free-function precedent but with
// EH (val by value needs dtor) and per-element assign; stride 8 via lea/sub 8.

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

void __cdecl Rva0021BAA3Insert(Rva0021915B *last, Rva0021915B val, Rva0021B753 comp);

void __cdecl Rva0021BAA3Insert(Rva0021915B *last, Rva0021915B val, Rva0021B753 comp)
{
	Rva0021915B *next = last - 1;
	while (comp(val, *next)) {
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}
