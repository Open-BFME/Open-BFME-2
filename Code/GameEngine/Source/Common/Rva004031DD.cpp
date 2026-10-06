// cl: /DNDEBUG /MD
// AttributeModifierPoolUpdate::isCategoryDisabled (WorldBuilder name, AttributeModifier.cpp line 806: the +0x30 per-category table test).
// was ?rva004031DD@Rva004031DD@@QAEEH@Z retail 0x004031DD 22B
// Unsigned frame-vs-slot check: return TheGameLogic+0x40 < this[index] at +0x30.
// Evidence: mov eax [TheGameLogic] mov eax [eax+0x40] mov edx esp+4 cmp setb ret 4;
// neighbours AttributeModifierPoolUpdateRva / Rva004031F3 share flags; owner
// unproven so honest Rva name; caller 0x0050876D in FUN_00908684.
class GameLogic
{
public:
	char _pad[0x40];
	unsigned int m_40;
};
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A

class AttributeModifierPoolUpdate
{
public:
	unsigned char isCategoryDisabled(int index);
private:
	char _pad[0x30];
	unsigned int m_vals[1];
};

unsigned char AttributeModifierPoolUpdate::isCategoryDisabled(int index)
{
	return TheGameLogic->m_40 < m_vals[index];
}
