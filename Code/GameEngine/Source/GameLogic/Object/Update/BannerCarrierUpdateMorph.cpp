// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include /Ireference/shims/iniexception /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ?rva00496E05@BannerCarrierUpdate@@QAEXPAX_N@Z, retail 0x00496E05 (299B, ret 8).
// BannerCarrierUpdate's morph step for one banner-carrier entry (its name is
// the AsciiString at entry +0x64): look up the entry's model-condition set in
// the module data (rowed 0x00496D43), clear every morph condition (a
// function-static mask built once from the 81-entry table at 0x00C4F6E0)
// while setting that set on the object (rowed Object::rva0028CFB2), refresh
// the object's shroud when it has a non-zero position, play the module
// data's +0x30 FX when asked, and switch the AI to the entry's locomotor set
// when the module data names one (rowed 0x00496DA3, the INI index worker
// 0x0002BCAB over TheLocomotorSetNames, AI virtual slot 0x238).
//
// Evidence (target): the ret 8 and this layout (+4 module data, +8 object),
// the static guard 0x00E03AC4 / mask 0x00E03A78 (memset 0x4C) / init byte
// 0x00E03A70, the table values read from retail .rdata, every call rowed.
// The entry's type and the method's name are not established.

#include <string.h>
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Common/Snapshot.h"
#include <vector>

// A 19-word model-condition mask; the zeroing constructor is the mask
// form, the bare words are what the set lookup fills in place.
struct BannerMorphConditionBits
{
	int m_bits[19];
};

struct BannerMorphConditionMask : public BannerMorphConditionBits
{
	BannerMorphConditionMask() throw() { memset(m_bits, 0, sizeof(m_bits)); }
	void set(unsigned int bit) { m_bits[bit >> 5] |= 1 << (bit & 0x1F); }
};

class Object;

class Player;

class Module;

class UpgradeTemplate;

class Gen_0028EF10;

class BannerContain;

struct ObjectInner04;

struct BfmeMorphCondition;

struct BfmeExpLevelDraw;

enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };

enum KindOfType { KINDOF_DUMMY=0 };

enum ObjectStatusTypes { STATUS_DUMMY=0 };

enum NameKeyType
{
	NK_UNKNOWN = 0
};

template<int N> class BannerSlots : public BannerSlots<N-1> { public: virtual void gap(char (*)[N])=0; };

template<> class BannerSlots<0> {};

class AIUpdateInterface : public BannerSlots<142> { public:
 virtual void chooseLocomotorSet(int set); // slot 142, 0x238
 bool isMoving() const;
 char pad04[0x3B1-4]; bool pending; // +0x3B1
};

class Object { public:
 bool isKindOf(KindOfType) const;
 bool testStatus(ObjectStatusTypes) const; // 0x0004E536
 bool hasUpgrade(const UpgradeTemplate *) const;
 Object *rva002931F5(bool);
 int rva0028AF76() const;
 Player *getControllingPlayer() const; // 0x0028AFA9
 void *rva0028C197() const; // 0x0028C197
 void rva0028CFB2(const int *clearFlags, const int *setFlags);
 void updateShroudNow(); // 0x0028C11A
 const Coord3D *getPosition() const { return &m_position; }
 AIUpdateInterface *getAI() const { return m_ai; }
 char pad00[4]; ObjectInner04 *m_04; // +0x04
 char matrix[0x30]; // +0x08
 Coord3D m_position; // +0x38
 char pad44[0x24C-0x44]; Gen_0028EF10 *m_stats; BannerContain *m_contain; // +0x24C, +0x250
 char pad254[4]; AIUpdateInterface *m_ai; // +0x258
 char pad25C[0x274-0x25C]; Object *m_containedBy; // +0x274
protected:
 Module *findModule(NameKeyType key) const;
};

class FXList
{
public:
	static void doFXObj(const FXList *,const Object *,const Object *); // 0x000B2235
};

// The module data's set lookup (rowed under this receiver spelling).
struct Rva00496D43Elem;
class Rva00496D43
{
public:
	void *rva00496D43(void *out, const AsciiString &key);
	char m_pad00[0x18];
private:
	Rva00496D43Elem **m_begin18; // +0x18
	Rva00496D43Elem **m_end1C; // +0x1C
};

class FXList;

// Field identity is retail's own INI table at 0x00C4F9E8; the +0x18/+0x24 element
// classes keep the names the ledger's vector destructor rows carry.
class BannerCarrierUpdateModuleData : public Snapshot
{
public:
	BannerCarrierUpdateModuleData();
	virtual ~BannerCarrierUpdateModuleData();
	AsciiString rva00496DA3(const AsciiString &name) const;
	const FXList *getFX() const { return m_bannerMorphFX; }
	int m_unused04; // +0x04
	unsigned m_idleSpawnRate; // +0x08
	unsigned m_meleeFreeUnitSpawnTime; // +0x0C
	int m_diedRespawnTime; // +0x10
	int m_meleeFreeBannerReSpawnTime; // +0x14
	_STL::vector<BfmeMorphCondition *> m_morphConditions; // +0x18
	_STL::vector<BfmeExpLevelDraw *> m_expLevelDraws; // +0x24
	const FXList *m_bannerMorphFX; // +0x30
	const FXList *m_unitSpawnFX; // +0x34
	bool m_replenishNearbyHorde; // +0x38
	bool m_replenishAllNearbyHordes; // +0x39
	unsigned char m_pad3A[2]; // +0x3A
	float m_scanHordeDistance; // +0x3C
	AsciiString m_upgradeRequired; // +0x40
};

extern "C" int rva002bcab_scanIndex(const char *token, const char *const *nameList, bool *found, bool doThrow) throw();
extern const char *TheLocomotorSetNames[];

class BannerBase { public: virtual void slot0();
 Object *getObject() const { return object; }
 const BannerCarrierUpdateModuleData *data; Object *object;
};

class BannerOther { public: virtual void slot0(); };

class UpdateModuleInterface { public: virtual UpdateSleepTime update()=0; };

class BannerCarrierUpdate : public BannerBase, public BannerOther, public UpdateModuleInterface {
public:
 virtual UpdateSleepTime update();
 void rva004973CF(); bool rva00496BD2(Object *); void rva00496E05(void *entry, bool playFX);
public:
	virtual NameKeyType getModuleNameKey() const;
};

static const unsigned int s_morphConditions[81] =
{
	214, 194, 195, 196, 197, 198, 184, 185, 186, 187, 188, 458,
	459, 460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470,
	471, 472, 473, 474, 475, 476, 477, 478, 479, 480, 481, 482,
	483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494,
	495, 496, 497, 498, 499, 500, 501, 502, 503, 504, 505, 506,
	507, 508, 509, 510, 511, 512, 513, 514, 515, 516, 517, 518,
	519, 520, 521, 522, 523, 524, 525, 526, 527
};

// ?rva00496E05@BannerCarrierUpdate@@QAEXPAX_N@Z @0x00496E05
void BannerCarrierUpdate::rva00496E05(void *entry, bool playFX)
{
	Object *obj = object;
	const BannerCarrierUpdateModuleData *bannerCarrierUpdateModuleData = data;
	const AsciiString &name = *(const AsciiString *)((char *)entry + 0x64);

	BannerMorphConditionBits setFlags;
	((Rva00496D43 *)bannerCarrierUpdateModuleData)->rva00496D43(&setFlags, name);

	static BannerMorphConditionMask s_clearFlags;
	static bool s_clearFlagsBuilt = false;
	if (!s_clearFlagsBuilt)
	{
		s_clearFlagsBuilt = true;
		for (unsigned int i = 0; i < sizeof(s_morphConditions) / sizeof(s_morphConditions[0]); ++i)
			s_clearFlags.set(s_morphConditions[i]);
	}
	obj->rva0028CFB2(s_clearFlags.m_bits, setFlags.m_bits);

	if (obj->getPosition()->GetLength() > 0.0f)
		obj->updateShroudNow();

	if (bannerCarrierUpdateModuleData->getFX() && playFX)
		FXList::doFXObj(bannerCarrierUpdateModuleData->getFX(), obj, 0);

	AsciiString locomotor = bannerCarrierUpdateModuleData->rva00496DA3(name);
	if (!locomotor.isEmpty())
	{
		bool found = false;
		int set = rva002bcab_scanIndex(locomotor.str(), TheLocomotorSetNames, &found, true);
		obj->getAI()->chooseLocomotorSet(set);
	}
}
