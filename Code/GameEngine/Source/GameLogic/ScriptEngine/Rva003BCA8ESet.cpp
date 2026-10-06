// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCA8ESet@@YGX_N@Z @0x003BCA8E 19B: script sets GameLogic +0x9b byte from bool arg.
// Evidence: mov al,[esp+4] mov ecx,[0xDFE78C]=TheGameLogic mov [ecx+0x9b],al ret 4; caller 0x003CD7E0; sibling Rva003BCA7BSet +0x9a same shape.
class GameLogic
{
public:
	unsigned char m_pad[0x9b];
	unsigned char m_9b;
};
extern GameLogic *TheGameLogic;

void __stdcall Rva003BCA8ESet(bool b)
{
	TheGameLogic->m_9b = b;
}
