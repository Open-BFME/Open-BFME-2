// cl: /Ireference/shims/bfme2_ascii /O1
// ?Rva003BCA43Do@@YGXABVAsciiString@@@Z @0x003BCA43 26B: script undoNamedMapReveal then tail-jump rva00357D52 same name. Evidence: push [esp+4] mov ecx g_Va call undoNamedMapReveal mov ecx g_Va jmp rva00357D52; callees rowed; callers 0x003CD6B1 0x003CD6FB; sibling Rva003BCA12Do same AsciiString stdcall shape.
#include "ascii_string.h"
class ScriptEngine
{
public:
	void undoNamedMapReveal(const AsciiString &name);
	void rva00357D52(const AsciiString &name);
};
extern ScriptEngine *g_Va009FE16C;
void __stdcall Rva003BCA43Do(const AsciiString &name)
{
	g_Va009FE16C->undoNamedMapReveal(name);
	g_Va009FE16C->rva00357D52(name);
}
