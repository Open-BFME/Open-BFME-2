// cl: /O1 /EHsc
// ??0Rva0020561C@@QAE@ABU?$pair@VAsciiString@@V1@@_STL@@ABV?$StringBase@D@@@Z @0x0020561C 57B
// Honest placeholder ctor: pair<AsciiString,AsciiString> at +0 via rowed
// 0x0020492B plus StringBase<char> at +8 via pinned 0x000365F0, returns this.
// Layout read from retail stores (pair copy then lea ecx esi+8). Callers at
// 0x0020569C and 0x0020ACE6. Pair/string decls mirror StringRecordInlineCopy.

template <typename T> class StringBase
{
	friend class AsciiString;
	friend struct Rva0020561C;
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
	void *m_data;

public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

namespace _STL {
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
	pair(const pair<T1, T2> &other);
	~pair();
};
}

struct Rva0020561C
{
	_STL::pair<AsciiString, AsciiString> m_pair; // +0
	StringBase<char> m_str; // +8
	Rva0020561C(const _STL::pair<AsciiString, AsciiString> &p, const StringBase<char> &s);
};

Rva0020561C::Rva0020561C(const _STL::pair<AsciiString, AsciiString> &p, const StringBase<char> &s)
	: m_pair(p), m_str(s)
{
}
