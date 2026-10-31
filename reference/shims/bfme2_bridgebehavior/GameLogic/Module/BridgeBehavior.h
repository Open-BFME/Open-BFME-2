// GameLogic/Module/BridgeBehavior.h, verbatim but for BFME 2's member offsets (marked "BFME 2:"). Copied from
// reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: BridgeBehavior.h /////////////////////////////////////////////////////////////////////////
// Author: Colin Day, July 2002
// Desc:   Behavior module for bridges
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __BRIDGE_BEHAVIOR_H_
#define __BRIDGE_BEHAVIOR_H_

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////
#include "Common/AudioEventRTS.h"
#include "GameClient/TerrainRoads.h"
#include "GameLogic/Module/BehaviorModule.h"
#include "GameLogic/Module/DamageModule.h"
#include "GameLogic/Module/Diemodule.h"
#include "GameLogic/Module/UpdateModule.h"

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
enum BridgeTowerType;
class FXList;
class ObjectCreationList;
class Bridge;
class Rva0027C36A;
typedef Rva0027C36A BridgeInfo;  // BFME 2: rowed under this name, see GameLogic/TerrainLogic.h

// TYPES //////////////////////////////////////////////////////////////////////////////////////////
// ------------------------------------------------------------------------------------------------
struct TimeAndLocationInfo
{
	UnsignedInt delay;			///< how long to wait to execute this
	AsciiString boneName;		///< which bone to execute at
};
// ------------------------------------------------------------------------------------------------
struct BridgeFXInfo
{
	const FXList *fx;
	TimeAndLocationInfo timeAndLocationInfo;
};

// ------------------------------------------------------------------------------------------------
struct BridgeOCLInfo
{
	const ObjectCreationList *ocl;
	TimeAndLocationInfo timeAndLocationInfo;
};

// ------------------------------------------------------------------------------------------------
typedef std::list< BridgeFXInfo > BridgeFXList;
typedef std::list< BridgeOCLInfo > BridgeOCLList;
typedef std::list< ObjectID > ObjectIDList;
typedef ObjectIDList::iterator ObjectIDListIterator;

// BFME 2: the scaffold IDs draw their nodes from the fixed-size pool at 0x00DA60E8 (free list at
// 0x00DA60F0), as ??1?$list@W4ObjectID@@V?$BfmeObjectIdPoolAllocator@W4ObjectID@@@@@_STL@@QAE@XZ
// 0x00268AFF and the list members createScaffolding 0x00457737 calls show.
class FreelistPool { public: void *pop(); };
extern FreelistPool g_freelistPool;
extern void *g_freeList;
template <class T> class BfmeObjectIdPoolAllocator {
public:
	typedef T value_type;
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef T &reference;
	typedef const T &const_reference;
	typedef unsigned int size_type;
	typedef int difference_type;
	template <class U> struct rebind { typedef BfmeObjectIdPoolAllocator<U> other; };
	BfmeObjectIdPoolAllocator() {}
	template <class U> BfmeObjectIdPoolAllocator(const BfmeObjectIdPoolAllocator<U> &) {}
	pointer allocate(size_type, const void * = 0) { return (pointer)g_freelistPool.pop(); }
	void deallocate(pointer p, size_type)
	{
		if (p)
		{
			*(void **)p = g_freeList;
			g_freeList = p;
		}
	}
	void construct(pointer p, const_reference value) { new (p) T(value); }
	void destroy(pointer p) { p->~T(); }
	size_type max_size() const { return (size_type)(-1)/sizeof(T); }
};
namespace _STL {
template <class T, class U>
inline BfmeObjectIdPoolAllocator<U> &__stl_alloc_rebind(BfmeObjectIdPoolAllocator<T> &a, const U *)
{ return (BfmeObjectIdPoolAllocator<U> &)a; }
template <class T, class U>
inline BfmeObjectIdPoolAllocator<U> __stl_alloc_create(const BfmeObjectIdPoolAllocator<T> &, const U *)
{ return BfmeObjectIdPoolAllocator<U>(); }
template <class T, class U> struct _Alloc_traits<T, BfmeObjectIdPoolAllocator<U> > {
	typedef BfmeObjectIdPoolAllocator<U> _Orig;
	typedef BfmeObjectIdPoolAllocator<T> allocator_type;
	static allocator_type create_allocator(const _Orig &a) { return allocator_type(a); }
};
}
typedef std::list<ObjectID, BfmeObjectIdPoolAllocator<ObjectID> > ScaffoldObjectIDList;
// BFME 2: retail keeps this list's node construction out of line: insert 0x002A1316 calls 0x0029FB80.
namespace _STL {
template <>
inline __declspec(noinline) ScaffoldObjectIDList::_Node *
ScaffoldObjectIDList::_M_create_node(const ObjectID &__x)
{
	_Node *__p = this->_M_node.allocate(1);
	_Construct(&__p->_M_data, __x);
	return __p;
}
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
class BridgeBehaviorInterface
{

public:

	virtual void setTower( BridgeTowerType towerType, Object *tower ) = 0;
	virtual ObjectID getTowerID( BridgeTowerType towerType ) = 0;
	virtual void createScaffolding( void ) = 0;
	virtual void removeScaffolding( void ) = 0;
	virtual Bool isScaffoldInMotion( void ) = 0;
	virtual Bool isScaffoldPresent( void ) = 0;

};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
class BridgeBehaviorModuleData : public BehaviorModuleData
{

public:

	BridgeBehaviorModuleData( void );
	~BridgeBehaviorModuleData( void );

	static void buildFieldParse( MultiIniFieldParse &p );

	Real m_lateralScaffoldSpeed;
	Real m_verticalScaffoldSpeed;
	BridgeFXList m_fx;							///< list of FX lists to execute
	BridgeOCLList m_ocl;						///< list of OCL to execute

	static void parseFX( INI *ini, void *instance, void *store, const void* userData );
	static void parseOCL( INI *ini, void *instance, void *store, const void* userData );

};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
class BridgeBehavior : public UpdateModule,
											 public BridgeBehaviorInterface,
											 public DamageModuleInterface,
											 public DieModuleInterface
{

	// BFME 2: the die interface's body is rowed as ?onDie@Rva004581FD@@UAEXPBVDamageInfo@@@Z 0x004581FD,
	// which calls this class's protected handleObjectsOnBridgeOnDie.
	friend class Rva004581FD;
	// BFME 2: keeps the rowed select-any setScaffoldData 0x004568EC emitted where no caller is compiled.
	friend void bfmeAnchorBridgeBehaviorSetScaffoldData( BridgeBehavior *bridgeBehavior );

	// BFME 2: MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA spelled out, because getModuleNameKey's body
	// is rowed at 0x004571A9 (BridgeBehaviorPoolKey.cpp) and the macro would define it here.
public:
	static Module* friend_newModuleInstance( Thing *thing, const ModuleData* moduleData ) { return ::new BridgeBehavior( thing, moduleData ); }
	virtual NameKeyType getModuleNameKey() const;
protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
	MAKE_STANDARD_MODULE_DATA_MACRO_ABC( BridgeBehavior, BridgeBehaviorModuleData )
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( BridgeBehavior, "BridgeBehavior" )

public:

	BridgeBehavior( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype provided by memory pool declaration

	// module methods
	static Int getInterfaceMask( void ) { return (MODULEINTERFACE_DAMAGE) | 
																							 (MODULEINTERFACE_DIE) |
																							 (MODULEINTERFACE_UPDATE); }
	virtual BridgeBehaviorInterface* getBridgeBehaviorInterface( void ) { return this; }
	virtual void onDelete( void );

	// Damage methods
	virtual DamageModuleInterface* getDamage( void ) { return this; }
	virtual void onDamage( DamageInfo *damageInfo );
	virtual void onHealing( DamageInfo *damageInfo );
	virtual void onBodyDamageStateChange( const DamageInfo* damageInfo, 
																				BodyDamageType oldState, 
																				BodyDamageType newState );

	// Die methods
	virtual DieModuleInterface* getDie( void ) { return this; }
	virtual void onDie( const DamageInfo *damageInfo );

	// Update methods
	virtual UpdateModuleInterface *getUpdate( void ) { return this; }
	virtual UpdateSleepTime update( void );

	// our own methods
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject( Object *obj );
	virtual void setTower( BridgeTowerType towerType, Object *tower );	///< connect tower to us
	virtual ObjectID getTowerID( BridgeTowerType towerType );						///< retrive one of our towers
	virtual void createScaffolding( void );		///< create scaffolding around bridge
	virtual void removeScaffolding( void );		///< remove scaffolding around bridge
	virtual Bool isScaffoldInMotion( void );	///< is scaffold in motion
	virtual Bool isScaffoldPresent( void ) { return m_scaffoldPresent; }

protected:

	void resolveFX( void );
	void handleObjectsOnBridgeOnDie( void );
	void doAreaEffects( TerrainRoadType *bridgeTemplate, Bridge *bridge, 
											const ObjectCreationList *ocl, const FXList *fx );
	void setScaffoldData( Object *obj, 
												Real *angle, 
												Real *sunkenHeight, 
												const Coord3D *riseToPos, 
												const Coord3D *buildPos, 
												const Coord3D *bridgeCenter );

	void getRandomSurfacePosition( TerrainRoadType *bridgeTemplate, 
																 const BridgeInfo *bridgeInfo, 
																 Coord3D *pos );

	ObjectID m_towerID[ BRIDGE_MAX_TOWERS ];		///< the towers that are a part of us

	// got damaged fx stuff
	const ObjectCreationList *m_damageToOCL[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	const FXList *m_damageToFX[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	// BFME 2: no sound tables. ?resolveFX@BridgeBehavior@@IAEXXZ 0x00456A49 writes the tables at
	// +0x3C/+0x6C/+0x9C/+0xCC and the resolved flag at +0xFC.

	// got repaired fx stuff
	const ObjectCreationList *m_repairToOCL[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	const FXList *m_repairToFX[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];

	Bool m_fxResolved;		///< TRUE until we've loaded our fx pointers and sounds

	Bool m_scaffoldPresent;									///< TRUE when we have repair scaffolding visible
	ScaffoldObjectIDList m_scaffoldObjectIDList;		///< list of scaffold object IDs

	UnsignedInt m_deathFrame;								///< frame we died on

};

#endif  // end __BRIDGE_DAMAGE_H_
