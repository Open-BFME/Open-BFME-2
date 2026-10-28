// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
// ?privateGatherAndMoveInFormationToPosition@BfmeC986@@QAEDHHHHH@Z, retail 0x003724B8, 137 bytes.
// BfmeC986-family guarded dispatch (same callee trio as rowed bfmeGo986C
// at 0x00372541: bfmeReady986C 0x36E357, bfmePrep986C 0x36D6B4,
// bfmeSend986C 0x371166): after the ready check, walk the member list at
// +4 for any entry whose +4 field has +0x78 set (via pinned
// Object::rva0028AC4E), then prep, a two-arg check (pinned 0x36D3A3), a
// two-arg step (pinned 0x5494A0) and the five-arg send. Identity of the two
// middle callees not recovered; address-derived BfmeC986 pins.

struct Coord3D;

// The argument block 0x00372571 takes (built inline by its callers).
struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};

class AIGroup
{
public:
	void groupMoveToPosition(Rva00372571Params *params, int source);
	void createFormation(int a, int b);
};

struct Rva0028AC4EField
{
	char m_pad[0x78];
	int m_78;
};

struct Rva0028AC4EEntry
{
	char m_pad00[4];
	Rva0028AC4EField *m_04;
};

class Object
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
};

struct ListNode
{
	ListNode *m_next;
	char m_pad04[4];
	Object *m_obj;
};

class BfmeC986
{
public:
	void bfmeGo986C(int a, int b, int c, int d);
	char bfmeReady986C();
	void bfmePrep986C();
	char rva0036D3A3(int a, int b);
	void bfmeSend986C(int a, int b, int c, int d, int e);
	char privateGatherAndMoveInFormationToPosition(int pos, int cmdSource, int attackMove, int, int adjustGroundPath);
	void groupGatherAndMoveInFormationToPosition(int pos, int cmdSource, int c, int d);
	void groupGatherAndAttackInFormationToPosition(int pos, int cmdSource, int c, int d);
	void rva00372B09(int a, int b, int c);

private:
	char m_pad00[4];
	ListNode *m_head;
};

void BfmeC986::bfmeGo986C(int a, int b, int c, int d)
{
	if (!bfmeReady986C())
		return;

	bfmePrep986C();
	bfmeSend986C(a, b, 0, c, d);
}

char BfmeC986::privateGatherAndMoveInFormationToPosition(int pos, int cmdSource, int attackMove, int, int adjustGroundPath)
{
	if (bfmeReady986C()) {
		char any = 0;
		for (ListNode *node = m_head->m_next; node != m_head; node = node->m_next) {
			Object *obj = node->m_obj;
			if (obj == 0)
				continue;
			const Rva0028AC4EEntry *entry = obj->rva0028AC4E();
			if (entry == 0)
				continue;
			if (entry->m_04->m_78 == 0)
				continue;
			any = 1;
		}
		if (!any)
			return 0;
		bfmePrep986C();
		if (!rva0036D3A3(pos, cmdSource))
			return 0;
		((AIGroup *)this)->createFormation(cmdSource, attackMove);
		bfmeSend986C(pos, cmdSource, attackMove, adjustGroundPath, 0);
	}
	return 1;
}

void BfmeC986::groupGatherAndMoveInFormationToPosition(int pos, int cmdSource, int c, int d)
{
	if (privateGatherAndMoveInFormationToPosition(pos, cmdSource, 0, c, d))
		return;
	Rva00372571Params params;
	params.m_14 |= -1;
	params.m_pos = (const Coord3D *)pos;
	params.m_04 = false;
	params.m_08 = 0;
	params.m_0C = 0;
	params.m_10 = 0;
	params.m_18 = 0;
	params.m_1C = false;
	((AIGroup *)this)->groupMoveToPosition(&params, cmdSource);
}

void BfmeC986::groupGatherAndAttackInFormationToPosition(int pos, int cmdSource, int c, int d)
{
	if (privateGatherAndMoveInFormationToPosition(pos, cmdSource, 1, c, d))
		return;
	rva00372B09(pos, 0x7FFFFFFF, cmdSource);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0036E357 reads ?rva0036E357@AIGroup@@QAE_NXZ
#pragma comment(linker, "/alternatename:?bfmeReady986C@BfmeC986@@QAEDXZ=?rva0036E357@AIGroup@@QAE_NXZ")
//   0x00371166 reads ?moveFormationToPos@AIGroup@@QAEXPBUCoord3D@@W4CommandSourceType@@H_N2@Z
#pragma comment(linker, "/alternatename:?bfmeSend986C@BfmeC986@@QAEXHHHHH@Z=?moveFormationToPos@AIGroup@@QAEXPBUCoord3D@@W4CommandSourceType@@H_N2@Z")
//   0x0036D6B4 reads ?rva0036D6B4@Rva0036ListOwner@@QAEXXZ
#pragma comment(linker, "/alternatename:?bfmePrep986C@BfmeC986@@QAEXXZ=?rva0036D6B4@Rva0036ListOwner@@QAEXXZ")
//   0x0036D3A3 reads ?computeGroundPath@AIGroup@@QAE_NPBUCoord3D@@W4CommandSourceType@@@Z
#pragma comment(linker, "/alternatename:?rva0036D3A3@BfmeC986@@QAEDHH@Z=?computeGroundPath@AIGroup@@QAE_NPBUCoord3D@@W4CommandSourceType@@@Z")
//   0x00372B09 reads ?groupAttackMoveToPosition@AIGroup@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z
#pragma comment(linker, "/alternatename:?rva00372B09@BfmeC986@@QAEXHHH@Z=?groupAttackMoveToPosition@AIGroup@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z")
