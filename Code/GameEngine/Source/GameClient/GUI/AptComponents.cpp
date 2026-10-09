// cl: /O1 /arch:SSE /MD
// AptComponents coordinate synchronization: complete native4102C8..4103A9
// RET0; WB10946D0's caller context and WB10935F0 establish the window,
// cached position14/18 and cached size1C/20. The existing GameWindow parent,
// position and size methods establish ABI and hierarchy independently.
// The banked implementation supplies the semantic skeleton. Replacing its
// folded RingRenderObj getter with the already pinned true winGetParent,
// then an ordinary two-float local constructor, closes all225 bytes. The
// constructor preserves a contiguous coordinate temporary so the parent
// output integers reuse dead argument slots, as retail does.
// No original helper or data-record type name is asserted.
class GameWindow
{
public:
 GameWindow*winGetParent();
	int winGetPosition(int *x, int *y);
	int winSetPosition(int x, int y);
	int winSetSize(int w, int h);
};

struct Rva004102C8Arg
{
	char m_00[0x10];
	GameWindow *m_10;
	float m_14;
	float m_18;
	float m_1C;
	float m_20;
};

struct ComponentPosition{float x,y;ComponentPosition(float a,float b):x(a),y(b){}};
void Rva004102C8Update(Rva004102C8Arg *a1, float *a2, float *a3)
{
	int ix;
	int iy;
	GameWindow* f;
	ComponentPosition pos(a2[0],a2[1]);
	f = a1->m_10->winGetParent();
	if (f != 0) {
		((GameWindow *)f)->winGetPosition(&ix, &iy);
		pos.x -= (float)ix;
		pos.y -= (float)iy;
	}
	if (pos.x != a1->m_14 || pos.y != a1->m_18) {
		a1->m_14 = pos.x;
		a1->m_18 = pos.y;
		if (a1->m_10 != 0)
			((GameWindow *)a1->m_10)->winSetPosition((int)pos.x, (int)pos.y);
	}
	if (a3[0] != a1->m_1C || a3[1] != a1->m_20) {
		a1->m_1C = a3[0];
		a1->m_20 = a3[1];
		if (a1->m_10 != 0)
			((GameWindow *)a1->m_10)->winSetSize((int)a3[0], (int)a3[1]);
	}
}
