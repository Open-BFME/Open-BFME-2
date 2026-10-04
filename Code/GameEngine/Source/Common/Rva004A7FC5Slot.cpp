// cl: /O1 /MD

// ?rva004A7FC5@Rva004A7D55@@UAEXXZ @0x004A7FC5 43B virtual slot 1 of vtable 0x00853790 class of ??1Rva004A7D55.
// Target evidence: vslot 1 plus call DockUpdate loadPostProcess 0x00589909 plus Thing getDrawable 0x005508E2 plus broadcast 0x0027164E with m_04+0x10 and m_88; sibling slot5 Rva004A7E43Slot pattern.

class Rva004A7D55;

class DockUpdate
{
protected:
	virtual void loadPostProcess();
	friend class Rva004A7D55;
};

class Drawable;
class Thing
{
public:
	Drawable *getDrawable() const;
};

class Rva002716Holder
{
public:
	void Rva0027164EBroadcast(int a, int b);
};

struct Rva004A7FC5Aux
{
	unsigned char m_pad[0x10];
	int m_10;
};

class GlobalData
{
public:
	unsigned char m_pad00[0xA5C];
	int m_A5C;
};

extern GlobalData *TheWritableGlobalData;

extern "C" __declspec(dllimport) double __cdecl ceil(double v);

class Rva004A7D55
{
public:
	virtual void s0();
	virtual void rva004A7FC5();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	void rva004A7F78(int val);
private:
	Rva004A7FC5Aux *m_04;
	Thing *m_08;
	unsigned char m_pad0C[0x88 - 0x0C];
	int m_88;
};

void Rva004A7D55::rva004A7FC5()
{
	((DockUpdate *)this)->DockUpdate::loadPostProcess();
	Thing *t = m_08;
	Rva004A7FC5Aux *aux = m_04;
	Drawable *d = t->getDrawable();
	if (d == 0)
		return;
	((Rva002716Holder *)d)->Rva0027164EBroadcast(aux->m_10, m_88);
}

void Rva004A7D55::rva004A7F78(int val)
{
	m_88 = (int)ceil((double)val / TheWritableGlobalData->m_A5C);
	Drawable *d = m_08->getDrawable();
	if (d == 0)
		return;
	((Rva002716Holder *)d)->Rva0027164EBroadcast(m_04->m_10, m_88);
}
