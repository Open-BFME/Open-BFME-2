// Target facts (addresses below are RVAs unless prefixed VA):
// INI has no bases, virtual functions or vtable. Constructor 0x0002CDB0
// clears its first word, constructs the filename at +4 via 0x00037BA0,
// and clears +8/+0xC/+0x10. Destructor 0x0002CE5B destroys members only;
// neither body installs an INI vptr. The apparent table at +0x428 is
// VA 0x00BBDCE8, the bytes "END\0", not code pointers. The real vptr
// belongs to the member at +0x838: its ctor 0x00601BBC and dtor
// 0x00601BF3 both install VA 0x00C7A6B0, whose sole slot is 0x00602056.
// Size 0x87C: 0x000541DB reserves exactly 0x87C stack bytes for the INI
// constructed at 0x000541F4. The ctor constructs a 0x34-byte member at
// +0x838, clears an AsciiString at +0x86C, and constructs a three-pointer
// vector at +0x870 via 0x00211E58. The dtor destroys those in reverse order.
// The helper and vector have opaque storage until they have shared types.
// Constructor stores six string pointers at +0x418/+0x41C/+0x420/+0x424/
// +0x428/+0x42C (separators, percent, colon, quote, END, ENDSCRIPT), clears
// byte +0x430 and buffers at +0x14/+0x431. readLine 0x0002D669 copies
// at most 0x403 bytes to +0x14 and terminates +0x417; it reads/increments
// +0x10 and saves the previous index at +0xC. prepFile 0x0002D2C1 stores
// its load-type argument at +8. getLineNum 0x0002BBED and getFilename
// 0x0002C005 resolve +0x10 through the helper, rather than returning fields;
// 0x0002BBDE/0x0002BFE5 do the same with +0xC. Separator accessors
// 0x0002BAD5/0x0002BADC/0x0002BAE3/0x0002BAEA are rowed out-of-line bodies.
// Zero Hour Common/INI.h proves the retained field/accessor vocabulary and
// prohibits copying. The two indices and unknown member storage stay neutral.
// Method names and signatures are the ledger's own INI rows at these RVAs:
// getSeps: 0x0002BAD5.
// getSepsPercent: 0x0002BADC.
// getSepsColon: 0x0002BAE3.
// getSepsQuote: 0x0002BAEA.
// isValidINIFilename: 0x0002BB7F.
// rva0002BBDE: 0x0002BBDE.
// getLineNum: 0x0002BBED.
// scanIndexList: 0x0002BD39.
// scanLookupList: 0x0002BD85.
// isEndOfBlock: 0x0002BDF2.
// unPrepFile: 0x0002BF4A.
// rva0002BFE5: 0x0002BFE5.
// getFilename: 0x0002C005.
// parseLine: 0x0002C0F5.
// isDeclarationOfType: 0x0002C2C7.
// rva0002CBCC: 0x0002CBCC.
// INI: 0x0002CDB0.
// ~INI: 0x0002CE5B.
// preprocessMacro: 0x0002D0A9.
// scanBool: 0x0002D14A.
// prepFile: 0x0002D2C1.
// readLine: 0x0002D669.
// rva0002D6F8: 0x0002D6F8.
// initFromINIMulti: 0x0002D7A8.
// load: 0x0002DA4B.
// loadFile: 0x0002DC75.
// loadBlock: 0x0002DD38.
// rva0002DE3C: 0x0002DE3C.
// initFromINI: 0x0002DE78.
// initFromINIMultiProc: 0x0002DEB5.
// getNextTokenOrNull: 0x0002DEED.
// getNextToken: 0x0002DF97.
// rva0002DFE2: 0x0002DFE2.
// rva0002E03D: 0x0002E03D.
// getNextSubToken: 0x0002E06B.
// parseIntMathExpression: 0x0002E0C9.
// parseUnsignedIntMathExpression: 0x0002E299.
// parseMathExpression: 0x0002E46A.
// loadDirectory: 0x0002E63B.
// parseBool: 0x0002E850.
// parseBitInInt32: 0x0002E86C.
// parseAsciiStringVectorAppend: 0x0002E896.
// getNextQuotedAsciiString: 0x0002E93F.
// getNextAsciiString: 0x0002EA4F.
// parseBitString32: 0x0002EB38.
// parseIndexList: 0x0002EC4E.
// dup_002EC6E: 0x0002EC6E.
// parseLookupList: 0x0002ECAF.
// scanInt: 0x0002ECCF.
// scanUnsignedInt: 0x0002ED3A.
// scanReal: 0x0002EDA5.
// dup_002EE10: 0x0002EE10.
// parseByte: 0x0002EE22.
// parseUnsignedByte: 0x0002EE6D.
// parseShort: 0x0002EEB9.
// parseUnsignedShort: 0x0002EF09.
// parseInt: 0x0002EF56.
// parseUnsignedInt: 0x0002EF72.
// parseReal: 0x0002EFC0.
// parsePositiveNonZeroReal: 0x0002EFDC.
// dup_002F02F: 0x0002F02F.
// dup_002F082: 0x0002F082.
// parseAngleReal: 0x0002F0D5.
// dup_002F0F7: 0x0002F0F7.
// parseAsciiString: 0x0002F11E.
// parseQuotedAsciiString: 0x0002F15A.
// parseAsciiStringVector: 0x0002F196.
// parsePercentToReal: 0x0002F1BA.
// parseBitString8: 0x0002F1DC.
// parseBitString16: 0x0002F21A.
// parseRGBColor: 0x0002F259.
// parseRGBAColorInt: 0x0002F2FF.
// parseColorInt: 0x0002F3FE.
// parseCoord3D: 0x0002F507.
// parseCoord2D: 0x0002F558.
// Rva002F592_ParseArmyPlacementPos: 0x0002F592.
// parseICoord2D: 0x0002F5BA.
// parseAudioSettingsDefinition: 0x0004171A.
// Rva000B2D93_ParseShadowReal: 0x000B2D93.
// Rva000B2DBB_ParseShadowAsciiString: 0x000B2DBB.
// Rva000B2DE3_ParseShadowBool: 0x000B2DE3.
// Rva000B6E5A_ParseLowercasedString: 0x000B6E5A.
// Rva000B6E9E_ParseTurretArtAngle: 0x000B6E9E.
// Rva000B6EBE_ParseTurretArtPitch: 0x000B6EBE.
// Rva000B9AFF_ParseShadowEvent: 0x000B9AFF.
// Rva000C2B23_ParseModelName: 0x000C2B23.
// Rva000C2C5FParseBoneRecord: 0x000C2C5F.
// Rva000C2CA4ParseTurretPitch: 0x000C2CA4.
// Rva000C3824_ParseTexturePair: 0x000C3824.
// Rva000C3AB3Parse: 0x000C3AB3.
// Rva000C3B6EParse: 0x000C3B6E.
// Rva000C3C59Parse: 0x000C3C59.
// parseAIDataDefinition: 0x001D8E7A.
// parseTerrainBridgeDefinition: 0x001DAEB8.
// parseControlBarSchemeDefinition: 0x001DB68C.
// parseWindowTransitions: 0x001DC66F.
// Rva001DCAED_ParseTransition: 0x001DCAED.
// parseDrawGroupNumberDefinition: 0x001DCC9F.
// parseMiscEvaData: 0x001DCFE5.
// parseLanguageDefinition: 0x001EA3F4.
// parseMappedImageDefinition: 0x001ED63C.
// parseMiscAudio: 0x001ED6EE.
// parseMouseDefinition: 0x001EE050.
// parseMouseCursorDefinition: 0x001EF2CB.
// parseMultiplayerSettingsDefinition: 0x001EF367.
// parseMultiplayerColorDefinition: 0x001EF3BF.
// parseOnlineChatColorDefinition: 0x001EF471.
// parseObjectDefinition: 0x001EFFC6.
// parseObjectReskinDefinition: 0x001F0016.
// parseChildObjectDefinition: 0x001F008C.
// parseParticleSystemDefinition: 0x001FD0B4.
// Rva001FDD33_ParseResourceModifierValues: 0x001FDD33.
// parseTerrainRoadDefinition: 0x001FF288.
// parseShellMenuSchemeDefinition: 0x00200984.
// parseTerrainDefinition: 0x00200A65.
// parseWaterSettingDefinition: 0x00200BEB.
// parseWaterTransparencyDefinition: 0x00200EE4.
// parseWeatherDefinition: 0x0020187A.
// parseHeaderTemplateDefinition: 0x00201CAF.
// parseDynamicGameLODLevel: 0x002025AC.
// parseBenchProfile: 0x002026D4.
// parseLODPreset: 0x00202E23.
// parseStaticGameLODDefinition: 0x00202F05.
// parseAudioLODDefinition: 0x00202F8A.
// Rva002216A6_ParseDefaultMessageColor: 0x002216A6.
// Rva00221714_ParseDefaultOpenAudio: 0x00221714.
// Rva0022175F_ParseDefaultMessageFont: 0x0022175F.
// Rva002890D1_ParseUpgradeList: 0x002890D1.
// Rva00289228_ParseRealList: 0x00289228.
// parseInGameUIDefinition: 0x0029A627.
// parseTerrainResourceClaimDecal: 0x0029B919.
// Rva002A8845_ParseProbability: 0x002A8845.
// Rva002A8945_ParseCombatChainDefinition: 0x002A8945.
// Rva002A898A_ParseBrutalDifficultyCheats: 0x002A898A.
// Rva002A89D2_ParseDifficultyTuning: 0x002A89D2.
// Rva002C5E40_ParseAITarget: 0x002C5E40.
// Rva002C5E8F_ParseAITargetList: 0x002C5E8F.
// parseAnim2DDefinition: 0x002D7554.
// Rva00318242_ParseNamedReal: 0x00318242.
// parseAngularVelocityReal: 0x003389DD.
// parseFXList: 0x00338A09.
// parseObjectCreationList: 0x00338A6F.
// scanScience: 0x00338A8D.
// parseGameClientRandomVariable: 0x00338A9D.
// parseDurationReal: 0x00338B0A.
// parseDurationUnsignedInt: 0x00338B30.
// parseDurationUnsignedShort: 0x00338B76.
// parseVelocityReal: 0x00338BBD.
// parseAccelerationReal: 0x00338BE3.
// parseVeterancyLevelFlags: 0x00338C0F.
// parseDamageTypeFlags: 0x00338CD0.
// parseDeathTypeFlags: 0x00338D91.
// Rva00338E52_ParseEnvelope: 0x00338E52.
// parseMappedImage: 0x003390B2.
// parseAnim2DTemplate: 0x00339109.
// parseThingTemplate: 0x0033940F.
// parseArmorTemplate: 0x003394FB.
// parseWeaponTemplate: 0x00339569.
// parseParticleSystemTemplate: 0x003395BB.
// parseDamageFX: 0x0033962F.
// parseUpgradeTemplate: 0x00339679.
// Rva003396D3_ParseKillerScience: 0x003396D3.
// parseScience: 0x003396D3.
// Rva00339761_ParseDurationUnsignedByte: 0x00339761.
// parseAndTranslateLabel: 0x0033987B.
// parseAudioEventRTS: 0x00339900.
// parseSpecialPowerTemplate: 0x00339918.
// Rva00339A13_ParseUpgradeKeyList: 0x00339A13.
// parseScienceVector: 0x00339AF1.
// Rva00339B50_ParseSpecialAbilities: 0x00339B50.
// Rva00339E1C_ParseBrowser: 0x00339E1C.
// Rva0033A167_ParseSoundRefList: 0x0033A167.
// Rva0033A1CE_ParseSoundList: 0x0033A1CE.
// Rva0033A49B_ParseDecal: 0x0033A49B.
// Rva0033B938_ParseTranslatedLabel: 0x0033B938.
// Rva0039A4FC_ParseNameCountList: 0x0039A4FC.
// Rva0039A565_ParseNameNameReal: 0x0039A565.
// Rva003EEABF_ParseAsciiString: 0x003EEABF.
// Rva003F156F_ParseRegionBonus: 0x003F156F.
// Rva003F1FD0_ParseGiveUpgrade: 0x003F1FD0.
// Rva003F2033_ParseOnVictoryGiveUpgrade: 0x003F2033.
// Rva003F341E_ParseConnections: 0x003F341E.
// Rva0041F524_ParseArmyMember: 0x0041F524.
// iniParseAnimAndDuration: 0x0044E6CD.
// Rva0045A22E_ParseQuery: 0x0045A22E.
// Rva004B2B64_ParseReplaceObject: 0x004B2B64.
// Rva004B60D5_ParsePercentage: 0x004B60D5.
// iniParseAnim: 0x004B6481.
// Rva004C2918_ParseUpgradeMoneyAmount: 0x004C2918.
// Rva004C381C_ParseUpgradeOCL: 0x004C381C.
// Rva004C3859_ParseUpgradeName: 0x004C3859.
// Rva004C3F48_ParseNamedReal: 0x004C3F48.
// Rva004C8F94_ParseSpawnObject: 0x004C8F94.
// Rva004CAB3D_ParseVoicePriority: 0x004CAB3D.
// Rva004DC625_ParseThreatBelow: 0x004DC625.
// Rva004DC64F_ParseThreatAbove: 0x004DC64F.
// Rva004DC745_ParseAIState: 0x004DC745.
// Rva004E3816Parse: 0x004E3816.
// Rva004E8E57_ParseAIKindOf: 0x004E8E57.
// Rva004E8EFF_ParseDisabledSlots: 0x004E8EFF.
// Rva005096FF_ParseWeaponSlot: 0x005096FF.
// parseMapCacheDefinition: 0x005350BA.
// Rva00563EA8_ParseEventFX: 0x00563EA8.
// parseCredits: 0x005B72A5.
// parseVideoDefinition: 0x0075A4DC.

#pragma once

#ifndef __BFME2_INI_H_
#define __BFME2_INI_H_

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class File;
class MultiIniFieldParse;
class Xfer;
struct FieldParse;
struct LookupListRec;
enum INILoadType;
enum ScienceType;

class INI
{
public:
	const char *getSeps() const;
	const char *getSepsPercent() const;
	const char *getSepsColon() const;
	const char *getSepsQuote() const;
protected:
	static bool isValidINIFilename(const char *filename);
public:
	int rva0002BBDE() const;
	int getLineNum() const;
	int scanIndexList(const char *token, const char *const *nameList);
	int scanLookupList(const char *token, const LookupListRec *lookupList);
	static bool isEndOfBlock(char *bufferToCheck);
protected:
	void unPrepFile();
public:
	AsciiString rva0002BFE5() const;
	AsciiString getFilename() const;
	void parseLine(AsciiString &filename);
	static bool isDeclarationOfType(AsciiString blockType, AsciiString blockName, char *bufferToCheck);
	void rva0002CBCC(const AsciiString &text, char value);
	INI();
	~INI();
	static const char *preprocessMacro(const char *token);
	bool scanBool(const char *token);
protected:
	bool prepFile(const AsciiString &filename, INILoadType loadType);
	void readLine();
public:
	AsciiString rva0002D6F8();
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
	void load(AsciiString filename, INILoadType loadType, Xfer *xfer, void (*parse)(INI *));
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer);
	bool loadBlock(AsciiString filename, AsciiString blockType, AsciiString blockName, INILoadType loadType, Xfer *xfer);
	static void rva0002DE3C(INI *ini, void *instance, void *store, const void *userData);
	void initFromINI(void *what, const FieldParse *parseTable);
	void initFromINIMultiProc(void *what, void (*proc)(MultiIniFieldParse &));
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getNextToken(const char *seps = 0);
	const char *rva0002DFE2(const char *seps, bool *substituted);
	const char *rva0002E03D(const char *seps, bool *substituted);
	const char *getNextSubToken(const char *expected);
	int parseIntMathExpression(const char *token, int (INI::*scan)(const char *));
	unsigned int parseUnsignedIntMathExpression(const char *token, unsigned int (INI::*scan)(const char *));
	float parseMathExpression(const char *token, float (INI::*scan)(const char *));
	bool loadDirectory(AsciiString dirName, bool subdirs, INILoadType loadType, Xfer *xfer, int fileFilter);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseBitInInt32(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiStringVectorAppend(INI *ini, void *instance, void *store, const void *userData);
	AsciiString getNextQuotedAsciiString();
	AsciiString getNextAsciiString();
	static void parseBitString32(INI *ini, void *instance, void *store, const void *userData);
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
	static void dup_002EC6E(INI *ini, void *instance, void *store, const void *userData);
	static void parseLookupList(INI *ini, void *instance, void *store, const void *userData);
	int scanInt(const char *token);
	unsigned int scanUnsignedInt(const char *token);
	float scanReal(const char *token);
	float dup_002EE10(const char *token);
	static void parseByte(INI *ini, void *instance, void *store, const void *userData);
	static void parseUnsignedByte(INI *ini, void *instance, void *store, const void *userData);
	static void parseShort(INI *ini, void *instance, void *store, const void *userData);
	static void parseUnsignedShort(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parsePositiveNonZeroReal(INI *ini, void *instance, void *store, const void *userData);
	static void dup_002F02F(INI *ini, void *instance, void *store, const void *userData);
	static void dup_002F082(INI *ini, void *instance, void *store, const void *userData);
	static void parseAngleReal(INI *ini, void *instance, void *store, const void *userData);
	static void dup_002F0F7(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseQuotedAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiStringVector(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseBitString8(INI *ini, void *instance, void *store, const void *userData);
	static void parseBitString16(INI *ini, void *instance, void *store, const void *userData);
	static void parseRGBColor(INI *ini, void *instance, void *store, const void *userData);
	static void parseRGBAColorInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseColorInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
	static void parseCoord2D(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002F592_ParseArmyPlacementPos(INI *ini, void *instance, void *store, const void *userData);
	static void parseICoord2D(INI *ini, void *instance, void *store, const void *userData);
	static void parseAudioSettingsDefinition(INI *ini);
	static void Rva000B2D93_ParseShadowReal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B2DBB_ParseShadowAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B2DE3_ParseShadowBool(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B6E5A_ParseLowercasedString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B6E9E_ParseTurretArtAngle(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B6EBE_ParseTurretArtPitch(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B9AFF_ParseShadowEvent(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C2B23_ParseModelName(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C2C5FParseBoneRecord(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C2CA4ParseTurretPitch(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C3824_ParseTexturePair(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C3AB3Parse(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C3B6EParse(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C3C59Parse(INI *ini, void *instance, void *store, const void *userData);
	static void parseAIDataDefinition(INI *ini);
	static void parseTerrainBridgeDefinition(INI *ini);
	static void parseControlBarSchemeDefinition(INI *ini);
	static void parseWindowTransitions(INI *ini);
	static void Rva001DCAED_ParseTransition(INI *ini, void *instance, void *store, const void *userData);
	static void parseDrawGroupNumberDefinition(INI *ini);
	static void parseMiscEvaData(INI *ini);
	static void parseLanguageDefinition(INI *ini);
	static void parseMappedImageDefinition(INI *ini);
	static void parseMiscAudio(INI *ini);
	static void parseMouseDefinition(INI *ini);
	static void parseMouseCursorDefinition(INI *ini);
	static void parseMultiplayerSettingsDefinition(INI *ini);
	static void parseMultiplayerColorDefinition(INI *ini);
	static void parseOnlineChatColorDefinition(INI *ini);
	static void parseObjectDefinition(INI *ini);
	static void parseObjectReskinDefinition(INI *ini);
	static void parseChildObjectDefinition(INI *ini);
	static void parseParticleSystemDefinition(INI *ini);
	static void Rva001FDD33_ParseResourceModifierValues(INI *ini, void *instance, void *store, const void *userData);
	static void parseTerrainRoadDefinition(INI *ini);
	static void parseShellMenuSchemeDefinition(INI *ini);
	static void parseTerrainDefinition(INI *ini);
	static void parseWaterSettingDefinition(INI *ini);
	static void parseWaterTransparencyDefinition(INI *ini);
	static void parseWeatherDefinition(INI *ini);
	static void parseHeaderTemplateDefinition(INI *ini);
	static void parseDynamicGameLODLevel(INI *ini, void *instance, void *store, const void *userData);
	static void parseBenchProfile(INI *ini);
	static void parseLODPreset(INI *ini);
	static void parseStaticGameLODDefinition(INI *ini);
	static void parseAudioLODDefinition(INI *ini);
	static void Rva002216A6_ParseDefaultMessageColor(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00221714_ParseDefaultOpenAudio(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0022175F_ParseDefaultMessageFont(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002890D1_ParseUpgradeList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00289228_ParseRealList(INI *ini, void *instance, void *store, const void *userData);
	static void parseInGameUIDefinition(INI *ini);
	static void parseTerrainResourceClaimDecal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002A8845_ParseProbability(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002A8945_ParseCombatChainDefinition(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002A898A_ParseBrutalDifficultyCheats(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002A89D2_ParseDifficultyTuning(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002C5E40_ParseAITarget(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002C5E8F_ParseAITargetList(INI *ini, void *instance, void *store, const void *userData);
	static void parseAnim2DDefinition(INI *ini);
	static void Rva00318242_ParseNamedReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseAngularVelocityReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static ScienceType scanScience(const char *token);
	static void parseGameClientRandomVariable(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedShort(INI *ini, void *instance, void *store, const void *userData);
	static void parseVelocityReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseAccelerationReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseVeterancyLevelFlags(INI *ini, void *instance, void *store, const void *userData);
	static void parseDamageTypeFlags(INI *ini, void *instance, void *store, const void *userData);
	static void parseDeathTypeFlags(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00338E52_ParseEnvelope(INI *ini, void *instance, void *store, const void *userData);
	static void parseMappedImage(INI *ini, void *instance, void *store, const void *userData);
	static void parseAnim2DTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void parseThingTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void parseArmorTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void parseWeaponTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void parseParticleSystemTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void parseDamageFX(INI *ini, void *instance, void *store, const void *userData);
	static void parseUpgradeTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void Rva003396D3_ParseKillerScience(INI *ini, void *instance, void *store, const void *userData);
	static void parseScience(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00339761_ParseDurationUnsignedByte(INI *ini, void *instance, void *store, const void *userData);
	static void parseAndTranslateLabel(INI *ini, void *instance, void *store, const void *userData);
	static void parseAudioEventRTS(INI *ini, void *instance, void *store, const void *userData);
	static void parseSpecialPowerTemplate(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00339A13_ParseUpgradeKeyList(INI *ini, void *instance, void *store, const void *userData);
	static void parseScienceVector(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00339B50_ParseSpecialAbilities(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00339E1C_ParseBrowser(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0033A167_ParseSoundRefList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0033A1CE_ParseSoundList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0033A49B_ParseDecal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0033B938_ParseTranslatedLabel(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0039A4FC_ParseNameCountList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0039A565_ParseNameNameReal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva003EEABF_ParseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva003F156F_ParseRegionBonus(INI *ini, void *instance, void *store, const void *userData);
	static void Rva003F1FD0_ParseGiveUpgrade(INI *ini, void *instance, void *store, const void *userData);
	static void Rva003F2033_ParseOnVictoryGiveUpgrade(INI *ini, void *instance, void *store, const void *userData);
	static void Rva003F341E_ParseConnections(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0041F524_ParseArmyMember(INI *ini, void *instance, void *store, const void *userData);
	static void iniParseAnimAndDuration(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0045A22E_ParseQuery(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004B2B64_ParseReplaceObject(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004B60D5_ParsePercentage(INI *ini, void *instance, void *store, const void *userData);
	static void iniParseAnim(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004C2918_ParseUpgradeMoneyAmount(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004C381C_ParseUpgradeOCL(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004C3859_ParseUpgradeName(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004C3F48_ParseNamedReal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004C8F94_ParseSpawnObject(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004CAB3D_ParseVoicePriority(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004DC625_ParseThreatBelow(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004DC64F_ParseThreatAbove(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004DC745_ParseAIState(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004E3816Parse(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004E8E57_ParseAIKindOf(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004E8EFF_ParseDisabledSlots(INI *ini, void *instance, void *store, const void *userData);
	static void Rva005096FF_ParseWeaponSlot(INI *ini, void *instance, void *store, const void *userData);
	static void parseMapCacheDefinition(INI *ini);
	static void Rva00563EA8_ParseEventFX(INI *ini, void *instance, void *store, const void *userData);
	static void parseCredits(INI *ini);
	static void parseVideoDefinition(INI *ini);

	INILoadType getLoadType() const { return m_loadType; }
	bool isEOF() const { return m_endOfFile; }

private:
	INI(const INI &);
	INI &operator=(const INI &);

public:
	File *m_file;
	AsciiString m_filename;
	INILoadType m_loadType;
	unsigned int m_field0c;
	unsigned int m_field10;
	char m_buffer[0x404];
	const char *m_seps;
	const char *m_sepsPercent;
	const char *m_sepsColon;
	const char *m_sepsQuote;
	const char *m_blockEndToken;
	const char *m_field42c;
	bool m_endOfFile;
	char m_curBlockStart[0x404];
	unsigned int m_field838[0x34 / 4];
	AsciiString m_field86c;
	void *m_field870[3];
};

#endif
