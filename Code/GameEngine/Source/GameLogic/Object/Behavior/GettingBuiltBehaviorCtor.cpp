// cl: /Ireference/shims/bfmelist /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0GettingBuiltBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004542FA, 169 bytes. Behavior-side ctor completing the GettingBuilt
// file-unit (ModuleData factory rowed at 0x24A9D5; behavior factory rowed
// at 0x24A99D news 0x44 with this pinned 2-arg ctor; poolkey rowed at
// 0x4543EB).
//
// No Zero Hour donor (BFME-new behavior). Retail-measured shape, mirroring
// PoisonedBehaviorCtor.cpp (UpdateModule 0x20 base plus inline-ctor fourth
// interface base carrying the +0x20 slot, /GX, /arch:SSE):
// - UpdateModule base resolves via its row at 0x00253390; setWakeFrame via
//   the established UpdateModule pin at 0x0044DF71 (called here with 1).
// - The +0x40 member is a 4-byte STLport list head whose default
//   construction calls the rowed BfmePod20 _List_base ctor at 0x00453ADD
//   with a stack allocator temp; the 20-byte element is an unidentified
//   payload, so BfmePod20 stands in per the pod-list placeholder
//   convention. +0x40 plus 4 is exactly the 0x44 factory news size.
// - Scalar members ride the init-list in declaration order (with a
//   non-trivial list member present they emit post-vptr mov-form stores,
//   not the pre-vptr and/or of the all-trivial probe); the +0x30 byte quad,
//   the +0x28 float and the repeated +0x3E zero are body assignments after
//   the list call, interleaved with the setWakeFrame setup in retail order.

#include <list>

class Thing;
class ModuleData;
class Object;

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../../../../reference/open-bfme-1/game/GameEngine/Include/GameLogic/Module/UpdateSleepTime.h"





// Retail table 0x00C40434 (+0x10) slot 0 is the rowed override 0x00454DF9.

#include "GettingBuiltBehaviorView.h"

// ??0GettingBuiltBehaviorInterface@@QAE@XZ @0x00453111 9B: the default constructor, storing the
// class's own vtable (VA 0x00C40020) and returning this.
GettingBuiltBehaviorInterface::GettingBuiltBehaviorInterface()
{
}

void *GettingBuiltBehavior::slot32()
{
	return static_cast<GettingBuiltBehaviorInterface *>(this);
}

void GettingBuiltBehavior::slot45(int)
{
	rva00454430();
}

bool GettingBuiltBehavior::rva004543B6()
{
	return m_b32;
}

bool GettingBuiltBehavior::checkCompletion()
{
	return m_b36;
}

double GettingBuiltBehavior::rva004543BA()
{
	return m_x38;
}

bool GettingBuiltBehavior::rva004543BE()
{
	return m_b35;
}

bool GettingBuiltBehavior::rva004543C2()
{
	return m_b33;
}

bool GettingBuiltBehavior::rva004543C6()
{
	return m_b3E;
}

void GettingBuiltBehavior::rva00454472(int frame)
{
	// UpdateModuleInterface is the +0x10 base of the live object.
	UpdateModuleInterface *updateInterface =
		reinterpret_cast<UpdateModuleInterface *>(reinterpret_cast<char *>(this) + 0x10);
	updateInterface->update();
	setWakeFrame(m_object, static_cast<UpdateSleepTime>(frame));
}

// ??0GettingBuiltBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x004542FA
GettingBuiltBehavior::GettingBuiltBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData),
	m_audio24(1),
	m_x2C(0),
	m_b34(0),
	m_b35(0),
	m_b36(0),
	m_x38(0),
	m_b3C(0),
	m_b3D(1),
	m_b3E(0)
{
	m_b30 = 0;
	m_f28 = 0.0f;
	m_b31 = 0;
	m_b32 = 0;
	m_b33 = 0;
	m_b3E = 0;
	setWakeFrame(const_cast<Object*>(getObject()), UPDATE_SLEEP_NONE);
}
