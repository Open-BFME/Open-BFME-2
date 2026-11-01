// Copied from reference/open-bfme-1/inputs/reference/shims/gamelod/Common/GameLOD.h.
// TU-scoped shim: Zero Hour's GameLOD.h plus GameLODManager::getAudioLODIndex,
// which BFME adds and Zero Hour has no counterpart for. Nothing else differs.

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

// FILE: GameLOD.h ///////////////////////////////////////////////////////////
//
// Used to set detail levels of various game systems.
//
// Author: Mark Wilczynski, Sept 2002
//
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _GAME_LOD_H_
#define _GAME_LOD_H_

enum ParticlePriorityType;

#define MAX_LOD_PRESETS_PER_LEVEL	32	//number of hardware configs preset for each low,medium,high
#define MAX_BENCH_PROFILES	16

//Make sure this enum stays in sync with GameLODNames[]
enum StaticGameLODLevel
{
	STATIC_GAME_LOD_UNKNOWN=-1,
	// BFME 2: init (0x002027EA) uses low 1, high 3 and custom 5.
	STATIC_GAME_LOD_LOW=1,
	STATIC_GAME_LOD_MEDIUM,
	STATIC_GAME_LOD_HIGH,
	STATIC_GAME_LOD_CUSTOM=5,	//make sure this remains last!
	STATIC_GAME_LOD_COUNT
};

enum DynamicGameLODLevel
{
	DYNAMIC_GAME_LOD_UNKNOWN=-1,
	// BFME has a fifth level ahead of LOW: the name table parseDynamicGameLODLevel
	// (0x0007C390) walks holds five entries starting at "VeryLow", and its loop
	// compares against 5.
	DYNAMIC_GAME_LOD_VERY_LOW,
	DYNAMIC_GAME_LOD_LOW,
	DYNAMIC_GAME_LOD_MEDIUM,
	DYNAMIC_GAME_LOD_HIGH,
	DYNAMIC_GAME_LOD_VERY_HIGH,
	DYNAMIC_GAME_LOD_COUNT
};

//Make sure this stays in sync with CPUNames[] in gamelod.cpp
enum CpuType
{
	XX,	//unknown type
	P3,
	P4,
	K7,
};

//Keep this in sync with VideoNames in Gamelod.cpp
enum ChipsetType
{	DC_UNKNOWN,
	DC_VOODOO2,
	DC_VOODOO3,
	DC_VOODOO4,
	DC_VOODOO5,
	DC_TNT,
	DC_TNT2,
	DC_GEFORCE2,
	DC_RADEON,
	DC_GENERIC_PIXEL_SHADER_1_1,
	DC_GEFORCE3,
	DC_GEFORCE4,
	DC_GENERIC_PIXEL_SHADER_1_4,
	DC_RADEON_8500,
	DC_GENERIC_PIXEL_SHADER_2_0,
	DC_RADEON_9700,
	DC_MAX
};

struct StaticGameLODInfo
{
	StaticGameLODInfo();
	//Static LOD constants
	Int m_minFPS;	///< minimum fps in order to recommend this LOD.
	Int m_minProcessorFPS;	///< minimum CPU time (in ms) to recommend this LOD.
	Int m_sampleCount2D; ///<How many 2-D (UI) samples should we allow simultaneously (Note: Hardware may support less than the desired number)
	Int m_sampleCount3D; ///<How many 3-D (World) samples should we allow simultaneously (Note: Hardware may support less than the desired number)
	Int m_streamCount; ///<How many streaming audio things should we allow simultaneously (Note: Hardware may support less than the desired number)
	Int m_maxParticleCount; ///<maximum number of particles that can exist
	Bool m_useShadowVolumes;	///<use volumetric shadows if available.
	Bool m_useShadowDecals;	///<use 2D Decal shadows.
	Bool m_useCloudMap;	///<use cloud shadows scrolling over terrain.
	Bool m_useLightMap;	///<use noise pattern over terrain to break up tiling.
	Bool m_showSoftWaterEdge;	///<feather water edge if supported by hardware.
	Int m_maxTankTrackEdges;	///<maximum length of tank track
	Int m_maxTankTrackOpaqueEdges;	///<maximum length of tank track before it starts fading.
	Int m_maxTankTrackFadeDelay;	///<maximum amount of time a tank track segment remains visible.
	Bool m_useBuildupScaffolds;		///<draw scaffold during structure building.
	Bool m_useTreeSway;		///<sway trees to simulate wind.
	Bool m_useEmissiveNightMaterials; ///<perform second lighting pass on night buildings. 
	Bool m_useHeatEffects;			///<draw heat distortion effects (i.e Microwave Tank).
	Int m_textureReduction;	///<reduce texture resolution by dividing in half n times.
	Bool m_useFpsLimit;	///<don't lock fps to 30hz
	Bool m_enableDynamicLOD;	///<don't do dynamic lod based on current fps.
	Bool m_useTrees;			///<don't include trees on map.

};

struct DynamicGameLODInfo
{
	DynamicGameLODInfo();
	//Dynamic LOD constants
	Int m_minFPS;	///< minimum fps in order to recommend his LOD.
	UnsignedInt m_dynamicParticleSkipMask;
	UnsignedInt m_dynamicDebrisSkipMask;
	Real m_slowDeathScale;
	ParticlePriorityType m_minDynamicParticlePriority;
	ParticlePriorityType m_minDynamicParticleSkipPriority;
};

struct LODPresetInfo
{
	// BFME 2: constructor 0x00201D48 initializes the extra word and 800 by 600 resolution.
	LODPresetInfo() : m_cpuType(XX),m_mhz(1),m_cpuPerfIndex(1.0f),m_videoType(DC_UNKNOWN),m_memory(1),m_pad14(1),m_xResolution(800),m_yResolution(600) {};
	CpuType  m_cpuType;
	Int	 m_mhz;
	Real m_cpuPerfIndex;	//used to select preset for unidentified cpu's
	ChipsetType  m_videoType; // +0x0C
	Int  m_memory; // +0x10
	// BFME 2: constructor 0x00201D48 and selector 0x00203288 prove the 32-byte record.
	Int m_pad14;
	Int m_xResolution; // +0x18
	Int m_yResolution; // +0x1C
};

struct BenchProfile
{
	BenchProfile() : m_cpuType(XX),m_mhz(1),m_intBenchIndex(1.0f),m_floatBenchIndex(1.0f),m_memBenchIndex(1.0f) {};

	CpuType  m_cpuType;
	Int	 m_mhz;
	Real m_intBenchIndex;
	Real m_floatBenchIndex;
	Real m_memBenchIndex;
};

// BFME 2: constructor 0x00201EAC uses six 76-byte, five 16-byte and two 8-byte records.
struct Rva00201DC4LODInfo
{
    Rva00201DC4LODInfo();
    int m_modelLOD, m_effectsLOD, m_maxParticleCount;
    bool m_useShadowVolumes, m_useShadowDecals, m_useShadowMapping;
    int m_shadowLOD;
    bool m_useTerrainNormalMap, m_useDistanceDependantTerrainTextures;
    int m_waterLOD;
    bool m_showSoftWaterEdge;
    int m_maxTankTrackEdges, m_maxTankTrackOpaqueEdges, m_maxTankTrackFadeDelay, m_textureReduction;
    bool flag30;
    int m_animationDetail, m_shaderLOD;
    bool m_shaderMaterialReplacement, flag3D;
    int m_decalLOD, m_minParticlePriority, m_minParticleSkipPriority;
};

struct Rva00201E2BLODInfo
{
    Rva00201E2BLODInfo();
    int minimumFPS, particleSkipMask, debrisSkipMask;
    float slowDeathScale;
};

struct AudioLODInfo
{
    AudioLODInfo();
    int maximumAmbientStreams;
    bool allowDolby, allowReverb;
};

class GameLODManager
{
public:
	GameLODManager(void);
	~GameLODManager();

	const char *getStaticGameLODLevelName(StaticGameLODLevel level);
	const char *getDynamicGameLODLevelName(DynamicGameLODLevel level);
	// BFME 2: rows 0x00202678 and 0x002026A0 provide the audio level queries.
	const char *getAudioLODLevelName(int level);
	int findAudioLODLevel() const;
	StaticGameLODLevel findStaticLODLevel(void);	///< calculate the optimal static LOD level for this system.
	Bool setStaticLODLevel(StaticGameLODLevel level);	///< set the current static LOD level.
	StaticGameLODLevel getStaticLODLevel(void) { return m_currentStaticLOD;}
	DynamicGameLODLevel findDynamicLODLevel(Real averageFPS);	///<given an average fps, return the optimal dynamic LOD.
	Bool setDynamicLODLevel(DynamicGameLODLevel level);	///< set the current dynamic LOD level.
	DynamicGameLODLevel getDynamicLODLevel(void) { return m_currentDynamicLOD;}
	// BFME 2: row 0x002027EA takes the requested static level.
	void init(Int staticLevel);	///<initialize tables of preset LOD's.
	void setCurrentTextureReduction(Int val) {m_currentTextureReduction = val;}
	Int getCurrentTextureReduction(void) {return m_currentTextureReduction;}
	Int getStaticGameLODIndex(AsciiString name);
	Int getDynamicGameLODIndex(AsciiString name);
	// BFME-only, and the third of the set: the AudioLOD block's parser calls it
	// at 0x0007D0C0 exactly the way parseStaticGameLODDefinition calls
	// getStaticGameLODIndex, except that it takes its name by reference where the
	// static one takes a copy -- retail passes &name with no copy construction --
	// and with the same -1-for-unknown convention. Zero Hour has no audio LOD level
	// at all, so the name follows the two siblings rather than any literal.
	Int getAudioLODIndex(const AsciiString &name);
	inline Bool isParticleSkipped(void);
	inline Bool isDebrisSkipped(void);
	inline Real getSlowDeathScale(void);
	inline ParticlePriorityType getMinDynamicParticlePriority(void);		///<priority at which particles will still render at current FPS.
	inline ParticlePriorityType	getMinDynamicParticleSkipPriority(void);	///<priority at which particles will never be skipped at any FPS.
	Int getRecommendedTextureReduction(void);	///<return the optimal texture reduction for the system.
	Int getLevelTextureReduction(StaticGameLODLevel level);	///<return texture reduction specified in INI for this game detail.
	LODPresetInfo *newLODPreset(StaticGameLODLevel index);
	BenchProfile *newBenchProfile(void);
	Bool didMemPass( void );
	void setReallyLowMHz(Int mhz) { m_reallyLowMHz = mhz; }
	Bool isReallyLowMHz() const;	// BFME: out of line, retail 0x0007BC80 (GameLODManagerIsReallyLowMHz.cpp)

	// BFME 2: constructor 0x00201EAC places presets at 0x228 and benchmarks at 0x1628.
	Rva00201DC4LODInfo m_staticGameLODInfo[6];
	Rva00201E2BLODInfo m_dynamicGameLODInfo[5];
	AudioLODInfo m_audioLODInfo[2];
	LODPresetInfo m_lodPresets[5][MAX_LOD_PRESETS_PER_LEVEL]; // +0x228
	BenchProfile m_benchProfiles[MAX_BENCH_PROFILES]; // +0x1628

protected:
	void applyStaticLODLevel(StaticGameLODLevel level);
	void applyDynamicLODLevel(DynamicGameLODLevel level);
	void refreshCustomStaticLODLevel(void);	///<grabs current globaldata values and makes them the custom detail setting.

	static const FieldParse m_staticGameLODFieldParseTable[];
	// BFME 2: rows 0x002027EA and 0x00203288 address these scalar fields and counters.
	StaticGameLODLevel m_currentStaticLOD; // +0x1768
	DynamicGameLODLevel m_currentDynamicLOD;
	Int m_currentAudioLOD;
	Int controlParticles, controlProcessor, controlMinimum, controlCloud, controlSamples, controlStreams;
	Int m_numParticleGenerations;
	Int m_dynamicParticleSkipMask;
	Int m_numDebrisGenerations;
	Int m_dynamicDebrisSkipMask;
	Real m_slowDeathScale;
	ParticlePriorityType m_minDynamicParticlePriority;
	ParticlePriorityType m_minDynamicParticleSkipPriority;
	Bool m_videoPassed;
	Bool m_cpuPassed;
	Bool m_memPassed;
	Int m_numLevelPresets[5]; // +0x17AC
	Int m_numBenchProfiles; // +0x17C0
	StaticGameLODLevel m_idealDetailLevel; // +0x17C4
	ChipsetType m_videoChipType; // +0x17C8
	CpuType m_cpuType; // +0x17CC
	unsigned __int64 m_numRAM; // +0x17D0
	Int m_cpuFreq; // +0x17D8
	Real m_intBenchIndex;
	Real m_floatBenchIndex;
	Real m_memBenchIndex;
	Real m_compositeBenchIndex;
	Int m_currentTextureReduction;
	Int m_reallyLowMHz;
};

Bool GameLODManager::isParticleSkipped(void)
{
	return (++m_numParticleGenerations & m_dynamicParticleSkipMask) != m_dynamicParticleSkipMask;
}

Bool GameLODManager::isDebrisSkipped(void)
{
	return (++m_numDebrisGenerations & m_dynamicDebrisSkipMask) != m_dynamicDebrisSkipMask;
}

Real GameLODManager::getSlowDeathScale(void)
{
	return m_slowDeathScale;
}

ParticlePriorityType GameLODManager::getMinDynamicParticlePriority(void)
{
	return m_minDynamicParticlePriority;
}

ParticlePriorityType GameLODManager::getMinDynamicParticleSkipPriority(void)
{
	return m_minDynamicParticleSkipPriority;
}

extern GameLODManager *TheGameLODManager;
#endif _GAME_LOD_H_