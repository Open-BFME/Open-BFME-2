// FILE: TerrainRoadType.h ///////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 TerrainRoadType (one road or bridge description).
//
// Target facts (RVAs; VA = RVA + 0x400000):
//  - newRoad 0x002DB57F (0x002DB591) and newBridge 0x002DB64E (0x002DB665) push
//    0x14C to the global operator new 0x0002FDA0 and call ??0TerrainRoadType
//    0x002DB1CA: sizeof 0x14C, no memory pool.
//  - The ctor (0x002DB1DC) and the dtor 0x002DB311 (0x002DB324) store only table
//    0x00803E24 at +0 and call no base constructor or destructor: no base class,
//    one vptr at +0. The table has one slot, ??_G 0x002DB47A (the next word is the
//    "DefaultRoad" literal newRoad pushes, 0x00803E28); ??_G calls the dtor, then
//    the global operator delete 0x0002FD60. So the only virtual is the destructor.
//  - Ctor stores: the eleven scalar strings (+4, +0x20, +0x24, +0x34..+0x50), byte +8,
//    +0xC, +0x10, +0x148 zeroed, floats +0x14 +0x18 +0x28 +0x2C +0x30 +0x144 = 0,
//    +0x1C = 1.0f. ??_L 0x00629512 (element ctor 0x00326BE6) and the dtor's ??_M
//    0x00629110: +0x54 x4, +0x74/+0xA4/+0xE4/+0x114 x12 with the AsciiString dtor
//    0x0048BA39; +0x64 and +0xD4 x4 with dtor 0x0010F149 (??1OpaqueRefElement4).
//  - Field parse tables (data rows, public statics): road 0x008039E8 (+0x38
//    texture, +0x14/+0x18 widths), bridge 0x00803A28 (+0x1C scale, +0x20/+0x24
//    scaffold names, +0x28 RadarColor via parseRGBColor, +0x34..+0x50 models and
//    textures, +0x54..+0x60 tower names, +0x68/+0xD8 sounds, +0x144, +0x148).
//  - Inline in retail: newRoad reads +0x38 (0x002DB5FD), +0x14/+0x18 (0x002DB612)
//    and writes +0xC, byte +8 and +0x10; newBridge reads/writes +0x1C (0x002DB6EA),
//    +0x144/+0x148 (0x002DB787) and passes +0x64/+0xD4 element addresses
//    (0x002DB7A3); findRoad 0x002DB496 compares the name at +4 in place and walks
//    +0x10; INI::parseTerrainRoadDefinition 0x001FF288 reads +4 and +8.
//  - The row ?getRoadWidth@TerrainRoadType@@QAEMXZ (0x0049CB57) is a folded body
//    that only weapon code calls (0x0034BF20, 0x0045BB8A, 0x004C2127, 0x004C21A9);
//    symbols.csv also pins ?rva0049CB57@WeaponTemplate@@QBEMXZ there. The road
//    code inlines the read, so getRoadWidth is inline here.
//  - Out of line: every TerrainRoadType row of reverse/functions.csv, with the
//    signature its decorated name states, and three getters newBridge calls at
//    pinned addresses (symbols.csv): getBridgeModel 0x000DE59C,
//    getBridgeModelNameDamaged 0x004DC8E7, getTextureReallyDamaged 0x000DE5B7.
// Donor (Zero Hour TerrainRoads.h) facts: member and accessor names, member order.
// Zero Hour derives from MemoryPoolObject and keeps data protected; BFME2 has no
// base, and the data is public here so units outside the class's rows can adopt.
//
// The sound records at +0x64 and +0xD4 are OpaqueRefElement4, the setter rows' parameter type.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef CANONICAL_TERRAINROADTYPE_H
#define CANONICAL_TERRAINROADTYPE_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"
#include "../Common/OpaqueRefElement4.h"

class INI;
struct FieldParse;
enum BodyDamageType;
enum BridgeTowerType;

//-------------------------------------------------------------------------------------------------
class TerrainRoadType
{
public:
	TerrainRoadType();													// 0x002DB1CA
	virtual ~TerrainRoadType();											// 0x002DB311 (slot 0: ??_G 0x002DB47A)

	const AsciiString &getName() const { return m_name; }
	const AsciiString &getTexture() const { return m_texture; }
	bool isBridge() const { return m_isBridge; }
	float getRoadWidth() { return m_roadWidth; }
	float getRoadWidthInTexture() { return m_roadWidthInTexture; }
	float getBridgeScale() const { return m_bridgeScale; }
	RGBColor getRadarColor() { return m_radarColor; }					// emitted 0x0004D636
	AsciiString getBridgeModel();										// pinned 0x000DE59C
	AsciiString getBridgeModelNameDamaged();							// pinned 0x004DC8E7
	AsciiString getBridgeModelNameBroken();								// 0x00062E72
	AsciiString getTextureReallyDamaged();								// pinned 0x000DE5B7
	AsciiString getTowerObjectName(BridgeTowerType tower);				// 0x00280BE6
	const OpaqueRefElement4 &getDamageToSoundString(BodyDamageType state) const { return m_damageToSoundString[state]; }
	AsciiString getDamageToOCLString(BodyDamageType state, int index);	// 0x002DACF4
	const OpaqueRefElement4 &getRepairedToSoundString(BodyDamageType state) const { return m_repairedToSoundString[state]; }
	float getTransitionEffectsHeight() const { return m_transitionEffectsHeight; }
	int getNumFXPerType() const { return m_numFXPerType; }

	// friend access methods to be used by the road collection only
	void friend_setName(AsciiString name);								// 0x002DAD19
	void friend_setTexture(AsciiString texture);						// 0x002DAD4D
	void friend_setBridge(bool isBridge) { m_isBridge = isBridge; }
	void friend_setID(unsigned int id) { m_id = id; }
	void friend_setNext(TerrainRoadType *next) { m_next = next; }
	TerrainRoadType *friend_getNext() { return m_next; }
	void friend_setRoadWidth(float width) { m_roadWidth = width; }
	void friend_setRoadWidthInTexture(float width) { m_roadWidthInTexture = width; }
	void friend_setBridgeScale(float scale) { m_bridgeScale = scale; }
	void friend_setBridgeModelName(AsciiString name);					// 0x002DAD81
	void friend_setBridgeModelNameDamaged(AsciiString name);			// 0x002DADB5
	void friend_setBridgeModelNameReallyDamaged(AsciiString name);		// 0x002DADE9
	void friend_setBridgeModelNameBroken(AsciiString name);				// 0x002DAE1D
	void friend_setTextureDamaged(AsciiString texture);					// 0x002DAE51
	void friend_setTextureReallyDamaged(AsciiString texture);			// 0x002DAE85
	void friend_setTextureBroken(AsciiString texture);					// 0x002DAEB9
	void friend_setDamageToSoundString(BodyDamageType state, const OpaqueRefElement4 &sound);	// 0x002DB44F
	void friend_setDamageToOCLString(BodyDamageType state, int index, AsciiString str);		// 0x002DAEED
	void friend_setDamageToFXString(BodyDamageType state, int index, AsciiString str);		// 0x002DAF2B
	void friend_setRepairedToSoundString(BodyDamageType state, const OpaqueRefElement4 &sound);	// 0x002DB463
	void friend_setRepairedToOCLString(BodyDamageType state, int index, AsciiString str);	// 0x002DAF6C
	void friend_setRepairedToFXString(BodyDamageType state, int index, AsciiString str);	// 0x002DAFAC
	void friend_setTransitionEffectsHeight(float height) { m_transitionEffectsHeight = height; }
	void friend_setNumFXPerType(int num) { m_numFXPerType = num; }

	static const FieldParse m_terrainRoadFieldParseTable[];				// 0x008039E8
	static const FieldParse m_terrainBridgeFieldParseTable[];			// 0x00803A28
	static void parseTransitionToOCL(INI *ini, void *instance, void *store, const void *userData);	// 0x002DAFEC
	static void parseTransitionToFX(INI *ini, void *instance, void *store, const void *userData);	// 0x002DB0DB

	AsciiString m_name;										// +0x04
	bool m_isBridge;										// +0x08
	unsigned int m_id;										// +0x0C
	TerrainRoadType *m_next;								// +0x10
	float m_roadWidth;										// +0x14
	float m_roadWidthInTexture;								// +0x18
	float m_bridgeScale;									// +0x1C
	AsciiString m_scaffoldObjectName;						// +0x20
	AsciiString m_scaffoldSupportObjectName;				// +0x24
	RGBColor m_radarColor;									// +0x28
	AsciiString m_bridgeModelName;							// +0x34
	AsciiString m_texture;									// +0x38
	AsciiString m_bridgeModelNameDamaged;					// +0x3C
	AsciiString m_textureDamaged;							// +0x40
	AsciiString m_bridgeModelNameReallyDamaged;				// +0x44
	AsciiString m_textureReallyDamaged;						// +0x48
	AsciiString m_bridgeModelNameBroken;					// +0x4C
	AsciiString m_textureBroken;							// +0x50
	AsciiString m_towerObjectName[4];						// +0x54, by BridgeTowerType
	OpaqueRefElement4 m_damageToSoundString[4];				// +0x64, by BodyDamageType
	AsciiString m_damageToOCLString[4][3];					// +0x74, [state][effect]
	AsciiString m_damageToFXString[4][3];					// +0xA4
	OpaqueRefElement4 m_repairedToSoundString[4];			// +0xD4
	AsciiString m_repairedToOCLString[4][3];				// +0xE4
	AsciiString m_repairedToFXString[4][3];					// +0x114
	float m_transitionEffectsHeight;						// +0x144
	int m_numFXPerType;										// +0x148
};

#endif // CANONICAL_TERRAINROADTYPE_H
