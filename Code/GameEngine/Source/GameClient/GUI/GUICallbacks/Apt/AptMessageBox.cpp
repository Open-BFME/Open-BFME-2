// cl: /O1 /DNDEBUG /MD /EHsc
//
// AptMessageBox (WorldBuilder GameClient/Gui/GUICallbacks/Apt/AptMessageBox.cpp).
// Target facts: the static Show 0x00437E84 and Change 0x00437EAC (cdecl,
// three arguments) forward to the singleton instance (WorldBuilder
// Instance(), the dword at 0x00A032FC, rowed as the address-named
// g_Va00E032FC) through 0x0054D2DD / 0x0054D3D9 (unnamed there, pinned
// address-named). Argument types are not recovered.
extern int g_Va00E032FC;

class AptMessageBox
{
public:
	static void Show(void *a, void *b, void *c);
	static void Change(void *a, void *b, void *c);

	void rva0054D2DD(void *a, void *b, void *c);
	void rva0054D3D9(void *a, void *b, void *c);

private:
	static AptMessageBox *Instance() { return (AptMessageBox *)g_Va00E032FC; }
};

void AptMessageBox::Show(void *a, void *b, void *c)
{
	Instance()->rva0054D2DD(a, b, c);
}

void AptMessageBox::Change(void *a, void *b, void *c)
{
	Instance()->rva0054D3D9(a, b, c);
}
