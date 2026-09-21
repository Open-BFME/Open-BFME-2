// Retail 0x007592E0 (?apply@Rva009A36F0Owner@@QAEXPAVRva009A36F0Param@@@Z).
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/Common/Rva009A36F0Owner.cpp
// (b1 0x009A36F0, // cl: /O2 /Ob0). The b2 body at 0x007592E0 is the same
// function: this = ebx (list-head pointer at +8, flag byte at +0xC06D),
// param = edi (virtual +0x18 void f(int), +0x1c returns a thing pointer).
// If param is null, or slot1c returns null, the function is a no-op.
// Otherwise it calls slot18(0), then links `thing` into the doubly-linked
// list rooted at this+8 when the flag is set (same back-slot/next idiom as
// the landed Rva009A3770HashChainInsert.cpp), or unlinks it and destroys it.
// callees: 0x00759220 (pinned unlinkChain), 0x00758500 (rowed CollisionData
// dtor), 0x0002FD60 (rowed operator delete).
// Adaptation vs the donor: the donor calls destroyDirect() on the thing, but
// the b2 retail call target 0x00758500 is the ledger-rowed
// ??1Rva009A45A0CollisionData@@QAE@XZ, so this TU calls that dtor directly.
// cl: /O2 /Ob1

class Rva009A36F0Thing
{
public:
	unsigned char m_pad0[4];
	int m_4;
	unsigned char m_pad8[8];
	void *m_10;
	Rva009A36F0Thing *m_14;
};

class Rva009A36F0Param
{
public:
	virtual void slot0();
	virtual void slot4();
	virtual void slot8();
	virtual void slotc();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18(int);
	virtual Rva009A36F0Thing *slot1c();
};

class Rva009A45A0CollisionData
{
public:
	~Rva009A45A0CollisionData();
};

void __cdecl operator delete(void *block);

class Rva009A36F0Owner
{
public:
	void apply(Rva009A36F0Param *param);
	void unlinkChain(Rva009A36F0Thing *thing);

private:
	unsigned char m_pad0[8];
	Rva009A36F0Thing *m_listHead;
	unsigned char m_padToFlag[0xc06d - 0xc];
	unsigned char m_flag;
};

void Rva009A36F0Owner::apply(Rva009A36F0Param *param)
{
	if (param == 0)
		return;

	Rva009A36F0Thing *thing = param->slot1c();
	if (thing == 0)
		return;

	param->slot18(0);

	if (m_flag)
	{
		if (thing->m_10 == 0)
		{
			Rva009A36F0Thing **slot = (Rva009A36F0Thing **)&m_listHead;

			thing->m_10 = slot;

			Rva009A36F0Thing *head = *slot;
			thing->m_14 = head;
			if (head != 0)
				head->m_10 = &thing->m_14;

			*slot = thing;
		}

		thing->m_4 = 0;
		return;
	}

	unlinkChain(thing);
	((Rva009A45A0CollisionData *)thing)->~Rva009A45A0CollisionData();
	operator delete(thing);
}
