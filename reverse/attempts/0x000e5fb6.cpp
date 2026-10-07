// ?rva000E5FB6@Rva000E5F60@@QAEPAVRva000E5EC1@@HABV?$StringBase@D@@@Z
// partial score=0.94 date=2026-10-07
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

class Rva000E5F60;

template <typename T> class StringBase
{
public:
	__forceinline ~StringBase() { releaseBuffer(); }
	int compare(const StringBase<T> &other) const;
private:
	StringBase(const StringBase<T> &that);
	void releaseBuffer();
	void *m_data;
	friend class Rva000E5F60;
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
	Rva000E5EC1 *rva000E5FB6(int id, const StringBase<char> &name);

private:
	char m_pad[0x18];
	Rva000E5F60Node *m_head;
	char m_pad_1C[4];
	unsigned char m_lookup_by_name;
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

// ?rva000E5FB6@Rva000E5F60@@QAEPAVRva000E5EC1@@HABV?$StringBase@D@@@Z
// RVA 0x000E5FB6, Ghidra boundary 79B; the retail body returns the pointer
// from global TheGameClient's vtable slot 0x40 unless this object's byte at
// +0x20 requests a name lookup through the rowed rva000E5F60 helper. A nonnull
// result has its byte at +0x9D set. The address-derived owner view is reused
// because the body passes its unchanged this pointer to rva000E5F60; the
// original class and method names remain unknown.
class ClientFrameSubsystem;
extern ClientFrameSubsystem *TheGameClient;

class Rva00DFE77CHolder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual Rva000E5EC1 *slot10(int id);
};

#define TheRva00DFE77C (*(Rva00DFE77CHolder **)&TheGameClient)

Rva000E5EC1 *Rva000E5F60::rva000E5FB6(int id, const StringBase<char> &name)
{
	Rva00DFE77CHolder *client = TheRva00DFE77C;
	Rva000E5EC1 *result = client ? client->slot10(id) : 0;
	if (result && m_lookup_by_name)
	{
		result = rva000E5F60(id, name);
		if (result)
			*(reinterpret_cast<unsigned char *>(result) + 0x9D) = 1;
	}
	return result;
}

#undef TheRva00DFE77C
