// cl: /MD
// ?rva001EB0FB@Rva001EB0FB@@QAE_NAAVRva00376A62@@@Z at 0x001EB0FB (17B). Null-checked tail-forward.
// Evidence: this+0x10 as Rva001EB023* into 0x1EB094 with same arg; false when null;
// chain lane via 0x1EB094; tail jmp shape.
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
	bool rva00376A62(const StringBase<char> &val);
};
struct Rva001EB023Elem {
	unsigned char m_pad[4];
	StringBase<char> m_str;
	unsigned char m_tail[0xA4];
};
class Rva001EB023 {
	unsigned char m_pad[0xA4];
	struct Rva001EB023Elem *m_begin;
	struct Rva001EB023Elem *m_end;
public:
	bool rva001EB094(Rva00376A62 &val);
};

class Rva001EB0FB {
	unsigned char m_pad[0x10];
	class Rva001EB023 *m_ptr;
public:
	bool rva001EB0FB(Rva00376A62 &val);
};

bool Rva001EB0FB::rva001EB0FB(Rva00376A62 &val)
{
	Rva001EB023 *p = m_ptr;
	if (p)
		return p->rva001EB094(val);
	return false;
}
