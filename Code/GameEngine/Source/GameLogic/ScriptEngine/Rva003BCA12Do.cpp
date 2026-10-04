// cl: /Ireference/shims/bfme2_ascii /O1
// ?Rva003BCA12Do@@YGXABVAsciiString@@00@Z @0x003BCA12 49B: script creates BfmeStringRecord via rva00358853 with 0.0f and 1 then doNamedMapReveal same name. Evidence: push 1 fldz push [esp+0xc] push ecx mov ecx,[0x00DFE16C]=g_Va009FE16C fstp [esp] push [esp+0x10] push [esp+0x1c] call rva00358853 then push [esp+0xc] mov ecx g_Va call doNamedMapReveal ret 0xc; callees rowed; caller 0x003CD6E3; sibling Rva003BC123Do same AsciiString stdcall shape.
#include "ascii_string.h"
struct BfmeStringRecord00204A30;
class ScriptEngine
{
public:
	BfmeStringRecord00204A30 *rva00358853(const AsciiString &name, const AsciiString &text0, float word1, const AsciiString &text1, int word2);
	void doNamedMapReveal(const AsciiString &revealName);
};
extern ScriptEngine *g_Va009FE16C;
void __stdcall Rva003BCA12Do(const AsciiString &text0, const AsciiString &text1, const AsciiString &name)
{
	g_Va009FE16C->rva00358853(name, text0, 0.0f, text1, 1);
	g_Va009FE16C->doNamedMapReveal(name);
}
