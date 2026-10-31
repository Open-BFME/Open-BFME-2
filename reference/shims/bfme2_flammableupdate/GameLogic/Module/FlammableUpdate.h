// Zero Hour's GameLogic/Module/FlammableUpdate.h with BFME 2's members (marked "BFME 2:"). Copied from
// reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h.
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

// FILE: FlammableUpdate.h /////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, April 2002
// Desc:   Update that manages Aflame and Burned statuses and their effects
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __FLAMMABLE_UPDATE_H_
#define __FLAMMABLE_UPDATE_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/AudioEventRTS.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "GameLogic/Module/DamageModule.h"
#include "GameLogic/Module/UpdateModule.h"

#include <vector>


//-------------------------------------------------------------------------------------------------
enum FlammabilityStatusType
{
	// These show the state I last noticed my object was in.
	FS_NORMAL = 0,
	FS_AFLAME,
	FS_BURNED,

	FS_NORMAL_COUNT	// keep last
};

//-------------------------------------------------------------------------------------------------
// BFME 2: the +0x18 holder. The dtor row 0x0048D075 releases it through Release_Ref 0x00050ED3 when
// non-null, and ?rva0048C7BF@FlammableUpdate@@QAEXXZ hands it to the audio event ctor 0x002DA461.
struct BurningSoundHolder
{
	~BurningSoundHolder()
	{
		if (m_ref.referent)
			m_ref.referent->Release_Ref();
	}
	BurningSoundHolder() { m_ref.referent = 0; }
	OpaqueRefElement4 m_ref;
};

// BFME 2: 8-byte element with a destructor (StlportVectorDtorChains.cpp, row ??$_Destroy@PAVCameraMarker@@ 0x0048CE25).
class CameraMarker { public: ~CameraMarker(); char m_pad[8]; };

// BFME 2: the rowed vector's cleanup is ??1CameraMarkerVec@@QAE@XZ 0x0048D003 and its clear calls
// ?erase@CameraMarkerVec@@QAEPAVCameraMarker@@PAV2@0@Z 0x0048D042, both out of line.
namespace _STL {
template<> vector<CameraMarker>::~vector();
template<> _Vector_base<CameraMarker, allocator<CameraMarker> >::~_Vector_base();
}
struct CameraMarkerVec : public _STL::vector<CameraMarker>
{
	__forceinline CameraMarkerVec() {}
	~CameraMarkerVec();
	CameraMarker *erase(CameraMarker *first, CameraMarker *last);
	void clear() { erase(begin(), end()); }
};

// BFME 2: the custom animation entry at +0x4C, an animation type (-1 for none) and two words: the ctor row 0x0048D541 stores -1, 0, 0.
struct CustomAnimAndDuration
{
	void reset()
	{
		m_animType = -1;
		m_frames = 0;
		m_extra = 0;
	}
	int m_animType;
	UnsignedInt m_frames;
	int m_extra;
};

//-------------------------------------------------------------------------------------------------
// BFME 2: TheAudio's slots as the rows call them: 0x64 from 0x0048C7BF, 0x6C from 0x0048C55E, 0x160 from 0x0048C582.
class AudioManagerSlots
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0; virtual void slot04() = 0;
	virtual void slot05() = 0; virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0; virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0; virtual void slot24() = 0;
	virtual AudioHandle addAudioEvent(const BfmeAudioEventPrefix136 *event) = 0;	// vslot 25 (+0x64)
	virtual void slot26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;	// vslot 27 (+0x6C)
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0; virtual void slot33() = 0; virtual void slot34() = 0;
	virtual void slot35() = 0; virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0; virtual void slot42() = 0; virtual void slot43() = 0; virtual void slot44() = 0;
	virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0; virtual void slot48() = 0; virtual void slot49() = 0;
	virtual void slot50() = 0; virtual void slot51() = 0; virtual void slot52() = 0; virtual void slot53() = 0; virtual void slot54() = 0;
	virtual void slot55() = 0; virtual void slot56() = 0; virtual void slot57() = 0; virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0; virtual void slot62() = 0; virtual void slot63() = 0; virtual void slot64() = 0;
	virtual void slot65() = 0; virtual void slot66() = 0; virtual void slot67() = 0; virtual void slot68() = 0; virtual void slot69() = 0;
	virtual void slot70() = 0; virtual void slot71() = 0; virtual void slot72() = 0; virtual void slot73() = 0; virtual void slot74() = 0;
	virtual void slot75() = 0; virtual void slot76() = 0; virtual void slot77() = 0; virtual void slot78() = 0; virtual void slot79() = 0;
	virtual void slot80() = 0; virtual void slot81() = 0; virtual void slot82() = 0; virtual void slot83() = 0; virtual void slot84() = 0;
	virtual void slot85() = 0; virtual void slot86() = 0; virtual void slot87() = 0;
	virtual void xferAudioHandle(Xfer *xfer, AudioHandle *handle) = 0;	// vslot 88 (+0x160)
};

// BFME 2: directly on Snapshot: the dtor row 0x0048D075 restores 0x00BBB554 below its own table and the
// module data row stores nothing else; +0x04 is never stored by the ctor row 0x0048D541.
class FlammableUpdateModuleData : public Snapshot
{
public:
	Int						m_unused04;
	UnsignedInt		m_burnedDelay;	///< How long before I am ::Burned.  0 means never
	UnsignedInt		m_aflameDuration; ///< How long I stay ::Aflame.  Independent of Burned.  
	// When aflame wears out is when I check to be normal or burned,  So my model can
	// change to burned while I am still aflame.
	UnsignedInt		m_aflameDamageDelay;	///< While ::Aflame, I take damage this often.  If 0, never.
	Int						m_aflameDamageAmount;	///< And this is how much I take.
	BurningSoundHolder	m_burningSoundName;			// BFME 2: see BurningSoundHolder
	Real					m_flameDamageLimitData;
	UnsignedInt		m_flameDamageExpirationDelay;

	// BFME 2: from the module's INI table 0x00C4C600 and the ctor row 0x0048D541.
	Int						m_damageType;									// +0x24
	CameraMarkerVec	m_fireMarkers;								// +0x28
	Bool					m_setBurnedStatus;						// +0x34
	Bool					m_swapModelWhenAflame;				// +0x35
	Bool					m_swapModelWhenQuenched;			// +0x36
	Bool					m_swapTextureWhenAflame;			// +0x37
	Bool					m_swapTextureWhenQuenched;		// +0x38
	Bool					m_burnContained;							// +0x39
	Bool					m_runToWater;									// +0x3A
	Real					m_runToWaterDepth;						// +0x3C
	Real					m_runToWaterSearchRadius;			// +0x40
	Real					m_runToWaterSearchIncrement;	// +0x44
	Bool					m_panicLocomotorWhileAflame;	// +0x48
	CustomAnimAndDuration	m_customAnimAndDuration;	// +0x4C

	FlammableUpdateModuleData();
	virtual ~FlammableUpdateModuleData();	// BFME 2: row ??1FlammableUpdateModuleData@@UAE@XZ 0x0048D075

	static void buildFieldParse(MultiIniFieldParse& p);

private:

};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class FlammableUpdate : public UpdateModule, public DamageModuleInterface
{

	// BFME 2: no pool glue and the macro's parts spelled out: the rows are the public virtual
	// ??1FlammableUpdate@@UAE@XZ 0x0048C724, the plain ??_G 0x0048C8DD and getModuleNameKey 0x0048C6DF.
public:
	static Module* friend_newModuleInstance( Thing *thing, const ModuleData* moduleData ) { return ::new FlammableUpdate( thing, moduleData ); }
	virtual NameKeyType getModuleNameKey() const;
	void operator delete( void *p ) { ::operator delete( p ); }	// BFME 2: ??_G 0x0048C8DD calls the global delete
protected:
	virtual const char *GetSnapshotName() const;
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
private:
	const FlammableUpdateModuleData* getFlammableUpdateModuleData() const { return (const FlammableUpdateModuleData*)getModuleData(); }

public:

	FlammableUpdate( Thing *thing, const ModuleData* moduleData );
	virtual ~FlammableUpdate();

	static Int getInterfaceMask() { return UpdateModule::getInterfaceMask() | (MODULEINTERFACE_DAMAGE); }
	virtual DamageModuleInterface* getDamage() { return this; }

	void tryToIgnite(); ///< FlammabeDamage uses this.  It is up to me to decide if I am burnable
	Bool wouldIgnite(); ///< Since we need to cheat sometimes and light something directly, ask if this would light
	void doAflameDamage();	// BFME 2: public, row ?doAflameDamage@FlammableUpdate@@QAEXXZ 0x0048C771
	void rva0048C7BF();			// BFME 2: starts the burning sound, row 0x0048C7BF
	void rva0048C8F9();			// BFME 2: ends the burn, row 0x0048C8F9

	//UpdateModuleInterface
	virtual UpdateSleepTime update();

	//DamageModuleInterface
	virtual void onDamage( DamageInfo *damageInfo );
	virtual void onHealing( DamageInfo *damageInfo ) { }
	virtual void onBodyDamageStateChange( const DamageInfo *damageInfo, 
																				BodyDamageType oldState, 
																				BodyDamageType newState ) { }

protected:
	
	UpdateSleepTime calcSleepTime();
	void stopBurningSound();

	FlammabilityStatusType	m_status;
	UnsignedInt							m_aflameEndFrame;
	UnsignedInt							m_burnedEndFrame;
	UnsignedInt							m_damageEndFrame;
	AudioHandle							m_audioHandle;
	Real										m_flameDamageLimit;
	UnsignedInt							m_lastFlameDamageDealt;
	// BFME 2: the object is 0x50 bytes (factory 0x0024D030); the xfer row 0x0048C582 saves these four.
	Bool										m_fleeing;										// +0x40
	UnsignedInt							m_specialConditionEndFrame;		// +0x44
	ObjectID								m_lastIgniterID;							// +0x48
	Bool										m_flag4C;											// +0x4C
};

#endif

