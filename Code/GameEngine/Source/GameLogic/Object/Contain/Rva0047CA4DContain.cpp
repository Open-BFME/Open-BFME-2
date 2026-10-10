// cl: /DNDEBUG /MD
// ?rva0047CA4D@Rva0047CA4D@@QAE_NPAVObject@@HH@Z, retail 0x0047CA4D, 142 bytes.
// Evidence: slot38-shape leaf like the matched 0x0047BA69 row (Object::testStatus
// 0x0004E536 STATUS_62 refusal, this-0x18 Object / this-0x1c table base,
// Object::getControllingPlayer 0x0028AFA9, BfmeTab1026::bfmeHas1026 pin 0x00362437
// over tab+0x18c with the limit at +0x190, same-controller pass-through). Deltas:
// the count member reads at +0x10c (not +0x100), the count gate is an && early
// return (jb-to-eval layout), and the tab/limit refusals delegate to the sibling
// slot38-shape body at 0x004771EB (address-named Rva004771EB::slot38 pin) while
// count/player refusals fall back to TransportContain::slot38 pin 0x00466EDE.
// Honest address name; the owning class is unproven (a HordeSiegeEngineContain
// slot is suspected from the matched slot53 row at the next address 0x0047CADB).

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
// 0x00362437 is rowed as Rva2225E0Filter::accepts(Object *, Player *); the old
// ?bfmeHas1026@BfmeTab1026@@QAEDHH@Z pin names the same body.
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};
class BfmeTab1026 : public Rva2225E0Filter
{
public:
};
class TransportContain
{
public:
	virtual bool slot38(Object *obj, int a, int b);
};
class Rva004771EB
{
public:
	virtual bool slot38(Object *obj, int a, int b);
};
class Rva0047CA4D
{
public:
	bool rva0047CA4D(Object *obj, int a2, int a3);
};

#pragma optimize("y", off)
bool Rva0047CA4D::rva0047CA4D(Object *obj, int a2, int a3)
{
	if (obj->testStatus(STATUS_62))
		return false;
	Object *o1 = *(Object **)((char *)this - 0x18);
	void *tabBase = *(void **)((char *)this - 0x1c);
	Player *p1 = o1->getControllingPlayer();
	BfmeTab1026 *tab = (BfmeTab1026 *)((char *)tabBase + 0x18c);
	if (!tab->accepts(obj, p1))
		goto failOther;
	int limit = *(int *)((char *)tabBase + 0x190);
	if (limit > 0) {
		if ((unsigned char)a2 != 0 && *(unsigned int *)((char *)this + 0x10c) >= (unsigned int)limit)
			return ((TransportContain *)this)->TransportContain::slot38(obj, a2, a3);
		{
			Object *o2 = *(Object **)((char *)this - 0x18);
			Player *p2 = o2->getControllingPlayer();
			Player *p3 = obj->getControllingPlayer();
			if (p3 != p2)
				return ((TransportContain *)this)->TransportContain::slot38(obj, a2, a3);
			return true;
		}
	}
 failOther:
	return ((Rva004771EB *)this)->Rva004771EB::slot38(obj, a2, a3);
}
#pragma optimize("", on)
