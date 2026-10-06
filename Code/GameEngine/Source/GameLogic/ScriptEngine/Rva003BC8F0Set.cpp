// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BC8F0Set@@YGX_N@Z @0x003BC8F0 19B: script sets GameLogic +0x9f byte from bool arg.
// Evidence: mov al,[esp+4] mov ecx,[0xDFE78C]=TheGameLogic mov [ecx+0x9f],al ret 4; caller 0x003CD4C3.
class GameLogic
{
public:
	unsigned char m_pad[0x9f];
	unsigned char m_9f;
};
extern GameLogic *TheGameLogic;

void __stdcall Rva003BC8F0Set(bool b)
{
	TheGameLogic->m_9f = b;
}
