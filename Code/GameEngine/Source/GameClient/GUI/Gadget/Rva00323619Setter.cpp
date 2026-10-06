// cl: /DNDEBUG /MD
// ?rva00323619@Rva00323619@@QAEXH@Z @0x00323619 41B
// Setter through GameWindow userData: *this+0 is GameWindow* via rowed winGetUserData 0x005C4ACD then store (TheWritableGlobalData+0x34 * arg)/0x300 into userData+0. Early-out when *this is null. ret 4.
// Evidence: callees rowed 0x005C4ACD plus TheWritableGlobalData ?TheWritableGlobalData@@3PAVGlobalData@@A; callers 0x0044045A 0x005BA907.
class GameWindow
{
public:
	void *winGetUserData();
};

class GlobalData
{
public:
	char _pad[0x34];
	int m_34;
};

extern GlobalData *TheWritableGlobalData;

class Rva00323619
{
public:
	void rva00323619(int v);
	void rva00323642();
private:
	GameWindow *m_window;
};

void GadgetListBoxReset(GameWindow *listbox);

void Rva00323619::rva00323619(int v)
{
	GameWindow *w = m_window;
	if (w == 0)
		return;
	int *p = (int *)w->winGetUserData();
	*p = (TheWritableGlobalData->m_34 * v) / 0x300;
}

// ?rva00323642@Rva00323619@@QAEXXZ @0x00323642 21B
// Adjacent method of same class: *this+0 GameWindow* null-guarded then GadgetListBoxReset(*(GameWindow**)(userData+8)).
// Evidence: callees rowed 0x005C4ACD winGetUserData plus 0x003247E5 GadgetListBoxReset; prev row same class.
void Rva00323619::rva00323642()
{
	GameWindow *w = m_window;
	if (w == 0)
		return;
	void *userData = w->winGetUserData();
	GadgetListBoxReset(*(GameWindow **)((char *)userData + 8));
}
