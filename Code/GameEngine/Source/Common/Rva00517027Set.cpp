// cl: /MD
// ?rva00517027@Rva00517027@@QAEXPBD@Z @0x00517027 33B
// Conditional string set: if StringBase at +0x28C isEmpty via rowed
// 0x00001E2F then set via rowed 0x000055F5 with the const char arg.
// Callers at 0x0057039B and 0x0056DC79; sole rowed callees.
template <typename T> class StringBase
{
public:
	bool isEmpty() const;
	void set(const char *str);
private:
	void *m_data;
};

struct Rva00517027
{
	unsigned char m_pad[0x28C];
	StringBase<char> m_28C;
	void rva00517027(const char *str);
};

void Rva00517027::rva00517027(const char *str)
{
	if (m_28C.isEmpty())
		m_28C.set(str);
}
