// cl: /DNDEBUG /MD /GX- /Op
//
// ?rva0028FAD1@Object@@QAEXPAV1@@Z, retail 0x0028fad1, 158 bytes. Banked partial (score 0.96) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Evidence: unlock; callers 0x4648B1 and 0x4F5784 pass Object* this with Object* arg;
// sets containedBy +0x274 and +0x27C from TheGameLogic+0x40; bit0 at +0x439;
// calls rowed setStatus 0x23DB0E and pinned Rva0028CDEB 0x28CDEB; two vtable +0xB0 calls on +0x250 module.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef int ObjectID;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0,
	OBJECT_STATUS_DESTROYED = 1,
	OBJECT_STATUS_CAN_ATTACK = 2,
	OBJECT_STATUS_UNDER_CONSTRUCTION = 3
};

struct ObjectStatusMask
{
	ObjectStatusMask *Rva0023DA79(int reserved, ObjectStatusTypes bit, bool flag);
	int m_bits[4];
};

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_unk40;
};

extern GameLogic *TheGameLogic;

struct Flag04
{
	char m_pad00[0x10E];
	unsigned char m_flag;
};

class Module2
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void *slot44(void *a, void *b);
};

class Module3
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void *slot44(void *a, void *b, int c);
};

class Object
{
public:
	void setStatus(ObjectStatusTypes bit, bool flag);
	void Rva0028CDEB(ObjectStatusMask *mask);
	void rva0028FAD1(Object *arg);

private:
	void *m_vtable;
	Flag04 *m_p04;
	char m_pad08[0x250 - 0x08];
	Module2 *m_mod250;
	char m_pad254[0x274 - 0x254];
	Object *m_containedBy;
	int m_pad278;
	int m_unk27C;
	char m_pad280[0x439 - 0x280];
	unsigned char m_bit439;
};

struct RetBits
{
	unsigned int m_bits[1];
	int test(int i) { return (m_bits[i >> 5] >> (i & 31)) & 1; }
};

void Object::rva0028FAD1(Object *arg)
{
	if (m_p04->m_flag & 0x80) {
		m_bit439 &= (unsigned char)~1;
		setStatus(OBJECT_STATUS_UNDER_CONSTRUCTION, false);
	} else {
		Module2 *mod;
		if (arg)
			mod = (Module2 *)((Object *)arg)->m_mod250;
		else
			mod = 0;
		if (mod) {
			ObjectStatusMask mask;
			void *ret = mod->slot44(&mask, this);
			unsigned int bits = *(unsigned int *)ret;
			bits >>= 3;
			_ReadWriteBarrier();
			if ((bits & 1) != 0)
				m_bit439 |= 1;
			else
				m_bit439 &= (unsigned char)~1;
		} else {
			m_bit439 &= (unsigned char)~1;
		}
		if (mod) {
			ObjectStatusMask mask2;
			void *ret2 = ((Module3 *)mod)->slot44(&mask2, this, 1);
			Rva0028CDEB((ObjectStatusMask *)ret2);
		}
	}
	m_containedBy = arg;
	m_unk27C = TheGameLogic->m_unk40;
}
