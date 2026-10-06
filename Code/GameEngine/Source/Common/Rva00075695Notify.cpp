// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ?Rva00075695Notify@@YAXH@Z 0x00075695 42B: free function indexed via g_00DE1F24 null check then virtual slot 1 call gated and cleared by g_00DE1F54; sibling Rva00075725Check.cpp pattern
class Rva00075695Item
{
public:
	virtual void f0();
	virtual void f1();
};

extern Rva00075695Item * volatile g_00DE1F24[];
extern int g_00DE1F54;

void __cdecl Rva00075695Notify(int index)
{
	if (g_00DE1F54 != 0) {
		Rva00075695Item * volatile *slot = &g_00DE1F24[index];
		if (*slot != 0)
			(*slot)->f1();
		g_00DE1F54 = 0;
	}
}
