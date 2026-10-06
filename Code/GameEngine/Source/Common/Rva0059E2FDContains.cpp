// cl: /MD
// ?rva0059E2FD@Rva0059E2FD@@QAE_NABV?$StringBase@D@@@Z at 0x0059E2FD (34B). Vector-contains via rowed Find.
// Evidence: this+0x1C/+0x20 as begin/end into Rva000BD22FFind at 0xBD22F; cmp against end plus setne;
// chain lane via 0xBD22F; 16B thunk at 0x59E31F forwards same ecx with arg+0x14.
template <typename T> class StringBase {
	void *m_data;
};
StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val);

class Rva0059E2FD {
	unsigned char m_pad[0x14];
	StringBase<char> m_14;
	unsigned char m_pad18[4];
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
public:
	bool rva0059E2FD(const StringBase<char> &val);
	bool rva0059E31F(const Rva0059E2FD &o);
};

bool Rva0059E2FD::rva0059E2FD(const StringBase<char> &val)
{
	StringBase<char> *last = m_end;
	StringBase<char> *first = m_begin;
	return Rva000BD22FFind(first, last, val) != last;
}

bool Rva0059E2FD::rva0059E31F(const Rva0059E2FD &o)
{
	return rva0059E2FD(o.m_14);
}
