// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// LevelGrantSpecialPower (vftable 0x0085C920, deleting dtor 0x004C2C5A) helpers
// and slot 17 (0x004C2D9D): it scans the objects within the module data's
// +0xCC radius of +0x44 over the partition filter chain and hands each hit to
// 0x004C2D2B with a vector of IDs already granted:
//
//   0x004C2B57  the per-object grant: through the source's slot 48 when one is
//               given, else the object's experience tracker (+0x264) when
//               0x0039AE04 allows, 0x0039B315 (amount, true, true, true, 0);
//               then FXList::doFXObj of the module data's +0xD4 on the object
//   0x004C2C7B  grant the module data's +0xC8 amount to an object: one whose
//               template has +0x114 bit 13 splits it over the 0x0029439D
//               result's slot-96 count and grants each contained object
//               (+0x250 slot 68 with 0x004C2B57); any other gets it all
//   0x004C2D2B  prefer the object 0x00049DC5 finds for +0x78 when its template
//               has bit 13; such an object is granted once per ID (+0x74)
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

enum ObjectID
{
	INVALID_ID = 0
};

// This TU's vector<ObjectID> frees through the game allocator wrapper at 0x30830.
void Rva00030830FreeAllocation(void *);
#pragma comment(linker, "/alternatename:?Rva00030830FreeAllocation@@YAXPAX@Z=_free")
namespace _STL {
template <> inline void allocator<ObjectID>::deallocate(pointer p, size_type) const
{
	if (p)
		::Rva00030830FreeAllocation(p);
}
}

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

class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

class ThingTemplate
{
public:
	char m_pad000[0x114];
	unsigned m_114;		// +0x114 (bit 13 tested)
};

// What 0x0029439D returns: slot 96 counts.
class Rva0029439DResult
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void rvaSlot48(Object *obj, float amount);	// vftable +0xC0
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual unsigned rvaSlot96(int arg);	// vftable +0x180
};

typedef void (*ContainIterateFunc)(Object *obj, void *userData);

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void rvaSlot68(ContainIterateFunc func, void *userData, bool reverse);	// vftable +0x110
};

// The tracker at Object +0x264 (its neighbours include ExperienceTracker's
// xfer 0x0039AFC8).
class ExperienceTracker
{
public:
	bool rva0039AE04() const;	// 0x0039AE04
	void rva0039B315(float amount, bool a, bool b, bool c, bool d);	// 0x0039B315
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
};

class Object
{
public:
	void *rva0029439D();	// 0x0029439D
	Player *getControllingPlayer() const;	// 0x0028AFA9
	unsigned rva004C2D2BBit13() const { return m_template->m_114 & 0x2000; }
	ObjectID getID() const { return m_74; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x74 - 0x08];
	ObjectID m_74;		// +0x74 the ID collected
	ObjectID m_78;		// +0x78 the ID looked up first
	char m_pad07C[0x250 - 0x7C];
	ContainModuleInterface *m_250;	// +0x250
	char m_pad254[0x264 - 0x254];
	ExperienceTracker *m_264;	// +0x264
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

class LevelGrantSpecialPowerModuleData
{
public:
	char m_pad00[0xC8];
	int m_C8;		// +0xC8 the amount
	float m_CC;		// +0xCC the radius
	char m_D0[4];		// +0xD0
	const FXList *m_D4;	// +0xD4
};

class SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();	// slot 17 (0x0045108D)
protected:
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class LevelGrantSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();
	void rva004C2C7B(Object *obj);
	void rva004C2D2B(Object *obj, std::vector<ObjectID> &seen);
private:
	const LevelGrantSpecialPowerModuleData *getLevelGrantSpecialPowerModuleData() const
	{
		return (const LevelGrantSpecialPowerModuleData *)m_moduleData;
	}
	char m_pad0C[0x44 - 0x0C];
	Coord3D m_44;		// +0x44
};

template <class T>
__forceinline T *rva004C2D9DAddress(const T &object)
{
	return (T *)&object;
}

// What 0x004C2B57 is handed for each object.
struct Rva004C2B57Args
{
	float m_amount;
	const FXList *m_D4;
	Rva0029439DResult *m_source;
};

void rva004C2B57(Object *obj, void *userData)
{
	Rva004C2B57Args *args = (Rva004C2B57Args *)userData;
	if (args->m_source) {
		args->m_source->rvaSlot48(obj, args->m_amount);
	} else {
		ExperienceTracker *tracker = obj->m_264;
		if (!tracker || !tracker->rva0039AE04())
			return;
		tracker->rva0039B315(args->m_amount, true, true, true, false);
	}
	if (args->m_D4)
		FXList::doFXObj(args->m_D4, obj, 0);
}

void LevelGrantSpecialPower::rva004C2C7B(Object *obj)
{
	const LevelGrantSpecialPowerModuleData *data = getLevelGrantSpecialPowerModuleData();
	if (data->m_C8 <= 0)
		return;
	if (obj->rva004C2D2BBit13()) {
		Rva0029439DResult *source = (Rva0029439DResult *)obj->rva0029439D();
		unsigned count = source ? source->rvaSlot96(0) : 0;
		if (count) {
			Rva004C2B57Args args;
			args.m_amount = (float)data->m_C8 / (float)count;
			args.m_D4 = data->m_D4;
			args.m_source = source;
			obj->m_250->rvaSlot68(rva004C2B57, &args, true);
		}
	} else {
		Rva004C2B57Args args;
		args.m_source = 0;
		args.m_amount = (float)data->m_C8;
		args.m_D4 = data->m_D4;
		rva004C2B57(obj, &args);
	}
}

void LevelGrantSpecialPower::rva004C2D2B(Object *obj, std::vector<ObjectID> &seen)
{
	Object *other = TheGameLogic->findObjectByID(obj->m_78);
	if (other && other->rva004C2D2BBit13())
		obj = other;
	if (obj->rva004C2D2BBit13()) {
		for (std::vector<ObjectID>::iterator it = seen.begin(); it != seen.end(); ++it) {
			if (*it == obj->getID())
				return;
		}
		seen.push_back(obj->getID());
	}
	rva004C2C7B(obj);
}

void LevelGrantSpecialPower::rva0045108D()
{
	SpecialAbilityUpdate::triggerAbilityEffect();
	Object *obj = m_object;
	const LevelGrantSpecialPowerModuleData *data = getLevelGrantSpecialPowerModuleData();
	std::vector<ObjectID> seen;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(
		&m_44, data->m_CC, 0,
		Rva002614DFFilter(obj).link(rva004C2D9DAddress(Rva00260EB1Filter(obj, 4, false)))
			->link(rva004C2D9DAddress(Rva0026119DFilter()))
			->link(rva004C2D9DAddress(Rva002611BFFilter(obj)))
			->link(rva004C2D9DAddress(Rva002614ECFilter(data->m_D0, obj->getControllingPlayer(), true))), 1);
	Object *other;
	while ((other = hits.next()) != 0)
		rva004C2D2B(other, seen);
}
