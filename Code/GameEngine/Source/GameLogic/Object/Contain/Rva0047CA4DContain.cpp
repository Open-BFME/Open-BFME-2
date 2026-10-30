// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/GameEngine/Include/GameLogic
// stlport
// ?rva0047CA4D@Rva0047CA4D@@QAE_NPAVObject@@HH@Z, retail 0x0047CA4D, 142 bytes.
// Evidence: slot38-shape leaf like the matched 0x0047BA69 row (Object::testStatus
// 0x0004E536 STATUS_62 refusal, this-0x18 Object / this-0x1c table base,
// Object::getControllingPlayer 0x0028AFA9, BfmeTab1026::bfmeHas1026 pin 0x00362437
// over tab+0x18c with the limit at +0x190, same-controller pass-through). Deltas:
// the count member reads at +0x10c (not +0x100), the count gate is an && early
// return (jb-to-eval layout), and the tab/limit refusals delegate to the sibling
// slot38-shape body at 0x004771EB (rowed HordeTransportContain::isValidContainerFor) while
// count/player refusals fall back to TransportContain::slot38 pin 0x00466EDE.
// Honest address name; the owning class is unproven (a HordeSiegeEngineContain
// slot is suspected from the matched slot53 row at the next address 0x0047CADB).

// ContainmentList for the HordeTransportContain view shared with HordeSiegeEngineContain.cpp.
#include "ContainmentListView.h"

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
class ModuleData;
// OpenContain / TransportContain as HordeSiegeEngineContain.cpp declares them.
class OpenContain
{
public:
	virtual void onDelete();
	virtual void removeAllContained(bool exposeStealthUnits);

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_padding0C[0x100 - 0x0C];
};

// Virtuals below are the ones this unit's bodies call by qualified name; their
// relative slot order is not asserted (no vtable is emitted from this view).
class TransportContain : public OpenContain
{
public:
	virtual void onContaining(Object *rider, bool wasSelected);
	virtual bool slot38(Object *obj, int a, int b);

private:
	unsigned char m_padding100[0x11C - 0x100];
};
// 0x004771EB is rowed as HordeTransportContain::isValidContainerFor.
class HordeTransportContain : public TransportContain
{
public:
	void rva00463A4D(ContainmentList riders, int arg);	// 0x00463A4D
	void redeployOccupants();					// 0x00477513
	virtual bool isValidContainerFor(Object *obj, bool a, bool b);	// 0x004771EB

private:
	unsigned char m_padding11C[0x128 - 0x11C];
};
class Rva0047CA4D
{
public:
	bool rva0047CA4D(Object *obj, int a2, int a3);
};

bool Rva0047CA4D::rva0047CA4D(Object *obj, int a2, int a3)
{
	if (obj->testStatus(STATUS_62))
		return false;
	Object *object = *(Object **)((char *)this - 0x18);
	void *tabBase = *(void **)((char *)this - 0x1c);
	Player *player = object->getControllingPlayer();
	BfmeTab1026 *tab = (BfmeTab1026 *)((char *)tabBase + 0x18c);
	if (!tab->accepts(obj, player))
		goto failOther;
	int limit = *(int *)((char *)tabBase + 0x190);
	if (limit > 0) {
		if ((unsigned char)a2 != 0 && *(unsigned int *)((char *)this + 0x10c) >= (unsigned int)limit)
			return ((TransportContain *)this)->TransportContain::slot38(obj, a2, a3);
		{
			Object *containerOwner = *(Object **)((char *)this - 0x18);
			Player *ownerPlayer = containerOwner->getControllingPlayer();
			Player *objectPlayer = obj->getControllingPlayer();
			if (objectPlayer != ownerPlayer)
				return ((TransportContain *)this)->TransportContain::slot38(obj, a2, a3);
			return true;
		}
	}
 failOther:
	return ((HordeTransportContain *)this)->HordeTransportContain::isValidContainerFor(obj, *(bool *)&a2, *(bool *)&a3);
}
