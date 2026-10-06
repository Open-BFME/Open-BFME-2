// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"
// ?Rva00444525Init@@YAXXZ @0x00444525 55B: free init pushing LanLobby.apt via Shell::push then background mode 1; evidence callees StringBase 0x00037BA0 Shell push 0x0035C74A rva002233A6 0x002233A6 all rowed, caller 0x005148D1, globals g_Va00A03354 g_Va00A01E48 TheRva00222A8BTarget; precedent Rva005185D8Init same pattern.
struct Outer00446A77;
extern struct Outer00446A77 *g_Va00A03354;
struct GlobalA01E48;
extern struct GlobalA01E48 *g_Va00A01E48;
class Shell
{
public:
	void push(AsciiString s, bool flag);
};
class Rva00222A8BTarget
{
public:
	void rva002233A6(int mode);
};
extern class Rva00222A8BTarget *TheRva00222A8BTarget;

void Rva00444525Init(void)
{
	if (g_Va00A03354 != 0)
		return;
	((Shell *)g_Va00A01E48)->push(AsciiString("LanLobby.apt"), false);
	TheRva00222A8BTarget->rva002233A6(1);
}
