// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva00516EE9@Rva00517048@@QAEXXZ @0x00516EE9 31B unlock via 0x00415EF8.
// Chat logout close invoke with ChatMessageClose plus six zeros. Evidence: same-class
// sibling ?rva00517048@Rva00517048@@QAEXABVUnicodeString@@@Z at 0x00517048 in
// Rva00517048Chat.cpp with owner at +0x274 and invoke pin 0x00222A8B;
// caller 0x00415F0B in 0x00415EF8 sets ecx from g_Va00A04904 Rva00517048 star;
// global TheRva00222A8BTarget at 0x009FE4CC; string ChatMessageClose.
class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
struct Rva00517048
{
	char m_pad[0x274];
	void *m_274Owner;
	void rva00516EE9();
};
void Rva00517048::rva00516EE9()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_274Owner, "ChatMessageClose", 0, 0, 0, 0, 0, 0);
}
