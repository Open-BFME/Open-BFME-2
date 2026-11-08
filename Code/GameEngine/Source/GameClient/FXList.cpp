// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/FXList.cpp); this unit had no counterpart under Code/.
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

// FILE: FXList.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson, December 2001
// Desc:   FXList descriptions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
// BFME 2's GameClientRandomVariable (default constructor 0x000B4979, which the particle
// nugget's constructor runs) stands in place of Zero Hour's ClientRandomValue.h class.
#include "../../Include/GameClient/GameClientRandomVariableInlines.h"
#define _CLIENT_RANDOM_VALUE_H_
extern int GetGameClientRandomValue( int lo, int hi, char *file, int line );
extern float GetGameClientRandomValueReal( float lo, float hi, char *file, int line );
#define GameClientRandomValue( lo, hi ) GetGameClientRandomValue( lo, hi, __FILE__, __LINE__ )
#define GameClientRandomValueReal( lo, hi ) GetGameClientRandomValueReal( lo, hi, __FILE__, __LINE__ )
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "GameClient/FXList.h"

#include "Common/DrawModule.h"
#include "Common/GameAudio.h"
#include "Common/INI.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"

#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/TerrainLogic.h"
#include "GameClient/Display.h"
#include "GameClient/GameClient.h"
#include "GameClient/Drawable.h"
#include "GameLogic/PartitionManager.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
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
// Suppress this TU's non-retail copy of ?_M_insert@?$hashtable@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@W4NameKeyType@@U?$hash@W:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class FXList;
namespace _STL { template <> pair<NameKeyType const ,FXList> & hashtable<pair<NameKeyType const ,FXList>,NameKeyType,rts::hash<NameKeyType>,_Select1st<pair<NameKeyType const ,FXList> >,rts::equal_to<NameKeyType>,allocator<pair<NameKeyType const ,FXList> > >::_M_insert(pair<NameKeyType const ,FXList> const &); }
// Suppress this TU's non-retail copy of ?resize@?$hashtable@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@W4NameKeyType@@U?$hash@W4Na:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class FXList;
namespace _STL { template <> void hashtable<pair<NameKeyType const ,FXList>,NameKeyType,rts::hash<NameKeyType>,_Select1st<pair<NameKeyType const ,FXList> >,rts::equal_to<NameKeyType>,allocator<pair<NameKeyType const ,FXList> > >::resize(unsigned int); }
// Suppress this TU's non-retail copy of ?_M_next_size@?$hashtable@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@W4NameKeyType@@U?$has:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class FXList;
namespace _STL { template <> unsigned int hashtable<pair<NameKeyType const ,FXList>,NameKeyType,rts::hash<NameKeyType>,_Select1st<pair<NameKeyType const ,FXList> >,rts::equal_to<NameKeyType>,allocator<pair<NameKeyType const ,FXList> > >::_M_next_size(unsigned int) const; }
// Suppress this TU's non-retail copy of ?_M_new_node@?$hashtable@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@W4NameKeyType@@U?$hash:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class FXList;
namespace _STL { template <> _Hashtable_node<pair<NameKeyType const ,FXList> > * hashtable<pair<NameKeyType const ,FXList>,NameKeyType,rts::hash<NameKeyType>,_Select1st<pair<NameKeyType const ,FXList> >,rts::equal_to<NameKeyType>,allocator<pair<NameKeyType const ,FXList> > >::_M_new_node(pair<NameKeyType const ,FXList> const &); }
// Suppress this TU's non-retail copy of ??$_Construct@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBW4Nam:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class FXList;
namespace _STL { template <> void _Construct<pair<NameKeyType const ,FXList>,pair<NameKeyType const ,FXList> >(pair<NameKeyType const ,FXList> *,pair<NameKeyType const ,FXList> const &); }
// Suppress this TU's non-retail copy of ??0?$_List_base@PAVFXNugget@@V?$allocator@PAVFXNugget@@@_STL@@@_STL@@QAE@ABV?$allocator@PA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class FXNugget;
namespace _STL { template <> _List_base<FXNugget *,allocator<FXNugget *> >::_List_base(allocator<FXNugget *> const &); }
// Suppress this TU's non-retail copy of ??0?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@QAE@ABU01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class FXList;
namespace _STL { template <> pair<NameKeyType const ,FXList>::pair(pair<NameKeyType const ,FXList> const &); }

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

FXListStore *TheFXListStore = NULL;					///< the FXList store definition

//-------------------------------------------------------------------------------------------------
// Zero Hour's helper is static; here it is select-any: DynamicDecalFXNuggetDoFXPos.cpp calls it,
// and ParticleSystemFXNuggetReallyDoFX.cpp carries a visible copy for its caller's frame layout.
__declspec(noinline) inline void adjustVector(Coord3D *vec, const Matrix3D* mtx)
{
	if (mtx)
	{
		Vector3 vectmp;
		vectmp.X = vec->x;
		vectmp.Y = vec->y;
		vectmp.Z = vec->z;
		vectmp = mtx->Rotate_Vector(vectmp);
		// Coord3D and Vector3 are the witnessed 12-byte float triplets.
		// Preserve the aggregate copy from the returned rotation temporary.
		*vec = *reinterpret_cast<const Coord3D *>(&vectmp);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE CLASSES ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// ?doFXObj@FXNugget@@ present-unmatched
void FXNugget::doFXObj(const Object* primary, const Object* secondary) const
{
	const Coord3D* p = primary ? primary->getPosition() : NULL;
	const Matrix3D* mtx = primary ? primary->getTransformMatrix() : NULL;
	const Real speed = 0.0f;	// yes, that's right -- NOT the object's speed.
	const Coord3D* s = secondary ? secondary->getPosition() : NULL;
	doFXPos(p, mtx, speed, s);
}

//-------------------------------------------------------------------------------------------------
class __declspec(novtable) SoundFXNugget : public FXNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(SoundFXNugget, "SoundFXNugget")		
	
public:

	virtual void doFXPos(const Coord3D *primary, const Matrix3D* /*primaryMtx*/, const Real /*primarySpeed*/, const Coord3D * /*secondary*/, const Real /*overrideRadius*/ ) const
	{
		AudioEventRTS sound(m_soundName);
		
		if (primary) 
		{
			sound.setPosition(primary);
		}

		TheAudio->addAudioEvent(&sound);
	}

	// Defined out of line in SoundFXNuggetSlots.cpp (retail 0x001E012E): the inline ZH
	// port copy compiled differently and would be a conflicting COMDAT definition.
	virtual void doFXObj(const Object* primary, const Object* secondary = NULL) const;


	static void parse(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
	{
		static const FieldParse myFieldParse[] = 
		{
			{ "Name",									INI::parseAsciiString,	NULL, offsetof( SoundFXNugget, m_soundName ) },
			{ 0, 0, 0, 0 }
		};

		SoundFXNugget* nugget = newInstance(SoundFXNugget);	
		ini->initFromINI(nugget, myFieldParse);
		((FXList*)instance)->addFXNugget(nugget);
	}

private:
	AsciiString		m_soundName;
public:
	SoundFXNugget();
};  
EMPTY_DTOR(SoundFXNugget)

//-------------------------------------------------------------------------------------------------
static Real calcDist(const Coord3D& src, const Coord3D& dst)
{
  Real dx = dst.x - src.x;
  Real dy = dst.y - src.y;
  Real dz = dst.z - src.z;
  return sqrt(dx*dx + dy*dy + dz*dz);
}

//-------------------------------------------------------------------------------------------------
class TracerFXNugget : public FXNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(TracerFXNugget, "TracerFXNugget")		
public:

	TracerFXNugget()
	{
		m_tracerName.set("GenericTracer");
    m_boneName.clear();
    m_speed = 0.0f; // means "use passed-in speed"
    m_decayAt = 1.0f;
		m_length = 10.0f;
		m_width = 1.0f;
		m_color.red = m_color.green = m_color.blue = 1.0f;
		m_probability = 1.0f;
	}

	virtual void doFXPos(const Coord3D *primary, const Matrix3D* primaryMtx, const Real primarySpeed, const Coord3D *secondary, const Real /*overrideRadius*/ ) const
	{
		if (m_probability <= GameClientRandomValueReal(0, 1))
			return;

		if (primary && secondary)
		{
			Drawable *tracer = TheThingFactory->newDrawable(TheThingFactory->findTemplate(m_tracerName));
			if(!tracer)
				return;
			
			//Kris -- Redid this section Sept 18, 2002
			//Calculate tracer orientations to face from primary to secondary position. This
			//should be the direction that the projectile is being fired towards. It doesn't make
			//sense that the old stuff made use of the muzzle fx bone orientation (because it's a 
			//subobject). It had other problems because of elevation variations the tracers would
			//stay on the ground.
			//tracer->setTransformMatrix(primaryMtx);
			Matrix3D tracerMtx;
			Vector3 pos( primary->x, primary->y, primary->z );
			Vector3 dir( secondary->x - primary->x, secondary->y - primary->y, secondary->z - primary->z );
			dir.Normalize(); //This is fantastically crucial for calling buildTransformMatrix!!!!!
			tracerMtx.buildTransformMatrix( pos, dir );
			tracer->setTransformMatrix( &tracerMtx );
			tracer->setPosition(primary);

			Real speed = m_speed;
			if (speed == 0.0f)
			{
				speed = primarySpeed;
			}

			TracerDrawInterface* tdi = NULL;
			for (DrawModule** drawModule = tracer->getDrawModules(); *drawModule; ++drawModule)
			{
				if ((tdi = (*drawModule)->getTracerDrawInterface()) != NULL)
				{
					tdi->setTracerParms(speed, m_length, m_width, m_color, 1.0f);
				}
			}

			// estimate how long it will take us to get to the destination
			Real dist = calcDist(*primary, *secondary) - m_length;
			Real frames = (dist >= 0.0f && speed >= 0.0f) ? (dist / speed) : 1;
			Int framesAdjusted = REAL_TO_INT_CEIL(frames * m_decayAt);
			tracer->setExpirationDate(TheGameLogic->getFrame() + framesAdjusted);
		}
		else
		{
			DEBUG_CRASH(("You must have a primary and secondary source for this effect"));
		}
	}

	static void parse(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
	{
		static const FieldParse myFieldParse[] = 
		{
			{ "TracerName",			INI::parseAsciiString,			NULL, offsetof( TracerFXNugget, m_tracerName ) },
			{ "BoneName",				INI::parseAsciiString,			NULL, offsetof( TracerFXNugget, m_boneName ) },
      { "Speed",          INI::parseVelocityReal,     NULL, offsetof( TracerFXNugget, m_speed ) },
      { "DecayAt",        INI::parseReal,             NULL, offsetof( TracerFXNugget, m_decayAt ) },
      { "Length",					INI::parseReal,             NULL, offsetof( TracerFXNugget, m_length ) },
      { "Width",					INI::parseReal,             NULL, offsetof( TracerFXNugget, m_width ) },
      { "Color",					INI::parseRGBColor,					NULL, offsetof( TracerFXNugget, m_color ) },
      { "Probability",		INI::parseReal,             NULL, offsetof( TracerFXNugget, m_probability ) },
			{ 0, 0, 0, 0 }
		};

		TracerFXNugget* nugget = newInstance( TracerFXNugget );	
		ini->initFromINI(nugget, myFieldParse);
		((FXList*)instance)->addFXNugget(nugget);
	}

private:
	AsciiString			m_tracerName;
  AsciiString     m_boneName;
  Real            m_speed;
  Real            m_decayAt;
	Real						m_length;
	Real						m_width;
	RGBColor				m_color;
	Real						m_probability;
};  
EMPTY_DTOR(TracerFXNugget)

//-------------------------------------------------------------------------------------------------
class __declspec(novtable) RayEffectFXNugget : public FXNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(RayEffectFXNugget, "RayEffectFXNugget")		
public:

	RayEffectFXNugget();

	virtual void doFXPos(const Coord3D *primary, const Matrix3D* /*primaryMtx*/, const Real /*primarySpeed*/, const Coord3D * secondary, const Real /*overrideRadius*/ ) const
	{
		const ThingTemplate* thingTemplate = TheThingFactory->findTemplate(m_templateName);
		DEBUG_ASSERTCRASH(thingTemplate, ("RayEffect %s not found\n",m_templateName.str()));
		if (primary && secondary && thingTemplate)
		{
			Coord3D sourcePos = *primary;
			sourcePos.x += m_primaryOffset.x;
			sourcePos.y += m_primaryOffset.y;
			sourcePos.z += m_primaryOffset.z;

			Coord3D targetPos = *secondary;
			targetPos.x += m_secondaryOffset.x;
			targetPos.y += m_secondaryOffset.y;
			targetPos.z += m_secondaryOffset.z;

			TheGameClient->createRayEffectByTemplate(&sourcePos, &targetPos, thingTemplate);
		}
		else
		{
			DEBUG_CRASH(("You must have a primary AND secondary source for this effect"));
		}
	}

	static void parse(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
	{
		static const FieldParse myFieldParse[] = 
		{
			{ "Name",									INI::parseAsciiString,			NULL, offsetof( RayEffectFXNugget, m_templateName ) },
			{ "PrimaryOffset",				INI::parseCoord3D,					NULL, offsetof( RayEffectFXNugget, m_primaryOffset ) },
			{ "SecondaryOffset",			INI::parseCoord3D,					NULL, offsetof( RayEffectFXNugget, m_secondaryOffset ) },
			{ 0, 0, 0, 0 }
		};

		RayEffectFXNugget* nugget = newInstance( RayEffectFXNugget ); 
		ini->initFromINI(nugget, myFieldParse);
		((FXList*)instance)->addFXNugget(nugget);
	}

private:
	AsciiString			m_templateName;
	Coord3D					m_primaryOffset;
	Coord3D					m_secondaryOffset;
};  
EMPTY_DTOR(RayEffectFXNugget)

//-------------------------------------------------------------------------------------------------
class LightPulseFXNugget : public FXNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(LightPulseFXNugget, "LightPulseFXNugget")		
public:

	LightPulseFXNugget();

	virtual void doFXObj(const Object* primary, const Object* /*secondary*/);

	virtual void doFXPos(const Coord3D *primary, const Matrix3D* /*primaryMtx*/, const Real /*primarySpeed*/, const Coord3D * /*secondary*/, const Real /*overrideRadius*/ ) const
	{
		if (primary)
		{
			TheDisplay->createLightPulse(primary, &m_color, 1, m_radius, m_increaseFrames, m_decreaseFrames);
		}
		else
		{
			DEBUG_CRASH(("You must have a primary source for this effect"));
		}
	}

	static void parse(INI *ini, void *instance, void* /*store*/, const void* /*userData*/);

private:
	RGBColor			m_color;
	Real					m_radius;
	Real					m_boundingCirclePct;
	UnsignedInt		m_increaseFrames;
	UnsignedInt		m_decreaseFrames;
};  
EMPTY_DTOR(LightPulseFXNugget)

//-------------------------------------------------------------------------------------------------
class ViewShakeFXNugget : public FXNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(ViewShakeFXNugget, "ViewShakeFXNugget")		
public:

	ViewShakeFXNugget();

	virtual void doFXPos(const Coord3D *primary, const Matrix3D* /*primaryMtx*/, const Real /*primarySpeed*/, const Coord3D * /*secondary*/, const Real /*overrideRadius*/ ) const
	{
		if (primary)
		{
			if (TheTacticalView)
				TheTacticalView->shake(primary, m_shake);
		}
		else
		{
			DEBUG_CRASH(("You must have a primary source for this effect"));
		}
	}

	static void parse(INI *ini, void *instance, void* /*store*/, const void* /*userData*/);

protected:
	static void parseShakeType( INI* ini, void *instance, void *store, const void* /*userData*/ )
	{
		static const LookupListRec shakeTypeNames[] = 
		{
			{ "SUBTLE", View::SHAKE_SUBTLE },
			{ "NORMAL", View::SHAKE_NORMAL },
			{ "STRONG", View::SHAKE_STRONG },
			{ "SEVERE", View::SHAKE_SEVERE },
			{ "CINE_EXTREME", View::SHAKE_CINE_EXTREME },
			{ "CINE_INSANE",  View::SHAKE_CINE_INSANE },
			{ 0, 0 }
		};
		*(Int *)store = INI::scanLookupList(ini->getNextToken(), shakeTypeNames);
	}

private:
	View::CameraShakeType m_shake;

};  
EMPTY_DTOR(ViewShakeFXNugget)

//-------------------------------------------------------------------------------------------------
class TerrainScorchFXNugget : public FXNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(TerrainScorchFXNugget, "TerrainScorchFXNugget")		
public:

	TerrainScorchFXNugget();

	virtual void doFXPos(const Coord3D *primary, const Matrix3D* /*primaryMtx*/, const Real /*primarySpeed*/, const Coord3D * /*secondary*/, const Real /*overrideRadius*/ ) const
	{
		if (primary)
		{
			Int scorch = m_scorch;
			if (scorch < 0)
			{
				scorch = GameClientRandomValue( SCORCH_1, SCORCH_4 );
			}
			TheGameClient->addScorch(primary, m_radius, (Scorches)scorch);
		}
		else
		{
			DEBUG_CRASH(("You must have a primary source for this effect"));
		}
	}

	static void parse(INI *ini, void *instance, void* /*store*/, const void* /*userData*/);

protected:

	static void parseScorchType( INI* ini, void *instance, void *store, const void* /*userData*/ )
	{
		static const LookupListRec scorchTypeNames[] = 
		{
			{ "SCORCH_1",				SCORCH_1 },
			{ "SCORCH_2",				SCORCH_2 },
			{ "SCORCH_3",				SCORCH_3 },
			{ "SCORCH_4",				SCORCH_4 },
			{ "SHADOW_SCORCH",	SHADOW_SCORCH },
			{ "RANDOM",					-1 },
			{ 0, 0 }
		};
		*(Int *)store = INI::scanLookupList(ini->getNextToken(), scorchTypeNames);
	}

private:
	Int		m_scorch;
	Real	m_radius;
};  
EMPTY_DTOR(TerrainScorchFXNugget)

//-------------------------------------------------------------------------------------------------
#include "../../Include/GameClient/Rva001DFEAABase.h"
// BFME 2's particle-system nugget (vftable 0x00BDD908): five slots, ??_G, doFXPos, doFXObj,
// slot 3 (rowed 0x001E0C77 under a placeholder) and the base's rva001DFF5D.
class ParticleSystemFXNugget : public Rva001DFEAABase
{
public:
	ParticleSystemFXNugget();
	virtual ~ParticleSystemFXNugget();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const;
	virtual void doFXObj(const Object* primary, const Object* secondary) const
	{
		if (primary)
		{
			if (m_ricochet && secondary)
			{
				// HERE WE MUST BUILD A MATRIX WHICH WILL ORIENT THE NEW PARTICLE SYSTEM TO FACE AWAY FROM THE SECONDARY OBJECT
				// THE RESULT SHOULD LOOK LIKE THE DIRECTION OF THE "ATTACK" IS CARRIED THROUGH LIKE A RICOCHET
				Real deltaX = primary->getPosition()->x - secondary->getPosition()->x;
				Real deltaY = primary->getPosition()->y - secondary->getPosition()->y;
				Real aimingAngle = atan2(deltaY, deltaX);
				Matrix3D aimingMatrix(1);
				aimingMatrix.Rotate_Z( aimingAngle );

				reallyDoFX(
					primary->getPosition(), &aimingMatrix, primary, secondary);
			}
			else
				// if we have an object, then adjust the offset and direction by the object's transformation
				// matrix, so that (say) an offset of +10 in the z axis "follows" the orientation of the object.
				reallyDoFX(
					primary->getPosition(), primary->getTransformMatrix(), primary, secondary);
		}
		else
		{
			DEBUG_CRASH(("You must have a primary source for this effect"));
		}
	}
	void reallyDoFX(const Coord3D *, const Matrix3D *, const Object *, const Object *) const;
	static void parse(INI *ini, void *instance, void *store, const void *userData);
private:
	AsciiString m_name; // +0x148
	int m_count; // +0x14C
	Coord3D m_offset; // +0x150
	GameClientRandomVariable m_radius; // +0x15C
	GameClientRandomVariable m_height; // +0x168
	GameClientRandomVariable m_delay; // +0x174
	float m_rotateX; // +0x180
	float m_rotateY; // +0x184
	float m_rotateZ; // +0x188
	bool m_orientToObject; // +0x18C
	bool m_attachToObject; // +0x18D
	unsigned char m_pad18E[2]; // +0x18E
	AsciiString m_attachToBone; // +0x190
	bool m_createAtGroundHeight; // +0x194
	bool m_ricochet; // +0x195
	unsigned char m_pad196[2]; // +0x196
	AsciiString m_createBoneOverride; // +0x198
	AsciiString m_targetBoneOverride; // +0x19C
	bool m_createBoneAtTarget; // +0x1A0
	unsigned char m_pad1A1[3]; // +0x1A1
	float m_targetCoeff; // +0x1A4
	int m_systemLife; // +0x1A8
	bool m_useTargetOffset; // +0x1AC
	bool m_setTargetMatrix; // +0x1AD
	bool m_onlyIfOnLand; // +0x1AE
	bool m_onlyIfOnWater; // +0x1AF
	Coord3D m_targetOffset; // +0x1B0
};

ParticleSystemFXNugget::ParticleSystemFXNugget()
{
	m_name.clear();
	m_count = 1;
	m_radius.setRange(0.0f, 0.0f, GameClientRandomVariable::CONSTANT);
	m_height.setRange(0.0f, 0.0f, GameClientRandomVariable::CONSTANT);
	m_delay.setRange(-1.0f, -1.0f, GameClientRandomVariable::CONSTANT);
	m_systemLife = -1;
	m_offset.x = m_offset.y = m_offset.z = 0.0f;
	m_orientToObject = false;
	m_attachToObject = false;
	m_createAtGroundHeight = false;
	m_rotateX = m_rotateY = m_rotateZ = 0.0f;
	m_nuggetType = 8;
	m_targetCoeff = 1.0f;
	m_createBoneAtTarget = false;
	m_useTargetOffset = false;
	m_targetOffset.x = m_targetOffset.y = m_targetOffset.z = 0.0f;
	m_setTargetMatrix = false;
	m_onlyIfOnLand = false;
	m_onlyIfOnWater = false;
	m_ricochet = false;
}

//-------------------------------------------------------------------------------------------------
class FXListAtBonePosFXNugget : public FXNugget
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(FXListAtBonePosFXNugget, "FXListAtBonePosFXNugget")		
public:

	FXListAtBonePosFXNugget()
	{
		m_fx = NULL;
    m_boneName.clear();
    m_orientToBone = true;
	}

	virtual void doFXPos(const Coord3D *primary, const Matrix3D* primaryMtx, const Real /*primarySpeed*/, const Coord3D * /*secondary*/, const Real /*overrideRadius*/ ) const
	{
		DEBUG_CRASH(("You must use the object form for this effect"));
	}

	virtual void doFXObj(const Object* primary, const Object* /*secondary*/) const;

	static void parse(INI *ini, void *instance, void* /*store*/, const void* /*userData*/)
	{
		static const FieldParse myFieldParse[] = 
		{
			{ "FX",								  	INI::parseFXList,			    NULL, offsetof( FXListAtBonePosFXNugget, m_fx ) },
			{ "BoneName",							INI::parseAsciiString,		NULL, offsetof( FXListAtBonePosFXNugget, m_boneName ) },
			{ "OrientToBone",					INI::parseBool,					  NULL, offsetof( FXListAtBonePosFXNugget, m_orientToBone ) },
			{ 0, 0, 0, 0 }
		};

		FXListAtBonePosFXNugget* nugget = newInstance( FXListAtBonePosFXNugget );	
		ini->initFromINI(nugget, myFieldParse);
		((FXList*)instance)->addFXNugget(nugget);
	}

protected:

	// Rowed in FXListAtBonePosFXNugget_doFxAtBones.cpp (0x001E2DD6); this unit only calls it.
	void doFxAtBones(const Object* obj, Int start) const;

private:

	enum { MAX_BONE_POINTS = 40 };

	const FXList*		m_fx;
  AsciiString     m_boneName;
  Bool            m_orientToBone;
};  
EMPTY_DTOR(FXListAtBonePosFXNugget)

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------


// ?FXList::FXList absent-from-retail (retail news 0x001E2747 from a name, never this)
FXList::FXList()
{
}

//-------------------------------------------------------------------------------------------------
// ??1FXList@@ present-unmatched
FXList::~FXList()
{
	clear();
}

// Retail 0x001E11A6 calls vtable slot 0 with a zero flag, then passes its
// returned allocation to operator delete. This is only that call-site ABI
// view; target bytes do not establish the slot's C++ class name.
class Rva001E11A6DeleteSlot0
{
public:
	virtual void *deleteInstance(int flags);
};

//-------------------------------------------------------------------------------------------------
// The unique BFME1 donor placement supplies the clear name. Retail bytes at
// 0x001E11A6 independently show the sentinel walk and the list-base tailcall.
void FXList::clear()
{
	for (FXNuggetList::iterator it = m_nuggets.begin(); it != m_nuggets.end(); ++it)
	{
		Rva001E11A6DeleteSlot0 *nugget = (Rva001E11A6DeleteSlot0 *)*it;
		if (nugget)
			::operator delete(nugget->deleteInstance(0));
	}
	m_nuggets.clear();
}

//-------------------------------------------------------------------------------------------------
void FXList::doFXPos(const Coord3D *primary, const Matrix3D* primaryMtx, const Real primarySpeed, const Coord3D *secondary, const Real overrideRadius ) const
{
	if (ThePartitionManager->getShroudStatusForPlayer(ThePlayerList->getLocalPlayer()->getPlayerIndex(), primary) != CELLSHROUD_CLEAR)
		return;

	for (FXNuggetList::const_iterator it = m_nuggets.begin(); it != m_nuggets.end(); ++it)
	{
		(*it)->doFXPos(primary, primaryMtx, primarySpeed, secondary, overrideRadius);
	}
}

//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// ??0FXListStore@@ present-unmatched
//-------------------------------------------------------------------------------------------------
// ??1FXListStore@@ present-unmatched
FXListStore::~FXListStore()
{
	m_fxmap.clear();
}

//-------------------------------------------------------------------------------------------------
// FXListStore::findFXList: defined in FXListStoreFindFXList.cpp (its row's unit).

//-------------------------------------------------------------------------------------------------
// The native parser and its table are owned by FXListStoreParse.cpp.
// Explicitly retain the already-matched implicit FXList copy constructor;
// the removed reference parser formerly instantiated this value-map member.
template FXList &std::hash_map<NameKeyType, FXList, rts::hash<NameKeyType>,
    rts::equal_to<NameKeyType> >::operator[](const NameKeyType &);

//-------------------------------------------------------------------------------------------------
/*static*/ void INI::parseFXListDefinition(INI *ini)
{
	FXListStore::parseFXListDefinition(ini);
}

void FXListAtBonePosFXNugget::doFXObj(const Object* primary, const Object* /*secondary*/) const
{
	if (primary)
	{
		// First, try the unadorned name, then the 01,02,03... names.
		doFxAtBones(primary, 0);
		doFxAtBones(primary, 1);
	}
	else
	{
		DEBUG_CRASH(("You must have a primary source for this effect"));
	}
}
