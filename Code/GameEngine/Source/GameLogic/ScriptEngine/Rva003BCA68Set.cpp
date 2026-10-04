// cl: /O1
// ?Rva003BCA68Set@@YGX_N@Z @0x003BCA68 19B evidence: mov al [esp+4] mov ecx [TheGameLogic] mov [ecx+0x99] al ret 4; caller at 0x003CD731; sibling Rva003BCA7BSet +0x9A same stdcall bool shape
class GameLogic {
public:
	unsigned char m_pad[0x99];
	unsigned char m_99;
};
extern GameLogic *TheGameLogic;
void __stdcall Rva003BCA68Set(bool b)
{
	TheGameLogic->m_99 = b;
}
