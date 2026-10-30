// cl: /Ireference/shims/bfme_pathfinder_get_cell_link /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/ocls /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameLogic/Object/ObjectCreationList.cpp); this unit had no counterpart under Code/.
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

// FILE: ObjectCreationList.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson, December 2001
// Desc:   ObjectCreationList descriptions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_SHADOW_NAMES								// for TheShadowNames[]
#define DEFINE_WEAPONSLOTTYPE_NAMES

#define NO_DEBUG_CRC

#include "Common/AudioEventRTS.h"
#include "Common/DrawModule.h"
#include "Common/GlobalData.h"
#include "Common/INI.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/GameLOD.h"

#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/Shadow.h"

#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/DeliverPayloadAIUpdate.h"
#include "GameLogic/Module/FloatUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/SpecialPowerCompletionDie.h"
#include "GameLogic/Module/LifetimeUpdate.h"
#include "GameLogic/Module/RadiusDecalUpdate.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/WeaponSet.h"

#include "GameLogic/AIPathfind.h"


#include "Common/CRCDebug.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString *>(AsciiString *, AsciiString *); }
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator++(); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> bool less<int>::operator()(int const &, int const &) const; }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// Call retail's hinted insert_unique (0x00422EC0) instead of emitting this unit's own copy.
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> pair<_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::iterator, bool> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::insert_unique(const pair<const int, int> &); }

// Keep comparisons local: external tree-base and max<unsigned> copies
// conflict with their selected providers. TRANSITIVE STL anchor.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

ObjectCreationListStore *TheObjectCreationListStore = NULL;					///< the ObjectCreationList store definition

//-------------------------------------------------------------------------------------------------
static void adjustVector(Coord3D *vec, const Matrix3D* mtx)
{
	if (mtx)
	{
		Vector3 vectmp;
		vectmp.X = vec->x;
		vectmp.Y = vec->y;
		vectmp.Z = vec->z;
		vectmp = mtx->Rotate_Vector(vectmp);
		vec->x = vectmp.X;
		vec->y = vectmp.Y;
		vec->z = vectmp.Z;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE CLASSES ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// ?create@ObjectCreationNugget@@ present-unmatched
Object* ObjectCreationNugget::create( const Object* primary, const Object* secondary, UnsignedInt lifetimeFrames ) const
{
	return create( primary, primary ? primary->getPosition() : NULL, secondary ? secondary->getPosition() : NULL, INVALID_ANGLE, lifetimeFrames );
}

//-------------------------------------------------------------------------------------------------
//void ObjectCreationNugget::create( const Object* primaryObj, const Coord3D *primary, const Coord3D *secondary, Real angle, UnsignedInt lifetimeFrames ) const
//{
//	create( primaryObj, primary ? primary->getPosition() : NULL, secondary ? secondary->getPosition() : NULL, angle, lifetimeFrames );
//}

//-------------------------------------------------------------------------------------------------
//This one is called only when we have a nugget that doesn't care about createOwner.
// ?create@ObjectCreationNugget@@ present-unmatched
Object* ObjectCreationNugget::create( const Object *primaryObj, const Coord3D *primary, const Coord3D *secondary, Bool createOwner, UnsignedInt lifetimeFrames ) const
{
	return create( primaryObj, primary, secondary, INVALID_ANGLE, lifetimeFrames );
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class FireWeaponNugget : public ObjectCreationNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(FireWeaponNugget, "FireWeaponNugget")		
	
public:

	FireWeaponNugget() : 
    m_weapon(NULL)
	{
	}

	virtual Object* create( const Object* primaryObj, const Coord3D *primary, const Coord3D* secondary, Real angle, UnsignedInt lifetimeFrames = 0 ) const
	{
		if (!primaryObj || !primary || !secondary)
		{ 
			DEBUG_CRASH(("You must have a primary and secondary source for this effect"));
      return NULL;
    }

	  if (m_weapon)
	  {
		  TheWeaponStore->createAndFireTempWeapon( m_weapon, primaryObj, secondary );
	  }
		return NULL;
  }

	static void parse(INI *ini, void *instance, void *store, const void *userData);

private:
	const WeaponTemplate* m_weapon;
};  
EMPTY_DTOR(FireWeaponNugget)

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class AttackNugget : public ObjectCreationNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(AttackNugget, "AttackNugget")		
public:

	AttackNugget();

	virtual Object* create( const Object* primaryObj, const Coord3D *primary, const Coord3D* secondary, Real angle, UnsignedInt lifetimeFrames = 0 ) const
	{
		if (!primaryObj || !primary || !secondary)
		{ 
			DEBUG_CRASH(("You must have a primary and secondary source for this effect"));
      return NULL;
    }

		// Star trekkin, across the universe.
		// Boldly goin forward now, cause we can't find reverse!

		// 1:30 left on the clock, Demo looming, should I de-const all of OCL since this one effect needs the 
		// Primary to help make the objects?  Should I rewrite superweapons to completely subsume them
		// into normal special powers, so I can have a spell attack with a global timer and a spinny clock?
		// Should I const cast?  Should I eat them?  No!  I'd rather hurt them stomp them crush them hurt them
		// stomp them while I dance!  Down.  Those insects make me dance!  Down.  I'll hurt them while I dance.

		Object *primaryObject = const_cast<Object *>(primaryObj);
		AIUpdateInterface *ai = primaryObject->getAIUpdateInterface();
		if( ai )
		{
			// lock merely fires till the weapon is empty or the attack is "done"
			primaryObject->setWeaponLock( m_weaponSlot, LOCKED_TEMPORARILY );
			ai->aiAttackPosition( secondary, m_numberOfShots, CMD_FROM_AI );
		}

		static NameKeyType key_RadiusDecalUpdate = NAMEKEY("RadiusDecalUpdate");
		RadiusDecalUpdate *rd = (RadiusDecalUpdate*)primaryObject->findUpdateModule(key_RadiusDecalUpdate);
		if (rd)
		{
			rd->createRadiusDecal(m_deliveryDecalTemplate, m_deliveryDecalRadius, *secondary);
			rd->killWhenNoLongerAttacking(true);
		}
		return NULL;
  }

	static void parse(INI *ini, void *instance, void *store, const void *userData);

private:
	RadiusDecalTemplate	m_deliveryDecalTemplate;
	Real								m_deliveryDecalRadius;
	Int									m_numberOfShots;
	WeaponSlotType			m_weaponSlot;
};  
EMPTY_DTOR(AttackNugget)

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// The separately recovered ApplyRandomForceNugget::create calls this owner.
void calcRandomForce(Real minMag, Real maxMag, Real minPitch, Real maxPitch, Coord3D* force)
{
#line 581 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp"
	Real angle = GameLogicRandomValueReal(0, 2*PI);
	Real pitch = GameLogicRandomValueReal(minPitch, maxPitch);
	Real mag = GameLogicRandomValueReal(minMag, maxMag);

#line 611 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp"
	Matrix3D mtx(1);
	mtx.Scale(mag);
	mtx.Rotate_Z(angle);
	mtx.Rotate_Y(-pitch);

	Vector3 v = mtx.Get_X_Vector();

	Coord3D result;
	result.x = v.X;
	result.y = v.Y;
	result.z = v.Z;
	*force = result;
}


#line 624 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\ObjectCreationList.cpp"
//-------------------------------------------------------------------------------------------------
class ApplyRandomForceNugget : public ObjectCreationNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(ApplyRandomForceNugget, "ApplyRandomForceNugget")		
public:

	ApplyRandomForceNugget() : 
		m_spinRate(0.0f),
		m_minMag(0.0f),
		m_maxMag(0.0f),
		m_minPitch(0.0f),
		m_maxPitch(0.0f)
	{
	}

	virtual Object* create( const Object* primary, const Object* secondary, UnsignedInt lifetimeFrames = 0 ) const
	{
		if (primary)
		{
			/// @todo srj -- ack. const_cast is evil.
			PhysicsBehavior* physicsBehavior = const_cast<Object*>(primary)->getPhysics();
      if (physicsBehavior)
      {
				Coord3D force;
				calcRandomForce(m_minMag, m_maxMag, m_minPitch, m_maxPitch, &force);
				physicsBehavior->applyForce(&force);

			  Real yaw = GameLogicRandomValueReal( -m_spinRate, m_spinRate );
			  Real roll = GameLogicRandomValueReal( -m_spinRate, m_spinRate );
			  Real pitch = GameLogicRandomValueReal( -m_spinRate, m_spinRate );
			  physicsBehavior->setYawRate(yaw);
			  physicsBehavior->setRollRate(roll);
			  physicsBehavior->setPitchRate(pitch);
      }
      else
      {
  			DEBUG_CRASH(("You must have a Physics module source for this effect"));
      }
		}
		else
		{
			DEBUG_CRASH(("You must have a primary source for this effect"));
		}
		return NULL;
	}

	virtual Object* create(const Object* primaryObj, const Coord3D *primary, const Coord3D* secondary, Real angle, UnsignedInt lifetimeFrames = 0 ) const
	{
		DEBUG_CRASH(("You must call this effect with an object, not a location"));
		return NULL;
	}

	static void parse(INI *ini, void *instance, void *store, const void *userData);

protected:

private:
	Real											m_spinRate;
	Real											m_minMag, m_maxMag;
	Real											m_minPitch, m_maxPitch;
};  
EMPTY_DTOR(ApplyRandomForceNugget)

//-------------------------------------------------------------------------------------------------
enum DebrisDisposition
{
	LIKE_EXISTING						= 0x00000001,
	ON_GROUND_ALIGNED				= 0x00000002,
	SEND_IT_FLYING					= 0x00000004,
	SEND_IT_UP							= 0x00000008,
	SEND_IT_OUT							= 0x00000010,
	RANDOM_FORCE						= 0x00000020,
	FLOATING								= 0x00000040,
	INHERIT_VELOCITY				= 0x00000080,
	WHIRLING								= 0x00000100
};

static const char* DebrisDispositionNames[] =
{
	"LIKE_EXISTING",
	"ON_GROUND_ALIGNED",
	"SEND_IT_FLYING",
	"SEND_IT_UP",
	"SEND_IT_OUT",
	"RANDOM_FORCE",
	"FLOATING",
	"INHERIT_VELOCITY",
	"WHIRLING",
};

std::vector<AsciiString>	debrisModelNamesGlobalHack;

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
static void parseFrictionPerSec( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	Real fricPerSec = INI::scanReal(ini->getNextToken());
	Real fricPerFrame = fricPerSec * SECONDS_PER_LOGICFRAME_REAL;
	*(Real *)store = fricPerFrame;
} 

//-------------------------------------------------------------------------------------------------
class GenericObjectCreationNugget : public ObjectCreationNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(GenericObjectCreationNugget, "GenericObjectCreationNugget")		
public:

	GenericObjectCreationNugget();	// rowed 0x001F0E32 (GenericObjectCreationNuggetCtor.cpp)

	virtual Object* create(const Object* primary, const Object* secondary, UnsignedInt lifetimeFrames = 0 ) const
	{
		if (primary)
		{
			if (m_skipIfSignificantlyAirborne && primary->isSignificantlyAboveTerrain())
				return NULL;

			return reallyCreate( primary->getPosition(), primary->getTransformMatrix(), primary->getOrientation(), primary, lifetimeFrames );
		}
		else
		{
			DEBUG_CRASH(("You must have a primary source for this effect"));
		}
		return NULL;
	}

	virtual Object* create(const Object* primaryObj, const Coord3D *primary, const Coord3D* secondary, Real angle, UnsignedInt lifetimeFrames = 0 ) const
	{
		if (primary)
		{
			const Matrix3D *xfrm = NULL;
			if( angle == INVALID_ANGLE )
			{
				//Vast majority of OCL's don't care about the angle, so if it comes in invalid, default the angle to 0.
				angle = 0.0f;
			}
			return reallyCreate( primary, xfrm, angle, primaryObj, lifetimeFrames );
		}
		else
		{
			DEBUG_CRASH(("You must have a primary source for this effect"));
		}
		return NULL;
	}

	static const FieldParse* getCommonFieldParse();	// rowed 0x001F01EB

	static void parseObject(INI *ini, void *instance, void *store, const void *userData);	// rowed 0x001F311B

	static void parseDebris(INI *ini, void *instance, void *store, const void *userData);	// rowed 0x001F340A

	static void parseAnimSet(INI *ini, void * /*instance*/, void* store, const void* /*userData*/)
	{
		AnimSet anim;
		anim.m_animInitial = ini->getNextAsciiString();
		anim.m_animFlying = ini->getNextAsciiString();
		anim.m_animFinal = ini->getNextAsciiString();
		((std::vector<AnimSet>*)store)->push_back(anim);
	}

protected:

	void doStuffToObj(
		Object* obj, 
		const AsciiString& modelName, 
		const Coord3D *pos, 
		const Matrix3D *mtx, 
		Real orientation, 
		const Object *sourceObj,
		UnsignedInt lifetimeFrames
	) const
	{
		obj->setProducer(sourceObj);

		static NameKeyType key_LifetimeUpdate = NAMEKEY("LifetimeUpdate");
		LifetimeUpdate* lup = (LifetimeUpdate*)obj->findUpdateModule(key_LifetimeUpdate);
		if( lup )
		{
			if( lifetimeFrames )
			{
				//Passed in override, use this value for a specific lifetime!!!
				lup->setLifetimeRange( lifetimeFrames, lifetimeFrames );
			}
			else if( m_maxFrames > 0 )
			{
				// They will both be zero if no lifetime was specified in the OCL.  It could be in the Object so don't mess with it.
				// So the OCL listing will override the Object listing for lifetime, but ONLY if there is one.
				lup->setLifetimeRange(m_minFrames, m_maxFrames);
			}
		}
		
		if (!m_nameAreObjects)
		{
			for (DrawModule** dm = obj->getDrawable()->getDrawModules(); *dm; ++dm)
			{
				DebrisDrawInterface* di = (*dm)->getDebrisDrawInterface();
				if (di)
				{
					di->setModelName(modelName, m_okToChangeModelColor ? obj->getIndicatorColor() : 0, m_shadowType);
					if (m_animSets.size() > 0)
					{
						Int which = GameLogicRandomValue(0, m_animSets.size()-1);
						di->setAnimNames(m_animSets[which].m_animInitial, m_animSets[which].m_animFlying, m_animSets[which].m_animFinal, m_fxFinal);
					}
				}
			}
		}

		Coord3D offset = m_offset;
		if (mtx)
			adjustVector(&offset, mtx);

		Coord3D chunkPos;
		chunkPos.x = pos->x + offset.x;
		chunkPos.y = pos->y + offset.y;
		chunkPos.z = pos->z + offset.z;
		
		if (!m_particleSysName.isEmpty())
		{
			const ParticleSystemTemplate *particleSystemTemplate = TheParticleSystemManager->findTemplate(m_particleSysName);
			if (particleSystemTemplate)
			{
				ParticleSystem *sys = TheParticleSystemManager->createParticleSystem(particleSystemTemplate);
				sys->attachToObject(obj);
			}
		}
		
		if (m_ignorePrimaryObstacle)
		{
			PhysicsBehavior* physicsBehavior = obj->getPhysics();
			if (physicsBehavior)
				physicsBehavior->setIgnoreCollisionsWith(sourceObj);
		}

		// set its beginning health
		BodyModuleInterface *body = obj->getBodyModule();
		Real healthPercent = GameLogicRandomValueReal( m_minHealth, m_maxHealth );
		if (body)
			body->setInitialHealth(healthPercent * 100.0f);

		// If they have a SlavedUpdate, then I have to tell them who their daddy is from now on.
		for (BehaviorModule** update = obj->getBehaviorModules(); *update; ++update)
		{
			SlavedUpdateInterface* sdu = (*update)->getSlavedUpdateInterface();
			if (sdu != NULL)
			{
				sdu->onEnslave( sourceObj );
				break;
			}
		}

		if (m_inheritsVeterancy && sourceObj && obj->getExperienceTracker()->isTrainable())
		{
			DEBUG_LOG(("Object %s inherits veterancy level %d from %s\n",
				obj->getTemplate()->getName().str(), sourceObj->getVeterancyLevel(), sourceObj->getTemplate()->getName().str()));
			VeterancyLevel v = sourceObj->getVeterancyLevel();
			obj->getExperienceTracker()->setVeterancyLevel(v);

			//In order to make things easier for the designers, we are going to transfer the unit name
			//to the ejected thing... so the designer can control the pilot with the scripts.
			TheScriptEngine->transferObjectName( sourceObj->getName(), obj );
		}

		if ( m_invulnerableTime > 0 )
		{
			obj->goInvulnerable( m_invulnerableTime ); 
		}

		if( BitTest( m_disposition, INHERIT_VELOCITY ) && sourceObj )
		{
			const PhysicsBehavior *sourcePhysics = sourceObj->getPhysics();
			PhysicsBehavior *objectPhysics = obj->getPhysics();
			if( sourcePhysics && objectPhysics )
			{
				objectPhysics->applyForce( sourcePhysics->getVelocity() );
			}
		}

		if( BitTest( m_disposition, LIKE_EXISTING ) )
		{
			if (mtx)
				obj->setTransformMatrix(mtx);
			else
				obj->setOrientation(orientation);
			obj->setPosition(&chunkPos);
			if (sourceObj && sourceObj->isAboveTerrain())
			{
				PhysicsBehavior* physics = obj->getPhysics();
				if (physics)
					physics->setAllowToFall(true);
			}	

      //Lorenzen sez:
      //Since the sneak attack is a structure created with an ocl, it bypasses a lot of the
      //goodness that it would have gotten from dozerAI::build( the normal way to make structures )
      // but, since it is a building... lets stamp it down in the pathfind map, here.
      if ( obj->isKindOf( KINDOF_STRUCTURE ) )
      {
	      // Flatten the terrain underneath the object, then adjust to the flattened height. jba.
	      TheTerrainLogic->flattenTerrain(obj);
	      Coord3D adjustedPos = *obj->getPosition();
	      adjustedPos.z = TheTerrainLogic->getGroundHeight(pos->x, pos->y);
	      obj->setPosition(&adjustedPos);
	      // Note - very important that we add to map AFTER we flatten terrain. jba.
	      TheAI->pathfinder()->addObjectToPathfindMap( obj );

      }







		}

		if( BitTest( m_disposition, ON_GROUND_ALIGNED ) )
		{
			chunkPos.z = 99999.0f;
			PathfindLayerEnum layer = TheTerrainLogic->getHighestLayerForDestination(&chunkPos);
			obj->setOrientation(GameLogicRandomValueReal(0.0f, 2 * PI));
			chunkPos.z = TheTerrainLogic->getLayerHeight( chunkPos.x, chunkPos.y, layer );
			// ensure we are slightly above the bridge, to account for fudge & sloppy art
			if (layer != LAYER_GROUND)
				chunkPos.z += 1.0f;
			obj->setLayer(layer);
			obj->setPosition(&chunkPos);
		}

		if( BitTest( m_disposition, SEND_IT_OUT ) )
		{
			obj->setOrientation(GameLogicRandomValueReal(0.0f, 2 * PI));
			chunkPos.z = TheTerrainLogic->getGroundHeight( chunkPos.x, chunkPos.y );
			obj->setPosition(&chunkPos);
			PhysicsBehavior* objUp = obj->getPhysics();
			if (objUp)
			{

				if (!m_nameAreObjects)
					objUp->setMass( m_mass );

				objUp->setExtraFriction(m_extraFriction);

				Coord3D force;
				Real horizForce = 4.0f * m_dispositionIntensity;		// 2
				force.x = GameLogicRandomValueReal( -horizForce, horizForce );
				force.y = GameLogicRandomValueReal( -horizForce, horizForce );
				force.z = 0;

				objUp->applyForce(&force);
				if (m_orientInForceDirection)
					orientation = atan2(force.y, force.x);

			}
		}

		if( BitTest( m_disposition, SEND_IT_FLYING | SEND_IT_UP | RANDOM_FORCE ) )
		{
			if (mtx)
			{
				DUMPMATRIX3D(mtx);
				obj->setTransformMatrix(mtx);
			}
			obj->setPosition(&chunkPos);
			DUMPCOORD3D(&chunkPos);
			PhysicsBehavior* objUp = obj->getPhysics();
			if (objUp)
			{

				if (!m_nameAreObjects)
				{
					DUMPREAL(m_mass);
					objUp->setMass( m_mass );
				}
				DEBUG_ASSERTCRASH(objUp->getMass() > 0.0f, ("Zero masses are not allowed for obj!\n"));

				objUp->setExtraBounciness(m_extraBounciness);
				objUp->setExtraFriction(m_extraFriction);
				objUp->setAllowBouncing(true);
				objUp->setBounceSound(&m_bounceSound);
				DUMPREAL(m_extraBounciness);
				DUMPREAL(m_extraFriction);
				
				// if omitted from INI, calc it based on intensity.
				Real spinRate		= m_spinRate >= 0.0f ? m_spinRate : (PI/32.0f) * m_dispositionIntensity;

				// Treat these as overrides.
				Real yawRate		= m_yawRate		>= 0.0f ? m_yawRate		: spinRate;
				Real rollRate		= m_rollRate	>= 0.0f ? m_rollRate	: spinRate;
				Real pitchRate	= m_pitchRate >= 0.0f ? m_pitchRate : spinRate;

				DUMPREAL(spinRate);
				DUMPREAL(yawRate);
				DUMPREAL(rollRate);
				DUMPREAL(pitchRate);
				
				Real yaw = GameLogicRandomValueReal( -yawRate, yawRate );
				Real roll = GameLogicRandomValueReal( -rollRate, rollRate );
				Real pitch = GameLogicRandomValueReal( -pitchRate, pitchRate );
				DUMPREAL(yaw);
				DUMPREAL(roll);
				DUMPREAL(pitch);

				Coord3D force;
				if( BitTest( m_disposition, SEND_IT_FLYING ) )
				{
					Real horizForce = 4.0f * m_dispositionIntensity;		// 2
					Real vertForce = 3.0f * m_dispositionIntensity;		// 3
					force.x = GameLogicRandomValueReal( -horizForce, horizForce );
					force.y = GameLogicRandomValueReal( -horizForce, horizForce );
					force.z = GameLogicRandomValueReal( vertForce * 0.33f, vertForce );
					DUMPREAL(horizForce);
					DUMPREAL(vertForce);
					DUMPCOORD3D(&force);
				}
				else if (BitTest(m_disposition, SEND_IT_UP) )
				{
					Real horizForce = 2.0f * m_dispositionIntensity;
					Real vertForce = 4.0f * m_dispositionIntensity;	
					
					force.x = GameLogicRandomValueReal( -horizForce, horizForce );
					force.y = GameLogicRandomValueReal( -horizForce, horizForce );
					force.z = GameLogicRandomValueReal( vertForce * 0.75f, vertForce );
					DUMPREAL(horizForce);
					DUMPREAL(vertForce);
					DUMPCOORD3D(&force);
				}
				else 
				{
					calcRandomForce(m_minMag, m_maxMag, m_minPitch, m_maxPitch, &force);
					DUMPREAL(m_minMag);
					DUMPREAL(m_maxMag);
					DUMPREAL(m_minPitch);
					DUMPREAL(m_maxPitch);
					DUMPCOORD3D(&force);
				}
				objUp->applyForce(&force);
				if (m_orientInForceDirection)
				{
					orientation = atan2(force.y, force.x);
				}
				DUMPREAL(orientation);
				objUp->setAngles(orientation, 0, 0);
				objUp->setYawRate(yaw);
				objUp->setRollRate(roll);
				objUp->setPitchRate(pitch);
				DUMPCOORD3D(objUp->getAcceleration());
				DUMPCOORD3D(objUp->getVelocity());
				DUMPMATRIX3D(obj->getTransformMatrix());

			}
		}
		if( BitTest( m_disposition, WHIRLING ) )
		{
			PhysicsBehavior* objUp = obj->getPhysics();
			if (objUp)
			{
				Real yaw = GameLogicRandomValueReal( -m_dispositionIntensity, m_dispositionIntensity );
				Real roll = GameLogicRandomValueReal( -m_dispositionIntensity, m_dispositionIntensity );
				Real pitch = GameLogicRandomValueReal( -m_dispositionIntensity, m_dispositionIntensity );

				objUp->setYawRate(yaw);
				objUp->setRollRate(roll);
				objUp->setPitchRate(pitch);
			}
		}
		
		if( BitTest( m_disposition, FLOATING ) )
		{
			static NameKeyType key = NAMEKEY( "FloatUpdate" );
			FloatUpdate *floatUpdate = (FloatUpdate *)obj->findUpdateModule( key );

			if( floatUpdate )
				floatUpdate->setEnabled( TRUE );

		}

		if( m_containInsideSourceObject )
		{
			// The Obj has been totally made, so stuff it inside ourselves if desired.
			if( sourceObj->getContain()  &&  sourceObj->getContain()->isValidContainerFor(obj, TRUE))
			{
				sourceObj->getContain()->addToContain( obj );

				// Need to hide if they are hidden.
				if( sourceObj->getDrawable() && obj->getDrawable() && sourceObj->getDrawable()->isDrawableEffectivelyHidden() )
					obj->getDrawable()->setDrawableHidden( TRUE );
			}
			else
			{
				DEBUG_ASSERTCRASH(FALSE,("A OCL with ContainInsideSourceObject failed the contain and is killing the new object."));
				// If we fail to contain it, we can't just leave it.  Stillborn it.
				TheGameLogic->destroyObject(obj);
			}
		}
    


    if ( m_diesOnBadLand && obj )
    {
	    // if we land in the water, we die. alas.
	    const Coord3D* riderPos = obj->getPosition();
	    Real waterZ, terrainZ;
	    if (TheTerrainLogic->isUnderwater(riderPos->x, riderPos->y, &waterZ, &terrainZ)
			    && riderPos->z <= waterZ + 10.0f
			    && obj->getLayer() == LAYER_GROUND)
	    {
		    // don't call kill(); do it manually, so we can specify DEATH_FLOODED
		    DamageInfo damageInfo;
		    damageInfo.in.m_damageType = DAMAGE_WATER;	// use this instead of UNRESISTABLE so we don't get a dusty damage effect
		    damageInfo.in.m_deathType = DEATH_FLOODED;
		    damageInfo.in.m_sourceID = INVALID_ID;
		    damageInfo.in.m_amount = HUGE_DAMAGE_AMOUNT;
		    obj->attemptDamage( &damageInfo );
	    }
	    
	    // Kill if materialized on impassable ground
	    Int cellX = REAL_TO_INT( obj->getPosition()->x / PATHFIND_CELL_SIZE );
	    Int cellY = REAL_TO_INT( obj->getPosition()->y / PATHFIND_CELL_SIZE );
	    
	    PathfindCell* cell = TheAI->pathfinder()->getCell( obj->getLayer(), cellX, cellY );
	    PathfindCell::CellType cellType = cell ? cell->getType() : PathfindCell::CELL_IMPASSABLE;
	    
	    // If we land outside the map, we die too.  
	    // Otherwise we exist outside the PartitionManger like a cheater.
	  if( obj->isOffMap() 
      || (cellType == PathfindCell::CELL_CLIFF) 
      || (cellType == PathfindCell::CELL_WATER) 
      || (cellType == PathfindCell::CELL_IMPASSABLE) )
	    {
		    // We are sorry, for reasons beyond our control, we are experiencing technical difficulties. Please die.
		    obj->kill();
	    }

  // Note: for future enhancement of this feature, we should test the object against the cell type he is on,
  // using obj->getAI()->hasLocomotorForSurface( __ ). We cshould not assume here that the object can not 
  // find happiness on cliffs or water or whatever.


    }




	}

	Object* reallyCreate(const Coord3D *pos, const Matrix3D *mtx, Real orientation, const Object *sourceObj, UnsignedInt lifetimeFrames ) const
	{
		static const ThingTemplate* debrisTemplate = TheThingFactory->findTemplate("GenericDebris");

		if (m_names.size() <= 0)
			return NULL;

		if (m_requiresLivePlayer && (!sourceObj || !sourceObj->getControllingPlayer() || !sourceObj->getControllingPlayer()->isPlayerActive()))
			return NULL; // don't spawn useful objects for dead players.  Avoid the zombie units from Yuri's.

		// Object type debris might need this information to process visual UpgradeModules.
		Team *debrisOwner = ThePlayerList->getNeutralPlayer() ? ThePlayerList->getNeutralPlayer()->getDefaultTeam() : NULL;

		if( sourceObj && sourceObj->getControllingPlayer() )
			debrisOwner = sourceObj->getControllingPlayer()->getDefaultTeam();
		
		Object* container = NULL;
		Object *firstObject = NULL;
		if (!m_putInContainer.isEmpty())
		{
			const ThingTemplate* containerTmpl = TheThingFactory->findTemplate(m_putInContainer);
			if (containerTmpl)
			{
				container = TheThingFactory->newObject( containerTmpl, debrisOwner );
				if( !container )
				{
					DEBUG_CRASH( ("OCL::reallyCreate() failed to create container %s.", m_putInContainer.str() ) );
					return firstObject;
				}
				firstObject = container;
				container->setProducer(sourceObj);
			}
		}


		for (Int nn = 0; nn < m_debrisToGenerate; nn++)
		{
			Int pick = GameLogicRandomValue(0, m_names.size() - 1);

			const ThingTemplate* thingTemplate;
			if (m_nameAreObjects)
				thingTemplate = TheThingFactory->findTemplate(m_names[pick]);
			else
			{	//this is using the generic debris type so it's probably safe to
				//remove if requested by the GameLOD manager.
				if (TheGameLODManager->isDebrisSkipped())
					continue;

				thingTemplate = debrisTemplate;
			}
			DEBUG_ASSERTCRASH(thingTemplate, ("Object %s not found\n",m_names[pick].str()));
			if (!thingTemplate)
				continue;

			Object *debris = TheThingFactory->newObject( thingTemplate, debrisOwner );
			if( !debris )
			{
				DEBUG_CRASH( ("OCL::reallyCreate() failed to create debris %s.", thingTemplate->getName().str() ) );
				return firstObject;
			}
			if( !firstObject )
			{
				firstObject = debris;
			}
			debris->setProducer(sourceObj);
			if (m_preserveLayer && sourceObj != NULL && container == NULL)
			{
				PathfindLayerEnum layer = sourceObj->getLayer();
				if (layer != LAYER_GROUND)
					debris->setLayer(layer);
			}

			if (container != NULL && container->getContain() != NULL && container->getContain()->isValidContainerFor(debris, true))
				container->getContain()->addToContain(debris);

			// if we want the objects being created to appear in a spread formation
			// PLEASE NOTE --> if/when the object placement logic is modified so that
			// objects that are placed in the same location are no longer placed in a
			// diagonal line but rather in random locations nearby, this logic will no
			// longer be necessary and can be taken out -- amit
			if (m_spreadFormation) 
			{
				Coord3D resultPos;
				FindPositionOptions fpOptions;
				fpOptions.minRadius = GameLogicRandomValueReal(m_minDistanceAFormation, m_minDistanceBFormation);
				fpOptions.maxRadius = m_maxDistanceFormation;
				fpOptions.flags = FPF_USE_HIGHEST_LAYER;
				ThePartitionManager->findPositionAround(pos, &fpOptions, &resultPos);
				doStuffToObj( debris, m_names[pick], &resultPos, mtx, orientation, sourceObj, lifetimeFrames );
			}
			else 
			{
				// do stuff to contained objects too
				doStuffToObj( debris, m_names[pick], pos, mtx, orientation, sourceObj, lifetimeFrames );
			}

			if (m_fadeIn) 
			{
				AudioEventRTS fadeAudioEvent(m_fadeSoundName);
				fadeAudioEvent.setObjectID(sourceObj->getID());
				TheAudio->addAudioEvent(&fadeAudioEvent);
				debris->getDrawable()->fadeIn(m_fadeFrames);
			}

			if (m_fadeOut) 
			{
				AudioEventRTS fadeAudioEvent(m_fadeSoundName);
				fadeAudioEvent.setObjectID(sourceObj->getID());
				TheAudio->addAudioEvent(&fadeAudioEvent);
				debris->getDrawable()->fadeOut(m_fadeFrames);
			}
		}

		if (container)
			doStuffToObj( container, AsciiString::TheEmptyString, pos, mtx, orientation, sourceObj, lifetimeFrames );
    
		return firstObject;
	}

	static void parseDebrisObjectNames( INI* ini, void *instance, void *store, const void* /*userData*/ )
	{
		GenericObjectCreationNugget* debrisNugget = (GenericObjectCreationNugget*)instance;
		for (const char* debrisName = ini->getNextToken(); debrisName; debrisName = ini->getNextTokenOrNull())
		{
			if (TheGlobalData->m_preloadAssets)
				debrisModelNamesGlobalHack.push_back(debrisName);
			debrisNugget->m_names.push_back(AsciiString(debrisName));
			debrisName = ini->getNextTokenOrNull();
		}
	}

private:
	struct AnimSet
	{
		AsciiString								m_animInitial;
		AsciiString								m_animFlying;
		AsciiString								m_animFinal;
	};
	std::vector<AsciiString>	m_names;
	AsciiString								m_putInContainer;
	std::vector<AnimSet>			m_animSets;
	const FXList*							m_fxFinal;
	AsciiString								m_particleSysName;
	Int												m_debrisToGenerate;
	Real											m_mass;
	Real											m_extraBounciness;
	Real											m_extraFriction;
	Coord3D										m_offset;
	DebrisDisposition					m_disposition;
	Real											m_dispositionIntensity;
	Real											m_spinRate;
	Real											m_yawRate;
	Real											m_rollRate;
	Real											m_pitchRate;
	Real											m_minMag, m_maxMag;
	Real											m_minPitch, m_maxPitch;
	UnsignedInt								m_minFrames, m_maxFrames;
	ShadowType								m_shadowType;
	StaticGameLODLevel				m_minLODRequired;
	UnsignedInt								m_invulnerableTime;
	Real											m_minHealth;
	Real											m_maxHealth;
	UnsignedInt								m_fadeFrames;
	AsciiString								m_fadeSoundName;
	Real											m_minDistanceAFormation;
	Real											m_minDistanceBFormation;
	Real											m_maxDistanceFormation;
	Int												m_objectCount; // how many objects will there be?
	AudioEventRTS							m_bounceSound;
	Bool											m_requiresLivePlayer;
	Bool											m_containInsideSourceObject; ///< The created stuff will be added to the Conatin module of the SourceObject
	Bool											m_preserveLayer;
	Bool											m_nameAreObjects;
	Bool											m_okToChangeModelColor;
	Bool											m_orientInForceDirection;
	Bool											m_spreadFormation;
	Bool											m_fadeIn;
	Bool											m_fadeOut;
	Bool											m_ignorePrimaryObstacle;
	Bool											m_inheritsVeterancy;
  Bool                      m_diesOnBadLand;
	Bool											m_skipIfSignificantlyAirborne;

};  
EMPTY_DTOR(GenericObjectCreationNugget)

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Keep the donor callback table emitted: existing matched callbacks depend on
// its references. This is not the BFME2 table at 0x00BE07F0.


//-------------------------------------------------------------------------------------------------
// Retail table at RVA 0x007E07F0: five named callbacks and a terminator.
// Names, order and callback addresses are read from retail; the donor's
// DeliverPayload entry is absent. Each callback has its own matched owner.
extern const FieldParse TheObjectCreationListFieldParse[] =
{
    { "CreateObject", GenericObjectCreationNugget::parseObject, 0, 0 },
    { "CreateDebris", GenericObjectCreationNugget::parseDebris, 0, 0 },
    { "ApplyRandomForce", ApplyRandomForceNugget::parse, 0, 0 },
    { "FireWeapon", FireWeaponNugget::parse, 0, 0 },
    { "Attack", AttackNugget::parse, 0, 0 },
    { NULL, NULL, 0, 0 }
};

// ?clear@ObjectCreationList@@ present-unmatched
void ObjectCreationList::clear()
{
	// do NOT delete the nuggets -- they're owned by the Store.
	m_nuggets.clear();
}

//-------------------------------------------------------------------------------------------------
void ObjectCreationList::addObjectCreationNugget(ObjectCreationNugget* nugget)
{
	m_nuggets.push_back(nugget);
	TheObjectCreationListStore->addObjectCreationNugget(nugget);
}

//-------------------------------------------------------------------------------------------------
// ?createInternal@ObjectCreationList@@ present-unmatched
Object* ObjectCreationList::createInternal( const Object* primaryObj, const Coord3D *primary, const Coord3D* secondary, Bool createOwner, UnsignedInt lifetimeFrames ) const
{
	DEBUG_ASSERTCRASH(primaryObj != NULL, ("You should always call OCLs with a non-null primary Obj, even for positional calls, to get team ownership right"));
	Object *theFirstObject = NULL;
	for (ObjectCreationNuggetVector::const_iterator i = m_nuggets.begin(); i != m_nuggets.end(); ++i)
	{
		Object *curObj = (*i)->create( primaryObj, primary, secondary, createOwner, lifetimeFrames );
		if (theFirstObject==NULL) {
			theFirstObject = curObj;
		}
	}
	return theFirstObject;
}

//-------------------------------------------------------------------------------------------------
// ?createInternal@ObjectCreationList@@ present-unmatched
Object* ObjectCreationList::createInternal( const Object* primaryObj, const Coord3D *primary, const Coord3D* secondary, Real angle, UnsignedInt lifetimeFrames ) const
{
	DEBUG_ASSERTCRASH(primaryObj != NULL, ("You should always call OCLs with a non-null primary Obj, even for positional calls, to get team ownership right"));
	Object *theFirstObject = NULL;
	for (ObjectCreationNuggetVector::const_iterator i = m_nuggets.begin(); i != m_nuggets.end(); ++i)
	{
		Object *curObj =  (*i)->create( primaryObj, primary, secondary, angle, lifetimeFrames );
		if (theFirstObject==NULL) {
			theFirstObject = curObj;
		}
	}
	return theFirstObject;
}

//-------------------------------------------------------------------------------------------------
// ?createInternal@ObjectCreationList@@ present-unmatched
Object* ObjectCreationList::createInternal( const Object* primary, const Object* secondary, UnsignedInt lifetimeFrames ) const
{
	DEBUG_ASSERTCRASH(primary != NULL, ("You should always call OCLs with a non-null primary Obj, even for positional calls, to get team ownership right"));
	Object *theFirstObject = NULL;
	for (ObjectCreationNuggetVector::const_iterator i = m_nuggets.begin(); i != m_nuggets.end(); ++i)
	{
		Object *curObj =  (*i)->create( primary, secondary, lifetimeFrames );
		if (theFirstObject==NULL) {
			theFirstObject = curObj;
		}
	}
	return theFirstObject;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// The complete constructor and destructor are defined by the retail owner units.

// Native IAT 0x00BBA518 is msvcr71.dll's _strcmpi import.
extern "C" int (__cdecl *_imp___strcmpi)(const char *, const char *);
const ObjectCreationList *ObjectCreationListStore::findObjectCreationList(const char* name) const
{
	if (_imp___strcmpi(name, "None") == 0)
		return NULL;

	NameKeyType key = NAMEKEY(name);
	// BFME2 places the map four bytes later and stores list pointers.
	const ObjectCreationListMap &lists = *reinterpret_cast<const ObjectCreationListMap *>(
		reinterpret_cast<const char *>(this) + 0x0c);
	ObjectCreationListMap::const_iterator it = lists.find(key);
	if (it == lists.end())
	{
		return NULL;
	}
	else
	{
		return *reinterpret_cast<const ObjectCreationList *const *>(&(*it).second);
	}
}

//-------------------------------------------------------------------------------------------------
void ObjectCreationListStore::addObjectCreationNugget(ObjectCreationNugget* nugget)
{
	m_nuggets.push_back(nugget);
}

//-------------------------------------------------------------------------------------------------

// Target parser 0x001F0C0B..0x001F0D04; named by WB 0x00B092E0 and
// reached by the retail ObjectCreationList INI dispatch at 0x007AD4CC.
// The owned constructor at 0x001F073A initializes 20 bytes: vector at +0,
// override flag at +0x0C and AsciiString at +0x10. Keep its existing name.
struct Rva001F073ACtor { Rva001F073ACtor(AsciiString *s); char bytes[20]; };
// Target-proven offsets. The template element spellings are ABI call views;
// the retired values are list pointers, not independently proven nuggets.
struct OclStoreParseView {
	char prefix[12];
	_STL::map<int, int> m_map0C;
	_STL::vector<ObjectCreationNugget *> m_vec18;
};
static __forceinline OclStoreParseView *oclParseStore() {
	return reinterpret_cast<OclStoreParseView *>(TheObjectCreationListStore);
}
void ObjectCreationListStore::parseObjectCreationListDefinition(INI *ini)
{
	const char *token = ini->getNextToken(0);
	NameKeyType key = TheNameKeyGenerator->nameToKey(token);
	int keySlot = key;
	_STL::map<int, int> *map = &oclParseStore()->m_map0C;
	_STL::map<int, int>::iterator found = map->find(keySlot);
	// The donor INI layout differs; retail reads load type at +8.
	if (found != map->end() && *reinterpret_cast<const int *>(reinterpret_cast<const char *>(ini) + 8) == 5)
	{
		_STL::map<int, void *>::iterator eit = (_STL::map<int, void *>::iterator &)found;
		((_STL::map<int, void *> *)map)->erase(eit);
		// Preserve retail's post-erase read order, also seen in WorldBuilder.
		ObjectCreationNugget *old = (ObjectCreationNugget *)found->second;
		if (old)
		{
			oclParseStore()->m_vec18.push_back(old);
			*(char *)((char *)old + 0x0C) = 1;
		}
	}
	// MSVC temporary lifetime supplies the conditional EH cleanup in retail.
	Rva001F073ACtor *result = new Rva001F073ACtor(&AsciiString(token));
	oclParseStore()->m_map0C.operator[](keySlot) = (int)result;
	ini->initFromINI(result, TheObjectCreationListFieldParse);
}

//-------------------------------------------------------------------------------------------------
/*static*/ void INI::parseObjectCreationListDefinition(INI *ini)
{
	ObjectCreationListStore::parseObjectCreationListDefinition(ini);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?findObjectCreationList@ObjectCreationListStore@@QAEPBVObjectCreationList@@PBD@Z=?findObjectCreationList@ObjectCreationListStore@@QBEPBVObjectCreationList@@PBD@Z")
// Retain the already-rowed default constructor formerly emitted by the donor
// parser's by-value map. Retail's replacement parser instead stores pointers.
template ObjectCreationList& _STL::map<NameKeyType, ObjectCreationList>::operator[](const NameKeyType&);

// parseObject/parseDebris are rowed in GenericObjectCreationNuggetParseObject.cpp;
// parseDebris's table used to be what emitted this unit's rowed parseAnimSet
// (and with it the AnimSet vector helpers), so reference it here.
// ?bfmeAnchorParseAnimSet absent-from-retail
void *bfmeAnchorParseAnimSet()
{
	return (void *)&GenericObjectCreationNugget::parseAnimSet;
}

// Native 5F8653/5F8752/5F8855 use the two-handle holder destroyed at
// 5F8447, not the Zero Hour DeliverPayloadNugget payload. Preserve the
// existing native holder view; its original application name is unknown.
struct Rva005F8447 { char m_storage[8]; ~Rva005F8447(); };
class Rva004C5DD0;
struct Rva004C5DD0Pair;
void __cdecl Rva004F6A52Assign(Rva004C5DD0 *, const Rva004C5DD0Pair *);
void __cdecl Rva005F85C8Destroy(Rva005F8447 *, Rva005F8447 *);
namespace _STL {
template <> __declspec(dllimport) __forceinline void _Construct<Rva005F8447, Rva005F8447>(Rva005F8447 *p, const Rva005F8447 &v)
{ Rva004F6A52Assign((Rva004C5DD0 *)p, (const Rva004C5DD0Pair *)&v); }
template <> __declspec(dllimport) __forceinline void _Destroy<Rva005F8447 *>(Rva005F8447 *f, Rva005F8447 *l)
{ Rva005F85C8Destroy(f, l); }
template void vector<Rva005F8447>::_M_clear();
template void vector<Rva005F8447>::_M_insert_overflow(Rva005F8447 *, const Rva005F8447 &, const __false_type &, unsigned int, bool);
template void vector<Rva005F8447>::push_back(const Rva005F8447 &);
}
