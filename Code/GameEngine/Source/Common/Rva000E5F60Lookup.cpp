// cl: /MD /EHs
//
// ?rva000E5F60@Rva000E5F60@@QAEPAVRva000E5EC1@@HV?$StringBase@D@@@Z
// RVA 0x000E5F60, 86B. List-find by (id, name) over a sentinel-circular list
// at +0x18 (next at +0x00, item at +0x08); the matcher is
// Rva000E5EC1::rva000E5EC1 (id at +0x4C, name at +0x8C via a StringBase
// compare). Returns the item or 0.
//
// Recovered from the banked body reverse/attempts/0x000e5f60.cpp (verdict
// 2026-09-28, partial score=1.0): the bytes were already exact, and the only
// thing blocking the landing was the commit gate. Written verbatim from that
// attempt otherwise, because its author had already proved the shape.
//
// WHY THE GATE REFUSED IT, AND THE ONE-LINE FIX. The by-value StringBase<char>
// parameter needs the temporary destroyed, and a destructor defined inside the
// class is an inline member: MSVC emits it as a COMDAT, so the TU defines a
// symbol the ledger does not declare and find_declared_unmatched refuses the
// whole source -- reported at the time as a false positive, and it is one, but
// it is also avoidable. Marking the destructor __forceinline keeps it inlined
// instead of emitted, so the bytes are unchanged and the TU defines only the
// body it was written for. `SmallGaps/Rva0083ED40StreamStateReport.cpp` landed
// through the same door.
//
// The callees are already rowed, so no pin is needed: releaseBuffer at
// 0x00036410 and Rva000E5EC1::rva000E5EC1 at 0x000E5EC1.

template <typename T> class StringBase
{
public:
	__forceinline ~StringBase() { releaseBuffer(); }
	int compare(const StringBase<T> &other) const;
private:
	void releaseBuffer();
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva000E5EC1
{
public:
	bool rva000E5EC1(int id, const StringBase<char> &name) const throw();
};

struct Rva000E5F60Node
{
	Rva000E5F60Node *m_next;
	Rva000E5F60Node *m_prev;
	Rva000E5EC1 *m_item;
};

class Rva000E5F60
{
public:
	Rva000E5EC1 *rva000E5F60(int id, StringBase<char> name);

private:
	char m_pad[0x18];
	Rva000E5F60Node *m_head;
};

Rva000E5EC1 *Rva000E5F60::rva000E5F60(int id, StringBase<char> name)
{
	Rva000E5F60Node *cur = m_head->m_next;
	while (cur != m_head)
	{
		if (cur->m_item->rva000E5EC1(id, name))
			return cur->m_item;
		cur = cur->m_next;
	}
	return 0;
}
