// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ireference/open-bfme-1/Code/GameEngine/Source/Common

class Rva003F7520
{
	char m_pad[0xC];
	unsigned m_lead : 21;
	unsigned m_bit : 1;

public:
	void set(unsigned char value);
};

void Rva003F7520::set(unsigned char value)
{
	m_bit = value;
}
