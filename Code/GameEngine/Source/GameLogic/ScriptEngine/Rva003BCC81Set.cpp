// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCC81Set@@YGX_N@Z @0x003BCC81 19B: script sets GlobalData +0xd34 byte from bool arg.
// Evidence: mov al,[esp+4] mov ecx,[0xDFE758]=TheWritableGlobalData mov [ecx+0xd34],al ret 4; caller 0x003CDAC6; siblings Rva003BCA7BSet same shape.
class GlobalData
{
public:
	unsigned char m_pad[0xd34];
	unsigned char m_d34;
};
extern GlobalData *TheWritableGlobalData;

void __stdcall Rva003BCC81Set(bool b)
{
	TheWritableGlobalData->m_d34 = b;
}
