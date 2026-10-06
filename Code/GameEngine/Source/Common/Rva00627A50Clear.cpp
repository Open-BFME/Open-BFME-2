// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva00627A50Clear.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?rva00627A50Clear@@YAXXZ 0x00548B3C (52B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

void b_00042a50();

unsigned char g_rva00627A50Flag;
void *g_rva00627A50A;
void *g_rva00627A50B;

void rva00627A50Clear()
{
	if (g_rva00627A50Flag)
	{
		b_00042a50();
		g_rva00627A50Flag = 0;
	}
	if (g_rva00627A50A)
		g_rva00627A50A = 0;
	if (g_rva00627A50B)
		g_rva00627A50B = 0;
}
