// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7
// ?Rva003BC9E0Do@@YGXABVAsciiString@@M00@Z @0x003BC9E0 50B: script creates BfmeStringRecord via rva00358853 with param float and 0 then doNamedMapReveal same name. Evidence: sibling Rva003BCA12Do same shape with 0.0f and 1; callees rowed rva00358853 doNamedMapReveal; TheScriptEngine global; caller 0x003CD699 unclaimed.
#include "ascii_string.h"
struct BfmeStringRecord00204A30;
class ScriptEngine
{
public:
	BfmeStringRecord00204A30 *rva00358853(const AsciiString &name, const AsciiString &text0, float word1, const AsciiString &text1, int word2);
	void doNamedMapReveal(const AsciiString &revealName);
};
extern class ScriptEngine *TheScriptEngine;
void __stdcall Rva003BC9E0Do(const AsciiString &text0, float f, const AsciiString &text1, const AsciiString &name)
{
	TheScriptEngine->rva00358853(name, text0, f, text1, 0);
	TheScriptEngine->doNamedMapReveal(name);
}
