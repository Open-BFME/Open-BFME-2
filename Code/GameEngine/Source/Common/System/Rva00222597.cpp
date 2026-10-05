// cl: /O1 /G7 /arch:SSE
// ?rva00222597@Rva00222597@@QAEXPAH@Z @0x00222597 121B
// Window point to mouse dispatch: rect test via WindowManager slot 0xD4
// bfmeGet then SetMousePos 0 0 else scale via slot 0x40. Evidence: rowed
// bfmeGet 0x313B6F SetMousePos 0x6CC950, TheWindowManager 0xDFEF1C,
// caller 0x40FFA2, neighbours Rva00222547Get stlport_deque_e16_o1, ret 4.
class BfmeQuadDO
{
public:
	int m_left;
	int m_top;
	int m_right;
	int m_bottom;
};

class Gen_00478220
{
public:
	int bfmeGet(BfmeQuadDO *out) const;
};

class GameWindowManager
{
public:
	virtual void pad00() = 0;
	virtual void pad01() = 0;
	virtual void pad02() = 0;
	virtual void pad03() = 0;
	virtual void pad04() = 0;
	virtual void pad05() = 0;
	virtual void pad06() = 0;
	virtual void pad07() = 0;
	virtual void pad08() = 0;
	virtual void pad09() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual void pad12() = 0;
	virtual void pad13() = 0;
	virtual void pad14() = 0;
	virtual void pad15() = 0;
	virtual void pad16() = 0;
	virtual void pad17() = 0;
	virtual void pad18() = 0;
	virtual void pad19() = 0;
	virtual void pad20() = 0;
	virtual void pad21() = 0;
	virtual void pad22() = 0;
	virtual void pad23() = 0;
	virtual void pad24() = 0;
	virtual void pad25() = 0;
	virtual void pad26() = 0;
	virtual void pad27() = 0;
	virtual void pad28() = 0;
	virtual void pad29() = 0;
	virtual void pad30() = 0;
	virtual void pad31() = 0;
	virtual void pad32() = 0;
	virtual void pad33() = 0;
	virtual void pad34() = 0;
	virtual void pad35() = 0;
	virtual void pad36() = 0;
	virtual void pad37() = 0;
	virtual void pad38() = 0;
	virtual void pad39() = 0;
	virtual void pad40() = 0;
	virtual void pad41() = 0;
	virtual void pad42() = 0;
	virtual void pad43() = 0;
	virtual void pad44() = 0;
	virtual void pad45() = 0;
	virtual void pad46() = 0;
	virtual void pad47() = 0;
	virtual void pad48() = 0;
	virtual void pad49() = 0;
	virtual void pad50() = 0;
	virtual void pad51() = 0;
	virtual void pad52() = 0;
	virtual Gen_00478220 *slot53() = 0;
};

extern GameWindowManager *TheWindowManager;

void __cdecl Rva006CC950SetMousePos(int x, int y);

class Rva00222597
{
public:
	virtual void pad00() = 0;
	virtual void pad01() = 0;
	virtual void pad02() = 0;
	virtual void pad03() = 0;
	virtual void pad04() = 0;
	virtual void pad05() = 0;
	virtual void pad06() = 0;
	virtual void pad07() = 0;
	virtual void pad08() = 0;
	virtual void pad09() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual void pad12() = 0;
	virtual void pad13() = 0;
	virtual void pad14() = 0;
	virtual void pad15() = 0;
	virtual float *slot16() = 0;
	void rva00222597(int *p);
};

void Rva00222597::rva00222597(int *p)
{
	Gen_00478220 *gen = TheWindowManager->slot53();
	if (gen != 0)
	{
		BfmeQuadDO rect;
		gen->bfmeGet(&rect);
		int x = p[0];
		if (x < rect.m_left)
			goto scaled;
		int y = p[1];
		if (y < rect.m_top)
			goto scaled;
		if (x > rect.m_right)
			goto scaled;
		if (y > rect.m_bottom)
			goto scaled;
		Rva006CC950SetMousePos(0, 0);
		return;
	}
scaled:
	float *scale = slot16();
	int sy = (int)((float)p[1] * scale[1]);
	int sx = (int)((float)p[0] * scale[0]);
	Rva006CC950SetMousePos(sx, sy);
}
