// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCC6ESet@@YGX_N@Z @0x003BCC6E 19B: script sets ScriptEngine +0x1a4d6 byte from bool arg.
// Evidence: mov al,[esp+4] mov ecx,[0xDFE16C]=g_Va009FE16C mov [ecx+0x1a4d6],al ret 4; caller 0x003CDA9B; siblings Rva003BCA7BSet Rva003BCA8ESet same shape.
class ScriptEngine
{
public:
	unsigned char m_pad[0x1a4d6];
	unsigned char m_1a4d6;
};
extern class ScriptEngine *TheScriptEngine;

void __stdcall Rva003BCC6ESet(bool b)
{
	TheScriptEngine->m_1a4d6 = b;
}
