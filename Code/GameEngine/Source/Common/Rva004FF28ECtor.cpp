// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FF28E (50B): five-int init storing vtable 0xC63B34 plus +0x28,
// forwarding three ints to pinned 0x4FBC4D and one int to the 0x20E449
// copy body via a placeholder int alias (same address, no EH).
// Returns this as int. Identities unproven.

class Rva004FBC4D
{
public:
	void rva004FBC4D(int a, int b, int c);
};

class Rva0020E449Caller
{
public:
	void rva0020E449Copy(int src);
};

class Rva004FF28EOwner
{
public:
	int rva004FF28E(int a0, int a1, int a2, int a3, int a4);

private:
	int m_vptr;		// +0x00 = 0xC63B34
	char m_pad04[0x24];	// +0x04..0x27
	int m_28;		// +0x28 = a0
	char m_2C[16];		// +0x2C copy target for 0x20E449
};

int Rva004FF28EOwner::rva004FF28E(int a0, int a1, int a2, int a3, int a4)
{
	((Rva004FBC4D *)this)->rva004FBC4D(a2, a3, a4);
	*(int *)this = 0xC63B34;
	m_28 = a0;
	((Rva0020E449Caller *)m_2C)->rva0020E449Copy(a1);
	return (int)this;
}
