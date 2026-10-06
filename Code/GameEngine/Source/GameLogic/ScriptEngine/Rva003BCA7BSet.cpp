// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCA7BSet@@YGX_N@Z @0x003BCA7B 19B: script sets GameLogic +0x9a byte from bool arg.
// Evidence: mov al,[esp+4] mov ecx,[0xDFE78C]=TheGameLogic mov [ecx+0x9a],al ret 4; caller 0x003CD74C; sibling Rva003BC8F0Set +0x9f same shape.
class GameLogic
{
public:
	unsigned char m_pad[0x9a];
	unsigned char m_9a;
};
extern GameLogic *TheGameLogic;

void __stdcall Rva003BCA7BSet(bool b)
{
	TheGameLogic->m_9a = b;
}
