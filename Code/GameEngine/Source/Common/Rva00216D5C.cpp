// cl: /DNDEBUG /MD /EHsc
// ?rva00216D5C@Rva000427195@@QAEPAU?$pair@$$CBVAsciiString@@VGen_003A8BE0@@@_STL@@ABU23@@Z, retail 0x00216D5C, 68 bytes.
// Evidence: reserve pin 0x00212858 plus bucketIndex row 0x00223149 plus buy-node row 0x00216762;
// caller 0x00216FE9; twin of Rva0046AC30 create-node style with hash insert.
class AsciiString;
class Gen_003A8BE0;

namespace _STL
{
template <class _T1, class _T2> struct pair;
}

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *key);
	_STL::pair<const AsciiString, Gen_003A8BE0> *rva00216D5C(const _STL::pair<const AsciiString, Gen_003A8BE0> &v);
private:
	char m_pad00[4];
	void **m_buckets; // +4
	char m_pad08[8];
	int m_count; // +0x10
};

class Rva00216762
{
public:
	void *rva00216762(const _STL::pair<const AsciiString, Gen_003A8BE0> &v);
};

_STL::pair<const AsciiString, Gen_003A8BE0> *Rva000427195::rva00216D5C(const _STL::pair<const AsciiString, Gen_003A8BE0> &v)
{
	rva00212858(m_count + 1);
	int idx = bucketIndex((const AsciiString *)&v);
	void *old = m_buckets[idx];
	void *node = ((Rva00216762 *)this)->rva00216762(v);
	*(void **)node = old;
	m_buckets[idx] = node;
	++m_count;
	return (_STL::pair<const AsciiString, Gen_003A8BE0> *)((char *)node + 4);
}
