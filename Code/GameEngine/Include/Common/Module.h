// FILE: Module.h /////////////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 Module, the common base of object and drawable modules.
//
// Written from the retail vftables (docs/linking_obstacles.md, "Module base
// chain"); tools/header_adopt_lane.py cannot generate it while the private
// views disagree on its size. Target facts:
//  - no Module vftable survives (its constructor inlines and the store dies);
//    ObjectModule's 0x00C07E1C has exactly 10 slots, DrawableModule's
//    0x00C07E54 11, and slot 9 differs between them, so Module has 9;
//  - ??_GObjectModule (0x004A10FD) calls 0x0049B47C, which restores
//    Snapshot's vftable 0x00BBB554 at [this]: Snapshot is the base at offset 0
//    and every destructor between them is empty;
//  - slots 1-3 are Snapshot's (Snapshot.h); slot 4 is __purecall in every
//    abstract table and Object::findModule (0x0028B6D6) compares [vtable+0x10];
//  - slots 5-8 are the empty `ret` 0x000B3FD0 in the base tables; matched
//    overriders name slot 5 onObjectCreated, 6 onDrawableBoundToObject and
//    8 onDelete. Slot 7 sits where Zero Hour has preloadAssets(TimeOfDay),
//    but every BFME2 implementation takes no stack argument;
//  - the ObjectModule and DrawableModule constructors store the ModuleData
//    argument at +4.
// Donor (Zero Hour Module.h) facts: the method names and the empty inline
// bodies. Zero Hour's MemoryPoolObject base and its TimeOfDay argument are not
// BFME2's.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BFME2_MODULE_H_
#define __BFME2_MODULE_H_

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

enum NameKeyType;
class ModuleData;

//-------------------------------------------------------------------------------------------------
class Module : public Snapshot
{
public:

	Module( const ModuleData *moduleData ) : m_moduleData( moduleData ) { }
	virtual ~Module() { }

	virtual NameKeyType getModuleNameKey() const = 0;					// slot 4

	/** called after all the Modules for a given Thing are created */
	virtual void onObjectCreated() { }									// slot 5

	/** called whenever a drawable is bound to the object */
	virtual void onDrawableBoundToObject() { }							// slot 6

	/// Zero Hour's preloadAssets position; BFME2's slot takes no argument
	virtual void preloadAssets() { }										// slot 7

	/** called on every module of an object or drawable before any is deleted */
	virtual void onDelete( void ) { }										// slot 8

protected:

	inline const ModuleData *getModuleData() const { return m_moduleData; }

	const ModuleData *m_moduleData;										// +0x04

};

#endif // __BFME2_MODULE_H_
