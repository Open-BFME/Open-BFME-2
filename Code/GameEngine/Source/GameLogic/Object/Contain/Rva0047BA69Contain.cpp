// cl: /DNDEBUG /MD
// ?rva0047BA69@Rva0047BA69@@QAE_NPAVObject@@HH@Z, retail 0x0047BA69, 126 bytes.
// Evidence: leaf lane called from 0x0047E530 thunk; callees Object::testStatus 0x0004E536,
// Object::getControllingPlayer 0x0028AFA9, BfmeTab1026::bfmeHas1026 pin 0x00362437,
// TransportContain::slot38 pin 0x00466EDE fallback; this-0x18/-0x1c/+0x100 layout;
// honest address name (owner unproven, Contain-adjacent).

enum ObjectStatusTypes
{
	STATUS_62 = 0x3e
};
class Player;
class Object
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	Player *getControllingPlayer() const;
};
class BfmeTab1026
{
public:
	char bfmeHas1026(int a, int b);
};
class TransportContain
{
public:
	virtual bool slot38(Object *obj, int a, int b);
};
class Rva0047BA69
{
public:
	bool rva0047BA69(Object *obj, int a2, int a3);
};

#pragma optimize("y", off)
bool Rva0047BA69::rva0047BA69(Object *obj, int a2, int a3)
{
	if (obj->testStatus(STATUS_62))
		return false;
	Object *o1 = *(Object **)((char *)this - 0x18);
	void *tabBase = *(void **)((char *)this - 0x1c);
	Player *p1 = o1->getControllingPlayer();
	BfmeTab1026 *tab = (BfmeTab1026 *)((char *)tabBase + 0x18c);
	if (!tab->bfmeHas1026((int)obj, (int)p1))
		goto fail;
	int limit = *(int *)((char *)tabBase + 0x190);
	if (limit <= 0)
		goto fail;
	if ((unsigned char)a2 != 0) {
		if (*(unsigned int *)((char *)this + 0x100) >= (unsigned int)limit)
			goto fail;
	}
	{
		Object *o2 = *(Object **)((char *)this - 0x18);
		Player *p2 = o2->getControllingPlayer();
		Player *p3 = obj->getControllingPlayer();
		if (p3 == p2)
			return true;
		goto fail;
	}
fail:
	return ((TransportContain *)this)->TransportContain::slot38(obj, a2, a3);
}
#pragma optimize("", on)
