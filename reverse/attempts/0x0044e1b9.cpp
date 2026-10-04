// ?rva0044E1B9@BloodthirstyUpdate@@UAE_NPAVObject@@@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /DNDEBUG /MD
//
// BloodthirstyUpdate +0x20 interface overrides (vtable 0x00C3EFC4, installed
// by the matched ctor 0x0044E0AA and dtor 0x0044DFE0). Overrides of a
// non-primary base take the +0x20 subobject this: the module data (+0x04) is
// [this-0x1C], the Object (+0x08) [this-0x18], m_bestTargetID (+0x24, the
// member name the matched ctor carries from the BFME 1 donor) [this+4].
// Names by address; the slot names are not established.
//
// Both resolve the candidate through the rowed Object::rva002931F5(false),
// fetch its rowed 0x0028C1A9 interface (slots 6 and 7 read a state and an
// owner ID), and run the module data's +0x08 filter (rowed
// Rva2225E0Filter::accepts 0x00362437) against our controlling player.
// Retail 0x0044E12F (138 bytes), slot 2: also requires the candidate's AI
// (+0x258) slot-110 predicate when it has an AI; true when the interface's
// owner ID is zero or ours and its state is zero. The BFME 1 analog
// (0x00287130, banked there at 0.78 as Gen_00287130::bfmeAccept) has the same
// flow.
// Retail 0x0044E1B9 (105 bytes), slot 3: true when the interface's owner ID
// is ours and the candidate is our current best target.
class Player;

#define VSLOTS10(P) \
	virtual void P##0(); virtual void P##1(); virtual void P##2(); \
	virtual void P##3(); virtual void P##4(); virtual void P##5(); \
	virtual void P##6(); virtual void P##7(); virtual void P##8(); \
	virtual void P##9()

class AIUpdateInterface
{
public:
	VSLOTS10(a0); VSLOTS10(a1); VSLOTS10(a2); VSLOTS10(a3); VSLOTS10(a4);
	VSLOTS10(a5); VSLOTS10(a6); VSLOTS10(a7); VSLOTS10(a8); VSLOTS10(a9);
	VSLOTS10(aA);
	virtual bool rvaSlot110();
};

class Rva0028C1A9Interface
{
public:
	virtual void i0();
	virtual void i1();
	virtual void i2();
	virtual void i3();
	virtual void i4();
	virtual void i5();
	virtual int getState();
	virtual unsigned int getOwnerID();
};

class Object
{
public:
	Object *rva002931F5(bool checkProducer);
	void *rva0028C1A9() const;
	Player *getControllingPlayer() const;
	unsigned int getID() const { return m_id; }
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad00[0x74];
	unsigned int m_id; // +0x74
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
};

struct Rva2225E0Filter
{
	bool accepts(Object *value, Player *player);
};

struct BloodthirstyUpdateModuleData
{
	unsigned char m_pad00[0x08];
	Rva2225E0Filter m_filter; // +0x08
};

struct B00 { virtual void f00(); BloodthirstyUpdateModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); unsigned char m_pad[12]; };
class Iface20
{
public:
	virtual void s00();
	virtual void s01();
	virtual bool rva0044E12F(Object *obj) = 0;
	virtual bool rva0044E1B9(Object *obj) = 0;
};
class BloodthirstyUpdate : public B00, public B0C, public B10, public Iface20
{
public:
	virtual bool rva0044E12F(Object *obj);
	virtual bool rva0044E1B9(Object *obj);
private:
	unsigned int m_bestTargetID; // +0x24
};

bool BloodthirstyUpdate::rva0044E12F(Object *obj)
{
	Object *candidate = obj->rva002931F5(false);
	BloodthirstyUpdateModuleData *data = m_moduleData;
	if (candidate == 0)
		return false;
	else
	{
		AIUpdateInterface *ai = candidate->getAI();
		if (ai != 0)
		{
			if (!ai->rvaSlot110())
				return false;
		}
		Rva0028C1A9Interface *iface = (Rva0028C1A9Interface *)candidate->rva0028C1A9();
		if (iface == 0)
			return false;
		Object *self = m_object;
		if (!data->m_filter.accepts(candidate, self->getControllingPlayer()))
			return false;
		if (iface->getOwnerID() == 0 || iface->getOwnerID() == self->getID())
		{
			bool idle = (iface->getState() == 0);
			return idle;
		}
		return false;
	}
}

bool BloodthirstyUpdate::rva0044E1B9(Object *obj)
{
	Object *candidate = obj->rva002931F5(false);
	BloodthirstyUpdateModuleData *data = m_moduleData;
	if (candidate == 0)
		return false;
	Rva0028C1A9Interface *iface = (Rva0028C1A9Interface *)candidate->rva0028C1A9();
	if (iface == 0)
		return false;
	Object *self = m_object;
	if (data->m_filter.accepts(candidate, self->getControllingPlayer())
		&& iface->getOwnerID() == self->getID())
	{
		bool best = (m_bestTargetID == candidate->getID());
		return best;
	}
	return false;
}
