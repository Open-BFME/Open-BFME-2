// Target facts: parseSpecialPowerDefinition (RVA 0x003B15D6) allocates 0x80 bytes at 0x003B1635, 0x003B1681 and 0x003B1739, then calls constructor 0x003B140E (ledger class Rva003B1101).
// Constructor 0x003B140E initializes Overridable at +0 (next +4, flag +8, integer +0x0C), then members from +0x10; destructor 0x003B1101 calls ~Overridable at 0x003B119B. Both store VA 0x00C1ED18; its sole slot is deleting destructor 0x003B152A. The base destructor 0x001E3624 restores VA 0x00BDDC48. SpecialPowerTemplate is polymorphic, with no additional virtual slots.
// The 22-entry parse table VA 0x00DC0E78, passed at 0x003B17CB, proves Flags +0x18, Enum +0x1C, ReloadTime +0x20, RequiredSciences +0x24, LightPointCost +0x30, sounds +0x34/+0x38, string names +0x3C/+0x40, EVA event +0x44, DetectionTime +0x48, view duration/range +0x4C/+0x50, radius +0x54, PublicTimer +0x58, SharedSyncedTimer +0x59, PalantirMovie +0x5C, filters +0x60/+0x78, conditions +0x64, ranges +0x74/+0x7C. Constructor 0x003B140E and assignment 0x003B1337 prove widths; destructor 0x003B1101 releases strings at +0x10/+0x3C/+0x40/+0x5C. Setter 0x003B0FAC writes name +0x10 and ID +0x14; lookup 0x003B11D2 compares the final override's +0x10 string. The named row getSpecialPowerType (0x002AAE3D) reads +0x14, getRequiredScience (0x0028F8D7) reads +0x1C, getLightPointCost (0x004210EF) reads +0x30, getEvaEventToPlayOnSuccess (0x0044EB4B) reads +0x44, getRadius (0x0029B6E2) reads +0x54 and rva0029B6D9 reads byte +0x59, all through 0x00288609. Zero Hour SpecialPower.h supplies accessor names; aggregate storage without a recovered C++ member type remains opaque.

#pragma once

#ifndef __BFME2_SPECIALPOWER_H_
#define __BFME2_SPECIALPOWER_H_

#include "Overridable.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

enum SpecialPowerType;
enum ScienceType;
struct FieldParse;

class SpecialPowerTemplate : public Overridable
{
public:

	SpecialPowerTemplate();
	virtual ~SpecialPowerTemplate();
	SpecialPowerTemplate &operator=( const SpecialPowerTemplate &that );

	SpecialPowerType getSpecialPowerType() const;
	ScienceType getRequiredScience() const;
	int getLightPointCost() const;
	int getEvaEventToPlayOnSuccess() const;
	float getRadius() const;
	bool rva0029B6D9() const;

	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	const AsciiString &getName() const { return getFO()->m_name; }
	unsigned int getID() const { return getFO()->m_id; }
	unsigned int getReloadTime() const { return getFO()->m_reloadTime; }
	bool hasPublicTimer() const { return getFO()->m_publicTimer; }
	bool isSharedNSync() const { return getFO()->m_sharedSyncedTimer; }
	unsigned int getDetectionTime() const { return getFO()->m_detectionTime; }
	unsigned int getViewObjectDuration() const { return getFO()->m_viewObjectDuration; }
	float getViewObjectRange() const { return getFO()->m_viewObjectRange; }
	float getRadiusCursorRadius() const { return getFO()->m_radiusCursorRadius; }

	static const FieldParse *getFieldParse() { return m_specialPowerFieldParse; }
	void friend_setNameAndID( const AsciiString &name, unsigned int id );

	AsciiString m_name; // +0x10
	unsigned int m_id; // +0x14
	unsigned int m_flags; // +0x18
	SpecialPowerType m_type; // +0x1C
	unsigned int m_reloadTime; // +0x20
	unsigned char field24[0x0C]; // +0x24
	int m_lightPointCost; // +0x30
	unsigned int field34; // +0x34
	unsigned int field38; // +0x38
	AsciiString m_unitSpecificSoundToUseAsInitiateIntendToDoVoice; // +0x3C
	AsciiString m_unitSpecificSoundToUseAsEnterStateInitiateIntendToDoVoice; // +0x40
	int m_evaEventToPlayOnSuccess; // +0x44
	unsigned int m_detectionTime; // +0x48
	unsigned int m_viewObjectDuration; // +0x4C
	float m_viewObjectRange; // +0x50
	float m_radiusCursorRadius; // +0x54
	bool m_publicTimer; // +0x58
	bool m_sharedSyncedTimer; // +0x59
	AsciiString m_palantirMovie; // +0x5C
	unsigned int field60; // +0x60
	unsigned char field64[0x10]; // +0x64
	float m_maxCastRange; // +0x74
	unsigned int field78; // +0x78
	float m_forbiddenObjectRange; // +0x7C

private:

	template<class T> friend struct DataRowPrivateProbe;
	static const FieldParse m_specialPowerFieldParse[];
};

#endif
