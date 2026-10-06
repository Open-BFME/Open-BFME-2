// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
// ?updateUpgradeModules@Object@@QAEXXZ, retail 0x00292EEA, 194 bytes.
// Object upgrade-module recheck: player mask at +0x13c ORed with self at
// +0x284 and castle at +0x284 (via CastleMember +0x14 and TheGameLogic at
// 0x00DFE78C), then per-module getUpgrade at slot 0x28, isAlreadyUpgraded
// at slot 0, attemptUpgrade at slot 4, postUpgradeCheck at slot 0x18.
// Evidence: BFME1 donor ObjectUpdateUpgradeModulesBody.cpp (same castle and
// post-check shape, masks 24B at +0x8c/+0x224 and behaviors at +0x1f0);
// BFME2 callers 0x0029306D 0x00293513 0x00294F73 0x00298A97 0x00298BF2 and
// Player::onUpgradeCompleted plus DozerAIUpdate updateUpgradeModules call
// prove Object owner; vtable slot layout from Bridge/Spawn precedents.

enum ObjectID
{
	INVALID_ID = 0
};

struct BfmeFixedStorage128
{
	BfmeFixedStorage128(const BfmeFixedStorage128&);
	unsigned char bytes[128];
};

namespace _STL
{
template<unsigned N> struct _Base_bitset;
template<> struct _Base_bitset<32>
{
	void _M_do_or(const _Base_bitset<32>&);
	unsigned long _M_w[32];
};
}

class Player
{
public:
	char m_pad00[0x13c];
	BfmeFixedStorage128 m_mask13c;
};

class Object;
class Module;

class CastleBehavior
{
public:
	static Module *rva000395708(Object *obj);
};

class GameLogic
{
public:
	class Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class UpgradeModuleInterface
{
public:
	virtual bool isAlreadyUpgraded() const = 0;
	virtual bool attemptUpgrade(const BfmeFixedStorage128 &mask) = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void postUpgradeCheck() = 0;
};

class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual UpgradeModuleInterface *getUpgrade() = 0;
};

class BfmeObjectModule
{
public:
	virtual void slot0() = 0;

private:
	unsigned int m_data[2];
};

class BehaviorModule : public BfmeObjectModule, public BehaviorModuleInterface
{
};

class Module
{
public:
	char m_pad00[0x14];
	ObjectID m_castleID;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void updateUpgradeModules();
	void rva00293003(const void *arg);
	void rva00293077(const void *arg);

private:
	char m_pad00[0x244];
	BehaviorModule **m_modules;
	char m_pad248[0x250 - 0x248];
	class Object250Helper *m_helper250;
	char m_pad254[0x284 - 0x254];
	_STL::_Base_bitset<32> m_mask284;
};

class Object250Helper
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual void s20() = 0;
	virtual void s21() = 0;
	virtual void s22() = 0;
	virtual void s23() = 0;
	virtual void s24() = 0;
	virtual void s25() = 0;
	virtual void s26() = 0;
	virtual void s27() = 0;
	virtual void s28() = 0;
	virtual void s29() = 0;
	virtual void s30() = 0;
	virtual void s31() = 0;
	virtual void s32() = 0;
	virtual void s33() = 0;
	virtual void s34() = 0;
	virtual void s35() = 0;
	virtual void s36() = 0;
	virtual void s37() = 0;
	virtual void s38() = 0;
	virtual void s39() = 0;
	virtual void s40() = 0;
	virtual void s41() = 0;
	virtual void s42() = 0;
	virtual void s43() = 0;
	virtual void s44() = 0;
	virtual void s45() = 0;
	virtual void s46() = 0;
	virtual void s47() = 0;
	virtual void s48() = 0;
	virtual void s49() = 0;
	virtual void s50() = 0;
	virtual void s51() = 0;
	virtual void s52() = 0;
	virtual void s53() = 0;
	virtual void s54() = 0;
	virtual void s55() = 0;
	virtual void s56() = 0;
	virtual void s57() = 0;
	virtual void s58() = 0;
	virtual void s59() = 0;
	virtual void s60() = 0;
	virtual void s61() = 0;
	virtual void s62() = 0;
	virtual void s63() = 0;
	virtual void s64() = 0;
	virtual void s65() = 0;
	virtual void s66() = 0;
	virtual void s67() = 0;
	virtual void s68() = 0;
	virtual void s69() = 0;
	virtual void s70() = 0;
	virtual void s71() = 0;
	virtual void s72() = 0;
	virtual void s73() = 0;
	virtual void s74() = 0;
	virtual void s75() = 0;
	virtual void s76() = 0;
	virtual void s77() = 0;
	virtual void s78() = 0;
	virtual void s79() = 0;
	virtual void s80() = 0;
	virtual void s81() = 0;
	virtual void s82() = 0;
	virtual void s83() = 0;
	virtual void s84() = 0;
	virtual void s85() = 0;
	virtual void s86() = 0;
	virtual void s87() = 0;
	virtual void s88() = 0;
	virtual void s89() = 0;
	virtual void s90() = 0;
	virtual void s91() = 0;
	virtual void s92() = 0;
	virtual void slot93(const void *mask, int zero) = 0;
};

class UpgradeTemplate
{
public:
	unsigned int getMaskIndex() const { return m_maskIndex; }

private:
	char m_pad00[0x38];
	unsigned int m_maskIndex;
};

struct UpgradeBatch
{
	char m_pad00[0x1c];
	UpgradeTemplate **m_begin;
	UpgradeTemplate **m_end;
	char m_pad24[0x38 - 0x24];
	unsigned int m_singleMask;
};

void Object::updateUpgradeModules()
{
	Player *player = getControllingPlayer();
	if (!player)
		return;
	Object *castle = 0;
	const BfmeFixedStorage128 *playerMask = &player->m_mask13c;
	Module *member = CastleBehavior::rva000395708(this);
	if (member != 0)
		castle = TheGameLogic->findObjectByID(member->m_castleID);
	for (BehaviorModule **m = m_modules; *m; ++m)
	{
		BehaviorModuleInterface *beh = (BehaviorModuleInterface *)((char *)*m + 0x0c);
		UpgradeModuleInterface *up = beh->getUpgrade();
		if (!up)
			continue;
		if (!up->isAlreadyUpgraded())
		{
			BfmeFixedStorage128 tmp(*playerMask);
			((_STL::_Base_bitset<32> *)&tmp)->_M_do_or(m_mask284);
			if (castle)
				((_STL::_Base_bitset<32> *)&tmp)->_M_do_or(castle->m_mask284);
			up->attemptUpgrade(tmp);
		}
		up->postUpgradeCheck();
	}
}

void Object::rva00293003(const void *arg)
{
	const UpgradeBatch *batch = (const UpgradeBatch *)arg;
	if (batch->m_begin != batch->m_end)
	{
		for (unsigned i = 0; i < (unsigned)(batch->m_end - batch->m_begin); ++i)
		{
			UpgradeTemplate *templ = batch->m_begin[i];
			if (!templ)
				continue;
			unsigned int idx = templ->getMaskIndex();
			m_mask284._M_w[idx >> 5] |= (unsigned long)1 << (idx & 31);
		}
	}
	else
	{
		unsigned int idx = batch->m_singleMask;
		m_mask284._M_w[idx >> 5] |= (unsigned long)1 << (idx & 31);
	}
	updateUpgradeModules();
}

void Object::rva00293077(const void *arg)
{
	if (!arg)
		return;
	rva00293003(arg);
	Object250Helper *helper = m_helper250;
	if (!helper)
		return;
	helper->slot93(&m_mask284, 0);
}
