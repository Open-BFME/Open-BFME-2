// cl: /DBFME_ASCII_DTOR_DECL /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/update_modules_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfmefrustum
// stlport
#include "../../../Common/RTS/XYDistanceCallView.h"
//
// ?update@LargeGroupBonusUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail
// 0x00490225, 589 bytes: slot 0 of the UpdateModuleInterface vtable
// 0x00C4D058 that the matched ctor 0x004900B1 installs at +0x10, so the
// override runs with the +0x10 subobject this. Layout is the 0x2C-byte class
// of LargeGroupBonusUpdateCtor.cpp / LargeGroupBonusUpdateXfer.cpp.
//
// Every module-data delay (+0x08) frames, or every frame for the object
// kinds whose template bits +0x109 bit 0/1 are set: count the horde members
// within the +0x14 radius (the HordeMemberFilter-led field +0x0C, BFME2's
// partition filter chain: that filter, same controlling player, alive, not
// this object), and turn the bonus on when the count reaches +0x10 - 1, or
// otherwise when a hit whose behavior interface (slot 0x74) answers slot 2
// lies within the +0x1C distance. A change applies or removes the attribute
// modifier named at +0x2C (Object::addAttributeModifierToPool /
// Object::removeAttributeModifierFromPool).

#include "ascii_string.h"
#include <vector>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

class Thing;
class ModuleData;
class Object;
class Player;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

template <int N> class Rva00490225Slots : public Rva00490225Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00490225Slots<0>
{
};

// The +0x0C field of the module data (the HordeMemberFilter entry).
struct Rva00490225MemberFilter
{
	void *m_00;
};

// The interface Object::rva0028C197 returns: slot 0x60 counts the members
// the given filter accepts.
class Rva00490225Contain : public Rva00490225Slots<96>
{
public:
	virtual UnsignedInt countMembers(const Rva00490225MemberFilter *filter) = 0;
};

// What a behavior module's slot 0x74 hands back: slot 2 says whether it
// counts toward the bonus.
class Rva00490225Member
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual Bool isActive() = 0;
};

class Rva00490225BehaviorIface : public Rva00490225Slots<29>
{
public:
	virtual Rva00490225Member *getMember() = 0;
};

enum NameKeyType { NK_UNKNOWN = 0 };
// ObjectModule stores m_moduleData at +0x04 and m_object at +0x08.
#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModule : public ObjectModule, public Rva00490225BehaviorIface
{
};

struct ObjectKindBytes
{
	// The KindOf mask. Retail tests +0x109 bit 0 and bit 1 with two
	// separate byte tests; read at one width, cl 7.1 folds the pair into a
	// single test al,3, so the second bit is read off the dword.
	unsigned char m_pad000[0x108];
	union {
		unsigned char m_bytes[28];
		unsigned int m_words[7];
	};
};

class Drawable {
public:
 void rva002724FD(const AsciiString &, int, int, float, float);
 void updateSubObjects();
};
class Object
{
public:
 Drawable *getDrawable() const;
	Player *getControllingPlayer() const;				// 0x0028AFA9
	void *rva0028C197() const;				// 0x0028C197
	Bool addAttributeModifierToPool(const AsciiString &name, int duration);
	void removeAttributeModifierFromPool(const AsciiString &name);
	const Coord3D *getPosition() const { return &m_pos; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	Bool isKindOf109Bit0() const { return (m_template->m_bytes[1] & 1) != 0; }
	unsigned int isKindOf109Bit1() const { return m_template->m_words[0] & 0x200; }
	__forceinline Rva00490225Member *findMember() const
	{
		for (BehaviorModule **behaviorModule = getBehaviorModules(); *behaviorModule; ++behaviorModule) {
			Rva00490225Member *member = (*behaviorModule)->getMember();
			if (member)
				return member;
		}
		return 0;
	}
	const ObjectKindBytes *m_template;	// +0x04 (after the vptr)
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_pos;				// +0x38
	unsigned char m_pad044[0x244 - 0x44];
	BehaviorModule **m_behaviors;		// +0x244
	unsigned char m_pad248[0x438 - 0x248];
	unsigned char m_438;			// +0x438
private:
	virtual void anchor();
};

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


// vftable 0x00C4D040, allow 0x00260F9E: the member filter at +0x08 and
// whether a counted hit allows.
class Rva00260F9EFilter : public Rva000421C8
{
public:
	Rva00260F9EFilter(const Rva00490225MemberFilter *filter, bool match)
		: m_filter(filter), m_match(match) {}
	virtual bool allow(Object *obj);
	const Rva00490225MemberFilter *m_filter;
	bool m_match;
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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF: not the given object.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

struct Rva00490225HitEntry
{
	Object *m_object;
	unsigned m_distanceBits;
};

struct Rva00490225HitList
{
	Rva00490225HitEntry *m_begin;	// +0x00
	Rva00490225HitEntry *m_end;	// +0x04
	void *m_08;
	Rva00490225HitEntry *m_cursor;	// +0x0C
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void reset() { m_value->m_cursor = m_value->m_begin; }
	Rva00490225HitList *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	Rva00490225MemberFilter m_data;
};
struct __declspec(novtable) LargeGroupBonusUpdateModuleData : public Snapshot
{
	friend class LargeGroupBonusUpdate;
public:
	virtual ~LargeGroupBonusUpdateModuleData();

private:
	int m_unused04; // +4
	int m_updateRate; // +8
	Rva00360D26Member m_hordeMemberFilter; // +0xC
	int m_count; // +0x10
	float m_radius; // +0x14
	bool m_alliesOnly; // +0x18
	float m_rubOffRadius; // +0x1C
	_STL::vector<AsciiString> m_flagSubObjectNames; // +0x20
	AsciiString m_attributeModifier; // +0x2C
};
class BehaviorModuleInterface { public: virtual void behaviorSlot(); };

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class LargeGroupBonusTrailing { public: virtual void trailingSlot(); };

class LargeGroupBonusUpdate : public UpdateModule, public LargeGroupBonusTrailing
{
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	void notify(int value);
	void rva004901B5();

protected:
	virtual void xfer(Xfer *xfer);

private:
	const LargeGroupBonusUpdateModuleData *getLargeGroupBonusUpdateModuleData() const
	{
		return (const LargeGroupBonusUpdateModuleData *)m_moduleData;
	}
	unsigned int m_24; // +0x24
	bool m_28; // +0x28
	bool m_29; // +0x29
	bool m_2A;
};

UpdateSleepTime LargeGroupBonusUpdate::update()
{
	Object *obj = m_object;
	if (!obj)
		return UPDATE_SLEEP_FOREVER;

	Bool wasActive = m_28;
	const LargeGroupBonusUpdateModuleData *data = getLargeGroupBonusUpdateModuleData();
	Bool everyFrame = obj->isKindOf109Bit0() || obj->isKindOf109Bit1();
	if (everyFrame || TheGameLogic->getFrame() > m_24 + data->m_updateRate) {
		m_24 = TheGameLogic->getFrame();
		Rva00260F9EFilter filterMember(reinterpret_cast<const Rva00490225MemberFilter *>(&data->m_hordeMemberFilter), true);
		Rva00260E2AFilter filterPlayer(obj->getControllingPlayer());
		Rva0026119DFilter filterAlive;
		Rva002611BFFilter filterNotThis(obj);
		BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(obj->getPosition(), data->m_radius, 3,
			filterMember.link(filterPlayer.link(filterAlive.link(&filterNotThis))), 0);
		UnsignedInt count = 0;
		Object *other;
		while ((other = hits.next()) != 0) {
			Rva00490225Contain *contain = (Rva00490225Contain *)other->rva0028C197();
			if (contain)
				count += contain->countMembers(reinterpret_cast<const Rva00490225MemberFilter *>(&data->m_hordeMemberFilter));
		}
		hits.reset();
		if (count >= data->m_count - 1) {
			m_29 = true;
			m_28 = true;
		} else {
			m_28 = false;
			m_29 = false;
			Real nearSqr = data->m_rubOffRadius * data->m_rubOffRadius;
			while ((other = hits.next()) != 0) {
				Rva00490225Member *member = other->findMember();
				if (member && member->isActive()) {
					Real distSqr = reinterpret_cast<Rva000CBA20 *>(m_object)->distSq(reinterpret_cast<const Rva000CBA20Point *>(other->getPosition()));
					if (distSqr <= nearSqr) {
						m_28 = true;
						break;
					}
				}
			}
		}
		if (wasActive != m_28) {
			if (m_28)
				obj->addAttributeModifierToPool(data->m_attributeModifier, 0);
			else
				obj->removeAttributeModifierFromPool(data->m_attributeModifier);
		}
	}
	if (obj->m_438 & 1)
		return UPDATE_SLEEP_FOREVER;
	obj->rva0028C197();
	return everyFrame ? (UpdateSleepTime)data->m_updateRate : UPDATE_SLEEP_NONE;
}

// BF1 f98983a7 LargeGroupBonusUpdateNotify.cpp supplies the loop purpose;
// native49015C and WB11DC2A0 independently establish the BFME2 Drawable
// getter and two scalar-zero float arguments.
void LargeGroupBonusUpdate::notify(int value)
{
 const LargeGroupBonusUpdateModuleData *data = getLargeGroupBonusUpdateModuleData();
 if (data->m_flagSubObjectNames.empty()) return;
 Drawable *drawable = m_object->getDrawable();
 if (!drawable || !m_object) return;
 for (_STL::vector<AsciiString>::const_iterator it = data->m_flagSubObjectNames.begin(); it != data->m_flagSubObjectNames.end(); ++it)
  drawable->rva002724FD(*it, value, 0, 0.0f, 0.0f);
 drawable->updateSubObjects();
}

// ?rva004901B5@LargeGroupBonusUpdate@@QAEXXZ @0x004901B5 8B, right after
// notify: slot 6 of the Rva0024A797_Root table 0x0084D124 of Rva0048FFB4,
// whose scalar deleting destructor 0x00490140 sits just before notify. It is
// notify(0). Address-named.
void LargeGroupBonusUpdate::rva004901B5()
{
 notify(0);
}
