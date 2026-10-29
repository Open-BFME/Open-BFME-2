// ?rva004E060C@LivingWorldBuilding@@QAEXE@Z, retail 0x004E060C, 25 bytes.
// Chain from 0x0052B024 (Rva0052B024Loop.cpp): thiscall setter that forwards
// its unsigned-char arg to the rowed Rva0052B024::rva0052B024 via the member
// at +0x2C, then stores the byte at +0x51. Callers at 0x004E1186 and
// 0x004FA666 were unclaimed; LivingWorldBuilding::DoXfer (0x004E0E78) calls
// it on its own this, and +0x2C/+0x51 match that class's members.
// Prev 0x004E0605/next 0x004E0625 carry no // cl: line so defaults are used.
class Rva0052B024
{
public:
	void rva0052B024(unsigned char v);
};

class Rva0052B278;

class LivingWorldBuilding
{
public:
	void rva004E060C(unsigned char v);

private:
	char m_pad[0x2C];
	Rva0052B278 *m_2C;
	char m_pad30[0x51 - 0x30];
	unsigned char m_51;
};

void LivingWorldBuilding::rva004E060C(unsigned char v)
{
	((Rva0052B024 *)m_2C)->rva0052B024(v);
	m_51 = v;
}
