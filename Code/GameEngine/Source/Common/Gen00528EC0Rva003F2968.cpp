// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?rva003F2968@Gen_00528EC0@@QAEXF@Z, retail 0x003F2968 24B.
// Sets dword at +0x04 from obfuscated hook of a 16-bit value passed twice.
// Evidence: callers 0x003F3505 0x003F3511 pass Gen_00528EC0 objects; offset +4 matches m_bfmeValue in S5HandleHashCompares.cpp; callee rowed 0x003F1DD5.

int __cdecl Rva003F1DD5Hook(int a, int b);

class Gen_00528EC0
{
public:
	void rva003F2968(short v);
private:
	char m_head[4];
	unsigned int m_value; // +0x04
};

void Gen_00528EC0::rva003F2968(short v)
{
	m_value = (unsigned int)Rva003F1DD5Hook(v, v);
}
