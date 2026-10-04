// cl: /O1 /MD /GX /arch:SSE
//
// InvisibilitySpecialPower::doSpecialPowerAtObject, retail 0x004C2419, 52
// bytes: slot 11 of the same interface; after the base (0x0049495B) the
// power's own object goes to TheGameLogic's +0x178 object (0x00439CF7).
//
// InvisibilitySpecialPower::doSpecialPowerAtLocation, retail 0x004C2517,
// 271 bytes: slot 12 of the class's +0x10 special-power interface vftable
// (0x00C5C4B8, stored by the ctor 0x004C23A4), so `this` is that subobject
// (module data and object at -0x0C/-0x08). The name follows the role:
// Zero Hour's overrides call SpecialPowerModule::doSpecialPowerAtLocation
// first, as this does (0x004949D8, BFME2's two-argument form). Then every
// object within the module data's +0x134 radius of the location that
// passes the 0x002614DF filter, is alive, shares the object's map status
// and passes the 0x002614EC filter (module data +0x138, the object's
// player) is handed to TheGameLogic's +0x178 object (0x00439CF7, with
// module data +0x13C and &+0x7C), near to far.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1), the ctors being inline.
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

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead (status bit 0),
// ZH's PartitionFilterAlive.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C07190, allow 0x002614DF.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
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

struct Coord3D
{
	float x;
	float y;
	float z;
};

class ModuleData;

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
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

struct InvisibilitySpecialPowerModuleData
{
	char m_pad000[0x7C];
	char m_7C[4];			// +0x7C
	char m_pad080[0x134 - 0x80];
	float m_radius;			// +0x134
	char m_138[4];			// +0x138
	int m_13C;			// +0x13C
};

class Rva00439CF7
{
public:
	void rva00439CF7(Object *obj, int value, const void *what);	// 0x00439CF7
};

class GameLogic
{
public:
	Rva00439CF7 *rva00439CF7Owner() { return m_178; }
	char m_pad000[0x178];
	Rva00439CF7 *m_178;		// +0x178
};
extern GameLogic *TheGameLogic;

class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

// The +0x10 interface (vftable 0x00C5C4B8 in this class): slot 12 places the
// power at a location.
class SpecialPowerModuleInterface
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
	virtual void s0A() = 0;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options) = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options) = 0;
};

class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);		// 0x0049495B
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
};

class InvisibilitySpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	const InvisibilitySpecialPowerModuleData *getData() const
	{
		return (const InvisibilitySpecialPowerModuleData *)m_moduleData;
	}
};

void InvisibilitySpecialPower::doSpecialPowerAtObject(Object *obj, unsigned int options)
{
	SpecialPowerModule::doSpecialPowerAtObject(obj, options);
	const InvisibilitySpecialPowerModuleData *data = getData();
	TheGameLogic->rva00439CF7Owner()->rva00439CF7(m_object, data->m_13C, data->m_7C);
}

void InvisibilitySpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	const InvisibilitySpecialPowerModuleData *data = getData();
	Object *obj = m_object;
	Rva002614DFFilter first(obj);
	Rva0026119DFilter alive;
	Rva002611BFFilter mapStatus(obj);
	Rva002614ECFilter owned(data->m_138, obj->getControllingPlayer(), true);
	first.link(&alive);
	first.link(&mapStatus);
	first.link(&owned);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(loc, data->m_radius, 0, &first, 1);
	Object *target;
	while ((target = hits.next()) != 0)
		TheGameLogic->rva00439CF7Owner()->rva00439CF7(target, data->m_13C, data->m_7C);
}
