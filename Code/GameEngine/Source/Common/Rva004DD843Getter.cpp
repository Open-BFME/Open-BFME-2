// cl: /EHsc /DNDEBUG /MD
//
// ?rva004DD843@Rva004DD843@@QAEMXZ @ 0x004DD843 (10B).
// Thiscall float getter forwarding int at +0x24 through rowed
// ?Rva004DD722Get@@YAMH@Z at 0x004DD722. Evidence: caller at 0x0028AD67;
// prev/next both /O1.

float __cdecl Rva004DD722Get(int value);

class Rva004DD843
{
public:
	float rva004DD843();
private:
	unsigned char m_pad[0x24];
	int m_x24;
};

float Rva004DD843::rva004DD843()
{
	return Rva004DD722Get(m_x24);
}
