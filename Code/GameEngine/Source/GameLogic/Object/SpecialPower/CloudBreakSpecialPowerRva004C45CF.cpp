// cl: /MD
// ?Rva004C45CFCreate@@YGXPBUCoord3D@@PBVAsciiString@@@Z @0x004C45CF 82B: free stdcall helper creating object from template name and placing at pos. Evidence: rowed rva002D06CA plus pinned newObject plus rowed setPosition plus g_009FF000 plus caller 0x004C4621 plus neighbours 0x004C4582 0x004C479A.
class AsciiString;
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class ThingTemplate;
enum ObjectID; extern class ThingFactory *TheThingFactory;
// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)
class ThingTemplate;
class Team;
struct CreateMask
{
public:
	unsigned int m_words[4]; // +0x00
};
class Object;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &name); Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, ObjectID flag); };
#include "../../../Common/Thing/thing.h"
void __stdcall Rva004C45CFCreate(const Coord3D *pos, const AsciiString *name)
{
    void *tmpl = (void *)TheThingFactory->findTemplate(*name);
    if (tmpl == 0)
        return;
    CreateMask mask;
    memset(&mask, 0, 0x10);
    Object *obj = TheThingFactory->newObject((const ThingTemplate *)tmpl, 0, &mask, (ObjectID)0);
    if (obj == 0)
        return;
    ((Thing *)obj)->setPosition(pos);
}

class ModuleData;
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
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
	virtual void doSpecialPowerUsingWaypoints(void *target, float angle, int commandOptions) = 0;
};

class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

	// Public: the rowed dtor at 0x00493DEF is ??1SpecialPowerModule@@UAE@XZ.
	virtual ~SpecialPowerModule();
	virtual void doSpecialPower(unsigned int options);	// 0x0049490F
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);	// 0x0049495B
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
	virtual void pauseCountdown(bool pause);	// 0x00492FC2
protected:
	unsigned char m_pad14[0x34 - 0x14];
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class CloudBreakSpecialPower : public SpecialPowerModule
{
public:
	CloudBreakSpecialPower( Thing *thing, const ModuleData *moduleData );
	virtual NameKeyType getModuleNameKey() const;

	// Rowed helpers: they stay out of line under this unit's /Ob2.
	__declspec(noinline) void rva004C4582();

	void rva004C4621(const Coord3D *position);
	__declspec(noinline) void rva004C45CF(const Coord3D *position, const AsciiString *name);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);

protected:
	virtual ~CloudBreakSpecialPower();
};

// ICF-folded twin of Rva004C45CFCreate above (same 82 bytes at 0x004C45CF):
// the member spelling ignores its receiver, so its stack frame matches the
// stdcall spelling exactly, including the callee-cleaned return.
void CloudBreakSpecialPower::rva004C45CF(const Coord3D *pos, const AsciiString *name)
{
    void *tmpl = (void *)TheThingFactory->findTemplate(*name);
    if (tmpl == 0)
        return;
    CreateMask mask;
    memset(&mask, 0, 0x10);
    Object *obj = TheThingFactory->newObject((const ThingTemplate *)tmpl, 0, &mask, (ObjectID)0);
    if (obj == 0)
        return;
    ((Thing *)obj)->setPosition(pos);
}
