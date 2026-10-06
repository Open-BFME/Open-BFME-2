// ?rva005294FC@Rva0052936C@@QAEXH@Z
// partial score=0.9 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
//
// ?rva005294FC@Rva0052936C@@QAEXH@Z @0x005294FC 217B
// Evidence: array 6 size 0x14 at +0x64 like dtor Rva0052936C plus window table g_bfmeWorldRV +0xdc plus GadgetButtonGetData 0x00327D56 plus ctors 0x0056858C 0x005C3697 plus clear 0x002BED91 set 0x003F8396 plus callers 0x00529605 0x00529E08

class GameWindow;
void *GadgetButtonGetData(GameWindow *button);

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva002BED91
{
	TargetRef00217D4C *m_ptr;
	void clear();
	void set(TargetRef00217D4C *p);
};

class Rva005C3549 : public TargetRef00217D4C
{
public:
	Rva005C3549(void *a, void *b, void *c);
private:
	char m_pad08[4];
};

class Rva005685EE : public Rva005C3549
{
public:
	Rva005685EE(void *a, void *b, void *c);
private:
	char m_extra0C[4];
};

struct BfmeWorldRV
{
	char m_pad[0xDC];
	GameWindow *m_windows[6];
};
extern struct BfmeWorldRV *g_bfmeWorldRV;

struct DataBody
{
	char m_pad00[0x14];
	int m_14;
	char m_pad18[0x102 - 0x18];
	unsigned char m_102;
};

struct Elem14
{
	void *m_00;
	void *m_04;
	void *m_08;
	Rva002BED91 m_0C;
	void *m_10;
};

class Rva0052936C
{
public:
	void rva005294FC(int index);
private:
	char m_pad00[0x30];
	void *m_30;
	char m_pad34[0x64 - 0x34];
	Elem14 m_64[6];
};

// ?rva005294FC@Rva0052936C@@QAEXH@Z present-unmatched
void Rva0052936C::rva005294FC(int index)
{
	Elem14 *e = &m_64[index];
	e->m_0C.clear();
	e->m_10 = 0;
	if (!e->m_00)
		return;
	BfmeWorldRV *world = g_bfmeWorldRV;
	GameWindow *win = world->m_windows[index];
	if (!win)
		return;
	void *data = GadgetButtonGetData(win);
	e->m_10 = data;
	if (!data)
		return;
	DataBody *d = (DataBody *)data;
	if (d->m_102 == 0)
		return;
	TargetRef00217D4C *tmp;
	if (d->m_14 == 0x39 && e->m_04 != 0 && e->m_08 != 0)
		tmp = new Rva005685EE(e->m_00, win, m_30);
	else
		tmp = new Rva005C3549(e->m_00, win, m_30);
	e->m_0C.set(tmp);
}
