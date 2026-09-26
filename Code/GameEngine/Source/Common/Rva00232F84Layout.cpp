// cl: /O1 /Oy- /DNDEBUG /MD
//
// Rva00232F84 layout at 0x00232F84, 184 bytes.
//
// Between DispDwordFieldGetters rows 0x00232F7D and 0x0023303C. The holder
// carries GameWindows at +0x3050/+0x3058/+0x3060. When +0x3050 is present
// and +0x3058 yields a font record through get at 0x00313D6C, the new width
// is ([font+0x10]+[0x009C8630])*arg, +0x3058 is resized to (w, newWidth),
// +0x3050 keeps its w and grows its h by the width delta, and +0x3060 (when
// present) keeps its y and shifts its x by the same delta. Callees are all
// rowed. Caller is 0x002338B4. No donor; honest address names.

class GameWindow
{
public:
	int winGetSize(int *a, int *b);
	int winSetSize(int a, int b);
	int winGetPosition(int *a, int *b);
	int winSetPosition(int a, int b);
};

class Rva00313D6CDwordField
{
public:
	int get() const;
};

extern int unknownGlobal009C8630;

class Rva00232F84
{
public:
	void rva00232F84(int v);

private:
	char m_pad0[0x3050];
	GameWindow *m_3050;
	char m_pad1[0x3058 - 0x3054];
	GameWindow *m_3058;
	char m_pad2[0x3060 - 0x305C];
	GameWindow *m_3060;
};

void Rva00232F84::rva00232F84(int v)
{
	if (m_3050 == 0) {
		return;
	}
	int fontVal = ((Rva00313D6CDwordField *)m_3058)->get();
	if (fontVal == 0) {
		return;
	}
	int newWidth = *(int *)(fontVal + 0x10) + unknownGlobal009C8630;
	newWidth *= v;
	int w;
	int h;
	m_3058->winGetSize(&w, &h);
	int delta = newWidth - h;
	m_3058->winSetSize(w, newWidth);
	m_3050->winGetSize(&w, &h);
	h += delta;
	m_3050->winSetSize(w, h);
	if (m_3060 == 0) {
		return;
	}
	int x;
	m_3060->winGetPosition(&x, &v);
	v += delta;
	m_3060->winSetPosition(x, v);
}
