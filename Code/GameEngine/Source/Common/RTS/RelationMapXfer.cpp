// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// cl: /O1 /DNDEBUG /MD /GX
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


// PlayerRelationMap::xfer and TeamRelationMap::xfer, ported from Zero Hour's
// GameEngine/Source/Common/RTS/Player.cpp and Team.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). Each is slot 3 of
// the vftable whose name getter returns its class.
//
// BFME 2 opens with the light-CRC gate. PlayerRelationMap versions through
// Xfer +0x28; TeamRelationMap calls Version1. The STLport hash_map at +0x04
// (element count at +0x14) is reached through its out-of-line members. These
// are ICF-shared bodies already rowed under other hash_map spellings:
// begin() 0x00427195 (returned through a hidden pointer), iterator ++
// 0x0041E832, and operator[] 0x0041F4E5. They are viewed here per key type.
// The relationship goes through XferRelationship (0x00305C32).

#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?resize@?$hashtable@U?$pair@$$CBIW4Relationship@@@_STL@@IU?$hash@I@2@U?$_Select1st@U?$pair:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum Relationship;
namespace _STL { template <> void hashtable<pair<unsigned int const ,Relationship>,unsigned int,hash<unsigned int>,_Select1st<pair<unsigned int const ,Relationship> >,equal_to<unsigned int>,allocator<pair<unsigned int const ,Relationship> > >::resize(unsigned int); }
// Suppress this TU's non-retail copy of ?resize@?$hashtable@U?$pair@$$CBHW4Relationship@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum Relationship;
namespace _STL { template <> void hashtable<pair<int const ,Relationship>,int,hash<int>,_Select1st<pair<int const ,Relationship> >,equal_to<int>,allocator<pair<int const ,Relationship> > >::resize(unsigned int); }
// Suppress this TU's non-retail copy of ?_M_new_node@?$hashtable@U?$pair@$$CBIW4Relationship@@@_STL@@IU?$hash@I@2@U?$_Select1st@U?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum Relationship;
namespace _STL { template <> _Hashtable_node<pair<unsigned int const ,Relationship> > * hashtable<pair<unsigned int const ,Relationship>,unsigned int,hash<unsigned int>,_Select1st<pair<unsigned int const ,Relationship> >,equal_to<unsigned int>,allocator<pair<unsigned int const ,Relationship> > >::_M_new_node(pair<unsigned int const ,Relationship> const &); }
// Suppress this TU's non-retail copy of ?_M_new_node@?$hashtable@U?$pair@$$CBHW4Relationship@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum Relationship;
namespace _STL { template <> _Hashtable_node<pair<int const ,Relationship> > * hashtable<pair<int const ,Relationship>,int,hash<int>,_Select1st<pair<int const ,Relationship> >,equal_to<int>,allocator<pair<int const ,Relationship> > >::_M_new_node(pair<int const ,Relationship> const &); }
// Suppress this TU's non-retail copy of ?_M_next_size@?$hashtable@U?$pair@$$CBIW4Relationship@@@_STL@@IU?$hash@I@2@U?$_Select1st@U:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum Relationship;
namespace _STL { template <> unsigned int hashtable<pair<unsigned int const ,Relationship>,unsigned int,hash<unsigned int>,_Select1st<pair<unsigned int const ,Relationship> >,equal_to<unsigned int>,allocator<pair<unsigned int const ,Relationship> > >::_M_next_size(unsigned int) const; }
// Suppress this TU's non-retail copy of ?_M_next_size@?$hashtable@U?$pair@$$CBHW4Relationship@@@_STL@@HU?$hash@H@2@U?$_Select1st@U:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum Relationship;
namespace _STL { template <> unsigned int hashtable<pair<int const ,Relationship>,int,hash<int>,_Select1st<pair<int const ,Relationship> >,equal_to<int>,allocator<pair<int const ,Relationship> > >::_M_next_size(unsigned int) const; }
// Suppress this TU's non-retail copy of ?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *__malloc_alloc<0>::allocate(size_t); }
// Suppress this TU's non-retail copy of ??A?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEABQAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *const &vector<void *>::operator[](size_t) const; }

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
// Suppress the TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

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

#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferVersion.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../Libraries/Include/Lib/Coord3DBase.h"

typedef unsigned short UnsignedShort;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

void XferRelationship( Xfer *xfer, Int *value );

typedef _STL::hash_map< Int, Relationship, _STL::hash<Int>, _STL::equal_to<Int> > PlayerRelationMapType;
typedef _STL::hash_map< UnsignedInt, Relationship, _STL::hash<UnsignedInt>, _STL::equal_to<UnsignedInt> > TeamRelationMapType;


// ------------------------------------------------------------------------------------------------
// Copy helper views use existing ICF-owned hash providers. The lookup's
// Object spelling is an opaque four-byte ABI carrier, not a relationship type.
typedef _STL::hashtable<_STL::pair<const int,Relationship>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<const int,Relationship> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,Relationship> > > PlayerRelationTableView;
// The neutral bucket-table owner supplies the complete retail clear at 1DBCDC.
#include "../../../Include/Common/Rva004DFC20.h"
class Object;
class ObjectLookupMap {public: Object **findSlot(int *);};
struct RelationCopyNodeView {void *next; int key; int value;};
class PlayerRelationMap
{
public:
 PlayerRelationMap *rva002ADE71(const PlayerRelationMap *);
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	PlayerRelationMapType m_map;																							///< 0x04
};

// ------------------------------------------------------------------------------------------------
class TeamRelationMap
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
private:
	TeamRelationMapType m_map;																								///< 0x04
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void PlayerRelationMap::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	Xfer::Version version( 1, 1 );
	*xfer == version;

	// player relation count
	PlayerRelationMapType::iterator playerRelationIt;
	UnsignedShort playerRelationCount = m_map.size();
	*xfer == playerRelationCount;

	// player relations
	Int playerIndex;
	Int r;
	if( xfer->IsStoring() )
	{

		// go through all player relations
		for( playerRelationIt = m_map.begin(); playerRelationIt != m_map.end(); ++playerRelationIt )
		{

			// write player index
			playerIndex = (*playerRelationIt).first;
			*xfer == playerIndex;

			// write relationship
			r = (*playerRelationIt).second;
			XferRelationship( xfer, &r );

		}  // end for, playerRelationIt

	}  // end if, save
	else
	{

		for( UnsignedShort i = 0; i < playerRelationCount; ++i )
		{

			// read player index
			*xfer == playerIndex;

			// read relationship
			XferRelationship( xfer, &r );

			// The retail find-or-insert at 41F4E5 owns this four-byte slot.
			*reinterpret_cast<Relationship*>(reinterpret_cast<ObjectLookupMap*>(&m_map)->findSlot(&playerIndex)) = (Relationship)r;

		}  // end for, i

	}  // end else, load

}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void TeamRelationMap::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// team relation count
	TeamRelationMapType::iterator teamRelationIt;
	UnsignedShort teamRelationCount = m_map.size();
	*xfer == teamRelationCount;

	// team relations
	UnsignedInt teamID;
	Int r;
	if( xfer->IsStoring() )
	{

		// go through all team relations
		for( teamRelationIt = m_map.begin(); teamRelationIt != m_map.end(); ++teamRelationIt )
		{

			// write team id
			teamID = (*teamRelationIt).first;
			*xfer == teamID;

			// write relationship
			r = (*teamRelationIt).second;
			XferRelationship( xfer, &r );

		}  // end for, teamRelationIt

	}  // end if, save
	else
	{

		for( UnsignedShort i = 0; i < teamRelationCount; ++i )
		{

			// read team id
			*xfer == teamID;

			// read relationship
			XferRelationship( xfer, &r );

			// The retail find-or-insert at 41F4E5 owns this four-byte slot (symbols.csv pins
			// this map's operator[] there; its only other emitter was a removed Player donor).
			*reinterpret_cast<Relationship*>(reinterpret_cast<ObjectLookupMap*>(&m_map)->findSlot(reinterpret_cast<Int*>(&teamID))) = (Relationship)r;

		}  // end for, i

	}  // end else, load

}  // end xfer

// WB C0FEC0 and named Player cloneFrom caller2B07A9 establish the relation
// map owner and clear/copy behavior. Native2ADE71..2ADEBE reads keys4/value8
// and uses the existing find-or-insert provider; original method name unknown.
// The direct hashtable begin view preserves the native hidden-return ordering.
PlayerRelationMap *PlayerRelationMap::rva002ADE71(const PlayerRelationMap *source) {
 reinterpret_cast<Rva004DFC20*>(&m_map)->clear();
 (this?_ReadWriteBarrier():_ReadWriteBarrier());
 PlayerRelationMapType *sourceMap=const_cast<PlayerRelationMapType*>(&source->m_map);
 PlayerRelationMapType::iterator it=reinterpret_cast<PlayerRelationTableView*>(const_cast<PlayerRelationMapType*>(&source->m_map))->begin();
 while(it != sourceMap->end()) {
  RelationCopyNodeView *node=reinterpret_cast<RelationCopyNodeView*>(it._M_cur);
  Object **slot=reinterpret_cast<ObjectLookupMap*>(&m_map)->findSlot(&node->key);
  *reinterpret_cast<int*>(slot)=node->value;
  ++it;
 }
 return this;
}
