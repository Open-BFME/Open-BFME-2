// ?rva00485C86@CreateObjectDieIfEldestKindof@@QAEXPBVDamageInfo@@@Z
// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?rva00485C86@CreateObjectDieIfEldestKindof@@QAEXPBVDamageInfo@@@Z, retail 0x00485C86 139B:
// the upgrade-gated create helper behind CreateObjectDieIfEldestKindof::onDie (0x00485D11),
// which tail-calls it as `push [ebp+8]; mov ecx,esi; call` -- so the method is __thiscall with
// `this` in ecx and `damageInfo` as its only stack argument (`ret 4`).
//
// Evidence: the literal "CreateObjectDieIfEldestKindof" appears in the caller at 0x00485D11 and
// passes the same `this`; vtable slot 12. Callees are all rowed: findUpgrade 0x0026F26D,
// getControllingPlayer 0x0028AFA9, Player::rva002AB87D 0x002AB87D, Object::rva00290D2B 0x00290D2B,
// GameLogic::findObjectByID 0x00049DC5 and ObjectCreationList::rva001F08D3 0x001F08D3.
// ModuleData view: OCL at +0x38, the upgrade name vector at +0x40 (begin) / +0x44 (end).
//
// Register shape (this is what the bytes pin down, and the reason the naive port mismatched):
// `this` stays live in edi to the very last push, the loop walks the name vector in ebx against
// esi=ModuleData, and the upgrading object is spilled to [ebp-4]. Re-deriving the tail argument
// from `this` rather than reusing the `obj` local is what keeps `this` live across the whole body
// and forces that spill; passing `obj` directly lets the optimiser drop the frame, and the body
// comes out 9 bytes short in a different register allocation.
#include "ascii_string.h"

class UpgradeTemplate
{
public:
	int m_00;
	int m_04;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern "C" UpgradeCenter *TheUpgradeCenter;
#pragma comment(linker, "/alternatename:_TheUpgradeCenter=?TheUpgradeCenter@@3PAVUpgradeCenter@@A")

class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *t) const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	bool rva00290D2B(const UpgradeTemplate *t) const;
};

enum ObjectID
{
	INVALID_ID = 0
};

class DamageInfo
{
public:
	int m_pad00[2];
	ObjectID m_sourceID08;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class ObjectCreationList
{
public:
	void rva001F08D3(void *a1, void *a2, void *a3);
};

class DieModule
{
	friend class CreateObjectDieIfEldestKindof;
protected:
	bool isDieApplicable(const DamageInfo *damageInfo) const;
public:
	void *m_04;
	Object *m_08;
};

struct CreateObjectDieModuleDataView
{
	char m_pad00[0x38];
	ObjectCreationList *m_ocl38;
	char m_pad3C[4];
	AsciiString *m_begin40;
	AsciiString *m_end44;
};

class CreateObjectDieIfEldestKindof
{
public:
	void rva00485C86(const DamageInfo *damageInfo);
};

// ?rva00485C86@CreateObjectDieIfEldestKindof@@QAEXPBVDamageInfo@@@Z
void CreateObjectDieIfEldestKindof::rva00485C86(const DamageInfo *damageInfo)
{
	if (!((DieModule *)((char *)this - 0x10))->isDieApplicable(damageInfo))
		return;
	Object *obj = *(Object **)((char *)this - 8);
	CreateObjectDieModuleDataView *data = *(CreateObjectDieModuleDataView **)((char *)this - 0x0C);
	AsciiString *cur = data->m_begin40;
	while (cur != data->m_end44)
	{
		const UpgradeTemplate *t = TheUpgradeCenter->findUpgrade(*cur);
		if (t)
		{
			bool ok;
			if (t->m_04 == 0)
				ok = obj->getControllingPlayer()->rva002AB87D(t);
			else
				ok = obj->rva00290D2B(t);
			if (!ok)
				return;
		}
		++cur;
	}
	ObjectCreationList *ocl = data->m_ocl38;
	if (ocl == 0)
		return;
	ocl->rva001F08D3(*(Object **)((char *)this - 8),
		TheGameLogic->findObjectByID(damageInfo->m_sourceID08), (void *)0);
}
