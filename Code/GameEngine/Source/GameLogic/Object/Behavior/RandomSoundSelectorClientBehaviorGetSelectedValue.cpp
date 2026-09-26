// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?getSelectedValue@RandomSoundSelectorClientBehavior@@UAE_NPAI@Z, retail 0x004CBD44, 56 bytes.
// Secondary interface method (secondary this +0x0C; reroll via primary -0x0C,
// moduleData via -8, m_randomSelection via +4): reroll via rowed 0x004CBCF2,
// then chance at +0x1D4 via comiss, then selectedValue at +0x1D8 plus
// selectedFlag at +0x1DC. Layout is the rowed 0x18-byte class (same as the
// Xfer TU: ObjectModule 0x0C plus secondary vptr at +0x0C giving +0x10 start);
// donor is BFME1 RandomSoundSelectorClientBehavior::getSelectedValue which
// reroll plus chance/selectedValue/selectedFlag proves.

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

struct RandomSoundSelectorClientBehaviorModuleDataView
{
	char m_pad[0x1D4];
	float m_chance;
	unsigned int m_selectedValue;
	bool m_selectedFlag;
};

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class SoundSelectorSecondary
{
public:
	virtual bool getSelectedValue(unsigned int *value);
};

class RandomSoundSelectorClientBehavior : public ObjectModule, public SoundSelectorSecondary
{
public:
	RandomSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);
	virtual bool getSelectedValue(unsigned int *value);

private:
	void reroll();

	float m_randomSelection;
	unsigned int m_lastFrame;
};

bool RandomSoundSelectorClientBehavior::getSelectedValue(unsigned int *value)
{
	RandomSoundSelectorClientBehaviorModuleDataView *moduleData =
		(RandomSoundSelectorClientBehaviorModuleDataView *)m_moduleData;
	reroll();
	if (m_randomSelection >= moduleData->m_chance)
		return false;
	*value = moduleData->m_selectedValue;
	return moduleData->m_selectedFlag;
}
