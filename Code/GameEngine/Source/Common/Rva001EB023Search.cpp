// cl: /MD
// ?rva001EB023@Rva001EB023@@QAEPAURva001EB023Elem@@AAVRva00376A62@@@Z at 0x001EB023 (54B). Struct-array search.
// Evidence: array at this+0xA4/+0xA8 stride 0xAC with StringBase at +4 into contains 0x376A62;
// returns found element else end; chain lane via 0x376A62; same loop as 0xFCA5A with structs.
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
	struct Rva001EB023Elem *rva001EB023(Rva00376A62 &val);
	bool rva001EB094(Rva00376A62 &val);
};

struct Rva001EB023Elem *Rva001EB023::rva001EB023(Rva00376A62 &val)
{
	struct Rva001EB023Elem *last = m_end;
	struct Rva001EB023Elem *first = m_begin;
	for (; first != last; ++first) {
		if (val.rva00376A62(first->m_str))
			return first;
	}
	return last;
}

bool Rva001EB023::rva001EB094(Rva00376A62 &val)
{
	struct Rva001EB023Elem *last = m_end;
	return rva001EB023(val) != last;
}
