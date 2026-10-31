// Zero Hour's Common/UserPreferences.h, verbatim but for BFME 2's preference classes (marked "BFME 2:"). Copied from
// reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
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

///////////////////////////////////////////////////////////////////////////////////////
// FILE: UserPreferences.h
// Author: Matthew D. Campbell, April 2002
// Description: Saving/Loading of user preferences
///////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __USERPREFERENCES_H__
#define __USERPREFERENCES_H__

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "Common/STLTypedefs.h"

class Money;

//-----------------------------------------------------------------------------
// PUBLIC TYPES ///////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

typedef std::map<AsciiString, AsciiString> PreferenceMap;

//-----------------------------------------------------------------------------
// UserPreferences base class 
//-----------------------------------------------------------------------------
class UserPreferences : public PreferenceMap
{
public:
	UserPreferences();
	virtual ~UserPreferences();

	// BFME 2: each member below is virtual and takes its key by reference in its row's mangled name
	// (0x003B1A09 to 0x003B21A6, Common/UserPreferences.cpp). MSVC lays the load overloads out in reverse order.
	virtual Bool load(const AsciiString &fname);
	virtual Bool load(const UnicodeString &fname);
	virtual Bool write(void);
	
	virtual Bool getBool(const AsciiString &key, Bool defaultValue) const;
	virtual Real getReal(const AsciiString &key, Real defaultValue) const;
	virtual Int getInt(const AsciiString &key, Int defaultValue) const;
	virtual Int getEnumIndex(const char *key, const char **names, Int count, Int defaultValue) const;
	virtual AsciiString getAsciiString(const AsciiString &key, const AsciiString &defaultValue) const;

	virtual void setBool(const AsciiString &key, Bool val);
	virtual void setReal(const AsciiString &key, Real val);
	virtual void setInt(const AsciiString &key, Int val);
	virtual void setAsciiString(const AsciiString &key, const AsciiString &val);

protected:
	// BFME 2: rows 0x003B2026 and 0x003B1BF3 pass the filename's str() to _wfopen.
	UnicodeString m_filename;
};

//-----------------------------------------------------------------------------
// OptionsPreferences options menu class 
//-----------------------------------------------------------------------------
// BFME 2: OptionPreferences table 0x00C04CE8 slot 0 -> deleting 0x002E42D2 -> complete destructor 0x002E4272,
// rowed as ??1Rva002E4272@@UAE@XZ; rows 0x00595E46 and 0x00595F80 bind ??1OptionPreferences to it.
class Rva002E4272 : public UserPreferences
{
public:
	virtual ~Rva002E4272();
};

class OptionPreferences : public Rva002E4272
{
public:
	OptionPreferences(  );
	virtual ~OptionPreferences();
	UnsignedInt getLANIPAddress(void);				// convenience function
	UnsignedInt getOnlineIPAddress(void);			// convenience function
	void setLANIPAddress(AsciiString IP);			// convenience function
	void setOnlineIPAddress(AsciiString IP);	// convenience function
	void setLANIPAddress(UnsignedInt IP);			// convenience function
	void setOnlineIPAddress(UnsignedInt IP);	// convenience function
	Bool getAlternateMouseModeEnabled(void);	// convenience function
	Bool getRetaliationModeEnabled();					// convenience function
	Bool getDoubleClickAttackMoveEnabled(void);	// convenience function
	Real getScrollFactor(void);								// convenience function
	Bool getSendDelay(void);									// convenience function
	Int getFirewallBehavior(void);						// convenience function
	Short getFirewallPortAllocationDelta(void);	// convenience function
	UnsignedShort getFirewallPortOverride(void); // convenience function
	Bool getFirewallNeedToRefresh(void);			// convenience function
	Bool usesSystemMapDir(void);							// convenience function
	AsciiString getPreferred3DProvider(void);	// convenience function
	AsciiString getSpeakerType(void);					// convenience function
	Real getSoundVolume(void);								// convenience function
	Real get3DSoundVolume(void);							// convenience function
	Real getSpeechVolume(void);								// convenience function
	Real getMusicVolume(void);								// convenience function
	Bool saveCameraInReplays(void);
	Bool useCameraInReplays(void);
	Int	 getStaticGameDetail(void);	// detail level selected by the user.
	Int	 getIdealStaticGameDetail(void);	// detail level detected for user.
 	Real getGammaValue(void);
	Int	 getTextureReduction(void);
	void getResolution(Int *xres, Int *yres);
	Bool get3DShadowsEnabled(void);
	Bool get2DShadowsEnabled(void);
	Bool getCloudShadowsEnabled(void);
	Bool getLightmapEnabled(void);
	Bool getSmoothWaterEnabled(void);
	Bool getTreesEnabled(void);
	Bool getExtraAnimationsDisabled(void);
	Bool getUseHeatEffects(void);
	Bool getDynamicLODEnabled(void);
	Bool getFPSLimitEnabled(void);
	Bool getNoDynamicLODEnabled(void);
	Bool getBuildingOcclusionEnabled(void);
	Int getParticleCap(void);

	Int	 getCampaignDifficulty(void);
	void setCampaignDifficulty( Int diff );
};

//-----------------------------------------------------------------------------
// LANPreferences class 
//-----------------------------------------------------------------------------
class LANPreferences : public UserPreferences
{
public:
	LANPreferences();
	virtual ~LANPreferences();
	UnicodeString getUserName(void);		// convenience function
	Int getPreferredFaction(void);			// convenience function
	Int getPreferredColor(void);				// convenience function
	AsciiString getPreferredMap(void);	// convenience function
	Bool usesSystemMapDir(void);		// convenience function
	Int getNumRemoteIPs(void);					// convenience function
	UnicodeString getRemoteIPEntry(Int i);	// convenience function

  Bool getSuperweaponRestricted(void) const;
  Money getStartingCash(void) const;
  void setSuperweaponRestricted( Bool superweaponRestricted);
  void setStartingCash( const Money & startingCash );
};

#endif // __USERPREFERENCES_H__
