// ?onDie@CreateObjectDie@@UAEXPBVDamageInfo@@@Z
// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?onDie@CreateObjectDie@@UAEXPBVDamageInfo@@@Z, retail 0x00485C86 139B (formerly the
// placeholder CreateObjectDieIfEldestKindof::rva00485C86): CreateObjectDie::onDie, slot 0 of
// CreateObjectDie's die-module table 0x00C4A7DC, gated on BFME2's upgrade list; also called by CreateObjectDieIfEldestKindof::onDie (0x00485D11),
// which tail-calls it as `push [ebp+8]; mov ecx,esi; call` -- so the method is __thiscall with
// `this` in ecx and `damageInfo` as its only stack argument (`ret 4`).
//
// Evidence: the literal "CreateObjectDieIfEldestKindof" appears in the caller at 0x00485D11 and
// passes the same `this`; vtable slot 12. Callees are all rowed: findUpgrade 0x0026F26D,
// getControllingPlayer 0x0028AFA9, Player::rva002AB87D 0x002AB87D, Object::hasUpgrade 0x00290D2B,
// GameLogic::findObjectByID 0x00049DC5 and ObjectCreationList::create 0x001F08D3.
// ModuleData view: OCL at +0x38, the upgrade name vector at +0x40 (begin) / +0x44 (end).
//
// Register shape (this is what the bytes pin down, and the reason the naive port mismatched):
// `this` stays live in edi to the very last push, the loop walks the name vector in ebx against
// esi=ModuleData, and the upgrading object is spilled to [ebp-4]. Re-deriving the tail argument
// from `this` rather than reusing the `obj` local is what keeps `this` live across the whole body
// and forces that spill; passing `obj` directly lets the optimiser drop the frame, and the body
// comes out 9 bytes short in a different register allocation.
#include "ascii_string.h"
#include "../../../../Include/GameLogic/Module/DieModule.h"

class UpgradeTemplate
{
public:
	int m_00;
	int m_type;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

struct PlayerTeamNode;
class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *t) const;
	char m_pad00[0x32C];
	PlayerTeamNode *m_head32C; // +0x32C
};

class Module;
struct findEldest;
class Object
{
protected:
	friend struct findEldest;
	Module *findModule(NameKeyType key) const;
public:
	Player *getControllingPlayer() const;
	bool hasUpgrade(const UpgradeTemplate *t) const;
	char m_pad00[0x74];
	int m_id74; // +0x74
};

#include "../../../Common/GameLogicObjectLookupView.h"

class DamageInfo
{
public:
	int m_pad00[2];
	ObjectID m_sourceID08;
};

extern GameLogic *TheGameLogic;

class ObjectCreationList
{
public:
	void create(void *a1, void *a2, void *a3);
};

struct CreateObjectDieModuleDataView
{
	char m_pad00[0x38];
	ObjectCreationList *m_ocl;
	char m_pad3C[4];
	AsciiString *m_requiredUpgradesBegin;
	AsciiString *m_requiredUpgradesEnd;
};

// MSVC enters this override through DieModuleInterface at +0x10, slot 0 of
// 0x00C4A7DC. The canonical base supplies the helper and owner/data offsets.
class CreateObjectDie : public DieModule
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
};

// ?onDie@CreateObjectDie@@UAEXPBVDamageInfo@@@Z
void CreateObjectDie::onDie(const DamageInfo *damageInfo)
{
	if (!isDieApplicable(damageInfo))
		return;
	Object *obj = m_object;
	const CreateObjectDieModuleDataView *data = (const CreateObjectDieModuleDataView *)m_moduleData;
	AsciiString *cur = data->m_requiredUpgradesBegin;
	while (cur != data->m_requiredUpgradesEnd)
	{
		const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade(*cur);
		if (upgradeTemplate)
		{
			bool ok;
			if (upgradeTemplate->m_type == 0)
				ok = obj->getControllingPlayer()->rva002AB87D(upgradeTemplate);
			else
				ok = obj->hasUpgrade(upgradeTemplate);
			if (!ok)
				return;
		}
		++cur;
	}
	ObjectCreationList *ocl = data->m_ocl;
	if (ocl == 0)
		return;
	ocl->create(*(Object **)((char *)this + 8),
		TheGameLogic->findObjectByID(damageInfo->m_sourceID08), (void *)0);
}
