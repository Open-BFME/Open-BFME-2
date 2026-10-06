// cl: /EHsc /MD
// ?rva00239C5E@Rva00239C5E@@QAEPAXV?$StringBase@D@@@Z @0x00239C5E 89B: circular-list find by string key at this+0xF4 compare node+8 return node+8 else NULL. Evidence: same head offset as 0x002399EB callers at 0x0023ACB3 0x0023B5D5 callees compare 0x000069D6 releaseBuffer 0x00036410.
template <typename T> class StringBase
{
public:
	StringBase(const StringBase &o);
	int compare(const StringBase &o) const throw();
	__forceinline ~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

struct Rva00239C5ENode {
	Rva00239C5ENode *m_next;
	void *m_link1;
	StringBase<char> m_text;
};
class Rva00239C5E
{
	char m_pad[0xF4];
	Rva00239C5ENode *m_head;
public:
	void *rva00239C5E(StringBase<char> key);
};
void *Rva00239C5E::rva00239C5E(StringBase<char> key)
{
	Rva00239C5ENode *cur = m_head->m_next;
	while (cur != m_head) {
		StringBase<char> &slot = cur->m_text;
		if (slot.compare(key) == 0)
			return (void *)((char *)cur + 8);
		cur = cur->m_next;
	}
	return 0;
}
