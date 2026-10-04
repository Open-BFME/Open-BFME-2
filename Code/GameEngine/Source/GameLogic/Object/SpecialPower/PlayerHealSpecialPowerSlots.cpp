// cl: /O1 /MD /GX /arch:SSE
//
// PlayerHealSpecialPower's three doSpecialPower overrides: slots 10, 11 and
// 12 of the class's +0x10 special-power interface vftable 0x00C5E308, so
// `this` is that subobject (the Object at -0x08). Each runs the
// SpecialPowerModule base first, Zero Hour style, then hands a location to
// the class's own helper 0x004C8095 on the primary this (pinned by address
// on these three call sites): the power's own position for doSpecialPower
// (0x004C8198, 31 bytes), the target Object's position for
// doSpecialPowerAtObject (0x004C8175, 35 bytes) and the given location for
// doSpecialPowerAtLocation (0x004C8155, 32 bytes).
// The base doSpecialPower 0x0049490F is the Zero Hour body (script-fired
// commands skip the paused and disabled tests), pinned on that evidence.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;		// +0x38
};

class ModuleData;
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
	virtual void doSpecialPower(unsigned int options) = 0;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options) = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options) = 0;
};

class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPower(unsigned int options);					// 0x0049490F
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);		// 0x0049495B
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
};

class PlayerHealSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(unsigned int options);
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C8095(const Coord3D *loc);
};

void PlayerHealSpecialPower::doSpecialPower(unsigned int options)
{
	SpecialPowerModule::doSpecialPower(options);
	rva004C8095(m_object->getPosition());
}

void PlayerHealSpecialPower::doSpecialPowerAtObject(Object *obj, unsigned int options)
{
	SpecialPowerModule::doSpecialPowerAtObject(obj, options);
	rva004C8095(obj->getPosition());
}

void PlayerHealSpecialPower::doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options)
{
	SpecialPowerModule::doSpecialPowerAtLocation(loc, options);
	rva004C8095(loc);
}
