// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// Retail 0x004568EC, 338B; this six-argument thiscall returns with ret 0x18.
// The ZH member declaration and body establish BridgeBehavior::setScaffoldData;
// the BFME 1 port is at
// reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorCreateScaffoldingThunk.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db).
// Retail directly reads this+4 for module data, with lateral/vertical speeds
// at data+8/+0xC. Its absolute float read at VA 0x00BC2A10 is 8.0f
// (RVA 0x007C2A10; retail bytes 00 00 00 41). Coord3D::length and all direct
// callees below are independently rowed; the minimal views preserve only the
// offsets and virtual slots witnessed by this body.

typedef float Real;
extern const Real g_00BC2A10;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	Real length() const;
};

class Thing
{
public:
	void *m_vtable;
	void setPosition(const Coord3D *position);
	void setOrientation(Real angle);
};

class Object : public Thing
{
};

class BridgeScaffoldBehaviorInterface
{
public:
	virtual void setPositions(const Coord3D *sunkenPosition,
		const Coord3D *risePosition, const Coord3D *buildPosition);
	virtual void setMotion(int motion);
	virtual int getCurrentMotion() const;
	virtual void reverseMotion();
	virtual void setLateralSpeed(Real speed);
	virtual void setVerticalSpeed(Real speed);
};

class BridgeScaffoldBehavior
{
public:
	static BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterfaceFromObject(Object *object);
};

struct BridgeBehaviorModuleData
{
	unsigned char m_unmodelled00[8];
	Real m_lateralScaffoldSpeed;
	Real m_verticalScaffoldSpeed;
};

class BridgeBehavior
{
public:
	void *m_vtable;
	BridgeBehaviorModuleData *m_moduleData;

protected:
	void setScaffoldData(Object *object, Real *angle, Real *sunkenHeight,
		const Coord3D *risePosition, const Coord3D *buildPosition,
		const Coord3D *bridgeCenter);
};

void BridgeBehavior::setScaffoldData(Object *object, Real *angle,
	Real *sunkenHeight, const Coord3D *risePosition,
	const Coord3D *buildPosition, const Coord3D *bridgeCenter)
{
	if (!object)
		return;
	if (!angle)
		return;
	if (!risePosition)
		return;
	if (!buildPosition)
		return;

	BridgeBehaviorModuleData *moduleData = m_moduleData;
	BridgeScaffoldBehaviorInterface *scaffold =
		BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(object);
	Coord3D sunkenPosition;
	sunkenPosition.x = risePosition->x;
	sunkenPosition.y = risePosition->y;
	sunkenPosition.z = risePosition->z - *sunkenHeight - g_00BC2A10;
	object->setPosition(&sunkenPosition);
	scaffold->setPositions(&sunkenPosition, risePosition, buildPosition);
	scaffold->setMotion(1);
	((Thing *)object)->setOrientation(*angle);

	Real lateralSpeed = moduleData->m_lateralScaffoldSpeed;
	Coord3D buildToCenter;
	buildToCenter.x = buildPosition->x - risePosition->x;
	buildToCenter.y = buildPosition->y - risePosition->y;
	buildToCenter.z = buildPosition->z - risePosition->z;
	Coord3D riseToCenter;
	riseToCenter.x = bridgeCenter->x - risePosition->x;
	riseToCenter.y = bridgeCenter->y - risePosition->y;
	riseToCenter.z = bridgeCenter->z - risePosition->z;
	Real buildDistance = buildToCenter.length();
	Real riseDistance = riseToCenter.length();
	scaffold->setLateralSpeed(lateralSpeed * (buildDistance / riseDistance));
	Real verticalSpeed = moduleData->m_verticalScaffoldSpeed;
	scaffold->setVerticalSpeed(verticalSpeed);
}
