// cl: /DNDEBUG /MD
// ?Rva003807F3Move@@YAXMM@Z @ 0x003807F3 (118B): MoveToolTip firer with float formatting.
// Retail fetches scale pair through GuiScale slot 0x40 on global 0x009FE4CC then formats
// x*scale[0] and y*scale[1] with "%g" via msvcr71 _snprintf into 16B stack buffers.
// Then fires "MoveToolTip" through Rva00222A8BTarget invoker with owner 0x009C06A0 as
// (owner name 2 bufX bufY 0 0 0) matching HideToolTip pattern in TooltipHide. Callers
// 0x001EF23A. Prev Hide proves target owner globals and invoker pin; honest-address
// free-function name with float params MM.
class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern void *TheRva00222A8BOwner;

class GuiScale
{
public:
	virtual ~GuiScale() {}
	virtual void g04() = 0;
	virtual void g08() = 0;
	virtual void g0C() = 0;
	virtual void g10() = 0;
	virtual void g14() = 0;
	virtual void g18() = 0;
	virtual void g1C() = 0;
	virtual void g20() = 0;
	virtual void g24() = 0;
	virtual void g28() = 0;
	virtual void g2C() = 0;
	virtual void g30() = 0;
	virtual void g34() = 0;
	virtual void g38() = 0;
	virtual void g3C() = 0;
	virtual void *getScale() = 0;
};

extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buf, unsigned int n, const char *fmt, ...);

void Rva003807F3Move(float x, float y)
{
	float *scale = (float *)(*(GuiScale **)&g_bfmeAptWindowManager)->getScale();
	char bufX[16];
	char bufY[16];
	_snprintf(bufX, 16, "%g", x * scale[0]);
	_snprintf(bufY, 16, "%g", y * scale[1]);
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(TheRva00222A8BOwner, "MoveToolTip", 2, bufX, bufY, 0, 0, 0);
}
