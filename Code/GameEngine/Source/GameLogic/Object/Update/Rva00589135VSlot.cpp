// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva00589135@WeaponModeSpecialPowerUpdateBase@@QAEXH@Z, retail 0x00589135 54B. Vslot 10 of 0x00870108 via rowed BitFlags 0x0023C58B any plus slot0 virtual on this-4 with 5 args. Donor WeaponModeSpecialPowerUpdateBaseCtor plus open-bfme-1 WeaponModeSpecialPowerUpdateCtorThunk.
template<int N>
class BitFlags
{
public:
	bool any() const;
};

struct VirtBase
{
	virtual void vf(void *a, int b, int c, int d, int e);
};

class Overridable
{
public:
	virtual void overridableAnchor();
	const Overridable *friend_getFinalOverride() const;
	unsigned char m_pad04[0x55];
	unsigned char m_hasOverride;
};

class SpecialPowerTemplate;
class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva002AC6B1PlayerTimers
{
public:
	unsigned int getOrStart(const SpecialPowerTemplate *tmpl);
};

class GameLogic
{
public:
	unsigned char m_pad00[0x40];
	int m_frame40;
};

extern GameLogic *TheGameLogic;

struct VirtPrimary
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual const Overridable *f6() const;
};

class WeaponModeSpecialPowerUpdateBase
{
public:
	void rva00589135(int arg);
	void rva0058916B(int arg1, int arg2);
	void rva005891A3(int arg1, int arg2);
	void rva005891DB(int arg1, int arg2, int arg3);
	int rva005893AD();
private:
	unsigned char m_pad00[4];
	int m_04;
	int m_08;
	int m_0C;
};

void WeaponModeSpecialPowerUpdateBase::rva00589135(int arg)
{
	if (m_08 > 0)
		return;
	void *p1 = *(void *const *)((const char *)this - 0x1c);
	BitFlags<11> *flags = (BitFlags<11> *)((char *)p1 + 0x1c8);
	if (flags->any())
		return;
	void *p2 = *(void *const *)((const char *)this - 0x20);
	VirtBase *vb = (VirtBase *)((char *)this - 4);
	vb->vf(*(void **)((char *)p2 + 8), 0, 0, arg, 0);
}

// ?rva0058916B@WeaponModeSpecialPowerUpdateBase@@QAEXHH@Z, retail 0x0058916B 56B. Vslot 11 of 0x00870108 via rowed BitFlags 0x0023C58B any plus slot0 virtual on this-4 with 5 args. Same pattern as vslot 10 0x00589135 with two int args.
void WeaponModeSpecialPowerUpdateBase::rva0058916B(int arg1, int arg2)
{
	if (m_08 > 0)
		return;
	void *p1 = *(void *const *)((const char *)this - 0x1c);
	BitFlags<11> *flags = (BitFlags<11> *)((char *)p1 + 0x1c8);
	if (flags->any())
		return;
	void *p2 = *(void *const *)((const char *)this - 0x20);
	VirtBase *vb = (VirtBase *)((char *)this - 4);
	vb->vf(*(void **)((char *)p2 + 8), arg1, 0, arg2, 0);
}

// ?rva005891A3@WeaponModeSpecialPowerUpdateBase@@QAEXHH@Z, retail 0x005891A3 56B. Vslot 12 of 0x00870108 via rowed BitFlags 0x0023C58B any plus slot0 virtual on this-4 with 5 args. Same pattern as vslots 10-11 with middle args shifted.
void WeaponModeSpecialPowerUpdateBase::rva005891A3(int arg1, int arg2)
{
	if (m_08 > 0)
		return;
	void *p1 = *(void *const *)((const char *)this - 0x1c);
	BitFlags<11> *flags = (BitFlags<11> *)((char *)p1 + 0x1c8);
	if (flags->any())
		return;
	void *p2 = *(void *const *)((const char *)this - 0x20);
	VirtBase *vb = (VirtBase *)((char *)this - 4);
	vb->vf(*(void **)((char *)p2 + 8), 0, arg1, arg2, 0);
}

// ?rva005891DB@WeaponModeSpecialPowerUpdateBase@@QAEXHHH@Z, retail 0x005891DB 58B. Vslot 13 of 0x00870108 via rowed BitFlags 0x0023C58B any plus slot0 virtual on this-4 with 5 args. Same pattern as vslots 10-12 with three int args.
void WeaponModeSpecialPowerUpdateBase::rva005891DB(int arg1, int arg2, int arg3)
{
	if (m_08 > 0)
		return;
	void *p1 = *(void *const *)((const char *)this - 0x1c);
	BitFlags<11> *flags = (BitFlags<11> *)((char *)p1 + 0x1c8);
	if (flags->any())
		return;
	void *p2 = *(void *const *)((const char *)this - 0x20);
	VirtBase *vb = (VirtBase *)((char *)this - 4);
	vb->vf(*(void **)((char *)p2 + 8), 0, arg1, arg3, arg2);
}

int WeaponModeSpecialPowerUpdateBase::rva005893AD()
{
	const Overridable *ov = ((const VirtPrimary *)this)->f6();
	const Overridable *fin = ov->friend_getFinalOverride();
	if (fin->m_hasOverride != 0) {
		Object *outer = *(Object **)((char *)this - 0x1c);
		if (outer != 0) {
			Player *player = outer->getControllingPlayer();
			if (player != 0) {
				const Overridable *ov2 = ((const VirtPrimary *)this)->f6();
				return (int)((Rva002AC6B1PlayerTimers *)player)->getOrStart((const SpecialPowerTemplate *)ov2);
			}
		}
	}
	if (m_08 > 0)
		goto gameLogic;
	{
		void *p1 = *(void *const *)((const char *)this - 0x1c);
		BitFlags<11> *flags = (BitFlags<11> *)((char *)p1 + 0x1c8);
		if (!flags->any())
			return m_04;
	}
gameLogic:
	return TheGameLogic->m_frame40 - m_0C + m_04;
}
