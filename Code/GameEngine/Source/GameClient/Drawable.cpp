// cl: /Ireference/shims/bfme2_vector3 -DNDEBUG -DWIN32 -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/shims/locomotor -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// stlport
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

// Drawable.cpp ///////////////////////////////////////////////////////////////////////////////////
// "Drawables" - graphical GameClient entities bound to GameLogic objects
// Author: Michael S. Booth, March 2001
///////////////////////////////////////////////////////////////////////////////////////////////////
  
// BFME's Snapshot base is polymorphic where Zero Hour's is not: ~TintEnvelope
// calls the vptr-store-then-release-AsciiString body at 0x009A1A40, not the
// bare release at 0x00887940 that the ZH spelling resolves to.  Renaming the
// class for this TU gives that call its own pinnable symbol instead of a second
// address under a name another TU already resolves elsewhere.
#define Snapshot BfmeDrawableSnapshot

#include <string.h>
#pragma intrinsic(memcpy)
#include "vector3.h" // use the verified BFME2 three-word constructor
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME's placement operator delete is one shared 12-byte body that calls the
// CRT free import directly; ZH's macro routes it through ::operator delete,
// which is a different (and here, wrong) callee.  The two headers that declare
// this TU's four pooled classes are pulled in here so the override reaches them
// and nothing else.
// GameMemory.h must be resolved BEFORE the override: every header below
// reaches it transitively, and its own #define would otherwise land after
// ours and silently restore ZH's ::operator delete routing.
#include "Common/GameMemory.h"
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
#include "Common/DynamicAudioEventInfo.h"
#include "GameClient/Drawable.h"
#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")

#include "Common/AudioEventInfo.h"
#include "Common/DynamicAudioEventInfo.h"
#include "Common/AudioSettings.h"
#include "Common/BitFlagsIO.h"
#include "Common/BuildAssistant.h"
#include "Common/ClientUpdateModule.h"
#include "Common/DrawModule.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/GameLOD.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/ModuleFactory.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"

#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/GameLogic.h"		// for logic frame count
#include "GameLogic/Object.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/StickyBombUpdate.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"

#include "GameClient/Anim2D.h"
#include "GameClient/Display.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/Drawable.h"
#include "GameClient/DrawGroupInfo.h"
#include "GameClient/GameClient.h"
#include "GameClient/GlobalLanguage.h"
#include "GameClient/InGameUI.h"
#include "GameClient/Image.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/LanguageFilter.h"
#include "GameClient/Shadow.h"
#include "GameClient/GameText.h"

//#define KRIS_BRUTAL_HACK_FOR_AIRCRAFT_CARRIER_DEBUGGING 
#ifdef KRIS_BRUTAL_HACK_FOR_AIRCRAFT_CARRIER_DEBUGGING
	#include "GameLogic/Module/ParkingPlaceBehavior.h"
#endif

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define VERY_TRANSPARENT_MATERIAL_PASS_OPACITY (0.001f)
#define MATERIAL_PASS_OPACITY_FADE_SCALAR (0.8f)

// Drawable::draw, 0x0027C157..0x0027C1F2. The reference's fade and draw-module
// loop survive; BFME2 prepares the full matrix in the native 0x0027BED0 helper.
// BFME1 donor: 1399ad37d42ea52a63829e417c46a1ba9ed2cd20, Drawable.cpp draw.
struct BfmeDrawableDrawObject
{
	unsigned char pad000[0x438];
	unsigned char status438;
};
// Retail dispatches doDrawModule through vtable +0x2c; the donor DrawModule
// header has a shorter base vtable, so use only the slot this body proves.
class Rva0027C157DrawModuleView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void doDrawModule(const Matrix3D *matrix);
};
struct BfmeDrawableDrawFields
{
	unsigned char pad000[0xfc];
	BfmeDrawableDrawObject *object;
	unsigned char pad100[0x118 - 0x100];
	unsigned char tintStatus;
	unsigned char pad119[0x14c - 0x119];
	Rva0027C157DrawModuleView **drawModules;
	unsigned char pad150[0x358 - 0x150];
	float secondMaterialPassOpacity;
	unsigned char pad35c[0x43d - 0x35c];
	bool hidden;
	bool hiddenByStealth;
	unsigned char pad43f;
	bool fullyObscuredByShroud;
};
class BfmeDrawableDrawTransform
{
public:
	void rva0027BED0(Matrix3D *matrix);
};

void Drawable::draw(View *view)
{
	BfmeDrawableDrawFields *self = (BfmeDrawableDrawFields *)this;
	if (!(self->tintStatus & 8))
	{
		if (self->object && (self->object->status438 & 1))
			self->secondMaterialPassOpacity = 0.0f;
		else if (self->secondMaterialPassOpacity > VERY_TRANSPARENT_MATERIAL_PASS_OPACITY)
			self->secondMaterialPassOpacity *= MATERIAL_PASS_OPACITY_FADE_SCALAR;
		else
			self->secondMaterialPassOpacity = 0.0f;
	}
	if (self->hidden || self->hiddenByStealth || self->fullyObscuredByShroud)
		return;
	Matrix3D transformMtx;
	((BfmeDrawableDrawTransform *)this)->rva0027BED0(&transformMtx);
	for (Rva0027C157DrawModuleView **dm = self->drawModules; *dm; ++dm)
		(*dm)->doDrawModule(&transformMtx);
}

static const char *TheDrawableIconNames[] = 
{
	"DefaultHeal",
	"StructureHeal",
	"VehicleHeal",
#ifdef ALLOW_DEMORALIZE
	"Demoralized",
#else
	"Demoralized_OBSOLETE",
#endif
	"BombTimed",
	"BombRemote",
	"Disabled",
	"BattlePlanIcon_Bombard",
	"BattlePlanIcon_HoldTheLine",
	"BattlePlanIcon_SeekAndDestroy",
  "Emoticon",
	"Enthusiastic",//a red cross? // soon to replace?
	"Subliminal",  //with the gold border! replace?
	"CarBomb",
	NULL
};


/** 
 * Returns a special DynamicAudioEventInfo which can be used to mark a sound as "no sound".
 * E.g. if m_customSoundAmbientInfo equals the value returned from this function, we
 * know it really means don't allow an ambient sound to be attached. 
 *
 * OK, so it's a bit of a hack, but it saves memory in every Drawable
 */

// Dedicated TU: only verified bodies from the donor are defined here.

// BFME's TintEnvelope carries ONE vtable pointer where the reference class
// derives from both MemoryPoolObject and Snapshot and carries two, so every
// member sits four bytes earlier: m_attackRate at +0x04, m_decayRate at +0x10,
// m_peakColor at +0x1c, m_currentColor at +0x28, m_sustainCounter at +0x34,
// m_envState at +0x38 and m_affect at +0x39 (TintEnvelope::play 0x004156D0).
struct BfmeTintEnvelopeRates
{
	void *m_vtable;
	Vector3 m_attackRate;						///< retail this+0x04
	Vector3 m_decayRate;						///< retail this+0x10
	Vector3 m_peakColor;						///< retail this+0x1c
	Vector3 m_currentColor;						///< retail this+0x28
	UnsignedInt m_sustainCounter;				///< retail this+0x34
	Byte m_envState;							///< retail this+0x38
	Bool m_affect;								///< retail this+0x39
};

// Retail calls msvcr71.dll!_strcmpi at this body's only import slot
// (0x00BBA518). The donor's `stricmp` is a macro, so /MD expands it to a call
// to __stricmp -- an export retail does not import. Declaring _strcmpi as a
// TU-scoped dllimport gives the call the identity the import directory proves;
// same override FXListStoreFindFXList.cpp carries for the same reason.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// The donor's only caller is one of the omitted bodies, so `static` here would
// leave the function unreferenced and elided; retail's own mangled name
// ?drawableIconNameToIndex@@YA?AW4DrawableIconType@@PBD@Z is a global __cdecl
// symbol, so the body is defined with external linkage here.
DrawableIconType drawableIconNameToIndex( const char *iconName )
{

	DEBUG_ASSERTCRASH( iconName != NULL, ("drawableIconNameToIndex - Illegal name\n") );

	for( Int i = ICON_FIRST; i < MAX_ICONS; ++i )
		if( _strcmpi( TheDrawableIconNames[ i ], iconName ) == 0 )
			return (DrawableIconType)i;

	return ICON_INVALID;

}  // end drawableIconNameToIndex

//-------------------------------------------------------------------------------------------------
/** remove self from the linked list */
//-------------------------------------------------------------------------------------------------
// list links live at +0x104/+0x108 in retail BFME Drawable (header still ZH-shaped)
void Drawable::removeFromList(Drawable **pListHead)
{
	struct Links {
		unsigned char pad[0x104];
		Links *next;
		Links *prev;
	};
	Links *self = reinterpret_cast<Links *>(this);
	if (self->next)
		self->next->prev = self->prev;
	if (self->prev)
		self->prev->next = self->next;
	else
		*reinterpret_cast<Links **>(pListHead) = self->next;
}

//-------------------------------------------------------------------------------------------------
// ?setDecayFrames@TintEnvelope@@AAEXI@Z
void TintEnvelope::setDecayFrames( UnsignedInt frames )
{
	BfmeTintEnvelopeRates *self = (BfmeTintEnvelopeRates *)this;

	Real recipFrames = ( -1.0f ) / (Real)MAX(1,frames);
	self->m_decayRate.Set( self->m_peakColor );
	Vector3 rateScale; rateScale.Set(recipFrames, recipFrames, recipFrames);
	self->m_decayRate.Scale(rateScale);
}


// BFME1 donor 6583b3c1ff21db4a561285717028fdafc780b7db; native
// TintEnvelope call chain and field accesses independently match these bodies.
const Real FADE_RATE_EPSILON = 0.001f;

void TintEnvelope::play(const RGBColor *peak, UnsignedInt atackFrames, UnsignedInt decayFrames, UnsignedInt sustainAtPeak )    
{
	BfmeTintEnvelopeRates *self = (BfmeTintEnvelopeRates *)this;

	Vector3 peakColor; peakColor.Set(peak->red, peak->green, peak->blue);
	self->m_peakColor = peakColor;

	setAttackFrames( atackFrames );
	setDecayFrames( decayFrames );

	self->m_envState = ENVELOPE_STATE_ATTACK;
	self->m_sustainCounter = sustainAtPeak;
	self->m_affect = TRUE;

	Vector3 delta;
	Vector3::Subtract(self->m_currentColor, self->m_peakColor, &delta);

	if ( delta.Length() <= FADE_RATE_EPSILON ) // we are practically already at this color
		self->m_envState = ENVELOPE_STATE_SUSTAIN;

}

// ?setAttackFrames@TintEnvelope@@AAEXI@Z
void TintEnvelope::setAttackFrames(UnsignedInt frames) 
{
	BfmeTintEnvelopeRates *self = (BfmeTintEnvelopeRates *)this;

	Real recipFrames = 1.0f / (Real)MAX(1,frames);
	self->m_attackRate.Set( self->m_currentColor );
	Vector3::Subtract( self->m_peakColor, self->m_attackRate, &self->m_attackRate);
	Vector3 rateScale; rateScale.Set(recipFrames, recipFrames, recipFrames);
	self->m_attackRate.Scale(rateScale);
}
