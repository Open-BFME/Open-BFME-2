// cl: /EHsc /MD
// ?rva000C2AA4@Rva000C2AA4@@QAEXABVAsciiString@@@Z at 0x000C2AA4 (127B). Lowercased check-then-add.
// Evidence: empty/none early-outs via 0x1E2F/0x37DE0; temp copy via 0x365F0 plus toLower 0x36A70;
// Find 0xBD22F over vector at +0x78/+0x7C; push_back 0x2DBE6 when missing; release 0x36410.
template <typename T> class StringBase {
	friend class AsciiString;
	StringBase(const StringBase &);
	void releaseBuffer();
	void *m_data;
public:
	bool isEmpty() const;
	bool isNone() const;
	void toLower();
};
class AsciiString : public StringBase<char> {
public:
	AsciiString(const AsciiString &o) : StringBase<char>(o) {}
	~AsciiString() { releaseBuffer(); }
};
StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val);

namespace _STL {
template <typename T> class allocator {
};
template <typename T, typename A = allocator<T> > class vector {
	unsigned char m_data[12];
public:
	void push_back(const T &val);
};
}

class Rva000C2AA4 {
	unsigned char m_pad[0x78];
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
	void *m_end_of_storage;
public:
	void rva000C2AA4(const AsciiString &val);
};

void Rva000C2AA4::rva000C2AA4(const AsciiString &val)
{
	if (val.isEmpty() || val.isNone())
		return;
	AsciiString tmp(val);
	tmp.toLower();
	StringBase<char> *last = m_end;
	StringBase<char> *first = m_begin;
	if (Rva000BD22FFind(first, last, tmp) == last)
		((_STL::vector<AsciiString> *)((char *)this + 0x78))->push_back(tmp);
}
