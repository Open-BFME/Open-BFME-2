// cl: /MD
// AptOnlineShell::LoadChildScreen (WorldBuilder name, AptOnlineShell.cpp line 480: set the pending child screen name at +0x28C).
// was ?rva00517027@Rva00517027@@QAEXPBD@Z @0x00517027 33B
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

class AptOnlineShell
{
public:
	unsigned char m_pad[0x28C];
	StringBase<char> m_28C;
	void LoadChildScreen(const char *str);
};

void AptOnlineShell::LoadChildScreen(const char *str)
{
	if (m_28C.isEmpty())
		m_28C.set(str);
}
