// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?find@Rva004CABE5Store@@QAE_NHPAURva002C99FB@@PBVRva000CF0D6@@@Z @0x004CABE5 74B.
// Find BfmeObject544 in vector via bit test plus indexed assign.
// Evidence: callees rowed 0x000CF0D6 0x002C99FB; caller 0x004CAC43; stride 0x220 proves 544B.
#include <vector>
#include <set>

class Rva000CF0D6
{
public:
	bool test(const Rva000CF0D6 *other) const;
	unsigned int m_bits[19];
};

#include "../../Include/Common/OpaqueRefElement4.h"

struct Rva002C99FB
{
	int m_first;
	OpaqueRefElement4 m_second;
	Rva002C99FB &operator=(const Rva002C99FB &other);
};

struct BfmeStringRecord002CF550
{
	bool operator<(const BfmeStringRecord002CF550 &other) const { return false; }
	char m_pad[0x10];
};

struct BfmeObject544View
{
	Rva000CF0D6 m_bits;
	Rva002C99FB m_arr[0x38];
	_STL::set<BfmeStringRecord002CF550> m_set;
	char m_tail[8];
};

// The sibling selector view observes begin/end at +08/+0C. The old vector
// spans +08..+14 (compiler layout); preserve its unread tail as padding.
struct Rva004CAB8BRecord;
class Rva004CABE5Store
{
public:
	bool find(int idx, Rva002C99FB *dest, const Rva000CF0D6 *tester);
private:
	char m_pad[8];
	Rva004CAB8BRecord *m_begin;
	Rva004CAB8BRecord *m_end;
	char m_pad10[4];
};

bool Rva004CABE5Store::find(int idx, Rva002C99FB *dest, const Rva000CF0D6 *tester)
{
	BfmeObject544View *finish = (BfmeObject544View *)m_end;
	BfmeObject544View *it = (BfmeObject544View *)m_begin;
	for (; it != finish; ++it) {
		if (!tester->test((const Rva000CF0D6 *)it))
			continue;
		if (*(int *)&it->m_arr[idx].m_second == 0)
			continue;
		*dest = it->m_arr[idx];
		return true;
	}
	return false;
}
