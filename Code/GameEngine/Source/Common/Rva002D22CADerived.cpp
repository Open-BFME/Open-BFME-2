// cl: /MD
//
// Opaque destructor tail-calling Rva002D22CA::~Rva002D22CA at 0x002D22CA
// (matched opaque derived dtor in GameEngineDeletingBaseDerived.cpp, itself
// tail-calling GameEngineDeletingBase; only declared here so the tail-call
// resolves to the ledger address instead of a same-TU definition). The
// class below stores its own vtable (0xBC4C20, DIR32 auto-patch) and
// tail-jumps to the base destructor. Owner identity is unproven (opaque
// Rva name). One ledger row per destructor, landed one commit at a time.

class Rva002D22CA
{
public:
	Rva002D22CA();
	virtual ~Rva002D22CA();
	virtual bool rva002D2457();
	void rva002D23ED(void *table, int index);
};

class Rva0004CA4C : public Rva002D22CA
{
public:
	Rva0004CA4C();
	virtual ~Rva0004CA4C();
	virtual void rva0004CA57();
};

Rva0004CA4C::~Rva0004CA4C()
{
}

Rva0004CA4C::Rva0004CA4C()
{
}

// Each entry {key, name, function}, key 0 until the load fills it, ending in a null record.
struct TableEntry
{
	int key;
	const char *name;
	void *func;
};

extern "C" {
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("?W3DCameoMovieDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DCommandBarBackgroundDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DCommandBarForegroundDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DCommandBarGenExpDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DCommandBarGridDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DCommandBarHelpPopupDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DCommandBarTopDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DDrawMapPreview@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetCheckBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetCheckBoxImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetComboBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetComboBoxImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetHorizontalSliderDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetHorizontalSliderImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetImageComboBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetListBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetListBoxImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetProgressBarDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetPushButtonDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetPushButtonImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetRadioButtonDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetRadioButtonImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetStaticTextDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetStaticTextImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetTabControlDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetTabControlImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetTextEntryDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetTextEntryImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DGadgetVerticalSliderImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DLeftHUDDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DPowerDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
void __identifier("?W3DRightHUDDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z")();
}

// Native table RVA 0x009b3d18: 35 window draw functions and the null record. W3DGadgetVerticalSliderDraw
// shares the horizontal body, and the empty W3DGadgetProgressBarImageDraw and W3DNoDraw share
// the ICF-folded trivial body whose owner row is Region2D's destructor.
TableEntry g_00DB3D18[36] = {
	{ 0, "W3DGadgetPushButtonDraw", (void *)&__identifier("?W3DGadgetPushButtonDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetPushButtonImageDraw", (void *)&__identifier("?W3DGadgetPushButtonImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetCheckBoxDraw", (void *)&__identifier("?W3DGadgetCheckBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetCheckBoxImageDraw", (void *)&__identifier("?W3DGadgetCheckBoxImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetRadioButtonDraw", (void *)&__identifier("?W3DGadgetRadioButtonDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetRadioButtonImageDraw", (void *)&__identifier("?W3DGadgetRadioButtonImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetTabControlDraw", (void *)&__identifier("?W3DGadgetTabControlDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetTabControlImageDraw", (void *)&__identifier("?W3DGadgetTabControlImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetListBoxDraw", (void *)&__identifier("?W3DGadgetListBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetListBoxImageDraw", (void *)&__identifier("?W3DGadgetListBoxImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetComboBoxDraw", (void *)&__identifier("?W3DGadgetComboBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetImageComboBoxDraw", (void *)&__identifier("?W3DGadgetImageComboBoxDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetComboBoxImageDraw", (void *)&__identifier("?W3DGadgetComboBoxImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetHorizontalSliderDraw", (void *)&__identifier("?W3DGadgetHorizontalSliderDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetHorizontalSliderImageDraw", (void *)&__identifier("?W3DGadgetHorizontalSliderImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetVerticalSliderDraw", (void *)&__identifier("?W3DGadgetHorizontalSliderDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetVerticalSliderImageDraw", (void *)&__identifier("?W3DGadgetVerticalSliderImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetProgressBarDraw", (void *)&__identifier("?W3DGadgetProgressBarDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetProgressBarImageDraw", (void *)&__identifier("??1Region2D@@QAE@XZ") },
	{ 0, "W3DGadgetStaticTextDraw", (void *)&__identifier("?W3DGadgetStaticTextDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetStaticTextImageDraw", (void *)&__identifier("?W3DGadgetStaticTextImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetTextEntryDraw", (void *)&__identifier("?W3DGadgetTextEntryDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DGadgetTextEntryImageDraw", (void *)&__identifier("?W3DGadgetTextEntryImageDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DLeftHUDDraw", (void *)&__identifier("?W3DLeftHUDDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DCameoMovieDraw", (void *)&__identifier("?W3DCameoMovieDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DRightHUDDraw", (void *)&__identifier("?W3DRightHUDDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DPowerDraw", (void *)&__identifier("?W3DPowerDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DCommandBarBackgroundDraw", (void *)&__identifier("?W3DCommandBarBackgroundDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DCommandBarTopDraw", (void *)&__identifier("?W3DCommandBarTopDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DCommandBarGenExpDraw", (void *)&__identifier("?W3DCommandBarGenExpDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DCommandBarHelpPopupDraw", (void *)&__identifier("?W3DCommandBarHelpPopupDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DCommandBarGridDraw", (void *)&__identifier("?W3DCommandBarGridDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DCommandBarForegroundDraw", (void *)&__identifier("?W3DCommandBarForegroundDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, "W3DNoDraw", (void *)&__identifier("??1Region2D@@QAE@XZ") },
	{ 0, "W3DDrawMapPreview", (void *)&__identifier("?W3DDrawMapPreview@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z") },
	{ 0, 0, 0 }
};
// g_00DE1CD8: matched references place it at VA 0xde1cd8; zero-filled at retail, sized to the
// 0xc-byte gap before the next known global there.
char g_00DE1CD8[12];
// g_00DE1CE4: matched references place it at VA 0xde1ce4; zero-filled at retail, sized to the
// 0x164-byte gap before the next known global there.
char g_00DE1CE4[356];

void Rva0004CA4C::rva0004CA57()
{
	Rva002D22CA::rva002D2457();
	rva002D23ED(g_00DB3D18, 3);
	rva002D23ED(g_00DE1CD8, 8);
	rva002D23ED(g_00DE1CE4, 5);
}
