// Target facts (game.dat 1.06; code addresses are RVAs, table addresses are VAs):
// 0x002E434E calls UserPreferences::UserPreferences (0x003B1FF1) with unchanged
// this, then stores 0x00C04CE8 at +0. There are no added data members or bases.
// 0x003B1FF1 constructs the 12-byte PreferenceMap at +4, stores 0x00C1EF0C
// at +0 and zeros the four-byte UnicodeString at +0x10. The locals constructed
// at 0x00238A75 and 0x005184B0 occupy ebp-0x20 through ebp-0x0D: sizeof 0x14.
// Both callers reserve 0x14 bytes below the saved EH link at ebp-0x0C.
// 0x002E4272 stores 0x00C04CE8 and tail-calls UserPreferences::~UserPreferences
// (0x003B1F65), which restores 0x00C1EF0C, releases +0x10 through 0x00036E70
// and destroys the +4 tree through 0x003B1E83. The two tables belong to derived
// and base destruction respectively. The derived destructor is rowed under
// Rva002E4272; the existing OptionPreferences destructor binding is 0x002E4272.
// 0x00C04CE8 has 13 slots and ends at non-code 0x00C04D1C. Slot 0 targets
// deleting destructor 0x002E42D2, which calls 0x002E4272. Slots 1-12 are the
// unchanged UserPreferences targets: 0x003B2026, 0x003B1A09, 0x003B1BF3,
// 0x003B1DBE, 0x003B1A67, 0x003B1AC7, 0x003B1CEE, 0x003B1FA1,
// 0x003B1B20, 0x003B1B65, 0x003B1BAE and 0x003B21A6. No virtual slot is added.
// All methods below are declarations of ledger bodies with their existing ABI:
// detail getters/dispatch 0x002E427D, 0x002E429B, 0x002E42AF; nine forwarders
// 0x002E42EE..0x002E432E; setters 0x002E43A6, 0x002E43EE, 0x002E4438;
// campaign 0x002E4573/0x002E4F1F; scroll 0x002E45DA; map/replay queries
// 0x002E4653/0x002E46AF/0x002E470B; audio 0x002E4767; network queries
// 0x002E47B0/0x002E4815/0x002E4874/0x002E48CE/0x002E4928;
// logo/online 0x002E498F/0x002E49EB; brightness/resolution/volume
// 0x002E4A47/0x002E4AA1/0x002E4B2D; boolean queries 0x002E4BC7, 0x002E4C2B,
// 0x002E4C8F, 0x002E4CF3, 0x002E4D4E, 0x002E4DAE, 0x002E4E12, 0x002E4E76;
// IP accessors 0x002E4F98/0x002E505A/0x002E50BB/0x002E514A/0x002E520C/0x002E526D;
// remaining setters 0x002E52FC/0x002E537B/0x002E53FA/0x002E545A/0x002E54EA/0x002E553D.
// Donor facts (Zero Hour UserPreferences.h): public UserPreferences inheritance
// and the shared convenience-method names. BFME2-only names follow the ledger;
// unnamed setting indices retain its signed 32-bit ABI without invented enums.

#pragma once

#ifndef __BFME2_OPTIONPREFERENCES_H_
#define __BFME2_OPTIONPREFERENCES_H_

#include "UserPreferences.h"

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

	int getStaticGameDetail();
	int getIdealStaticGameDetail();
	int Rva002E42AFDispatch(int index);
	int getModelLOD();
	int getAnimationLOD();
	int getEffectsLOD();
	int getShadowLOD();
	int getTerrainLOD();
	int getWaterLOD();
	int Rva002E431EForward();
	int Rva002E4326Forward();
	int Rva002E432EForward();

	void rva002E43A6(int value);
	void rva002E43EE(short value);
	void rva002E4438(unsigned short value);
	int getCampaignDifficulty();
	void setCampaignDifficulty(int value);
	float getScrollFactor();
	bool usesSystemMapDir();
	bool saveCameraInReplays();
	bool useCameraInReplays();
	int getAudioLOD();
	bool getSendDelay();
	int getFirewallBehavior();
	short getFirewallPortAllocationDelta();
	unsigned short getFirewallPortOverride();
	bool getFirewallNeedToRefresh();
	bool hasSeenLogoMovies();
	bool hasGotOnline();
	float getBrightness();
	void getResolution(int *xres, int *yres);
	float getVolume(int index);
	bool getLanguageFilter();
	bool getTurnOffMessengerInGame();
	bool getDoubleClickGuard();
	bool getAllHealthBars();
	bool getAlternateMouseSetup();
	bool getRefreshNet();
	bool getDisplayForeignLanguage();
	bool getUseEAX3();

	unsigned int getLANIPAddress();
	unsigned int getOnlineIPAddress();
	void setLANIPAddress(AsciiString ip);
	void setLANIPAddress(unsigned int ip);
	void setOnlineIPAddress(AsciiString ip);
	void setOnlineIPAddress(unsigned int ip);
	void rva002E52FC(int value);
	void rva002E537B(int value);
	void rva002E53FA(int value);
	void setVolume(int index, float value);
	void rva002E54EA();
	void setSetting(int setting, int value);
};

#endif
