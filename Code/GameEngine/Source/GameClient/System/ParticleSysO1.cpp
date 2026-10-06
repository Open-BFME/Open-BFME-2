// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Ireference/open-bfme-1/inputs/reference/shims/campaignmanagerascii /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/System/ParticleSys.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ParticleSystemTemplate::parseRGBColorKeyframe 0x0055B913 (44B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
#define Matrix4x4 Matrix4  // BFME renamed it
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

// ParticleSys.cpp ////////////////////////////////////////////////////////////////////////////////
// Particle System implementation
// Author: Michael S. Booth, November 2001
///////////////////////////////////////////////////////////////////////////////////////////////////

#define _STLP_USE_STATIC_LIB
#define BFME_PARTICLE_LIST_NODE_TAIL
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_PARTICLE_SYSTEM_NAMES

#include "Common/GameState.h"
#include "Common/INI.h"
#include "Common/PerfTimer.h"
#include "Common/ThingFactory.h"
#include "Common/GameLOD.h"
#include "Common/Xfer.h"

#include "GameClient/Drawable.h"
#include "GameClient/DebugDisplay.h"
#include "GameClient/Display.h"
#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"
// BFME's placement operator delete is one shared 12-byte body that calls the
// CRT free import directly; ZH's macro routes it through ::operator delete,
// which is a different (and here, wrong) callee.  The header declaring this
// TU's three pooled classes is pulled in under the override and nothing else.
#pragma push_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
extern "C" void free(void *);
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return MP_GLUE_ALLOCATE(ARGCLASS); \
	} \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		free(p); \
	} \
protected: \
	inline void *operator new(size_t s) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return ::operator new(s); \
	} \
	inline void operator delete(void *p) \
	{ \
		::operator delete(p); \
	} \
private: \
	virtual MemoryPool *getObjectMemoryPool() \
	{ \
		return ARGCLASS::getClassMemoryPool(); \
	} \
public:
#include "GameClient/ParticleSys.h"
#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")

#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/TerrainLogic.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//------------------------------------------------------------------------------ Performance Timers 
//#include "Common/PerfMetrics.h"
//#include "Common/PerfTimer.h"

//static PerfTimer s_particleSys("ParticleSys::update", false, PERFMETRICS_LOGIC_STARTFRAME, PERFMETRICS_LOGIC_STOPFRAME);
//-------------------------------------------------------------------------------------------------

// the singleton
extern ParticleSystemManager *TheParticleSystemManager;


  // end loadPostProcess

/** Load post process */
// ------------------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
enum
{
	MAX_SIZE_BONUS = 50
};


//todo move this somewhere more useful.
static Real angleBetween(const Coord2D *vecA, const Coord2D *vecB);


  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
#if 0
  // end loadPostProcess
#endif


// ------------------------------------------------------------------------------------------------
/** Stop emitting, wait for all of our particles to die, then destroy self. */
// ------------------------------------------------------------------------------------------------
// BFME holds the slave system in a lazy-pointer wrapper, not a bare pointer:
// dereferencing it substitutes a shared fallback object when the pointer is null,
// while testing it does not. That is the `test eax,eax / jne +5 / call 0x00001B18`
// pair retail has inside the walk and nothing outside it. The flag is at +0x1A8
// and the wrapper at +0x160.
//
// Retail's body is a LOOP, not a call: `m_slaveSystem->destroy()` is a tail call
// to this same function, and the compiler turns that into a walk down the slave
// chain. The source below is the reference's recursion unchanged; the loop is the
// compiler's doing, which is why nothing here spells one.
ParticleSystem *Make00001B18( void );

class BfmeParticleSystemPtr
{
public:
	operator ParticleSystem *( void ) const
	{
		return m_target;
	}

	ParticleSystem *operator->( void ) const
	{
		ParticleSystem *target = m_target;
		if( !target )
			target = Make00001B18();
		return target;
	}

private:
	ParticleSystem *m_target;
};

struct BfmeParticleDestroyView
{
	unsigned char m_unreconstructed_000[ 0x160 ];
	BfmeParticleSystemPtr m_slaveSystem;			///< retail this+0x160
	unsigned char m_unreconstructed_164[ 0x1a8 - 0x164 ];
	unsigned char m_isDestroyed;				///< retail this+0x1A8
};


// ------------------------------------------------------------------------------------------------
/** Get the position of the particle system */
// ------------------------------------------------------------------------------------------------
// m_localTransform is at ParticleSystem+0xC0 in retail and +0x274 in the vendored
// class -- retail reads the translation column at +0xCC, +0xDC and +0xEC, which is
// the matrix's own +0x0C/+0x1C/+0x2C. Everything else about the body is identical.
struct BfmeParticleTransformView
{
	unsigned char m_unreconstructed_000[ 0xc0 ];
	Matrix3D m_localTransform;				///< retail this+0xC0
};


// ------------------------------------------------------------------------------------------------
/** Parse a "color keyframe".
 * The format is "FIELD = R:r G:g B:b frame". */
// ------------------------------------------------------------------------------------------------
void ParticleSystemTemplate::parseRGBColorKeyframe( INI* ini, void *instance,
																													void *store, const void* /*userData*/ )
{
	RGBColorKeyframe *key = static_cast<RGBColorKeyframe *>(store);

	INI::parseRGBColor( ini, instance, &key->color, NULL );
	INI::parseUnsignedInt( ini, instance, &key->frame, NULL );
}


