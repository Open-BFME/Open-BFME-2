// cl: /DNDEBUG /MD
//
// ??0HijackerUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004A4055, 74 bytes.
// HijackerUpdate behavior ctor over the rowed UpdateModule base (0x253390):
// zeroes the target ID (+0x20) and the update, in-vehicle and airborne flags
// (+0x30/+0x31/+0x32), then re-stores the primary vtable slot and the
// +0x0C/+0x10 secondary slots (address-of TU-local dummies, DIR32-masked),
// then zeroes the eject position (+0x24/+0x28/+0x2C) through an inlined
// Coord3D::zero. The float zeroes are what make retail prepare xmm0 before
// the integer zero (xorps ahead of xor) and need /arch:SSE. Body follows the
// ZH donor ctor in HijackerUpdate.cpp (m_targetID = INVALID_ID, both flag
// setters FALSE, m_wasTargetAirborne false, m_ejectPos.zero()); the outline
// setters stay out of line callers elsewhere. The pinned instance factory
// 0x24ED27 is the sole raw caller; class from the ModuleFactory literal.
// Row supersedes the ctor pin.

class ModuleData;
class Thing;

extern "C" const void *const __identifier("??_7Rva004A3F8B@@6BUpdateModule@@@")[];
extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@")[];
extern "C" const void *const __identifier("??_7Rva004A3F8B@@6BRva004A3F8B_B2@@@")[];

// Opaque UpdateModule base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

typedef int ObjectID;

enum
{
	INVALID_ID = 0
};

// Coord3D: shared header/view; no private copy.
#include "../../../../../Libraries/Include/Lib/Coord3DInline.h"

class HijackerUpdate : public UpdateModule
{
public:
	HijackerUpdate(Thing *thing, const ModuleData *moduleData);

private:
	ObjectID m_targetID; // +0x20
	Coord3D m_ejectPos; // +0x24
	unsigned char m_update; // +0x30
	unsigned char m_isInVehicle; // +0x31
	bool m_wasTargetAirborne; // +0x32
	unsigned char m_pad33;
};

// ??0HijackerUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x4A4055
HijackerUpdate::HijackerUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_targetID = INVALID_ID;
	m_update = 0;
	m_isInVehicle = 0;
	m_wasTargetAirborne = false;
	m_vtable = __identifier("??_7Rva004A3F8B@@6BUpdateModule@@@");
	m_p0C = __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@");
	m_p10 = __identifier("??_7Rva004A3F8B@@6BRva004A3F8B_B2@@@");
	m_ejectPos.zero();
}
