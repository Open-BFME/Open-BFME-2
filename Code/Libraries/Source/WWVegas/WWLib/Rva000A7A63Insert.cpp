// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?rva000A7A63@Rva000427195@@QAEPAXPBU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z retail 0x000A7A63 68 bytes.
// Hash-table insert: reserve(count+1) via rowed rva00212858, bucketIndex via rowed EvaBucketIndex,
// create 12B node via rowed Rva000A7976Create, link buckets[idx], count++, return pair (block+4).
// Evidence: calls to 0x00212858 pin Rva000427195 reserve, 0x00223149 bucketIndex row, 0x000A7976 Create row;
// caller 0x000A7B3C passes pair at ebp-0x18 (AsciiString copy plus zeroed value) and returns pair+4;
// this layout +4 buckets +0x10 count matches EvaBucketIndex begin/end plus count.
#include "ascii_string.h"
#include <map>

struct NoCaseTreeValue4
{
public:
	unsigned char m_data[4];
};

class Rva000427195
{
public:
	void rva00212858(unsigned int count);
	int bucketIndex(const AsciiString *name);
	void *rva000A7A63(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src);
	void *rva000A7976(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src);
private:
	void *m_00;
	void **m_buckets;
	void *m_08;
	void *m_0C;
	unsigned int m_count;
};

void *Rva000427195::rva000A7A63(const _STL::pair<const AsciiString, NoCaseTreeValue4> *src)
{
	rva00212858(m_count + 1);
	int idx = bucketIndex((const AsciiString *)src);
	void *old = m_buckets[idx];
	void *block = rva000A7976(src);
	*(void **)block = old;
	m_buckets[idx] = block;
	++m_count;
	return (char *)block + 4;
}
