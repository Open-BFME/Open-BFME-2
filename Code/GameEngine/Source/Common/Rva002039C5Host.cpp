// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002039C5@Rva002039C5Host@@QAEXXZ at retail 0x002039C5 (15B).
// Copies TheGameLogic->m_frame (+0x40) into this+0x1A160, the sibling of
// ?rva002039B6@Rva002039B6Host@@QAEXXZ (+0x1A15C).
// Target evidence: mov eax,[0xDFE78C]; mov eax,[eax+0x40];
// mov [ecx+0x1A160],eax. Caller at 0x0039D8C4.

class GameLogic
{
public:
	char m_pad[0x40]; // +0x00..0x40
	int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;


class Rva002039C5Host
{
public:
	void rva002039C5();

private:
	char m_pad[0x1A160]; // +0x00..0x1A160
	int m_cachedFrame; // +0x1A160
};

void Rva002039C5Host::rva002039C5()
{
	m_cachedFrame = TheGameLogic->m_frame;
}
