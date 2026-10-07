// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva004B5A65@Rva004B5A65_Secondary@@QAEXXZ @0x004B5A65 91B: secondary-slot
// UpgradeModule apply (vtable 0x00C580E8 slot 0) with the twins' MI shape:
// mask owner at this-0x0C (flag byte at +0x128), status target at this-8,
// vfunc00 gate, vfunc09(0) tail. Flag set: controlling player grants
// through 0x002B0E55 with the target sub-int at +0x68, then returns.
// Flag clear: same player removes through 0x002ADC03 with the target int
// at +0x74, then falls into vfunc09(0). Player identity via the rowed
// Object::getControllingPlayer at 0x0028AFA9; the two Player workers are
// unrowed pins. Names stay address-derived.

class Rva004B5A65Owner;
class Player;

struct Rva004B5A65Sub
{
	char m_pad[0x64];
	int m_64; // +0x64
};

class Object
{
public:
	virtual void vfunc00();
	Player *getControllingPlayer() const;

	Rva004B5A65Sub *m_sub; // +0x04
	char m_pad08[0x74 - 8];
	int m_74; // +0x74
};

class Rva004B5A65Owner
{
public:
	char m_pad[0x128];
	unsigned char m_128; // +0x128
};

class Player
{
public:
	void rva002B0E55(Rva004B5A65Owner *owner, int value);
	void rva002ADC03(Rva004B5A65Owner *owner, int value);
	void rva002B212A(Rva004B5A65Owner *owner, int value);
	void rva002ACD09(Rva004B5A65Owner *owner, int value);
};
class Rva004B5A65_Secondary
{
public:
	virtual bool vfunc00() = 0;
	virtual void vfunc01() = 0;
	virtual void vfunc02() = 0;
	virtual void vfunc03() = 0;
	virtual void vfunc04() = 0;
	virtual void vfunc05() = 0;
	virtual void vfunc06() = 0;
	virtual void vfunc07() = 0;
	virtual void vfunc08() = 0;
	virtual void vfunc09(int arg) = 0;
	void rva004B5A65();
	void rva004B5B4C();
};

// ?rva004B5A65@Rva004B5A65_Secondary@@QAEXXZ
void Rva004B5A65_Secondary::rva004B5A65()
{
	if (!vfunc00())
		return;
	Rva004B5A65Owner *owner = *(Rva004B5A65Owner * *)((char *)this - 0x0C);
	if (owner->m_128 != 0)
	{
		Object *target = *(Object * *)((char *)this - 8);
		Player *player = target->getControllingPlayer();
		if (player != 0)
		{
			Object *target2 = *(Object * *)((char *)this - 8);
			player->rva002B0E55(owner, (int)&target2->m_sub->m_64);
		}
		return;
	}
	Object *target = *(Object * *)((char *)this - 8);
	Player *player = target->getControllingPlayer();
	if (player != 0)
	{
		Object *target2 = *(Object * *)((char *)this - 8);
		player->rva002ADC03(owner, target2->m_74);
	}
	vfunc09(0);
}

// ?rva004B5B4C@Rva004B5A65_Secondary@@QAEXXZ
void Rva004B5A65_Secondary::rva004B5B4C()
{
	Object *target = *(Object * *)((char *)this - 8);
	Player *player = target->getControllingPlayer();
	Rva004B5A65Owner *owner = *(Rva004B5A65Owner * *)((char *)this - 0x0C);
	if (owner->m_128 != 0)
	{
		Object *target2 = *(Object * *)((char *)this - 8);
		player->rva002B212A(owner, (int)&target2->m_sub->m_64);
	}
	else
	{
		Object *target2 = *(Object * *)((char *)this - 8);
		player->rva002ACD09(owner, target2->m_74);
	}
}

class Rva004B5AC0_Primary
{
public:
	void __fastcall rva004B5AC0(int /*unused*/, Player *player1, Player *player2);
};

// ?rva004B5AC0@Rva004B5AC0_Primary@@QAIXHPAVPlayer@@0@Z
void __fastcall Rva004B5AC0_Primary::rva004B5AC0(int /*unused*/, Player *player1, Player *player2)
{
	Rva004B5A65_Secondary *secondary = (Rva004B5A65_Secondary *)((char *)this + 0x10);
	if (!secondary->vfunc00())
		return;
	Rva004B5A65Owner *owner = *(Rva004B5A65Owner * *)((char *)this + 4);
	if (owner->m_128 != 0)
	{
		if (player1 != 0)
		{
			Object *target = *(Object * *)((char *)this + 8);
			player1->rva002B0E55(owner, (int)&target->m_sub->m_64);
		}
		if (player2 != 0)
		{
			Object *target = *(Object * *)((char *)this + 8);
			player2->rva002B212A(owner, (int)&target->m_sub->m_64);
		}
		return;
	}
	if (player1 != 0)
	{
		Object *target = *(Object * *)((char *)this + 8);
		player1->rva002ADC03(owner, target->m_74);
		secondary->vfunc09(0);
	}
	if (player2 != 0)
	{
		Object *target = *(Object * *)((char *)this + 8);
		player2->rva002ACD09(owner, target->m_74);
		secondary->vfunc09(1);
	}
}
