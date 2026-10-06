// cl: /MD
// Retail 0x00689380 (69B). Three-string-plus-POD record copy ctor: each
// string member copies via StringBase<char>::set at 0x366F0 (the retail
// inlined AsciiString assignment path, NOT the 0x365F0 ctor family), then the
// bytes and dwords copy inline. Transferred from the BFME1 reconstruction
// (Rva000C3380Copy.cpp); member layout and call shape match retail exactly.
// Members use the implicit trivial default ctor (no AsciiString() defined,
// so this TU emits no ??0AsciiString copy); retail never calls it.

template <class T> class StringBase
{
public:
	void set(const StringBase<T> &other);
};

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	char *m_data;
};

class Rva000C3380
{
	AsciiString m_00;
	AsciiString m_04;
	AsciiString m_08;
	char m_0C;
	int m_10;
	char m_14;
	int m_18;

public:
	Rva000C3380(const Rva000C3380 &other);
};

// ??0Rva000C3380@@QAE@ABV0@@Z
Rva000C3380::Rva000C3380(const Rva000C3380 &other)
{
	((StringBase<char> *)&m_00)->set(*(const StringBase<char> *)&other.m_00);
	((StringBase<char> *)&m_04)->set(*(const StringBase<char> *)&other.m_04);
	((StringBase<char> *)&m_08)->set(*(const StringBase<char> *)&other.m_08);
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:??4Video@@QAEAAV0@ABV0@@Z=??0Rva000C3380@@QAE@ABV0@@Z")
