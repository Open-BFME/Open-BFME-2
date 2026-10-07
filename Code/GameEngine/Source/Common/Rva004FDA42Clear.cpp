// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FDA42 (32B): call 0x1F34BA, then free the +0x101C pointer via
// rowed FreeGame when non-null and clear it. Identities unproven.

class Rva001F34BA
{
public:
	void rva001F34BA();
};

extern "C" void __cdecl FreeGame(void *p);

class Rva004FDA42Owner
{
public:
	void rva004FDA42();

private:
	char m_pad[0x101C];	// +0x00..0x101B
	void *m_101C;		// +0x101C freed pointer
};

void Rva004FDA42Owner::rva004FDA42()
{
	((Rva001F34BA *)this)->rva001F34BA();
	void *p = m_101C;
	if (p)
		FreeGame(p);
	m_101C = 0;
}
