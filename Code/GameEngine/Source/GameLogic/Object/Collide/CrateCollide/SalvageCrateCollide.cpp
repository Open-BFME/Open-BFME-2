// cl: /Ireference/shims/bfme2_ascii /MD /GX
//
// SalvageCrateCollide.cpp (the unit the random-value calls name).
// SalvageCrateCollide's vftable 0x00C5A9C0: slot 0 the deleting dtor
// 0x004BD265, slot 12 executeCrateBehavior, slot 13 isValidToExecute; its
// module data (ctor 0x00255B7E) keeps the level chance at +0x64, the unit
// level radius at +0x68, the money range at +0x70/+0x74, the upgrade name at
// +0x78 and the allow-computer-pickup flag at +0x7C. BFME1's SalvageCrateCollide
// (reference/open-bfme-1, doMoney and executeCrateBehavior) is the donor;
// BFME2 adds the upgrade and nearby-units outcomes and the player-scored
// deposit.
//
//   0x004BD281  pick the outcome: 2 (a rank) when the roll falls under the
//               level chance, else 4 with an upgrade name and 3 without
//   0x004BD2D0  give one level to each object of the hit list
//   0x004BD314  isValidToExecute: CrateCollide's test, an AI and not
//               template +0x108 bit 2
//   0x004BD342  doMoney: the money range (scaled by the local player's
//               multiplayer money multiplier in multiplayer), deposited for
//               the picker's player and shown with GUI:AddCash
//   0x004BD442  executeCrateBehavior: refuse computer players unless
//               allowed, then by outcome level the units in range of the
//               picker owned by its player (or give the money when none),
//               raise the picker a rank (GUI:GainRank), grant the player
//               upgrade, or give the money

#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../../Common/RTS/PlayerUpgradeStatus.h"

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD04, allow 0x00260E2A, slot 2 0x00260E1E: +0x08 a player.
class Rva00260E2AFilter : public Rva000421C8
{
public:
	Rva00260E2AFilter(Player *player) : m_player(player) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
};

// vftable 0x00C5A99C, allow 0x00260E44: no members beyond the link.
class Rva00260E44Filter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

// The hit list's payload: 8-byte entries from +0x00 to +0x04.
struct BfmeWideHit
{
	Object *m_obj;
	int m_extra;
};

struct BfmeWideList
{
	BfmeWideHit *m_begin;
	BfmeWideHit *m_end;
	unsigned size() const { return (unsigned)(m_end - m_begin); }
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	BfmeWideList *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

extern float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);	// 0x00234092
extern int GetGameLogicRandomValue(int lo, int hi, char *file, int line);	// 0x00233FF4

class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16();
	virtual const UnicodeString *slot44(const char *label, bool *exists);
};
extern GameTextInterface *TheGameText;

class GameLogic
{
public:
	char rva0023C6FD();	// 0x0023C6FD
};
extern GameLogic *TheGameLogic;

class PlayerList
{
public:
	int rva002A7C0B(bool flag);	// 0x002A7C0B
};
extern PlayerList *ThePlayerList;

class MultiPlayMults
{
public:
	float getMoneyMult(int slot) const;	// 0x00235971
};

class GlobalData
{
public:
	char m_pad000[0xEC4];
	MultiPlayMults m_multiPlayMults;	// +0xEC4
};
extern class GlobalData *TheWritableGlobalData;

class UpgradeTemplate
{
public:
	char m_pad00[0x04];
	int m_type;	// +0x04 (0 a player upgrade)
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;	// 0x0026F26D
};
extern UpgradeCenter *TheUpgradeCenter;

class Rva0039B7AD
{
	char m_pad[4];
};

class Rva003B0D7C
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *score, bool flag);	// 0x003B0D7C
	char m_pad[4];
};

class Player
{
public:
	int ScaleMoney(int amount);	// 0x002A9E36
	Upgrade *rva002AE329(const UpgradeTemplate *upgrade, UpgradeStatusType status, int flag);	// 0x002AE329
	char m_pad000[0x5C];
	int m_5C;			// +0x5C (1 a computer player)
	char m_pad060[0x90 - 0x60];
	Rva003B0D7C m_money;		// +0x90
	char m_pad094[0x3BC - 0x94];
	Rva0039B7AD m_3BC;		// +0x3BC
};

class ExperienceTracker
{
public:
	bool rva0039B4EC(int levels, bool flag1, bool flag2);	// 0x0039B4EC
};

class ThingTemplate
{
public:
	char m_pad000[0x108];
	unsigned m_108;		// +0x108 (bit 2 tested)
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos;			// +0x38
	char m_pad044[0x258 - 0x44];
	void *m_ai;			// +0x258
	char m_pad25C[0x264 - 0x25C];
	ExperienceTracker *m_experienceTracker;	// +0x264
};

struct SalvageCrateCollideModuleData
{
	char m_pad00[0x64];
	float m_levelChance;	// +0x64
	float m_unitRadius;	// +0x68
	char m_pad6C[0x70 - 0x6C];
	int m_minMoney;		// +0x70
	int m_maxMoney;		// +0x74
	AsciiString m_upgrade;	// +0x78
	bool m_allowComputerPickup;	// +0x7C
};

class CrateCollide
{
public:
	virtual ~CrateCollide();
protected:
	virtual bool executeCrateBehavior(Object *other);
	virtual bool isValidToExecute(const Object *other) const;	// 0x004BC6C2
	void rva004BCF92(const Object *other, const UnicodeString *text);	// 0x004BCF92
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class SalvageCrateCollide : public CrateCollide
{
protected:
	virtual bool executeCrateBehavior(Object *other);
	virtual bool isValidToExecute(const Object *other) const;
private:
	const SalvageCrateCollideModuleData *getSalvageCrateCollideModuleData() const
	{
		return (const SalvageCrateCollideModuleData *)m_moduleData;
	}
	int rva004BD281();
	void rva004BD2D0(BfmeWideResult *hits);
	void doMoney(Object *other);
};

int SalvageCrateCollide::rva004BD281()
{
	const SalvageCrateCollideModuleData *data = getSalvageCrateCollideModuleData();
	float roll = GetGameLogicRandomValueReal(0.0f, 1.0f,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Collide\\CrateCollide\\SalvageCrateCollide.cpp",
		0x45);
	if (roll < data->m_levelChance)
		return 2;
	return data->m_upgrade.getLength() > 0 ? 4 : 3;
}

void SalvageCrateCollide::rva004BD2D0(BfmeWideResult *hits)
{
	Object *obj;
	while ((obj = hits->next()) != 0) {
		ExperienceTracker *tracker = obj->m_experienceTracker;
		if (tracker)
			tracker->rva0039B4EC(1, true, false);
	}
}

bool SalvageCrateCollide::isValidToExecute(const Object *other) const
{
	if (CrateCollide::isValidToExecute(other) && other->m_ai != 0
			&& !(other->m_template->m_108 & 4))
		return true;
	return false;
}

void SalvageCrateCollide::doMoney(Object *other)
{
	const SalvageCrateCollideModuleData *data = getSalvageCrateCollideModuleData();
	int money;
	if (data->m_minMoney != data->m_maxMoney)
		money = GetGameLogicRandomValue(data->m_minMoney, data->m_maxMoney,
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Collide\\CrateCollide\\SalvageCrateCollide.cpp",
			0xDB);
	else
		money = data->m_minMoney;
	if (money > 0) {
		if (TheGameLogic->rva0023C6FD()) {
			float mult = TheWritableGlobalData->m_multiPlayMults.getMoneyMult(ThePlayerList->rva002A7C0B(false));
			money = (int)(money * mult);
		}
		Player *player = other->getControllingPlayer();
		if (player) {
			money = player->ScaleMoney(money);
			player->m_money.rva003B0D7C(money, &player->m_3BC, true);
		}
		UnicodeString moneyString;
		moneyString.format(TheGameText->slot44("GUI:AddCash", 0), money);
		rva004BCF92(other, &moneyString);
	}
}

bool SalvageCrateCollide::executeCrateBehavior(Object *other)
{
	const SalvageCrateCollideModuleData *data = getSalvageCrateCollideModuleData();
	if (!data->m_allowComputerPickup && other) {
		Player *player = other->getControllingPlayer();
		if (player && player->m_5C == 1)
			return false;
	}
	switch (rva004BD281()) {
	case 0:
	case 1: {
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(other->getPosition(),
			data->m_unitRadius, 1,
			Rva00260E2AFilter(other->getControllingPlayer()).link(&Rva00260E44Filter()), 0);
		if (hits.m_value->size() > 0)
			rva004BD2D0(&hits);
		else
			doMoney(other);
		break;
	}
	case 2:
		if (other && other->m_experienceTracker) {
			other->m_experienceTracker->rva0039B4EC(1, true, false);
			UnicodeString rankString;
			rankString.format(TheGameText->slot44("GUI:GainRank", 0), 1);
			rva004BCF92(other, &rankString);
		}
		break;
	case 4: {
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(data->m_upgrade);
		if (upgrade && upgrade->m_type == 0)
			other->getControllingPlayer()->rva002AE329(upgrade, UPGRADE_STATUS_COMPLETE, 0);
		break;
	}
	default:
		doMoney(other);
		break;
	}
	return true;
}
