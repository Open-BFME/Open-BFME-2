// FILE: ObjectModule.h ///////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 ObjectModule, the base of every object module.
//
// Target facts (docs/linking_obstacles.md, "Module base chain"):
//  - ??0ObjectModule@@QAE@PAVThing@@PBVModuleData@@@Z (0x00306AA7) installs
//    vftable 0x00C07E1C, stores the ModuleData argument at +4 (Module's
//    m_moduleData) and the thing's object at +8;
//  - that vftable holds exactly 10 slots (its class-name literal follows):
//    Module's nine, then slot 9 = 0x0050B238 `ret 8`, an empty virtual with
//    two stack arguments. Zero Hour's ObjectModule declares
//    onCapture(Player *, Player *) there; its onDisabledEdge has no slot in
//    BFME2.
// The view majority (127 of 163 census views) spells the destructor out of
// line, which this header keeps.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_OBJECTMODULE_H_
#define __BFME2_OBJECTMODULE_H_

#include "Module.h"

class Object;
class Player;
class Thing;

//-------------------------------------------------------------------------------------------------
class ObjectModule : public Module
{
public:

	ObjectModule( Thing *thing, const ModuleData *moduleData );
	virtual ~ObjectModule();

	virtual void onCapture( Player *oldOwner, Player *newOwner ) { }		// slot 9

protected:

	inline Object *getObject() { return m_object; }
	inline const Object *getObject() const { return m_object; }

	Object *m_object;														// +0x08

};

#endif // __BFME2_OBJECTMODULE_H_
