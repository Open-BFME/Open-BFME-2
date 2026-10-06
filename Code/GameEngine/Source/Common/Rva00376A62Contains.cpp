// cl: /MD
// ?rva00376A62@Rva00376A62@@QAE_NABV?$StringBase@D@@@Z at 0x00376A62 (34B). Vector-contains via rowed Find.
// Evidence: this+0x08/+0x0C as begin/end into Rva000BD22FFind at 0xBD22F; cmp against end plus setne;
// chain lane via 0xBD22F; same last-first locals shape as 0x59E2FD.
template <typename T> class StringBase {
	void *m_data;
};
StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val);

class AsciiString : public StringBase<char> {
};

namespace _STL {
template <typename T> class allocator {
};
template <typename T, typename A = allocator<T> > class vector {
	unsigned char m_data[12];
public:
	void push_back(const T &val);
};
}

class Rva00376A62 {
	unsigned char m_pad[8];
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
	void *m_end_of_storage;
	StringBase<char> m_14;
public:
	bool rva00376A62(const StringBase<char> &val);
	bool rva00376A84(const void *o);
	void rva00376B50(const AsciiString &val);
	bool rva0059E872(const Rva00376A62 &o);
};

bool Rva00376A62::rva00376A62(const StringBase<char> &val)
{
	StringBase<char> *last = m_end;
	StringBase<char> *first = m_begin;
	return Rva000BD22FFind(first, last, val) != last;
}

bool Rva00376A62::rva00376A84(const void *o)
{
	if (!o)
		return false;
	return rva00376A62(*(const StringBase<char> *)((const char *)o + 0x64));
}

void Rva00376A62::rva00376B50(const AsciiString &val)
{
	if (!rva00376A62(val))
		((_STL::vector<AsciiString> *)((char *)this + 8))->push_back(val);
}

bool Rva00376A62::rva0059E872(const Rva00376A62 &o)
{
	return rva00376A62(o.m_14);
}
