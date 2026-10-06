// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002039B6@Rva002039B6Host@@QAEXXZ at retail 0x002039B6 (15B).
// Copies TheGameLogic->m_frame (+0x40) into this+0x1A15C.
// Target evidence: mov eax,[0xDFE78C]; mov eax,[eax+0x40];
// mov [ecx+0x1A15C],eax. Callers (e.g. 0x002A9D02) pass TheScriptEngine
// in ecx. GameLogic m_frame +0x40 is the established BFME2 layout
// (GameLogicAwakenUpdate precedent).

class GameLogic
{
public:
	char m_pad[0x40]; // +0x00..0x40
	int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;


class Rva002039B6Host
{
public:
	void rva002039B6();

private:
	char m_pad[0x1A15C]; // +0x00..0x1A15C
	int m_cachedFrame; // +0x1A15C
};

void Rva002039B6Host::rva002039B6()
{
	m_cachedFrame = TheGameLogic->m_frame;
}
