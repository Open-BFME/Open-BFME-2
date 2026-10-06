// cl: /MD
// ?rva004E2CD5@Rva004E2CD5@@QAE_NABV?$StringBase@D@@@Z at 0x004E2CD5 (34B). Vector-contains via rowed Find.
// Evidence: this+0x38/+0x3C as begin/end into Rva000BD22FFind at 0xBD22F; cmp against end plus setne;
// chain lane via 0xBD22F; same last-first locals shape as 0x59E2FD and 0x376A62.
template <typename T> class StringBase {
	void *m_data;
};
StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val);

class Rva004E2CD5 {
	unsigned char m_pad[0x38];
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
public:
	bool rva004E2CD5(const StringBase<char> &val);
};

bool Rva004E2CD5::rva004E2CD5(const StringBase<char> &val)
{
	StringBase<char> *last = m_end;
	StringBase<char> *first = m_begin;
	return Rva000BD22FFind(first, last, val) != last;
}
