// cl: /MD
// ?rva004FCA5A@Rva004FCA5A@@QAE PAXABVRva00376A62@@@Z at 0x004FCA5A (54B). Pointer-array search via forward.
// Evidence: array at this+0xA4/+0xA8 of Rva00376A62*; call 0x59E872 with arg; return [found+4] else null;
// chain lane via 0x59E872; same loop shape as tree predicate without tree.
template <typename T> class StringBase {
	void *m_data;
};
class Rva00376A62 {
	unsigned char m_pad[8];
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
	void *m_end_of_storage;
	StringBase<char> m_14;
public:
	bool rva0059E872(const Rva00376A62 &o);
};

class Rva004FCA5A {
	unsigned char m_pad[0xA4];
	Rva00376A62 **m_begin;
	Rva00376A62 **m_end;
public:
	void *rva004FCA5A(const Rva00376A62 &val);
};

void *Rva004FCA5A::rva004FCA5A(const Rva00376A62 &val)
{
	Rva00376A62 **last = m_end;
	Rva00376A62 **first = m_begin;
	for (; first != last; ++first) {
		Rva00376A62 *p = *first;
		if (p->rva0059E872(val))
			return *(void **)((char *)p + 4);
	}
	return 0;
}
