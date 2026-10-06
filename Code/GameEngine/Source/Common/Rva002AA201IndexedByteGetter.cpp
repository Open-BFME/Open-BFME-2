// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?get@Rva002AA201IndexedByteField@@QBEEH@Z @ 0x002AA201 (14B): indexed byte
// getter (mov eax,[esp+4] / mov al,[eax+ecx+0x340] / ret 4). Caller at 0x003E4C56
// passes [eax+0x54] with ecx=esi and tests al; prev 0x002AA14D is the Bonuses
// ctor and next 0x002AA21C is a disp32 dword getter. Identity unrecovered:
// opaque address-derived holder following the Rva004B0DA0 indexed-byte-clear
// precedent (m_flags[index] shape).
// ?set@Rva002AA201IndexedByteField@@QAEXH@Z @ 0x002AA1E4 (29B): indexed byte set
// plus frame (mov byte [eax+ecx+0x340],1 then TheGameLogic+0x40 to +0x354).
extern class GameLogic *TheGameLogic;

class Rva002AA201IndexedByteField
{
public:
	unsigned char get(int index) const;
	void set(int index);
private:
	char m_pad[0x340];
	unsigned char m_flags[1];
	char m_pad2[0x354 - 0x340 - 1];
	int m_frame;
};
unsigned char Rva002AA201IndexedByteField::get(int index) const
{
	return m_flags[index];
}
struct Rva002AA1E4GameLogic
{
	char m_pad[0x40];
	int m_frame;
};
#define TheGameLogic (*(Rva002AA1E4GameLogic **)&TheGameLogic)
void Rva002AA201IndexedByteField::set(int index)
{
	m_flags[index] = 1;
	m_frame = TheGameLogic->m_frame;
}
