// ?rva002DB4DA@Rva002DB4DA@@QAEPAURva002DB4DANode@@V?$StringBase@D@@@Z
// cl: /GX /MD
//
// Fix over the banked attempt: declare the leaf compare `throw()` so MSVC omits
// the `and dword ptr [ebp-4],0` unwind-state init, keep releaseBuffer a plain
// potentially-throwing declaration so the EH frame stays, and return the match
// from inside the loop (an early return) instead of `break` + a single return --
// the single-return form lets MSVC drop the frame entirely (45B). Same recipe
// as its sibling Rva002DB496Finish.cpp.
//
// ?rva002DB4DA@Rva002DB4DA@@QAEPAURva002DB4DANode@@V?$StringBase@D@@@Z @0x002DB4DA (68B).
// Rva002DB4DA::rva002DB4DA(): finds list node whose StringBase<char> at +4
// equals the by-value key. Retail walks head at this+0x10 via rowed
// StringBase<char>::compare at 0x000069D6 and destroys the key via rowed
// releaseBuffer at 0x00036410 with EH prolog at 0x00629188, returning the
// match in eax (ret 4). Callers include 0x0004FEDB 0x002DB55B 0x00456AA0.
// Prev 0x002DB463 array setter / next 0x002DB93E ctor share /O1.
template <typename T>
class StringBase
{
public:
	int compare(const StringBase<T> &str) const throw();
	~StringBase() { releaseBuffer(); }

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
	void releaseBuffer();
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


struct Rva002DB4DANode
{
	char m_pad0[4];
	StringBase<char> m_name;
	char m_pad1[8];
	Rva002DB4DANode *m_next;
};

struct Rva002DB4DA
{
	char m_pad[0x10];
	Rva002DB4DANode *m_head;
	Rva002DB4DANode *rva002DB4DA(StringBase<char> name);
};

Rva002DB4DANode *Rva002DB4DA::rva002DB4DA(StringBase<char> name)
{
	for (Rva002DB4DANode *cur = m_head; cur != 0; cur = cur->m_next) {
		if (cur->m_name.compare(name) == 0)
			return cur;
	}
	return 0;
}
