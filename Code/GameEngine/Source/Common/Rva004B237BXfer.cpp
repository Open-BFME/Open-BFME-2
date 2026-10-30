// cl: /MD
// ?rva004B23C5@EntEnragedUpdate@@UAEXPAVXfer@@@Z, retail 0x004B23C5, 147 bytes.
// Virtual slot 3 (offset 0xC) of vtable 0x00856948 (VA 0x00C56948), class of
// ??1EntEnragedUpdate@@UAE@XZ (was Rva004B237B) in Rva0024A797Derived.cpp. UpdateModule xfer via
// rowed 0x0044DF9F with Version(1,1) via Xfer slot 0x28 then uint fields at
// +0x20/+0x24/+0x28 via slot 0x78 and bool fields at +0x2C/+0x2D/+0x2E/+0x2F/
// +0x30 via slot 0x90. Xfer spelling copied from FoundationAIUpdateXfer.cpp.

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

#include "../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };

enum NameKeyType { NK_UNKNOWN = 0 };

class Thing;
class Object;
class ModuleData;
class BodyModuleInterface;
class Xfer;

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual BodyModuleInterface *getBody() { return 0; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public PB_DeepBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	// Defined once, out of line, in UpdateModuleCtor.cpp (retail 0x00253390): derived
	// ctors call it, and a copy here would offer the link a second, non-retail body.
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	// The module's vptr (its own slots are not modelled here; xfer stays the
	// plain member the derived body calls qualified).
	void xfer(Xfer *xfer);

private:
	unsigned int m_field14;
	int m_field18;
	int m_field1C;
};

class EntEnragedUpdate : public UpdateModule
{
public:
	EntEnragedUpdate(Thing *, const ModuleData *);
	virtual ~EntEnragedUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual void rva004B23C5(Xfer *xfer); // slot 3 of 0x00C56948
	// Rowed in EntEnragedUpdateUpdate.cpp: slot 0 of retail's UpdateModuleInterface table 0x00C5693C.
	virtual UpdateSleepTime update();
	bool rva004B25C9();
	bool rva004B266D();

private:
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	bool m_2C;
	bool m_2D;
	bool m_2E;
	bool m_2F;
	bool m_30;
};

void EntEnragedUpdate::rva004B23C5( Xfer *xfer )
{
	Xfer::Version version( 1, 1 );
	*xfer == version;
	UpdateModule::xfer( xfer );
	*xfer == m_20;
	*xfer == m_2C;
	*xfer == m_24;
	*xfer == m_2F;
	*xfer == m_2D;
	*xfer == m_30;
	*xfer == m_28;
	*xfer == m_2E;
}
