// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva004CF0FB@Rva004CF0FB@@QAEHH@Z @0x004CF0FB 24B
// Bounds-checked slot read returning 1 when out of range else dword at +0x120A0.
// Evidence: abuts prev 0x004CF0CD isPlayerSlotActive and next 0x004CF113 attachTransport; caller 0x0025E900 in 0x0025E75F; offset +0x120A0 matches m_120a0 in Rva004CF35DFunc and m_playerFlags in ConnectionManagerInit; honest address method.

class Rva004CF0FB
{
public:
	int rva004CF0FB(int slot);
private:
	char m_pad[0x120A0];
	int m_120A0[8];
};

int Rva004CF0FB::rva004CF0FB(int slot)
{
	if ((unsigned int)slot >= 8)
	{
		return 1;
	}

	return m_120A0[slot];
}
