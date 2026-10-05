// ?Rva003E4860Get@@YG_NPAVParameter@@@Z
// partial score=0.97 date=2026-10-05
// ?Rva003E4860Get@@YG_NPAVParameter@@@Z
// cl: /O1 /EHsc
// @0x003E4860 193B leaf single-param object track via rowed getUnitNamed
// 0x003588E7 plus rowed new 0x0002FDA0 plus rowed delete 0x0002FD60.
// Evidence: caller 0x003EB8DB; prev 0x003E477F Rva003E477FGet; next
// 0x003E4921 ScriptConditions method. List head g_00E02E00 nodes carry
// object id +0x74 with frame from TheGameLogic +0x40 and value from
// iface slot 0x114 at object +0x250; new nodes get vtable g_00C35B34.
class Parameter;
class Object;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};
extern ScriptEngine *g_Va009FE16C;
class Iface0250
{
public:
	virtual void _d00(), _d01(), _d02(), _d03(), _d04(), _d05(), _d06();
	virtual void _d07(), _d08(), _d09(), _d10(), _d11(), _d12(), _d13();
	virtual void _d14(), _d15(), _d16(), _d17(), _d18(), _d19(), _d20();
	virtual void _d21(), _d22(), _d23(), _d24(), _d25(), _d26(), _d27();
	virtual void _d28(), _d29(), _d30(), _d31(), _d32(), _d33(), _d34();
	virtual void _d35(), _d36(), _d37(), _d38(), _d39(), _d40(), _d41();
	virtual void _d42(), _d43(), _d44(), _d45(), _d46(), _d47(), _d48();
	virtual void _d49(), _d50(), _d51(), _d52(), _d53(), _d54(), _d55();
	virtual void _d56(), _d57(), _d58(), _d59(), _d60(), _d61(), _d62();
	virtual void _d63(), _d64(), _d65(), _d66(), _d67(), _d68();
	virtual int iface0114(int arg);
};
class Object
{
public:
	int m_pad74[29];
	int m_id74;
	int m_pad78[118];
	Iface0250 *m_iface250;
};
class GameLogic
{
public:
	int m_pad40[16];
	int m_frame40;
};
extern GameLogic *TheGameLogic;
struct Rva003E4860Entry
{
	const void *vptr;
	Rva003E4860Entry *next;
	int id;
	int frame;
	int value;
};
extern Rva003E4860Entry *g_00E02E00;
extern const void *const g_00C35B34[];
void *__cdecl operator new(unsigned int size) throw();

// ?Rva003E4860Get@@YG_NPAVParameter@@@Z present-unmatched
bool __stdcall Rva003E4860Get(Parameter *p)
{
	Object *obj = g_Va009FE16C->getUnitNamed(p);
	int curVal = 0;
	if (!obj)
		return false;
	Rva003E4860Entry *n = g_00E02E00;
	while (n && n->id != obj->m_id74)
		n = n->next;
	Iface0250 *iface = obj->m_iface250;
	if (iface)
		curVal = iface->iface0114(curVal);
	int frame = TheGameLogic->m_frame40;
	if (!n) {
		Rva003E4860Entry *nn = (Rva003E4860Entry *)operator new(sizeof(*nn));
		int zero = 0;
		if (nn != (Rva003E4860Entry *)zero) {
			nn->vptr = (const void *)g_00C35B34;
			nn->next = (Rva003E4860Entry *)zero;
			nn->id = zero;
			nn->frame = zero;
			nn->value = zero;
		} else {
			nn = 0;
		}
		nn->id = obj->m_id74;
		Rva003E4860Entry *head = g_00E02E00;
		nn->frame = frame;
		nn->value = curVal;
		nn->next = head;
		g_00E02E00 = nn;
		return false;
	}
	if (n->frame == frame - 1 && n->value > 0 && curVal == 0)
		return true;
	n->frame = frame;
	n->value = curVal;
	return false;
}
