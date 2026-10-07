// cl: /MD
// ?rva0023DCCE@Rva0023DCCE@@QAEXABVAsciiString@@ABUOpaqueRefElement4@@1@Z — RVA 0x0023DCCE, 122B.
// Conditional copy-or-clear: if arg string empty or global flag [0x009FE758]+0x9AD set,
// release AsciiString member +0x84 and clear two OpaqueRef members +0x88/+0x8c, flag +0x72=0;
// else copy all three args and set flag=1.
// Evidence: retail branch bytes; callees rowed (isEmpty 0x1E2F, StringBase set 0x366F0,
// OpaqueRef op= 0x239099, releaseBuffer 0x36410, clear 0xA8C9B); callers at 0x1EB5A3 0x21258A 0x242953 0x2B3739 0x515598.

class Rva0023DC8E;

template <typename T> class StringBase
{
public:
	bool isEmpty() const;
	void set(const StringBase<T> &other);
private:
	void releaseBuffer();
	T *m_data;
	friend class Rva0023DCCE;
	friend class Rva0023DC8E;
};

class AsciiString : public StringBase<char>
{
};

struct OpaqueRefElement4
{
	void *m_ptr;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva000A8C9B
{
	void *m_ptr;
	void clear();
};

class GlobalData
{
public:
	char m_pad[0x9AD];
	unsigned char m_flag9AD;
};
extern GlobalData *TheWritableGlobalData;

class Rva0023DCCE
{
public:
	void rva0023DCCE(const AsciiString &a, const OpaqueRefElement4 &b, const OpaqueRefElement4 &c);
	char m_00[0x72];
	unsigned char m_flag;
	char m_01[0x11];
	AsciiString m_str;
	OpaqueRefElement4 m_a;
	OpaqueRefElement4 m_b;
};

void Rva0023DCCE::rva0023DCCE(const AsciiString &a, const OpaqueRefElement4 &b, const OpaqueRefElement4 &c)
{
	if (a.isEmpty() || TheWritableGlobalData->m_flag9AD)
	{
		m_flag = 0;
		((StringBase<char> *)&m_str)->releaseBuffer();
		((Rva000A8C9B *)&m_a)->clear();
		((Rva000A8C9B *)&m_b)->clear();
	}
	else
	{
		m_flag = 1;
		((StringBase<char> *)&m_str)->set(a);
		m_a = b;
		m_b = c;
	}
}

// Ghidra FUN_0063dc8e is a 64-byte sibling immediately before this setter.
// It applies the same empty-string/global-flag condition to a single string
// member at +0x74; its host identity remains address-derived.
class Rva0023DC8E
{
public:
	void rva0023DC8E(const AsciiString &value);

private:
	char m_pad00[0x72];
	unsigned char m_flag;
	char m_pad73;
	AsciiString m_string;
};

void Rva0023DC8E::rva0023DC8E(const AsciiString &value)
{
	if (value.isEmpty() || TheWritableGlobalData->m_flag9AD)
	{
		m_flag = 0;
		((StringBase<char> *)&m_string)->releaseBuffer();
	}
	else
	{
		m_flag = 1;
		((StringBase<char> *)&m_string)->set(value);
	}
}
// ?TheWritableGlobalData@@3PAVGlobalData@@A: the global at VA 0xdfe758.
