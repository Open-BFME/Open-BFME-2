// cl: /EHsc /MD
//
// ?rva002DCDBF@Rva002DCDBF@@QAEPAXV?$StringBase@D@@H@Z, retail 0x002DCDBF, 101 bytes.
// Bucketed circular-list find by AsciiString key: bucket = this+0x10[index],
// walk sentinel list comparing node text at +12 via rowed compare 0x000069D6,
// return node+8 on match else NULL with rowed releaseBuffer 0x00036410 for
// the by-value key. Evidence: same compare/release callees and ret-8 two-arg
// shape as Rva00239C5EFind; bucket lea and empty-key early-outs read off the
// disassembly; callers 0x002DCE24 0x002DEEC3. Honest address name.
template <typename T> class StringBase
{
	friend class Rva002DCDBF;
public:
	StringBase(const StringBase &o);
	int compare(const StringBase &o) const throw();
	__forceinline ~StringBase() { releaseBuffer(); }
	struct Header { int ref; unsigned short len, cap; T data[1]; };
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

struct Rva002DCDBFNode {
	Rva002DCDBFNode *m_next;
	void *m_pad04;
	void *m_ret08;
	StringBase<char> m_text;
};
class Rva002DCDBF
{
	char m_pad[0x10];
	Rva002DCDBFNode *m_buckets[1];
public:
	void *rva002DCDBF(StringBase<char> key, int index);
};

void *Rva002DCDBF::rva002DCDBF(StringBase<char> key, int index)
{
	if (key.m_data == 0)
		return 0;
	if (((StringBase<char>::Header *)key.m_data)->len == 0)
		return 0;
	Rva002DCDBFNode **bkt = &m_buckets[index];
	Rva002DCDBFNode *cur = (*bkt)->m_next;
	while (cur != *bkt) {
		void *found = (char *)cur + 8;
		if (((StringBase<char> *)((char *)found + 4))->compare(key) == 0)
			return found;
		cur = cur->m_next;
	}
	return 0;
}
