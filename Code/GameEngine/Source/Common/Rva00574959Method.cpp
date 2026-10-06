// cl: /O1 /DNDEBUG /MD
// ?rva00574959@Rva00574959@@QAEHHH@Z retail 0x00574959 79B
// The local object's matched constructor at 0x00574815 installs the vtable
// whose virtual slots the 0x005CBB4A helper dispatches through. The helper
// receives raw fields at outer offsets +0x1C and +0x44 plus this method's
// 32-bit argument; their meanings are unresolved. Cleanup uses the matched
// 0x005CB9F3 vtable-reset body through its existing address-derived owner.
class Rva0005CB9F3DwordImmSetter
{
public:
	void apply();
};

class Rva00574815
{
public:
	Rva00574815(int arg);
	void rva005CBB4A(int first, int second, int third);
	__forceinline ~Rva00574815()
	{
		((Rva0005CB9F3DwordImmSetter *)this)->apply();
	}

private:
	unsigned int m_layout[3];
};

class Rva00574959
{
public:
	int rva00574959(int arg, int unused);

private:
	char m_pad00[0x1c];
	int m_1c;
	char m_pad20[0x24];
	int m_44;
	char m_pad48[0x10];
	unsigned char m_58;
};

int Rva00574959::rva00574959(int arg, int unused)
{
	m_58 = 1;
	Rva00574815 local((int)this);
	local.rva005CBB4A(m_1c, arg, m_44);
	return 0;
}
