// GlobalData: canonical BFME2 interface and target layout.
// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x0023631C calls SubsystemInterface at 0x00236331 (target 0x001B4E63) and stores table 0x00BED1C4 at 0x00236338. Destructor 0x002376CC restores that table at 0x002376DE and calls the parent destructor 0x001B4E74 at 0x00237A58. The parent's 0x00BD77A0 belongs to base construction/destruction, not to GlobalData.
// newOverride pushes sizeof 0x1254 at 0x00237A76, allocates at 0x00237A7B and calls the constructor at 0x00237A8F. The base occupies +0..+0xB; its constructor clears byte +4 and the AsciiString pointer +8.
// Table 0x00BED1C4 has fourteen slots: 0=0x00237CFD (deleting destructor), 1/3/8/10/12=0x000B3FD0 (ret), 2=0x001B5384 (SubsystemInterface::loadIniFilesFromLegend), 4=0x0023624A (vslot04(int), ret 4), 5=0x0047A699 (false), 6=0x002376C6 (vslot06(), returns 0x00BE8520), 7/13=0x0047A69C (ret 4), 9=0x00235736 (reset), 11=0x005CB9FF (false, ret 4). The first non-code word is at 0x00BED1FC. GlobalData is polymorphic; neutral inherited slots retain the parent's names.
// Rowed methods stay out of line: constructor 0x0023631C, destructor 0x002376CC, init/update 0x000B3FD0, reset 0x00235736, vslot04 0x0023624A, vslot06 0x002376C6, setTimeOfDay 0x002352BC, rva00235312 0x00235312, applyOptionPreferences 0x0023576A, newOverride 0x00237A6B, parseGameDataDefinition 0x00237AB1, getPicturePath 0x0023611A, rva002360DE 0x002360DE and rva002360FC 0x002360FC.
// The 457 non-null sixteen-byte INI records at 0x00BE8520 provide token, parser, user data and member offset; the following record is null. Named fields below use these target tokens, with existing spellings retained where equivalent. Unproved regions remain neutral storage. Field evidence follows as offset, width and retail record or instruction:
// +0x000C, 4 bytes, m_mapName: INI VA 0xbe8550: MapName, parseAsciiString RVA 0x2f11e.
// +0x0010, 4 bytes, m_moveHintName: INI VA 0xbe8560: MoveHintName, parseAsciiString RVA 0x2f11e.
// +0x0014, 4 bytes, m_genericDamageFieldName: INI VA 0xbe8570: GenericDamageFieldName, parseAsciiString RVA 0x2f11e.
// +0x0018, 4 bytes, m_genericDamageWarningName: INI VA 0xbe8580: GenericDamageWarningName, parseAsciiString RVA 0x2f11e.
// +0x001C, 1 bytes, m_showProps: INI VA 0xbe8590: ShowProps, parseBool RVA 0x2e850.
// +0x001D, 1 bytes, m_pushAsideShrubs: INI VA 0xbe85b0: PushAsideShrubs, parseBool RVA 0x2e850.
// +0x0020, 4 bytes, field0020: 0x0023635a: mov dword ptr [esi + 0x20], eax.
// +0x0024, 1 bytes, field0024: 0x0023635d: mov byte ptr [esi + 0x24], bl.
// +0x0025, 1 bytes, field0025: 0x00236360: mov byte ptr [esi + 0x25], al.
// +0x0026, 1 bytes, m_useFpsLimit: INI VA 0xbe85a0: UseFPSLimit, parseBool RVA 0x2e850.
// +0x0027, 1 bytes, m_dumpAssetUsage: INI VA 0xbe85c0: DumpAssetUsage, parseBool RVA 0x2e850.
// +0x0028, 4 bytes, m_framesPerSecondLimit: INI VA 0xbe85d0: FramesPerSecondLimit, parseInt RVA 0x2ef56.
// +0x002C, 1 bytes, m_windowed: INI VA 0xbe8520: Windowed, parseBool RVA 0x2e850.
// +0x002D, 1 bytes, m_skipMapUnroll: INI VA 0xbe94d0: SkipMapUnroll, parseBool RVA 0x2e850.
// +0x0030, 4 bytes, m_xResolution: INI VA 0xbe8530: XResolution, parseInt RVA 0x2ef56.
// +0x0034, 4 bytes, m_yResolution: INI VA 0xbe8540: YResolution, parseInt RVA 0x2ef56.
// +0x0038, 4 bytes, m_maxShellScreens: INI VA 0xbe85e0: MaxShellScreens, parseInt RVA 0x2ef56.
// +0x003C, 1 bytes, m_useCloudMap: INI VA 0xbe85f0: UseCloudMap, parseBool RVA 0x2e850.
// +0x003D, 1 bytes, m_showWater: INI VA 0xbe8600: ShowWater, parseBool RVA 0x2e850.
// +0x003E, 1 bytes, m_showRoads: INI VA 0xbe8610: ShowRoads, parseBool RVA 0x2e850.
// +0x003F, 1 bytes, m_showTrees: INI VA 0xbe8620: ShowTrees, parseBool RVA 0x2e850.
// +0x0040, 1 bytes, m_allowTreeFading: INI VA 0xbe8630: AllowTreeFading, parseBool RVA 0x2e850.
// +0x0041, 1 bytes, m_useReverseMouseScroll: INI VA 0xbe86a0: UseReverseMouseScroll, parseBool RVA 0x2e850.
// +0x0044, 4 bytes, m_use3WayTerrainBlends: INI VA 0xbe8660: Use3WayTerrainBlends, parseInt RVA 0x2ef56.
// +0x0048, 1 bytes, m_useLightMap: INI VA 0xbe8640: UseLightMap, parseBool RVA 0x2e850.
// +0x0049, 1 bytes, field0049: 0x0023639b: mov byte ptr [esi + 0x49], al.
// +0x004A, 1 bytes, field004A: 0x0023639e: mov byte ptr [esi + 0x4a], al.
// +0x004B, 1 bytes, m_adjustCliffTextures: INI VA 0xbe8650: AdjustCliffTextures, parseBool RVA 0x2e850.
// +0x004C, 1 bytes, m_stretchTerrain: INI VA 0xbe8670: StretchTerrain, parseBool RVA 0x2e850.
// +0x004D, 1 bytes, m_useHalfHeightMap: INI VA 0xbe8680: UseHalfHeightMap, parseBool RVA 0x2e850.
// +0x004E, 1 bytes, m_drawEntireTerrain: INI VA 0xbe8700: DrawEntireTerrain, parseBool RVA 0x2e850.
// +0x0050, 4 bytes, m_terrainLOD: INI VA 0xbe8710: TerrainLOD, parseIndexList RVA 0x2ec4e.
// +0x0054, 1 bytes, field0054: 0x002363b4: mov byte ptr [esi + 0x54], al.
// +0x0058, 4 bytes, m_terrainLODTargetTimeMS: INI VA 0xbe8720: TerrainLODTargetTimeMS, parseInt RVA 0x2ef56.
// +0x005C, 1 bytes, field005C: 0x002363ba: mov byte ptr [esi + 0x5c], al.
// +0x005D, 1 bytes, m_rightMouseAlwaysScrolls: INI VA 0xbe8730: RightMouseAlwaysScrolls, parseBool RVA 0x2e850.
// +0x005E, 1 bytes, field005E: 0x002363c0: mov byte ptr [esi + 0x5e], bl.
// +0x005F, 1 bytes, m_useCloudPlane: INI VA 0xbe8740: UseCloudPlane, parseBool RVA 0x2e850.
// +0x0060, 1 bytes, m_useShadowVolumes: INI VA 0xbe8760: UseShadowVolumes, parseBool RVA 0x2e850.
// +0x0061, 1 bytes, m_useShadowDecals: INI VA 0xbe8770: UseShadowDecals, parseBool RVA 0x2e850.
// +0x0062, 1 bytes, m_useShadowMapping: INI VA 0xbe8780: UseShadowMapping, parseBool RVA 0x2e850.
// +0x0064, 4 bytes, field0064: 0x002363cf: mov dword ptr [esi + 0x64], ebx.
// +0x0068, 1 bytes, m_useBehindBuildingMarker: INI VA 0xbe87d0: UseBehindBuildingMarker, parseBool RVA 0x2e850.
// +0x006C, 4 bytes, m_waterPositionX: INI VA 0xbe87e0: WaterPositionX, parseReal RVA 0x2efc0.
// +0x0070, 4 bytes, m_waterPositionY: INI VA 0xbe87f0: WaterPositionY, parseReal RVA 0x2efc0.
// +0x0074, 4 bytes, m_waterPositionZ: INI VA 0xbe8800: WaterPositionZ, parseReal RVA 0x2efc0.
// +0x0078, 4 bytes, m_waterExtentX: INI VA 0xbe8810: WaterExtentX, parseReal RVA 0x2efc0.
// +0x007C, 4 bytes, m_waterExtentY: INI VA 0xbe8820: WaterExtentY, parseReal RVA 0x2efc0.
// +0x0080, 4 bytes, m_waterType: INI VA 0xbe8830: WaterType, parseInt RVA 0x2ef56.
// +0x0084, 1 bytes, m_showSoftWaterEdge: INI VA 0xbe8850: ShowSoftWaterEdge, parseBool RVA 0x2e850.
// +0x0085, 1 bytes, field0085: 0x002363fa: mov byte ptr [esi + 0x85], bl.
// +0x0086, 1 bytes, m_liveCampaignMode: INI VA 0xbe86c0: LiveCampaignMode, parseBool RVA 0x2e850.
// +0x0087, 1 bytes, m_hideLivingWorldRegions: INI VA 0xbe86d0: HideLivingWorldRegions, parseBool RVA 0x2e850.
// +0x0088, 1 bytes, m_livingWorldTurbo: INI VA 0xbe86f0: LivingWorldTurbo, parseBool RVA 0x2e850.
// +0x0090, 4 bytes, m_featherWater: INI VA 0xbe8840: FeatherWater, parseInt RVA 0x2ef56.
// +0x0094, 4 bytes, m_downwindAngle: INI VA 0xbe8750: DownwindAngle, parseReal RVA 0x2efc0.
// +0x0098, 4 bytes, field0098: 0x00236446: movss dword ptr [esi + 0x98], xmm0.
// +0x009C, 4 bytes, m_defaultCameraMinHeight: INI VA 0xbe88a0: DefaultCameraMinHeight, parseReal RVA 0x2efc0.
// +0x00A0, 4 bytes, m_defaultCameraMaxHeight: INI VA 0xbe88b0: DefaultCameraMaxHeight, parseReal RVA 0x2efc0.
// +0x00A4, 4 bytes, m_defaultCameraPitchAngle: INI VA 0xbe88c0: DefaultCameraPitchAngle, parseReal RVA 0x2efc0.
// +0x00A8, 4 bytes, m_defaultCameraYawAngle: INI VA 0xbe88d0: DefaultCameraYawAngle, parseReal RVA 0x2efc0.
// +0x00AC, 4 bytes, m_defaultCameraScrollSpeedScalar: INI VA 0xbe88e0: DefaultCameraScrollSpeedScalar, parseReal RVA 0x2efc0.
// +0x00B0, 4 bytes, m_terrainHeightAtEdgeOfMap: INI VA 0xbe8910: TerrainHeightAtEdgeOfMap, parseReal RVA 0x2efc0.
// +0x00B4, 4 bytes, m_unitDamagedThreshold: INI VA 0xbe8920: UnitDamagedThreshold, parseReal RVA 0x2efc0.
// +0x00B8, 4 bytes, m_unitReallyDamagedThreshold: INI VA 0xbe8930: UnitReallyDamagedThreshold, parseReal RVA 0x2efc0.
// +0x00BC, 4 bytes, m_groundStiffness: INI VA 0xbe8940: GroundStiffness, parseReal RVA 0x2efc0.
// +0x00C0, 4 bytes, m_structureStiffness: INI VA 0xbe8950: StructureStiffness, parseReal RVA 0x2efc0.
// +0x00C4, 4 bytes, m_gravity: INI VA 0xbe8960: Gravity, parseAccelerationReal RVA 0x338be3.
// +0x00C8, 4 bytes, m_stealthFriendlyOpacity: INI VA 0xbe8970: StealthFriendlyOpacity, parsePercentToReal RVA 0x2f1ba.
// +0x00CC, 4 bytes, m_defaultOcclusionDelay: INI VA 0xbe8980: DefaultOcclusionDelay, parseDurationUnsignedInt RVA 0x338b30.
// +0x00D0, 1 bytes, field00D0: 0x002364dc: mov byte ptr [esi + 0xd0], bl.
// +0x00D4, 4 bytes, m_partitionCellSize: INI VA 0xbe8990: PartitionCellSize, parseReal RVA 0x2efc0.
// +0x00D8, 4 bytes, m_terrainResourceCellSize: INI VA 0xbe89a0: TerrainResourceCellSize, parseReal RVA 0x2efc0.
// +0x00DC, 12 bytes, m_ammoPipWorldOffset: INI VA 0xbe89d0: AmmoPipWorldOffset, parseCoord3D RVA 0x2f507.
// +0x00E8, 12 bytes, m_containerPipWorldOffset: INI VA 0xbe89e0: ContainerPipWorldOffset, parseCoord3D RVA 0x2f507.
// +0x00F4, 8 bytes, m_ammoPipScreenOffset: INI VA 0xbe89f0: AmmoPipScreenOffset, parseCoord2D RVA 0x2f558.
// +0x00FC, 8 bytes, m_containerPipScreenOffset: INI VA 0xbe8a00: ContainerPipScreenOffset, parseCoord2D RVA 0x2f558.
// +0x0104, 4 bytes, m_ammoPipScaleFactor: INI VA 0xbe89b0: AmmoPipScaleFactor, parseReal RVA 0x2efc0.
// +0x0108, 4 bytes, m_containerPipScaleFactor: INI VA 0xbe89c0: ContainerPipScaleFactor, parseReal RVA 0x2efc0.
// +0x010C, 4 bytes, m_maxTerrainTracks: INI VA 0xbe8a10: MaxTerrainTracks, parseInt RVA 0x2ef56.
// +0x0110, 4 bytes, field0110: reader RVA 0x00084CC7; dword +0x110.
// +0x0114, 4 bytes, field0114: reader RVA 0x00084CD6; dword +0x114.
// +0x0118, 4 bytes, field0118: reader RVA 0x00084CE5; dword +0x118.
// +0x011C, 4 bytes, m_levelGainAnimationName: INI VA 0xbe8a80: LevelGainAnimationName, parseAsciiString RVA 0x2f11e.
// +0x0120, 4 bytes, m_levelGainAnimationTime: INI VA 0xbe8a90: LevelGainAnimationTime, parseReal RVA 0x2efc0.
// +0x0124, 4 bytes, m_levelGainAnimationZRise: INI VA 0xbe8aa0: LevelGainAnimationZRise, parseReal RVA 0x2efc0.
// +0x0128, 4 bytes, m_getHealedAnimationName: INI VA 0xbe8ab0: GetHealedAnimationName, parseAsciiString RVA 0x2f11e.
// +0x012C, 4 bytes, m_getHealedAnimationTime: INI VA 0xbe8ac0: GetHealedAnimationTime, parseReal RVA 0x2efc0.
// +0x0130, 4 bytes, m_getHealedAnimationZRise: INI VA 0xbe8ad0: GetHealedAnimationZRise, parseReal RVA 0x2efc0.
// +0x0134, 4 bytes, m_timeOfDay: setTimeOfDay(TimeOfDay) RVA 0x002352CA stores its argument to +0x134; INI VA 0xbe8a20: TimeOfDay, parseIndexList RVA 0x2ec4e; Zero Hour declares TimeOfDay m_timeOfDay.
// +0x0138, 4 bytes, m_weather: INI VA 0xbe8a30: Weather, parseIndexList RVA 0x2ec4e.
// +0x013C, 1 bytes, m_makeTrackMarks: INI VA 0xbe8a40: MakeTrackMarks, parseBool RVA 0x2e850.
// +0x013D, 1 bytes, m_hideGarrisonFlags: INI VA 0xbe8a50: HideGarrisonFlags, parseBool RVA 0x2e850.
// +0x013E, 1 bytes, m_forceModelsToFollowTimeOfDay: INI VA 0xbe8a60: ForceModelsToFollowTimeOfDay, parseBool RVA 0x2e850.
// +0x013F, 1 bytes, m_forceModelsToFollowWeather: INI VA 0xbe8a70: ForceModelsToFollowWeather, parseBool RVA 0x2e850.
// +0x0140, 648 bytes, m_terrainLighting: constructor 0x00236587..0x002365DA builds 18 records of 0x24 bytes at +0x140 through eh vector constructor 0x00629512; destructor 0x002379E5 tears them down. INI TerrainLighting<Time>Ambient/Diffuse/LightPos[2|3] records (VA 0xbe8ae0/0xbe8af0/0xbe8b00 for Morning at +0x1AC/+0x1B8/+0x1C4) write parseRGBColor 0x2f259, parseRGBColor and parseCoord3D 0x2f507 at element +0/+0xC/+0x18, rows 0x6C apart per time of day; Zero Hour GlobalData.h supplies TerrainLighting and these names.
// +0x03C8, 648 bytes, m_terrainObjectsLighting: constructor 0x002365ED..0x002365F8 builds 18 records of 0x24 bytes; destructor 0x002379D0; INI TerrainObjectsLighting<Time>Ambient/Diffuse/LightPos[2|3] records (VA 0xbe8ba0 for MorningAmbient at +0x434) write in the same element shape.
// +0x0650, 648 bytes, field0650: constructor 0x0023660F..0x00236616 builds 18 records of 0x24 bytes; destructor 0x002379BB; no INI record names it.
// +0x08D8, 36 bytes, m_terrainAmbient: setTimeOfDay 0x002352D3..0x00235305 copies three twelve-byte ambient, diffuse and position records to +0x8D8/+0x8FC/+0x920; Zero Hour GlobalData.h supplies these names and RGBColor/Coord3D types.
// +0x08FC, 36 bytes, m_terrainDiffuse: setTimeOfDay 0x002352D3..0x00235305; three RGBColor records at +0x8FC.
// +0x0920, 36 bytes, m_terrainLightPos: setTimeOfDay 0x002352D3..0x00235305; three Coord3D records at +0x920.
// +0x0944, 12 bytes, field0944: constructor 0x00236673..0x00236682 stores 1.0f (VA 0x00BBB8D8) to +0x944/+0x948/+0x94C through one base pointer; updateScorches 0x00067929..0x00067951 multiplies them per channel with m_terrainDiffuse[0], renderOneObject 0x0006FF69..0x0006FF95 scales three floats by them.
// +0x0950, 4 bytes, field0950: 0x0023668f: movss dword ptr [esi + 0x950], xmm1.
// +0x0954, 4 bytes, m_humanSoloPlayerHealthBonus_Easy: INI VA 0xbe9400: HumanSoloPlayerHealthBonus_Easy, parsePercentToReal RVA 0x2f1ba.
// +0x0958, 4 bytes, m_humanSoloPlayerHealthBonus_Normal: INI VA 0xbe9410: HumanSoloPlayerHealthBonus_Normal, parsePercentToReal RVA 0x2f1ba.
// +0x095C, 4 bytes, m_humanSoloPlayerHealthBonus_Hard: INI VA 0xbe9420: HumanSoloPlayerHealthBonus_Hard, parsePercentToReal RVA 0x2f1ba.
// +0x0964, 4 bytes, m_aISoloPlayerHealthBonus_Easy: INI VA 0xbe9440: AISoloPlayerHealthBonus_Easy, parsePercentToReal RVA 0x2f1ba.
// +0x0968, 4 bytes, m_aISoloPlayerHealthBonus_Normal: INI VA 0xbe9450: AISoloPlayerHealthBonus_Normal, parsePercentToReal RVA 0x2f1ba.
// +0x096C, 4 bytes, m_aISoloPlayerHealthBonus_Hard: INI VA 0xbe9460: AISoloPlayerHealthBonus_Hard, parsePercentToReal RVA 0x2f1ba.
// +0x0974, 4 bytes, m_maxTranslucentObjects: INI VA 0xbe8f70: MaxTranslucentObjects, parseInt RVA 0x2ef56.
// +0x0978, 4 bytes, field0978: 0x002366c6: mov dword ptr [esi + 0x978], eax.
// +0x097C, 4 bytes, field097C: 0x002366cc: mov dword ptr [esi + 0x97c], eax.
// +0x0980, 4 bytes, field0980: 0x002366d2: mov dword ptr [esi + 0x980], eax.
// +0x0984, 4 bytes, m_occludedColorLuminanceScale: INI VA 0xbe8f80: OccludedColorLuminanceScale, parseReal RVA 0x2efc0.
// +0x0988, 4 bytes, m_numberGlobalLights: INI VA 0xbe8f60: NumberGlobalLights, parseInt RVA 0x2ef56.
// +0x098C, 4 bytes, m_maxRoadSegments: INI VA 0xbe8f90: MaxRoadSegments, parseInt RVA 0x2ef56.
// +0x0990, 4 bytes, m_maxRoadVertex: INI VA 0xbe8fa0: MaxRoadVertex, parseInt RVA 0x2ef56.
// +0x0994, 4 bytes, m_maxRoadIndex: INI VA 0xbe8fb0: MaxRoadIndex, parseInt RVA 0x2ef56.
// +0x0998, 4 bytes, m_maxRoadTypes: INI VA 0xbe8fc0: MaxRoadTypes, parseInt RVA 0x2ef56.
// +0x099C, 1 bytes, m_audioOn: INI VA 0xbe8ff0: AudioOn, parseBool RVA 0x2e850.
// +0x099D, 1 bytes, m_musicOn: INI VA 0xbe9000: MusicOn, parseBool RVA 0x2e850.
// +0x099E, 1 bytes, m_soundsOn: INI VA 0xbe9020: SoundsOn, parseBool RVA 0x2e850.
// +0x099F, 1 bytes, m_sounds3DOn: INI VA 0xbe9030: Sounds3DOn, parseBool RVA 0x2e850.
// +0x09A0, 1 bytes, m_speechOn: INI VA 0xbe9040: SpeechOn, parseBool RVA 0x2e850.
// +0x09A1, 1 bytes, m_ambientStreamsOn: INI VA 0xbe9010: AmbientStreamsOn, parseBool RVA 0x2e850.
// +0x09A2, 1 bytes, field09A2: 0x00236708: mov byte ptr [esi + 0x9a2], bl.
// +0x09A3, 1 bytes, m_videoOn: INI VA 0xbe9050: VideoOn, parseBool RVA 0x2e850.
// +0x09A4, 1 bytes, m_disableCameraMovements: INI VA 0xbe9060: DisableCameraMovements, parseBool RVA 0x2e850.
// +0x09A5, 1 bytes, m_showSelectedUnitMarker: INI VA 0xbe8790: ShowSelectedUnitMarker, parseBool RVA 0x2e850.
// +0x09A6, 1 bytes, m_useSimpleHordeDecals: INI VA 0xbe87a0: UseSimpleHordeDecals, parseBool RVA 0x2e850.
// +0x09A7, 1 bytes, m_useSimpleMergeDecals: INI VA 0xbe87b0: UseSimpleMergeDecals, parseBool RVA 0x2e850.
// +0x09A8, 4 bytes, m_opacityOfSimpleMergeDecals: INI VA 0xbe87c0: OpacityOfSimpleMergeDecals, parsePercentToReal RVA 0x2f1ba.
// +0x09AC, 1 bytes, field09AC: 0x00236736: mov byte ptr [esi + 0x9ac], bl.
// +0x09AD, 1 bytes, field09AD: 0x0023673c: mov byte ptr [esi + 0x9ad], bl.
// +0x09AE, 1 bytes, field09AE: 0x00236742: mov byte ptr [esi + 0x9ae], bl.
// +0x09AF, 1 bytes, field09AF: 0x00236748: mov byte ptr [esi + 0x9af], 1.
// +0x09B0, 1 bytes, m_showClientPhysics: INI VA 0xbe90a0: ShowClientPhysics, parseBool RVA 0x2e850.
// +0x09B1, 1 bytes, m_showTerrainNormals: INI VA 0xbe90b0: ShowTerrainNormals, parseBool RVA 0x2e850.
// +0x09B4, 4 bytes, field09B4: 0x0023675c: mov dword ptr [esi + 0x9b4], ebx.
// +0x09B8, 4 bytes, field09B8: 0x00236762: mov dword ptr [esi + 0x9b8], ebx.
// +0x09BC, 1 bytes, m_debugAIObstacles: INI VA 0xbe9090: DebugAIObstacles, parseBool RVA 0x2e850.
// +0x09BD, 1 bytes, m_showObjectHealth: INI VA 0xbe90c0: ShowObjectHealth, parseBool RVA 0x2e850.
// +0x09BE, 1 bytes, field09BE: 0x00236775: mov byte ptr [esi + 0x9be], bl.
// +0x09BF, 1 bytes, m_showTooltips: INI VA 0xbe90d0: ShowTooltips, parseBool RVA 0x2e850.
// +0x09C0, 1 bytes, field09C0: 0x00236782: mov byte ptr [esi + 0x9c0], bl.
// +0x09C1, 1 bytes, field09C1: 0x00236788: mov byte ptr [esi + 0x9c1], bl.
// +0x09C2, 1 bytes, field09C2: 0x0023678e: mov byte ptr [esi + 0x9c2], bl.
// +0x09C3, 1 bytes, field09C3: 0x00236794: mov byte ptr [esi + 0x9c3], bl.
// +0x09C4, 1 bytes, field09C4: 0x0023679a: mov byte ptr [esi + 0x9c4], bl.
// +0x09C5, 1 bytes, field09C5: 0x002367a0: mov byte ptr [esi + 0x9c5], 1.
// +0x09C6, 1 bytes, field09C6: 0x002367a7: mov byte ptr [esi + 0x9c6], 1.
// +0x09C7, 1 bytes, field09C7: 0x002367ae: mov byte ptr [esi + 0x9c7], bl.
// +0x09C8, 1 bytes, field09C8: 0x002367b6: mov byte ptr [esi + 0x9c8], bl.
// +0x09CC, 4 bytes, field09CC: 0x002367bd: mov dword ptr [esi + 0x9cc], eax.
// +0x09D0, 1 bytes, field09D0: 0x002367c3: mov byte ptr [esi + 0x9d0], bl.
// +0x09D1, 1 bytes, field09D1: 0x002367c9: mov byte ptr [esi + 0x9d1], bl.
// +0x09D2, 1 bytes, field09D2: 0x002367cf: mov byte ptr [esi + 0x9d2], bl.
// +0x09D4, 4 bytes, field09D4: 0x002367d5: mov dword ptr [esi + 0x9d4], ebx; signed: parsePlayerTemplateDefinition 0x001FF151/0x001FF156 jle/jg.
// +0x09D8, 1 bytes, field09D8: 0x002367db: mov byte ptr [esi + 0x9d8], bl.
// +0x09DC, 4 bytes, m_defaultUnitHealingBuffFxList: INI VA 0xbe8860: DefaultUnitHealingBuffFxList, parseAsciiString RVA 0x2f11e.
// +0x09E0, 4 bytes, m_defaultStructureRepairBuffFxList: INI VA 0xbe8870: DefaultStructureRepairBuffFxList, parseAsciiString RVA 0x2f11e.
// +0x09E4, 1 bytes, field09E4: 0x002367ed: mov byte ptr [esi + 0x9e4], bl.
// +0x09E8, 4 bytes, m_fixedSeed: INI VA 0xbe9490: FixedSeed, parseInt RVA 0x2ef56.
// +0x09EC, 4 bytes, m_particleScale: INI VA 0xbe90e0: ParticleScale, parseReal RVA 0x2efc0.
// +0x09F0, 4 bytes, m_autoFireParticleSmallPrefix: INI VA 0xbe90f0: AutoFireParticleSmallPrefix, parseAsciiString RVA 0x2f11e.
// +0x09F4, 4 bytes, m_autoFireParticleSmallSystem: INI VA 0xbe9100: AutoFireParticleSmallSystem, parseAsciiString RVA 0x2f11e.
// +0x09F8, 4 bytes, m_autoFireParticleSmallMax: INI VA 0xbe9110: AutoFireParticleSmallMax, parseInt RVA 0x2ef56.
// +0x09FC, 4 bytes, m_autoFireParticleMediumPrefix: INI VA 0xbe9120: AutoFireParticleMediumPrefix, parseAsciiString RVA 0x2f11e.
// +0x0A00, 4 bytes, m_autoFireParticleMediumSystem: INI VA 0xbe9130: AutoFireParticleMediumSystem, parseAsciiString RVA 0x2f11e.
// +0x0A04, 4 bytes, m_autoFireParticleMediumMax: INI VA 0xbe9140: AutoFireParticleMediumMax, parseInt RVA 0x2ef56.
// +0x0A08, 4 bytes, m_autoFireParticleLargePrefix: INI VA 0xbe9150: AutoFireParticleLargePrefix, parseAsciiString RVA 0x2f11e.
// +0x0A0C, 4 bytes, m_autoFireParticleLargeSystem: INI VA 0xbe9160: AutoFireParticleLargeSystem, parseAsciiString RVA 0x2f11e.
// +0x0A10, 4 bytes, m_autoFireParticleLargeMax: INI VA 0xbe9170: AutoFireParticleLargeMax, parseInt RVA 0x2ef56.
// +0x0A14, 4 bytes, m_autoSmokeParticleSmallPrefix: INI VA 0xbe9180: AutoSmokeParticleSmallPrefix, parseAsciiString RVA 0x2f11e.
// +0x0A18, 4 bytes, m_autoSmokeParticleSmallSystem: INI VA 0xbe9190: AutoSmokeParticleSmallSystem, parseAsciiString RVA 0x2f11e.
// +0x0A1C, 4 bytes, m_autoSmokeParticleSmallMax: INI VA 0xbe91a0: AutoSmokeParticleSmallMax, parseInt RVA 0x2ef56.
// +0x0A20, 4 bytes, m_autoSmokeParticleMediumPrefix: INI VA 0xbe91b0: AutoSmokeParticleMediumPrefix, parseAsciiString RVA 0x2f11e.
// +0x0A24, 4 bytes, m_autoSmokeParticleMediumSystem: INI VA 0xbe91c0: AutoSmokeParticleMediumSystem, parseAsciiString RVA 0x2f11e.
// +0x0A28, 4 bytes, m_autoSmokeParticleMediumMax: INI VA 0xbe91d0: AutoSmokeParticleMediumMax, parseInt RVA 0x2ef56.
// +0x0A2C, 4 bytes, m_autoSmokeParticleLargePrefix: INI VA 0xbe91e0: AutoSmokeParticleLargePrefix, parseAsciiString RVA 0x2f11e.
// +0x0A30, 4 bytes, m_autoSmokeParticleLargeSystem: INI VA 0xbe91f0: AutoSmokeParticleLargeSystem, parseAsciiString RVA 0x2f11e.
// +0x0A34, 4 bytes, m_autoSmokeParticleLargeMax: INI VA 0xbe9200: AutoSmokeParticleLargeMax, parseInt RVA 0x2ef56.
// +0x0A38, 4 bytes, m_autoAflameParticlePrefix: INI VA 0xbe9210: AutoAflameParticlePrefix, parseAsciiString RVA 0x2f11e.
// +0x0A3C, 4 bytes, m_autoAflameParticleSystem: INI VA 0xbe9220: AutoAflameParticleSystem, parseAsciiString RVA 0x2f11e.
// +0x0A40, 4 bytes, m_autoAflameParticleMax: INI VA 0xbe9230: AutoAflameParticleMax, parseInt RVA 0x2ef56.
// +0x0A44, 4 bytes, field0A44: 0x00236883: mov dword ptr [esi + 0xa44], eax; signed: AptMpGameSetup::OnHostStartGame 0x00440F5E jge against an int count.
// +0x0A48, 4 bytes, field0A48: 0x00236889: mov dword ptr [esi + 0xa48], ebx.
// +0x0A4C, 4 bytes, m_firewallBehavior: INI VA 0xbe94f0: FirewallBehavior, parseInt RVA 0x2ef56.
// +0x0A50, 1 bytes, field0A50: 0x00236895: mov byte ptr [esi + 0xa50], bl.
// +0x0A54, 4 bytes, m_firewallPortOverride: INI VA 0xbe9500: FirewallPortOverride, parseInt RVA 0x2ef56; unsigned: NAT::attachSlotList 0x005A6B97 jbe; Zero Hour declares UnsignedInt.
// +0x0A58, 2 bytes, m_firewallPortAllocationDelta: constructor 0x002368A1 stores a word; OptionPreferences::getFirewallPortAllocationDelta reads a word at 0x002E48AA and returns short; INI VA 0xbe9510: FirewallPortAllocationDelta, parseInt RVA 0x2ef56.
// +0x0A5C, 4 bytes, m_valuePerSupplyBox: INI VA 0xbe8fd0: ValuePerSupplyBox, parseInt RVA 0x2ef56.
// +0x0A60, 4 bytes, m_supplyBoxesPerTree: INI VA 0xbe8fe0: SupplyBoxesPerTree, parseInt RVA 0x2ef56.
// +0x0A64, 4 bytes, m_BuildSpeed: INI VA 0xbe9240: BuildSpeed, parseReal RVA 0x2efc0.
// +0x0A68, 4 bytes, m_MinDistFromEdgeOfMapForBuild: INI VA 0xbe9250: MinDistFromEdgeOfMapForBuild, parseReal RVA 0x2efc0.
// +0x0A6C, 4 bytes, m_SupplyBuildBorder: INI VA 0xbe9260: SupplyBuildBorder, parseReal RVA 0x2efc0.
// +0x0A70, 4 bytes, m_allowedHeightVariationForBuilding: INI VA 0xbe9270: AllowedHeightVariationForBuilding, parseReal RVA 0x2efc0.
// +0x0A74, 4 bytes, m_MinLowEnergyProductionSpeed: INI VA 0xbe9280: MinLowEnergyProductionSpeed, parseReal RVA 0x2efc0.
// +0x0A78, 4 bytes, m_MaxLowEnergyProductionSpeed: INI VA 0xbe9290: MaxLowEnergyProductionSpeed, parseReal RVA 0x2efc0.
// +0x0A7C, 4 bytes, m_LowEnergyPenaltyModifier: INI VA 0xbe92a0: LowEnergyPenaltyModifier, parseReal RVA 0x2efc0.
// +0x0A80, 4 bytes, m_MultipleFactory: INI VA 0xbe92b0: MultipleFactory, parseReal RVA 0x2efc0.
// +0x0A84, 4 bytes, m_RefundPercent: INI VA 0xbe92c0: RefundPercent, parsePercentToReal RVA 0x2f1ba.
// +0x0A88, 4 bytes, m_timeAfterDamageUntilRepairAllowed: INI VA 0xbe8880: TimeAfterDamageUntilRepairAllowed, parseUnsignedInt RVA 0x2ef72.
// +0x0A8C, 4 bytes, m_commandCenterHealRange: INI VA 0xbe92d0: CommandCenterHealRange, parseReal RVA 0x2efc0.
// +0x0A90, 4 bytes, m_commandCenterHealAmount: INI VA 0xbe92e0: CommandCenterHealAmount, parseReal RVA 0x2efc0.
// +0x0A94, 4 bytes, m_maxLineBuildObjects: INI VA 0xbe92f0: MaxLineBuildObjects, parseInt RVA 0x2ef56.
// +0x0A98, 4 bytes, m_maxTunnelCapacity: INI VA 0xbe9300: MaxTunnelCapacity, parseInt RVA 0x2ef56.
// +0x0A9C, 4 bytes, m_horizontalScrollSpeedFactor: INI VA 0xbe9330: HorizontalScrollSpeedFactor, parseReal RVA 0x2efc0.
// +0x0AA0, 4 bytes, m_verticalScrollSpeedFactor: INI VA 0xbe9340: VerticalScrollSpeedFactor, parseReal RVA 0x2efc0.
// +0x0AA4, 4 bytes, m_screenEdgeScrollSpeedFactor: INI VA 0xbe9350: ScreenEdgeScrollSpeedFactor, parseReal RVA 0x2efc0.
// +0x0AA8, 4 bytes, field0AA8: 0x00236942: mov dword ptr [esi + 0xaa8], 0x12c; INI VA 0xbe9360: ScreenEdgeScrollRampTime, RVA 0x2f0f7 stores __ftol2(seconds * 1000.0f); signed: 0x0042F2D1 jle, 0x0042F2DB cdq/idiv.
// +0x0AAC, 4 bytes, m_scrollAmountCutoff: INI VA 0xbe9370: ScrollAmountCutoff, parseReal RVA 0x2efc0.
// +0x0AB0, 4 bytes, m_cameraAdjustSpeed: INI VA 0xbe9380: CameraAdjustSpeed, parseReal RVA 0x2efc0.
// +0x0AB4, 1 bytes, m_enforceMaxCameraHeight: INI VA 0xbe9390: EnforceMaxCameraHeight, parseBool RVA 0x2e850.
// +0x0AB5, 1 bytes, field0AB5: 0x0023696a: mov byte ptr [esi + 0xab5], bl; bool: MapCache::loadUserMaps 0x003052C1 cmp byte ptr [eax + 0xab5], 0; Zero Hour Bool m_buildMapCache.
// +0x0AB8, 4 bytes, field0AB8: constructor 0x00236970 clears +0xAB8; destructor 0x00237899 releases it through narrow releaseBuffer 0x00036410; parseFile 0x003BA25A passes it as the converter's second output.
// +0x0ABC, 4 bytes, m_initialFile: constructor 0x00236976 clears +0xABC; destructor 0x0023788A releases it through 0x00036410; parseFile 0x003BA24A assigns args[1] to it, as Zero Hour's parseFile assigns m_initialFile.
// +0x0AC0, 4 bytes, field0AC0: constructor 0x0023697C clears +0xAC0; cleanup at 0x00237650 and destructor 0x00237885 call narrow releaseBuffer 0x00036410 on +0xAC0.
// +0x0AC4, 1 bytes, field0AC4: 0x00236982: mov byte ptr [esi + 0xac4], bl.
// +0x0AC5, 1 bytes, field0AC5: 0x00236988: mov byte ptr [esi + 0xac5], bl.
// +0x0AC8, 4 bytes, m_maxParticleCount: INI VA 0xbe9310: MaxParticleCount, parseInt RVA 0x2ef56.
// +0x0ACC, 4 bytes, m_maxFieldParticleCount: INI VA 0xbe9320: MaxFieldParticleCount, parseInt RVA 0x2ef56.
// +0x0AD0, 4 bytes, m_weaponBonusSet: INI VA 0xbe9470 WeaponBonus record parses +0xAD0 through WeaponBonusSet::parseWeaponBonusSetPtr 0x002CA81C; constructor 0x002369CB stores the new object built by 0x00235A21; Weapon::computeBonus 0x002C9A92 loads the pointer; Zero Hour GlobalData.h names m_weaponBonusSet.
// +0x0AD4, 16 bytes, m_healthBonus: constructor 0x00237655..0x00237665 fills four floats with 1.0 at +0xAD4; INI VA 0x00BE93D0/0x00BE93E0/0x00BE93F0 assigns veteran/elite/heroic at +0xAD8/+0xADC/+0xAE0 through parsePercentToReal 0x0002F1BA; Zero Hour GlobalData.h names m_healthBonus[LEVEL_COUNT].
// +0x0AE4, 4 bytes, m_defaultStructureRubbleHeight: INI VA 0xbe9480: DefaultStructureRubbleHeight, parseReal RVA 0x2efc0.
// +0x0AE8, 4 bytes, m_attributeModifierArmorMaxBonus: INI VA 0xbe9430: AttributeModifierArmorMaxBonus, parsePercentToReal RVA 0x2f1ba.
// +0x0AEC, 4 bytes, m_shellMapName: INI VA 0xbe94a0: ShellMapName, parseAsciiString RVA 0x2f11e.
// +0x0AF0, 1 bytes, m_shellMapOn: INI VA 0xbe94b0: ShellMapOn, parseBool RVA 0x2e850.
// +0x0AF1, 1 bytes, m_shellMapOffByCommandArgument: INI VA 0xbe94c0: ShellMapOffByCommandArgument, parseBool RVA 0x2e850.
// +0x0AF2, 1 bytes, m_playIntro: INI VA 0xbe94e0: PlayIntro, parseBool RVA 0x2e850.
// +0x0AF3, 1 bytes, field0AF3: 0x00236a11: mov byte ptr [esi + 0xaf3], bl.
// +0x0AF4, 1 bytes, field0AF4: 0x00236a17: mov byte ptr [esi + 0xaf4], bl.
// +0x0AF5, 1 bytes, field0AF5: 0x00236a1d: mov byte ptr [esi + 0xaf5], bl.
// +0x0AF8, 4 bytes, m_keyboardScrollSpeedFactor: INI VA 0xbe93a0: KeyboardScrollSpeedFactor, parseReal RVA 0x2efc0.
// +0x0AFC, 4 bytes, m_keyboardDefaultScrollSpeedFactor: INI VA 0xbe93b0: KeyboardDefaultScrollSpeedFactor, parseReal RVA 0x2efc0.
// +0x0B00, 1 bytes, field0B00: 0x00236a33: mov byte ptr [esi + 0xb00], 1.
// +0x0B01, 1 bytes, field0B01: 0x00236a3a: mov byte ptr [esi + 0xb01], bl.
// +0x0B04, 4 bytes, field0B04: 0x00236a4a: mov dword ptr [esi + 0xb04], ebx.
// +0x0B38, 4 bytes, field0B38: 0x00236a55: or dword ptr [esi + 0xb38], 0xffffffff.
// +0x0B3C, 4 bytes, m_movementPenaltyDamageState: INI VA 0xbe93c0: MovementPenaltyDamageState, parseIndexList RVA 0x2ec4e.
// +0x0B40, 4 bytes, m_damageRadiusMinimumForSplash: INI VA 0xbe9520: DamageRadiusMinimumForSplash, parseReal RVA 0x2efc0.
// +0x0B44, 4 bytes, m_groupSelectMinSelectSize: INI VA 0xbe9530: GroupSelectMinSelectSize, parseInt RVA 0x2ef56.
// +0x0B48, 4 bytes, m_groupSelectVolumeBase: INI VA 0xbe9540: GroupSelectVolumeBase, parseReal RVA 0x2efc0.
// +0x0B4C, 4 bytes, m_groupSelectVolumeIncrement: INI VA 0xbe9550: GroupSelectVolumeIncrement, parseReal RVA 0x2efc0.
// +0x0B50, 4 bytes, m_maxUnitSelectSounds: INI VA 0xbe9560: MaxUnitSelectSounds, parseInt RVA 0x2ef56.
// +0x0B54, 4 bytes, m_selectionFlashSaturationFactor: INI VA 0xbe9570: SelectionFlashSaturationFactor, parseReal RVA 0x2efc0.
// +0x0B58, 1 bytes, m_selectionFlashHouseColor: INI VA 0xbe9580: SelectionFlashHouseColor, parseBool RVA 0x2e850.
// +0x0B5C, 4 bytes, m_cameraAudibleRadius: INI VA 0xbe9590: CameraAudibleRadius, parseReal RVA 0x2efc0.
// +0x0B60, 4 bytes, m_groupMoveClickToGatherAreaFactor: INI VA 0xbe95a0: GroupMoveClickToGatherAreaFactor, parseReal RVA 0x2efc0.
// +0x0B64, 4 bytes, field0B64: 0x00236ad8: mov dword ptr [esi + 0xb64], ebx.
// +0x0B68, 1 bytes, field0B68: 0x00236ade: mov byte ptr [esi + 0xb68], 1.
// +0x0B69, 1 bytes, field0B69: 0x00236ae5: mov byte ptr [esi + 0xb69], bl.
// +0x0B6A, 1 bytes, field0B6A: 0x00236aeb: mov byte ptr [esi + 0xb6a], bl.
// +0x0B6B, 1 bytes, field0B6B: 0x00236af1: mov byte ptr [esi + 0xb6b], bl.
// +0x0B6C, 1 bytes, field0B6C: 0x00236af7: mov byte ptr [esi + 0xb6c], bl.
// +0x0B6D, 1 bytes, field0B6D: 0x00236afd: mov byte ptr [esi + 0xb6d], bl.
// +0x0B6E, 1 bytes, field0B6E: 0x00236b03: mov byte ptr [esi + 0xb6e], bl.
// +0x0B6F, 1 bytes, field0B6F: 0x00236b09: mov byte ptr [esi + 0xb6f], bl.
// +0x0B70, 1 bytes, field0B70: 0x00236b0f: mov byte ptr [esi + 0xb70], bl.
// +0x0B71, 1 bytes, m_useCameraInReplay: INI VA 0xbe9070: UseCameraInReplay, parseBool RVA 0x2e850.
// +0x0B74, 4 bytes, m_shakeSubtleIntensity: INI VA 0xbe95b0: ShakeSubtleIntensity, parseReal RVA 0x2efc0.
// +0x0B78, 4 bytes, m_shakeNormalIntensity: INI VA 0xbe95c0: ShakeNormalIntensity, parseReal RVA 0x2efc0.
// +0x0B7C, 4 bytes, m_shakeStrongIntensity: INI VA 0xbe95d0: ShakeStrongIntensity, parseReal RVA 0x2efc0.
// +0x0B80, 4 bytes, m_shakeSevereIntensity: INI VA 0xbe95e0: ShakeSevereIntensity, parseReal RVA 0x2efc0.
// +0x0B84, 4 bytes, m_shakeCineExtremeIntensity: INI VA 0xbe95f0: ShakeCineExtremeIntensity, parseReal RVA 0x2efc0.
// +0x0B88, 4 bytes, m_shakeCineInsaneIntensity: INI VA 0xbe9600: ShakeCineInsaneIntensity, parseReal RVA 0x2efc0.
// +0x0B8C, 4 bytes, m_maxShakeIntensity: INI VA 0xbe9610: MaxShakeIntensity, parseReal RVA 0x2efc0.
// +0x0B90, 4 bytes, m_maxShakeRange: INI VA 0xbe9620: MaxShakeRange, parseReal RVA 0x2efc0.
// +0x0B94, 4 bytes, m_sellPercentage: INI VA 0xbe9630: SellPercentage, parsePercentToReal RVA 0x2f1ba.
// +0x0B98, 4 bytes, m_baseRegenHealthPercentPerSecond: INI VA 0xbe9640: BaseRegenHealthPercentPerSecond, parsePercentToReal RVA 0x2f1ba.
// +0x0B9C, 4 bytes, m_baseRegenDelay: INI VA 0xbe9650: BaseRegenDelay, parseDurationUnsignedInt RVA 0x338b30.
// +0x0BA0, 4 bytes, m_hotKeyTextColor: INI VA 0xbe9720: HotKeyTextColor, parseColorInt RVA 0x2f3fe.
// +0x0BA4, 4 bytes, m_specialPowerViewObject: INI VA 0xbe9660: SpecialPowerViewObject, parseAsciiString RVA 0x2f11e.
// +0x0BA8, 12 bytes, m_standardPublicBones: INI VA 0xbe9670: StandardPublicBone, parseAsciiStringVectorAppend RVA 0x2e896; constructor 0x00236BB7 builds it through _Vector_base 0x00211E58; destructor 0x0023783F calls vector<AsciiString>::~vector 0x0002CC70; Zero Hour std::vector<AsciiString> m_standardPublicBones.
// +0x0BB4, 1 bytes, m_showMetrics: INI VA 0xbe9680: ShowMetrics, parseBool RVA 0x2e850.
// +0x0BB8, 4 bytes, m_defaultStartingCash: INI VA 0xbe9690: DefaultStartingCash, parseUnsignedInt RVA 0x2ef72.
// +0x0BBC, 1 bytes, field0BBC: 0x00236bc9: mov byte ptr [esi + 0xbbc], bl.
// +0x0BBD, 1 bytes, field0BBD: 0x00236bcf: mov byte ptr [esi + 0xbbd], bl.
// +0x0BC0, 4 bytes, m_powerBarBase: INI VA 0xbe9730: PowerBarBase, parseInt RVA 0x2ef56.
// +0x0BC4, 4 bytes, m_powerBarIntervals: INI VA 0xbe9740: PowerBarIntervals, parseReal RVA 0x2efc0.
// +0x0BC8, 4 bytes, m_powerBarYellowRange: INI VA 0xbe9750: PowerBarYellowRange, parseInt RVA 0x2ef56.
// +0x0BCC, 4 bytes, field0BCC: 0x00236c01: movss dword ptr [esi + 0xbcc], xmm0.
// +0x0BD0, 4 bytes, m_unlookPersistDuration: INI VA 0xbe9760: UnlookPersistDuration, parseDurationUnsignedInt RVA 0x338b30.
// +0x0BD4, 1 bytes, field0BD4: 0x00236c13: mov byte ptr [esi + 0xbd4], bl.
// +0x0BD8, 4 bytes, field0BD8: 0x00236c2a: mov dword ptr [esi + 0xbd8], eax.
// +0x0BDC, 12 bytes, m_shroudColor: INI VA 0xbe96a0: ShroudColor, parseRGBColor RVA 0x2f259.
// +0x0BE8, 1 bytes, m_clearAlpha: INI VA 0xbe96b0: ClearAlpha, parseUnsignedByte RVA 0x2ee6d.
// +0x0BE9, 1 bytes, m_fogAlpha: INI VA 0xbe96c0: FogAlpha, parseUnsignedByte RVA 0x2ee6d.
// +0x0BEA, 1 bytes, m_shroudAlpha: INI VA 0xbe96d0: ShroudAlpha, parseUnsignedByte RVA 0x2ee6d.
// +0x0BEC, 12 bytes, m_taintColor: INI VA 0xbe96f0: TaintColor, parseRGBColor RVA 0x2f259.
// +0x0BF8, 12 bytes, m_elvenWoodColor: INI VA 0xbe9700: ElvenWoodColor, parseRGBColor RVA 0x2f259.
// +0x0C04, 1 bytes, m_taintAlpha: INI VA 0xbe9710: TaintAlpha, parseUnsignedByte RVA 0x2ee6d.
// +0x0C08, 4 bytes, m_networkFPSHistoryLength: INI VA 0xbe9770: NetworkFPSHistoryLength, parseInt RVA 0x2ef56.
// +0x0C0C, 4 bytes, m_networkLatencyHistoryLength: INI VA 0xbe9780: NetworkLatencyHistoryLength, parseInt RVA 0x2ef56.
// +0x0C10, 4 bytes, m_networkRunAheadMetricsTime: INI VA 0xbe9790: NetworkRunAheadMetricsTime, parseInt RVA 0x2ef56.
// +0x0C14, 4 bytes, m_networkCushionHistoryLength: INI VA 0xbe97a0: NetworkCushionHistoryLength, parseInt RVA 0x2ef56.
// +0x0C18, 4 bytes, m_networkRunAheadSlack: INI VA 0xbe97b0: NetworkRunAheadSlack, parseInt RVA 0x2ef56.
// +0x0C1C, 4 bytes, m_networkKeepAliveDelay: INI VA 0xbe97c0: NetworkKeepAliveDelay, parseInt RVA 0x2ef56.
// +0x0C20, 4 bytes, m_networkDisconnectTime: INI VA 0xbe97d0: NetworkDisconnectTime, parseInt RVA 0x2ef56.
// +0x0C24, 4 bytes, m_networkPlayerTimeoutTime: INI VA 0xbe97e0: NetworkPlayerTimeoutTime, parseInt RVA 0x2ef56.
// +0x0C28, 4 bytes, m_networkDisconnectScreenNotifyTime: INI VA 0xbe97f0: NetworkDisconnectScreenNotifyTime, parseInt RVA 0x2ef56.
// +0x0C2C, 4 bytes, m_keyboardCameraRotateSpeed: INI VA 0xbe9800: KeyboardCameraRotateSpeed, parseReal RVA 0x2efc0.
// +0x0C30, 4 bytes, m_playStats: INI VA 0xbe9810: PlayStats, parseInt RVA 0x2ef56.
// +0x0C34, 4 bytes, m_defaultVoiceAttackChargeTimeout: INI VA 0xbe9820: DefaultVoiceAttackChargeTimeout, parseDurationUnsignedInt RVA 0x338b30.
// +0x0C38, 4 bytes, m_defaultMaxDistanceForEngaged: INI VA 0xbe9830: DefaultMaxDistanceForEngaged, parseReal RVA 0x2efc0.
// +0x0C3C, 4 bytes, m_defaultEngagedStateTimeout: INI VA 0xbe9840: DefaultEngagedStateTimeout, parseDurationUnsignedInt RVA 0x338b30.
// +0x0C40, 4 bytes, m_animationSharingCap: INI VA 0xbe9850: AnimationSharingCap, parseInt RVA 0x2ef56.
// +0x0C44, 4 bytes, m_animationSharingFrameTolerance: INI VA 0xbe9860: AnimationSharingFrameTolerance, parseReal RVA 0x2efc0.
// +0x0C48, 4 bytes, m_animationSharingSpeedTolerance: INI VA 0xbe9870: AnimationSharingSpeedTolerance, parseReal RVA 0x2efc0.
// +0x0C4C, 4 bytes, m_animationSharingWorryThreshold: INI VA 0xbe9880: AnimationSharingWorryThreshold, parseReal RVA 0x2efc0.
// +0x0C50, 4 bytes, m_animationSharingDrasticThreshold: INI VA 0xbe9890: AnimationSharingDrasticThreshold, parseReal RVA 0x2efc0.
// +0x0C54, 12 bytes, field0C54: constructor 0x00236D30 builds it through _Vector_base 0x00211E58; destructor 0x00237830 calls vector<AsciiString>::~vector 0x0002CC70; W3DDisplay::draw 0x0004C3A7 compares its first two words (empty()).
// +0x0C60, 4 bytes, field0C60: 0x00236d44: or dword ptr [esi + 0xc60], 0xffffffff.
// +0x0C64, 1 bytes, field0C64: 0x00236d4b: mov byte ptr [esi + 0xc64], bl.
// +0x0C65, 1 bytes, field0C65: 0x00236d51: mov byte ptr [esi + 0xc65], bl.
// +0x0C66, 1 bytes, field0C66: 0x00236d57: mov byte ptr [esi + 0xc66], bl.
// +0x0C67, 1 bytes, field0C67: 0x00236d5d: mov byte ptr [esi + 0xc67], 1.
// +0x0C68, 1 bytes, field0C68: 0x00236d64: mov byte ptr [esi + 0xc68], 1.
// +0x0C69, 1 bytes, field0C69: 0x00236d6b: mov byte ptr [esi + 0xc69], 1.
// +0x0C6A, 1 bytes, m_taintOn: INI VA 0xbe96e0: TaintOn, parseBool RVA 0x2e850.
// +0x0C6B, 1 bytes, field0C6B: 0x00236d78: mov byte ptr [esi + 0xc6b], bl.
// +0x0C6C, 1 bytes, field0C6C: 0x00236d7e: mov byte ptr [esi + 0xc6c], bl.
// +0x0C6D, 1 bytes, field0C6D: 0x00236d84: mov byte ptr [esi + 0xc6d], bl.
// +0x0C6E, 1 bytes, field0C6E: 0x00236d8a: mov byte ptr [esi + 0xc6e], bl.
// +0x0C6F, 1 bytes, field0C6F: 0x00236d90: mov byte ptr [esi + 0xc6f], bl.
// +0x0C70, 4 bytes, field0C70: 0x00236d96: or dword ptr [esi + 0xc70], 0xffffffff.
// +0x0C74, 1 bytes, field0C74: 0x00236d9d: mov byte ptr [esi + 0xc74], bl.
// +0x0C75, 1 bytes, field0C75: 0x00236da3: mov byte ptr [esi + 0xc75], bl.
// +0x0C78, 4 bytes, field0C78: 0x00236da9: mov dword ptr [esi + 0xc78], ebx; signed: GameClient::update 0x0023C0AB jle.
// +0x0C7C, 1 bytes, field0C7C: 0x00236daf: mov byte ptr [esi + 0xc7c], bl.
// +0x0C7D, 1 bytes, field0C7D: 0x00236db5: mov byte ptr [esi + 0xc7d], bl.
// +0x0C80, 4 bytes, field0C80: 0x00236dbb: mov dword ptr [esi + 0xc80], 0x20.
// +0x0C88, 4 bytes, field0C88: 0x00236dca: mov dword ptr [esi + 0xc88], eax.
// +0x0C8C, 1 bytes, field0C8C: 0x00236dd0: mov byte ptr [esi + 0xc8c], bl.
// +0x0C90, 4 bytes, field0C90: 0x00236dd6: mov dword ptr [esi + 0xc90], 0x1388.
// +0x0C94, 4 bytes, field0C94: 0x00236df1: mov dword ptr [esi + 0xc94], eax.
// +0x0C98, 1 bytes, field0C98: 0x00236df7: mov byte ptr [esi + 0xc98], bl.
// +0x0C9C, 4 bytes, field0C9C: 0x00236dfd: mov dword ptr [esi + 0xc9c], 0x2710.
// +0x0CA0, 4 bytes, field0CA0: 0x00236e0c: mov dword ptr [esi + 0xca0], eax.
// +0x0CA4, 1 bytes, field0CA4: 0x00236e12: mov byte ptr [esi + 0xca4], bl.
// +0x0CCC, 1 bytes, field0CCC: 0x00236e18: mov byte ptr [esi + 0xccc], bl.
// +0x0CD0, 4 bytes, field0CD0: 0x00236e1e: movss dword ptr [esi + 0xcd0], xmm0.
// +0x0CD4, 4 bytes, field0CD4: 0x00236e26: mov dword ptr [esi + 0xcd4], 0x4d.
// +0x0CF8, 1 bytes, field0CF8: 0x00236e30: mov byte ptr [esi + 0xcf8], bl.
// +0x0CF9, 1 bytes, field0CF9: 0x00236e36: mov byte ptr [esi + 0xcf9], bl.
// +0x0CFA, 1 bytes, field0CFA: 0x00236e3c: mov byte ptr [esi + 0xcfa], bl.
// +0x0CFB, 1 bytes, field0CFB: 0x00236e42: mov byte ptr [esi + 0xcfb], bl.
// +0x0CFC, 1 bytes, field0CFC: 0x00236e48: mov byte ptr [esi + 0xcfc], bl.
// +0x0CFD, 1 bytes, field0CFD: 0x00236e4e: mov byte ptr [esi + 0xcfd], bl.
// +0x0CFE, 1 bytes, field0CFE: 0x00236e54: mov byte ptr [esi + 0xcfe], bl.
// +0x0CFF, 1 bytes, field0CFF: 0x00236e5a: mov byte ptr [esi + 0xcff], bl.
// +0x0D00, 1 bytes, field0D00: 0x00236e60: mov byte ptr [esi + 0xd00], bl.
// +0x0D01, 1 bytes, field0D01: 0x00236e71: mov byte ptr [esi + 0xd01], bl.
// +0x0D0C, 4 bytes, field0D0C: 0x00236e90: mov dword ptr [esi + 0xd0c], ebx.
// +0x0D10, 4 bytes, field0D10: 0x00236e96: mov dword ptr [esi + 0xd10], ebx.
// +0x0D14, 4 bytes, field0D14: 0x00236e9c: mov dword ptr [esi + 0xd14], ebx.
// +0x0D18, 4 bytes, field0D18: 0x00236ea2: mov dword ptr [esi + 0xd18], ebx.
// +0x0D1C, 4 bytes, field0D1C: 0x00236ea8: mov dword ptr [esi + 0xd1c], ebx.
// +0x0D20, 4 bytes, field0D20: 0x00236eae: mov dword ptr [esi + 0xd20], ebx.
// +0x0D24, 1 bytes, field0D24: 0x00236eb4: mov byte ptr [esi + 0xd24], 1.
// +0x0D28, 4 bytes, field0D28: 0x00236ebb: mov dword ptr [esi + 0xd28], 0x5a.
// +0x0D2C, 1 bytes, field0D2C: 0x00236ec5: mov byte ptr [esi + 0xd2c], 1.
// +0x0D2D, 1 bytes, field0D2D: 0x00236ecc: mov byte ptr [esi + 0xd2d], bl.
// +0x0D2E, 1 bytes, field0D2E: 0x00236ed2: mov byte ptr [esi + 0xd2e], bl.
// +0x0D2F, 1 bytes, field0D2F: 0x00236ed8: mov byte ptr [esi + 0xd2f], bl.
// +0x0D34, 1 bytes, field0D34: 0x00236ee4: mov byte ptr [esi + 0xd34], bl.
// +0x0D35, 1 bytes, field0D35: 0x00236eea: mov byte ptr [esi + 0xd35], bl.
// +0x0D36, 1 bytes, field0D36: 0x00236ef0: mov byte ptr [esi + 0xd36], bl.
// +0x0D38, 4 bytes, m_modDir: constructor 0x00236EF6 clears +0xD38; destructor 0x002377F4 releases it through 0x00036410; parseMod 0x003BA49B assigns the directory path to it, as Zero Hour's parseMod assigns m_modDir.
// +0x0D3C, 4 bytes, m_modBIG: constructor 0x00236EFC clears +0xD3C; destructor 0x002377E5 releases it through 0x00036410; parseMod 0x003BA4A9 assigns the archive path to it, as Zero Hour's parseMod assigns m_modBIG.
// +0x0D40, 4 bytes, field0D40: 0x00236f0a: movss dword ptr [esi + 0xd40], xmm1.
// +0x0D44, 1 bytes, field0D44: 0x00236f12: mov byte ptr [esi + 0xd44], bl.
// +0x0D45, 1 bytes, field0D45: 0x00236f18: mov byte ptr [esi + 0xd45], bl.
// +0x0D46, 1 bytes, field0D46: 0x00236f1e: mov byte ptr [esi + 0xd46], 1.
// +0x0D48, 4 bytes, field0D48: 0x00236f25: mov dword ptr [esi + 0xd48], ebx; signed: W3DDisplay::init 0x00046EA1 setg.
// +0x0D4C, 4 bytes, m_particleCursorAnim2DTemplateName: INI VA 0xbe98a0: ParticleCursorAnim2DTemplateName, parseAsciiString RVA 0x2f11e.
// +0x0D50, 4 bytes, m_particleCursorBurstCount: INI VA 0xbe98b0: ParticleCursorBurstCount, parseUnsignedInt RVA 0x2ef72.
// +0x0D54, 12 bytes, m_particleCursorBurstFactor: INI VA 0xbe98c0: ParticleCursorBurstFactor, parseGameClientRandomVariable RVA 0x338a9d; constructor 0x00236f3e stores int 0 and two 0.0f at +0/+4/+8.
// +0x0D60, 4 bytes, m_particleCursorStopBurstFactor: INI VA 0xbe98d0: ParticleCursorStopBurstFactor, parseReal RVA 0x2efc0.
// +0x0D64, 4 bytes, m_particleCursorBurstFrequency: INI VA 0xbe98e0: ParticleCursorBurstFrequency, parseUnsignedInt RVA 0x2ef72.
// +0x0D68, 12 bytes, m_particleCursorParticleLife: INI VA 0xbe98f0: ParticleCursorParticleLife, parseGameClientRandomVariable RVA 0x338a9d; constructor 0x00236f5a stores int 0 and two 0.0f at +0/+4/+8.
// +0x0D74, 12 bytes, m_particleCursorSystemLife: INI VA 0xbe9900: ParticleCursorSystemLife, parseGameClientRandomVariable RVA 0x338a9d; constructor 0x00236f6c stores int 0 and two 0.0f at +0/+4/+8.
// +0x0D80, 12 bytes, m_particleCursorDriftVelX: INI VA 0xbe9910: ParticleCursorDriftVelX, parseGameClientRandomVariable RVA 0x338a9d; constructor 0x00236f7e stores int 0 and two 0.0f at +0/+4/+8.
// +0x0D8C, 12 bytes, m_particleCursorDriftVelY: INI VA 0xbe9920: ParticleCursorDriftVelY, parseGameClientRandomVariable RVA 0x338a9d; constructor 0x00236f90 stores int 0 and two 0.0f at +0/+4/+8.
// +0x0D98, 12 bytes, m_particleCursorVelocityDrag: INI VA 0xbe9930: ParticleCursorVelocityDrag, parseGameClientRandomVariable RVA 0x338a9d; constructor 0x00236fae stores int 0 and two 0.0f at +0/+4/+8.
// +0x0DA4, 12 bytes, m_particleCursorParticleSize: INI VA 0xbe9940: ParticleCursorParticleSize, parseGameClientRandomVariable RVA 0x338a9d; constructor 0x00236fc0 stores int 0 and two 0.0f at +0/+4/+8. InGameUI 0x002A4B83..0x002A4B89 calls GameClientRandomVariable::getValue 0x002341A1 on it.
// +0x0DB0, 1 bytes, m_particleCursorPerFrameSize: INI VA 0xbe9950: ParticleCursorPerFrameSize, parseBool RVA 0x2e850.
// +0x0DB4, 4 bytes, m_particleCursorAlpha: INI VA 0xbe9960: ParticleCursorAlpha, parseInt RVA 0x2ef56.
// +0x0DB8, 8 bytes, m_particleCursorOffset: INI VA 0xbe9970: ParticleCursorOffset, parseICoord2D RVA 0x2f5ba.
// +0x0DC0, 8 bytes, m_progressMovieOffset: INI VA 0xbe9980: ProgressMovieOffset, parseICoord2D RVA 0x2f5ba.
// +0x0DC8, 8 bytes, m_progressMovieSize: INI VA 0xbe9990: ProgressMovieSize, parseICoord2D RVA 0x2f5ba.
// +0x0DD0, 1 bytes, m_useHelpTextSystem: INI VA 0xbe99a0: UseHelpTextSystem, parseBool RVA 0x2e850.
// +0x0DD1, 1 bytes, m_guiTextureFiltering: INI VA 0xbe99b0: GuiTextureFiltering, parseBool RVA 0x2e850.
// +0x0DD4, 4 bytes, m_cameraLockHeightDelta: INI VA 0xbe88f0: CameraLockHeightDelta, parseReal RVA 0x2efc0.
// +0x0DD8, 4 bytes, m_cameraTerrainSampleRadiusForHeight: INI VA 0xbe99c0: CameraTerrainSampleRadiusForHeight, parseReal RVA 0x2efc0.
// +0x0DDC, 1 bytes, m_enableHouseColor: INI VA 0xbe99d0: EnableHouseColor, parseBool RVA 0x2e850.
// +0x0DE0, 4 bytes, m_cameraEaseFactor: INI VA 0xbe8900: CameraEaseFactor, parseReal RVA 0x2efc0.
// +0x0DE4, 4 bytes, field0DE4: 0x00237043: movss dword ptr [esi + 0xde4], xmm1.
// +0x0DE8, 1 bytes, field0DE8: 0x0023704b: mov byte ptr [esi + 0xde8], bl.
// +0x0DFC, 4 bytes, m_goodCommandPointsBonus: INI VA 0xbe9a00: GoodCommandPointsBonus, parseInt RVA 0x2ef56.
// +0x0E00, 4 bytes, m_evilCommandPointsBonus: INI VA 0xbe9a10: EvilCommandPointsBonus, parseInt RVA 0x2ef56.
// +0x0E84, 4 bytes, m_initialMaxRingLevel: INI VA 0xbe9b60: InitialMaxRingLevel, parseInt RVA 0x2ef56.
// +0x0E88, 4 bytes, m_resourceBonusMultiplier: INI VA 0xbe9b70: ResourceBonusMultiplier, parseReal RVA 0x2efc0.
// +0x0E8C, 4 bytes, m_goodCommandPointLimit: INI VA 0xbe9b80: GoodCommandPointLimit, parseInt RVA 0x2ef56.
// +0x0E90, 4 bytes, m_evilCommandPointLimit: INI VA 0xbe9b90: EvilCommandPointLimit, parseInt RVA 0x2ef56.
// +0x0E94, 4 bytes, m_powerLimit: INI VA 0xbe9ba0: PowerLimit, parseInt RVA 0x2ef56.
// +0x0E98, 4 bytes, m_resourceMultiplierLimit: INI VA 0xbe9bb0: ResourceMultiplierLimit, parseReal RVA 0x2efc0.
// +0x0E9C, 1 bytes, field0E9C: 0x002371aa: mov byte ptr [esi + 0xe9c], bl.
// +0x0E9D, 1 bytes, field0E9D: 0x002371b0: mov byte ptr [esi + 0xe9d], bl.
// +0x0EA0, 4 bytes, field0EA0: 0x002371b6: mov dword ptr [esi + 0xea0], ebx; int: W3DDisplay::draw 0x0004C17B cvtsi2ss from it, 0x0004C229 test; jle and 0x0004C309 cmp; jl against it.
// +0x0EA4, 1 bytes, field0EA4: 0x002371bc: mov byte ptr [esi + 0xea4], 1.
// +0x0EA5, 1 bytes, field0EA5: 0x002371c3: mov byte ptr [esi + 0xea5], 1.
// +0x0EA6, 1 bytes, field0EA6: 0x002371ca: mov byte ptr [esi + 0xea6], bl.
// +0x0EA7, 1 bytes, field0EA7: 0x002371d0: mov byte ptr [esi + 0xea7], 1.
// +0x0EA8, 4 bytes, field0EA8: 0x002371d7: movss dword ptr [esi + 0xea8], xmm1.
// +0x0EAC, 4 bytes, field0EAC: 0x002371e5: movss dword ptr [esi + 0xeac], xmm0.
// +0x10A4, 4 bytes, m_handicapBuildSpeed5: INI VA 0xbe9c60: HandicapBuildSpeed5, parsePercentToReal RVA 0x2f1ba.
// +0x10A8, 4 bytes, m_handicapBuildSpeed10: INI VA 0xbe9c70: HandicapBuildSpeed10, parsePercentToReal RVA 0x2f1ba.
// +0x10AC, 4 bytes, m_handicapBuildSpeed15: INI VA 0xbe9c80: HandicapBuildSpeed15, parsePercentToReal RVA 0x2f1ba.
// +0x10B0, 4 bytes, m_handicapBuildSpeed20: INI VA 0xbe9c90: HandicapBuildSpeed20, parsePercentToReal RVA 0x2f1ba.
// +0x10B4, 4 bytes, m_handicapBuildSpeed25: INI VA 0xbe9ca0: HandicapBuildSpeed25, parsePercentToReal RVA 0x2f1ba.
// +0x10B8, 4 bytes, m_handicapBuildSpeed30: INI VA 0xbe9cb0: HandicapBuildSpeed30, parsePercentToReal RVA 0x2f1ba.
// +0x10BC, 4 bytes, m_handicapBuildSpeed35: INI VA 0xbe9cc0: HandicapBuildSpeed35, parsePercentToReal RVA 0x2f1ba.
// +0x10C0, 4 bytes, m_handicapBuildSpeed40: INI VA 0xbe9cd0: HandicapBuildSpeed40, parsePercentToReal RVA 0x2f1ba.
// +0x10C4, 4 bytes, m_handicapBuildSpeed45: INI VA 0xbe9ce0: HandicapBuildSpeed45, parsePercentToReal RVA 0x2f1ba.
// +0x10C8, 4 bytes, m_handicapBuildSpeed50: INI VA 0xbe9cf0: HandicapBuildSpeed50, parsePercentToReal RVA 0x2f1ba.
// +0x10CC, 4 bytes, m_handicapBuildSpeed55: INI VA 0xbe9d00: HandicapBuildSpeed55, parsePercentToReal RVA 0x2f1ba.
// +0x10D0, 4 bytes, m_handicapBuildSpeed60: INI VA 0xbe9d10: HandicapBuildSpeed60, parsePercentToReal RVA 0x2f1ba.
// +0x10D4, 4 bytes, m_handicapBuildSpeed65: INI VA 0xbe9d20: HandicapBuildSpeed65, parsePercentToReal RVA 0x2f1ba.
// +0x10D8, 4 bytes, m_handicapBuildSpeed70: INI VA 0xbe9d30: HandicapBuildSpeed70, parsePercentToReal RVA 0x2f1ba.
// +0x10DC, 4 bytes, m_handicapBuildSpeed75: INI VA 0xbe9d40: HandicapBuildSpeed75, parsePercentToReal RVA 0x2f1ba.
// +0x10E0, 4 bytes, m_handicapBuildSpeed80: INI VA 0xbe9d50: HandicapBuildSpeed80, parsePercentToReal RVA 0x2f1ba.
// +0x10E4, 4 bytes, m_handicapBuildSpeed85: INI VA 0xbe9d60: HandicapBuildSpeed85, parsePercentToReal RVA 0x2f1ba.
// +0x10E8, 4 bytes, m_handicapBuildSpeed90: INI VA 0xbe9d70: HandicapBuildSpeed90, parsePercentToReal RVA 0x2f1ba.
// +0x10EC, 4 bytes, m_handicapBuildSpeed95: INI VA 0xbe9d80: HandicapBuildSpeed95, parsePercentToReal RVA 0x2f1ba.
// +0x10F0, 4 bytes, m_handicapBuildSpeed100: INI VA 0xbe9d90: HandicapBuildSpeed100, parsePercentToReal RVA 0x2f1ba.
// +0x10F4, 12 bytes, field10F4: constructor 0x0023723C builds it through _Vector_base 0x00211E58; destructor 0x0023777C calls vector<AsciiString>::~vector 0x0002CC70.
// +0x1100, 1 bytes, field1100: 0x00237250: mov byte ptr [esi + 0x1100], bl.
// +0x1104, 4 bytes, field1104: 0x00237256: mov dword ptr [esi + 0x1104], ebx.
// +0x1108, 4 bytes, m_blockedByWallLeeway: INI VA 0xbe9e80: BlockedByWallLeeway, parseInt RVA 0x2ef56.
// +0x110C, 4 bytes, m_secondsBeforeBaseCheckActive: INI VA 0xbe9e90: SecondsBeforeBaseCheckActive, parseReal RVA 0x2efc0.
// +0x1110, 1 bytes, field1110: 0x0023726e: mov byte ptr [esi + 0x1110], 1.
// +0x1111, 1 bytes, field1111: 0x0023727b: mov byte ptr [esi + 0x1111], bl.
// +0x1114, 4 bytes, m_basicTutorialMap: INI VA 0xbe9da0: BasicTutorialMap, parseAsciiString RVA 0x2f11e.
// +0x1118, 4 bytes, m_basicTutorialLoadMovie: INI VA 0xbe9db0: BasicTutorialLoadMovie, parseAsciiString RVA 0x2f11e.
// +0x111C, 4 bytes, m_basicTutorialLoadScreenStillImage: INI VA 0xbe9dc0: BasicTutorialLoadScreenStillImage, parseAsciiString RVA 0x2f11e.
// +0x1120, 4 bytes, m_basicTutorialLoadScreenVoiceTrack: INI VA 0xbe9dd0: BasicTutorialLoadScreenVoiceTrack, parseAsciiString RVA 0x2f11e.
// +0x1124, 4 bytes, m_basicTutorialLoadScreenMusicTrack: INI VA 0xbe9de0: BasicTutorialLoadScreenMusicTrack, parseAsciiString RVA 0x2f11e.
// +0x1134, 4 bytes, m_basicTutorialMillisecondsAfterStartToStartFadeUp: INI VA 0xbe9e00: BasicTutorialMillisecondsAfterStartToStartFadeUp, parseDurationUnsignedInt RVA 0x338b30.
// +0x1138, 4 bytes, m_advancedTutorialMap: INI VA 0xbe9e10: AdvancedTutorialMap, parseAsciiString RVA 0x2f11e.
// +0x113C, 4 bytes, m_advancedTutorialLoadMovie: INI VA 0xbe9e20: AdvancedTutorialLoadMovie, parseAsciiString RVA 0x2f11e.
// +0x1140, 4 bytes, m_advancedTutorialLoadScreenStillImage: INI VA 0xbe9e30: AdvancedTutorialLoadScreenStillImage, parseAsciiString RVA 0x2f11e.
// +0x1144, 4 bytes, m_advancedTutorialLoadScreenVoiceTrack: INI VA 0xbe9e40: AdvancedTutorialLoadScreenVoiceTrack, parseAsciiString RVA 0x2f11e.
// +0x1148, 4 bytes, m_advancedTutorialLoadScreenMusicTrack: INI VA 0xbe9e50: AdvancedTutorialLoadScreenMusicTrack, parseAsciiString RVA 0x2f11e.
// +0x1158, 4 bytes, m_advancedTutorialMillisecondsAfterStartToStartFadeUp: INI VA 0xbe9e70: AdvancedTutorialMillisecondsAfterStartToStartFadeUp, parseDurationUnsignedInt RVA 0x338b30.
// +0x115C, 4 bytes, field115C: 0x00237291: mov dword ptr [esi + 0x115c], ebx.
// +0x1160, 4 bytes, field1160: 0x00237297: mov dword ptr [esi + 0x1160], 0xff0b5ef2.
// +0x1164, 4 bytes, field1164: 0x002372a5: mov dword ptr [esi + 0x1164], 0xffd92102.
// +0x116C, 4 bytes, m_scoreKeeper_UnitsBuiltMultiplier: INI VA 0xbe9eb0: ScoreKeeper_UnitsBuiltMultiplier, parseReal RVA 0x2efc0.
// +0x1170, 4 bytes, m_scoreKeeper_UnitsDestroyedMultiplier: INI VA 0xbe9ec0: ScoreKeeper_UnitsDestroyedMultiplier, parseReal RVA 0x2efc0.
// +0x1174, 4 bytes, m_scoreKeeper_StructuresBuiltMultiplier: INI VA 0xbe9ed0: ScoreKeeper_StructuresBuiltMultiplier, parseReal RVA 0x2efc0.
// +0x1178, 4 bytes, m_scoreKeeper_StructuresDestroyedMultiplier: INI VA 0xbe9ee0: ScoreKeeper_StructuresDestroyedMultiplier, parseReal RVA 0x2efc0.
// +0x117C, 4 bytes, m_scoreKeeper_HeroesVettedMultiplier: INI VA 0xbe9ef0: ScoreKeeper_HeroesVettedMultiplier, parseReal RVA 0x2efc0.
// +0x1180, 4 bytes, m_scoreKeeper_UnitsVettedMultiplier: INI VA 0xbe9f00: ScoreKeeper_UnitsVettedMultiplier, parseReal RVA 0x2efc0.
// +0x1184, 4 bytes, m_scoreKeeper_ObjectivesCompletedMultiplier: INI VA 0xbe9f10: ScoreKeeper_ObjectivesCompletedMultiplier, parseReal RVA 0x2efc0.
// +0x1188, 4 bytes, m_scoreKeeper_SuppliesCollectedMultiplier: INI VA 0xbe9f20: ScoreKeeper_SuppliesCollectedMultiplier, parseReal RVA 0x2efc0.
// +0x118C, 4 bytes, m_scoreKeeper_PowerPointsMultiplier: INI VA 0xbe9f30: ScoreKeeper_PowerPointsMultiplier, parseReal RVA 0x2efc0.
// +0x1190, 4 bytes, m_scoreKeeper_RegionCommandPointsMultiplier: INI VA 0xbe9f40: ScoreKeeper_RegionCommandPointsMultiplier, parseReal RVA 0x2efc0.
// +0x1194, 4 bytes, m_scoreKeeper_RegionResourcesMultiplier: INI VA 0xbe9f50: ScoreKeeper_RegionResourcesMultiplier, parseReal RVA 0x2efc0.
// +0x1198, 4 bytes, m_scoreKeeper_RegionPowerPointsMultiplier: INI VA 0xbe9f60: ScoreKeeper_RegionPowerPointsMultiplier, parseReal RVA 0x2efc0.
// +0x119C, 4 bytes, m_scoreKeeper_TimeTakenMultiplier: INI VA 0xbe9f90: ScoreKeeper_TimeTakenMultiplier, parseReal RVA 0x2efc0.
// +0x11A0, 4 bytes, m_scoreKeeper_TimeTakenMaximumScore: INI VA 0xbe9fa0: ScoreKeeper_TimeTakenMaximumScore, parseReal RVA 0x2efc0.
// +0x11A4, 4 bytes, m_scoreKeeper_TimeTakenMinimumScore: INI VA 0xbe9fb0: ScoreKeeper_TimeTakenMinimumScore, parseReal RVA 0x2efc0.
// +0x11A8, 4 bytes, m_scoreKeeper_TotalVictoryRequiredScore: INI VA 0xbe9fc0: ScoreKeeper_TotalVictoryRequiredScore, parseReal RVA 0x2efc0.
// +0x11AC, 4 bytes, m_scoreKeeper_NormalVictoryRequiredScore: INI VA 0xbe9fd0: ScoreKeeper_NormalVictoryRequiredScore, parseReal RVA 0x2efc0.
// +0x11B0, 4 bytes, m_scoreKeeper_NormalVictoryRequiredObjectivesPercentage: INI VA 0xbe9fe0: ScoreKeeper_NormalVictoryRequiredObjectivesPercentage, parseReal RVA 0x2efc0.
// +0x11B4, 4 bytes, m_scoreKeeper_SkillPointsMultiplier: INI VA 0xbe9f70: ScoreKeeper_SkillPointsMultiplier, parseReal RVA 0x2efc0.
// +0x11B8, 4 bytes, m_scoreKeeper_PlayerEliminatedMultiplier: INI VA 0xbe9f80: ScoreKeeper_PlayerEliminatedMultiplier, parseReal RVA 0x2efc0.
// +0x11BC, 1 bytes, field11BC: 0x002372ba: mov byte ptr [esi + 0x11bc], 1.
// +0x11C0, 4 bytes, m_tintUnitIfPathingForMoreThan: INI VA 0xbe9ff0: TintUnitIfPathingForMoreThan, parseInt RVA 0x2ef56; unsigned: Pathfinder::processPathfindQueue 0x002F1168..0x002F116D fild with the 2^32 correction.
// +0x11C4, 4 bytes, m_clampedLOSHeightForCastleStructures: INI VA 0xbea000: ClampedLOSHeightForCastleStructures, parseReal RVA 0x2efc0.
// +0x11C8, 1 bytes, field11C8: 0x002372d7: mov byte ptr [esi + 0x11c8], bl.
// +0x11C9, 1 bytes, field11C9: 0x002372dd: mov byte ptr [esi + 0x11c9], bl.
// +0x11CA, 1 bytes, m_planningModeEnabled: INI VA 0xbe86b0: PlanningModeEnabled, parseBool RVA 0x2e850.
// +0x11CB, 1 bytes, field11CB: 0x002372f2: mov byte ptr [esi + 0x11cb], bl.
// +0x11CC, 4 bytes, m_reinvisibityDelay: INI VA 0xbea010: ReinvisibityDelay, parseDurationUnsignedInt RVA 0x338b30.
// +0x11D0, 4 bytes, m_invisibilityOpacityMin: INI VA 0xbea020: InvisibilityOpacityMin, parseReal RVA 0x2efc0.
// +0x11D4, 4 bytes, m_invisibilityOpacityMax: INI VA 0xbea030: InvisibilityOpacityMax, parseReal RVA 0x2efc0.
// +0x11D8, 4 bytes, m_invisibilityOpacityCycleFrames: INI VA 0xbea040: InvisibilityOpacityCycleFrames, parseUnsignedInt RVA 0x2ef72.
// +0x11DC, 4 bytes, m_builderFadeOutTime: INI VA 0xbea050: BuilderFadeOutTime, parseDurationUnsignedInt RVA 0x338b30.
// +0x11E0, 4 bytes, m_builderFadeInTime: INI VA 0xbea060: BuilderFadeInTime, parseDurationUnsignedInt RVA 0x338b30.
// +0x11E4, 4 bytes, m_builderMoveFromNewStructureDistance: INI VA 0xbea070: BuilderMoveFromNewStructureDistance, parseReal RVA 0x2efc0.
// +0x11E8, 4 bytes, m_maxPathfindCellsPerFrame: INI VA 0xbea080: MaxPathfindCellsPerFrame, parseUnsignedInt RVA 0x2ef72.
// +0x11EC, 4 bytes, m_maxCellsFindMeleeEngagementLocation: INI VA 0xbea090: MaxCellsFindMeleeEngagementLocation, parseUnsignedInt RVA 0x2ef72.
// +0x11F0, 4 bytes, m_maxCellsAdjustDestination: INI VA 0xbea0a0: MaxCellsAdjustDestination, parseUnsignedInt RVA 0x2ef72.
// +0x11F4, 4 bytes, m_maxCellsAdjustHordeMeleeDestination: INI VA 0xbea0b0: MaxCellsAdjustHordeMeleeDestination, parseUnsignedInt RVA 0x2ef72.
// +0x11F8, 4 bytes, m_maxCellsAdjustTargetDestination: INI VA 0xbea0c0: MaxCellsAdjustTargetDestination, parseUnsignedInt RVA 0x2ef72.
// +0x11FC, 4 bytes, m_maxCellsAdjustToPossibleDestination: INI VA 0xbea0d0: MaxCellsAdjustToPossibleDestination, parseUnsignedInt RVA 0x2ef72.
// +0x1200, 4 bytes, m_maxCellsAdjustToMeleeDestination: INI VA 0xbea0e0: MaxCellsAdjustToMeleeDestination, parseUnsignedInt RVA 0x2ef72.
// +0x1204, 4 bytes, m_maxCellsAdjustToNearestGroundCell: INI VA 0xbea0f0: MaxCellsAdjustToNearestGroundCell, parseUnsignedInt RVA 0x2ef72.
// +0x1208, 4 bytes, m_maxCellsAdjustToNearestValidCell: INI VA 0xbea100: MaxCellsAdjustToNearestValidCell, parseUnsignedInt RVA 0x2ef72.
// +0x120C, 4 bytes, m_maxCellsPatchPath: INI VA 0xbea110: MaxCellsPatchPath, parseUnsignedInt RVA 0x2ef72.
// +0x1210, 4 bytes, m_maxCellsFindPathLimit: INI VA 0xbea120: MaxCellsFindPathLimit, parseUnsignedInt RVA 0x2ef72.
// +0x1214, 4 bytes, m_maxCellsFindAttackPath: INI VA 0xbea130: MaxCellsFindAttackPath, parseUnsignedInt RVA 0x2ef72.
// +0x1218, 4 bytes, m_maxCellsFindAttackPathSideways: INI VA 0xbea140: MaxCellsFindAttackPathSideways, parseUnsignedInt RVA 0x2ef72.
// +0x121C, 4 bytes, m_maxCellsToExamineTowardsGoal: INI VA 0xbea150: MaxCellsToExamineTowardsGoal, parseUnsignedInt RVA 0x2ef72.
// +0x1220, 4 bytes, m_maxCastleRadius: INI VA 0xbea160: MaxCastleRadius, parseReal RVA 0x2efc0.
// +0x1224, 4 bytes, m_garrisonedRangeMultiplier: INI VA 0xbea170: GarrisonedRangeMultiplier, parseReal RVA 0x2efc0.
// +0x1228, 4 bytes, field1228: 0x002373b9: or dword ptr [esi + 0x1228], 0xffffffff.
// +0x122C, 4 bytes, m_numMinutesBeforePlayersCanTransferMoney: INI VA 0xbea180: NumMinutesBeforePlayersCanTransferMoney, parseInt RVA 0x2ef56.
// +0x1230, 4 bytes, m_maxNumMembersToForceToImmediatelyEnter: INI VA 0xbea190: MaxNumMembersToForceToImmediatelyEnter, parseUnsignedInt RVA 0x2ef72.
// +0x1234, 4 bytes, m_waitToForceMemberToEnterDelay: INI VA 0xbea1a0: WaitToForceMemberToEnterDelay, parseUnsignedInt RVA 0x2ef72.
// +0x1238, 4 bytes, field1238: 0x002373d6: mov dword ptr [esi + 0x1238], ebx.
// +0x123C, 1 bytes, field123C: 0x002373dc: mov byte ptr [esi + 0x123c], bl.
// +0x123D, 1 bytes, field123D: 0x002373e2: mov byte ptr [esi + 0x123d], bl.
// +0x1240, 4 bytes, field1240: rva002360DE RVA 0x002360E6 takes +0x1240; copy call 0x002360F0 to 0x000365F0.
// +0x1244, 4 bytes, field1244: rva002360FC RVA 0x00236104 takes +0x1244; copy call 0x0023610E to 0x00037050.
// +0x1248, 4 bytes, m_picturePath: getPicturePath RVA 0x0023611A uses +0x1248.
// +0x124C, 4 bytes, m_userDataLeafName: INI VA 0xbe8690: UserDataLeafName, parseQuotedAsciiString RVA 0x2f15a.
// +0x1250, 4 bytes, m_next: newOverride RVA 0x00237A9A stores previous global at +0x1250; reset RVA 0x00235736 follows it.
#ifndef BFME2_GLOBALDATA_H
#define BFME2_GLOBALDATA_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include GlobalData.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"
#include "MultiPlayMults.h"
#include "../GameLogic/ObjectFilter.h"
#include "../GameClient/GameClientRandomVariable.h"

enum TimeOfDay;
class INI;
struct FieldParse;
class WeaponBonusSet;

class GlobalData : public SubsystemInterface {
public:
    GlobalData();
    virtual ~GlobalData();
    virtual void init();
    virtual bool vslot04(int);
    virtual int vslot06();
    virtual void reset();
    virtual void update();

    bool setTimeOfDay(TimeOfDay);
    bool rva00235312(TimeOfDay, TimeOfDay, float);
    void applyOptionPreferences();
    GlobalData *newOverride();
    static void parseGameDataDefinition(INI *ini);
    AsciiString getPicturePath() const;
    AsciiString rva002360DE() const;
    UnicodeString rva002360FC() const;
    static const FieldParse s_GlobalDataFieldParseTable[];

    struct TerrainLighting {
        RGBColor ambient;
        RGBColor diffuse;
        Coord3D lightPos;
    };

    AsciiString m_mapName;
    AsciiString m_moveHintName;
    AsciiString m_genericDamageFieldName;
    AsciiString m_genericDamageWarningName;
    bool m_showProps;
    bool m_pushAsideShrubs;
    unsigned char storage001E[0x2];
    unsigned int field0020;
    unsigned char field0024;
    unsigned char field0025;
    bool m_useFpsLimit;
    bool m_dumpAssetUsage;
    int m_framesPerSecondLimit;
    bool m_windowed;
    bool m_skipMapUnroll;
    unsigned char storage002E[0x2];
    int m_xResolution;
    int m_yResolution;
    int m_maxShellScreens;
    bool m_useCloudMap;
    bool m_showWater;
    bool m_showRoads;
    bool m_showTrees;
    bool m_allowTreeFading;
    bool m_useReverseMouseScroll;
    unsigned char storage0042[0x2];
    int m_use3WayTerrainBlends;
    bool m_useLightMap;
    unsigned char field0049;
    unsigned char field004A;
    bool m_adjustCliffTextures;
    bool m_stretchTerrain;
    bool m_useHalfHeightMap;
    bool m_drawEntireTerrain;
    unsigned char storage004F[0x1];
    int m_terrainLOD;
    unsigned char field0054;
    unsigned char storage0055[0x3];
    int m_terrainLODTargetTimeMS;
    bool field005C;
    bool m_rightMouseAlwaysScrolls;
    unsigned char field005E;
    bool m_useCloudPlane;
    bool m_useShadowVolumes;
    bool m_useShadowDecals;
    bool m_useShadowMapping;
    unsigned char storage0063[0x1];
    unsigned int field0064;
    bool m_useBehindBuildingMarker;
    unsigned char storage0069[0x3];
    float m_waterPositionX;
    float m_waterPositionY;
    float m_waterPositionZ;
    float m_waterExtentX;
    float m_waterExtentY;
    int m_waterType;
    bool m_showSoftWaterEdge;
    unsigned char field0085;
    bool m_liveCampaignMode;
    bool m_hideLivingWorldRegions;
    bool m_livingWorldTurbo;
    unsigned char storage0089[0x3];
    AsciiString m_livingWorldCampaignOverrride;
    int m_featherWater;
    float m_downwindAngle;
    float field0098;
    float m_defaultCameraMinHeight;
    float m_defaultCameraMaxHeight;
    float m_defaultCameraPitchAngle;
    float m_defaultCameraYawAngle;
    float m_defaultCameraScrollSpeedScalar;
    float m_terrainHeightAtEdgeOfMap;
    float m_unitDamagedThreshold;
    float m_unitReallyDamagedThreshold;
    float m_groundStiffness;
    float m_structureStiffness;
    float m_gravity;
    float m_stealthFriendlyOpacity;
    unsigned int m_defaultOcclusionDelay;
    unsigned char field00D0;
    unsigned char storage00D1[0x3];
    float m_partitionCellSize;
    float m_terrainResourceCellSize;
    Coord3D m_ammoPipWorldOffset;
    Coord3D m_containerPipWorldOffset;
    Coord2D m_ammoPipScreenOffset;
    Coord2D m_containerPipScreenOffset;
    float m_ammoPipScaleFactor;
    float m_containerPipScaleFactor;
    int m_maxTerrainTracks;
    int field0110;
    int field0114;
    int field0118;
    AsciiString m_levelGainAnimationName;
    float m_levelGainAnimationTime;
    float m_levelGainAnimationZRise;
    AsciiString m_getHealedAnimationName;
    float m_getHealedAnimationTime;
    float m_getHealedAnimationZRise;
    TimeOfDay m_timeOfDay;
    int m_weather;
    bool m_makeTrackMarks;
    bool m_hideGarrisonFlags;
    bool m_forceModelsToFollowTimeOfDay;
    bool m_forceModelsToFollowWeather;
    // Rows by time of day (six), columns by global light (three).
    TerrainLighting m_terrainLighting[6][3];
    TerrainLighting m_terrainObjectsLighting[6][3];
    TerrainLighting field0650[6][3];
    RGBColor m_terrainAmbient[3];
    RGBColor m_terrainDiffuse[3];
    Coord3D m_terrainLightPos[3];
    float field0944[3];
    float field0950;
    float m_humanSoloPlayerHealthBonus_Easy;
    float m_humanSoloPlayerHealthBonus_Normal;
    float m_humanSoloPlayerHealthBonus_Hard;
    unsigned char storage0960[0x4];
    float m_aISoloPlayerHealthBonus_Easy;
    float m_aISoloPlayerHealthBonus_Normal;
    float m_aISoloPlayerHealthBonus_Hard;
    unsigned char storage0970[0x4];
    int m_maxTranslucentObjects;
    unsigned int field0978;
    unsigned int field097C;
    unsigned int field0980;
    float m_occludedColorLuminanceScale;
    int m_numberGlobalLights;
    int m_maxRoadSegments;
    int m_maxRoadVertex;
    int m_maxRoadIndex;
    int m_maxRoadTypes;
    bool m_audioOn;
    bool m_musicOn;
    bool m_soundsOn;
    bool m_sounds3DOn;
    bool m_speechOn;
    bool m_ambientStreamsOn;
    unsigned char field09A2;
    bool m_videoOn;
    bool m_disableCameraMovements;
    bool m_showSelectedUnitMarker;
    bool m_useSimpleHordeDecals;
    bool m_useSimpleMergeDecals;
    float m_opacityOfSimpleMergeDecals;
    unsigned char field09AC;
    unsigned char field09AD;
    unsigned char field09AE;
    unsigned char field09AF;
    bool m_showClientPhysics;
    bool m_showTerrainNormals;
    unsigned char storage09B2[0x2];
    unsigned int field09B4;
    unsigned int field09B8;
    bool m_debugAIObstacles;
    bool m_showObjectHealth;
    unsigned char field09BE;
    bool m_showTooltips;
    unsigned char field09C0;
    unsigned char field09C1;
    unsigned char field09C2;
    unsigned char field09C3;
    unsigned char field09C4;
    unsigned char field09C5;
    unsigned char field09C6;
    unsigned char field09C7;
    unsigned char field09C8;
    unsigned char storage09C9[0x3];
    unsigned int field09CC;
    unsigned char field09D0;
    unsigned char field09D1;
    unsigned char field09D2;
    unsigned char storage09D3[0x1];
    int field09D4;
    unsigned char field09D8;
    unsigned char storage09D9[0x3];
    AsciiString m_defaultUnitHealingBuffFxList;
    AsciiString m_defaultStructureRepairBuffFxList;
    unsigned char field09E4;
    unsigned char storage09E5[0x3];
    int m_fixedSeed;
    float m_particleScale;
    AsciiString m_autoFireParticleSmallPrefix;
    AsciiString m_autoFireParticleSmallSystem;
    int m_autoFireParticleSmallMax;
    AsciiString m_autoFireParticleMediumPrefix;
    AsciiString m_autoFireParticleMediumSystem;
    int m_autoFireParticleMediumMax;
    AsciiString m_autoFireParticleLargePrefix;
    AsciiString m_autoFireParticleLargeSystem;
    int m_autoFireParticleLargeMax;
    AsciiString m_autoSmokeParticleSmallPrefix;
    AsciiString m_autoSmokeParticleSmallSystem;
    int m_autoSmokeParticleSmallMax;
    AsciiString m_autoSmokeParticleMediumPrefix;
    AsciiString m_autoSmokeParticleMediumSystem;
    int m_autoSmokeParticleMediumMax;
    AsciiString m_autoSmokeParticleLargePrefix;
    AsciiString m_autoSmokeParticleLargeSystem;
    int m_autoSmokeParticleLargeMax;
    AsciiString m_autoAflameParticlePrefix;
    AsciiString m_autoAflameParticleSystem;
    int m_autoAflameParticleMax;
    int field0A44;
    unsigned int field0A48;
    int m_firewallBehavior;
    bool field0A50;
    unsigned char storage0A51[0x3];
    unsigned int m_firewallPortOverride;
    short m_firewallPortAllocationDelta;
    unsigned char storage0A5A[0x2];
    int m_valuePerSupplyBox;
    int m_supplyBoxesPerTree;
    float m_BuildSpeed;
    float m_MinDistFromEdgeOfMapForBuild;
    float m_SupplyBuildBorder;
    float m_allowedHeightVariationForBuilding;
    float m_MinLowEnergyProductionSpeed;
    float m_MaxLowEnergyProductionSpeed;
    float m_LowEnergyPenaltyModifier;
    float m_MultipleFactory;
    float m_RefundPercent;
    unsigned int m_timeAfterDamageUntilRepairAllowed;
    float m_commandCenterHealRange;
    float m_commandCenterHealAmount;
    int m_maxLineBuildObjects;
    int m_maxTunnelCapacity;
    float m_horizontalScrollSpeedFactor;
    float m_verticalScrollSpeedFactor;
    float m_screenEdgeScrollSpeedFactor;
    int field0AA8;
    float m_scrollAmountCutoff;
    float m_cameraAdjustSpeed;
    bool m_enforceMaxCameraHeight;
    bool field0AB5;
    unsigned char storage0AB6[0x2];
    AsciiString field0AB8;
    AsciiString m_initialFile;
    AsciiString field0AC0;
    unsigned char field0AC4;
    unsigned char field0AC5;
    unsigned char storage0AC6[0x2];
    int m_maxParticleCount;
    int m_maxFieldParticleCount;
    WeaponBonusSet *m_weaponBonusSet;
    float m_healthBonus[4];
    float m_defaultStructureRubbleHeight;
    float m_attributeModifierArmorMaxBonus;
    AsciiString m_shellMapName;
    bool m_shellMapOn;
    bool m_shellMapOffByCommandArgument;
    bool m_playIntro;
    unsigned char field0AF3;
    unsigned char field0AF4;
    unsigned char field0AF5;
    unsigned char storage0AF6[0x2];
    float m_keyboardScrollSpeedFactor;
    float m_keyboardDefaultScrollSpeedFactor;
    unsigned char field0B00;
    unsigned char field0B01;
    unsigned char storage0B02[0x2];
    unsigned int field0B04;
    unsigned char storage0B08[0x30];
    unsigned int field0B38;
    int m_movementPenaltyDamageState;
    float m_damageRadiusMinimumForSplash;
    int m_groupSelectMinSelectSize;
    float m_groupSelectVolumeBase;
    float m_groupSelectVolumeIncrement;
    int m_maxUnitSelectSounds;
    float m_selectionFlashSaturationFactor;
    bool m_selectionFlashHouseColor;
    unsigned char storage0B59[0x3];
    float m_cameraAudibleRadius;
    float m_groupMoveClickToGatherAreaFactor;
    unsigned int field0B64;
    bool field0B68;
    bool field0B69;
    bool field0B6A;
    unsigned char field0B6B;
    bool field0B6C;
    bool field0B6D;
    unsigned char field0B6E;
    unsigned char field0B6F;
    unsigned char field0B70;
    bool m_useCameraInReplay;
    unsigned char storage0B72[0x2];
    float m_shakeSubtleIntensity;
    float m_shakeNormalIntensity;
    float m_shakeStrongIntensity;
    float m_shakeSevereIntensity;
    float m_shakeCineExtremeIntensity;
    float m_shakeCineInsaneIntensity;
    float m_maxShakeIntensity;
    float m_maxShakeRange;
    float m_sellPercentage;
    float m_baseRegenHealthPercentPerSecond;
    unsigned int m_baseRegenDelay;
    int m_hotKeyTextColor;
    AsciiString m_specialPowerViewObject;
    // Typed where the unit included STLport's <vector> first; GlobalData.h includes no STL header,
    // so other includers keep the same bytes as opaque storage.
#ifdef _STLP_INTERNAL_VECTOR_H
    _STL::vector<AsciiString> m_standardPublicBones;
#else
    unsigned char storage0BA8[0xC];
#endif
    bool m_showMetrics;
    unsigned char storage0BB5[0x3];
    unsigned int m_defaultStartingCash;
    unsigned char field0BBC;
    unsigned char field0BBD;
    unsigned char storage0BBE[0x2];
    int m_powerBarBase;
    float m_powerBarIntervals;
    int m_powerBarYellowRange;
    float field0BCC;
    unsigned int m_unlookPersistDuration;
    unsigned char field0BD4;
    unsigned char storage0BD5[0x3];
    unsigned int field0BD8;
    RGBColor m_shroudColor;
    unsigned char m_clearAlpha;
    unsigned char m_fogAlpha;
    unsigned char m_shroudAlpha;
    unsigned char storage0BEB[0x1];
    RGBColor m_taintColor;
    RGBColor m_elvenWoodColor;
    unsigned char m_taintAlpha;
    unsigned char storage0C05[0x3];
    int m_networkFPSHistoryLength;
    int m_networkLatencyHistoryLength;
    int m_networkRunAheadMetricsTime;
    int m_networkCushionHistoryLength;
    int m_networkRunAheadSlack;
    int m_networkKeepAliveDelay;
    int m_networkDisconnectTime;
    int m_networkPlayerTimeoutTime;
    int m_networkDisconnectScreenNotifyTime;
    float m_keyboardCameraRotateSpeed;
    int m_playStats;
    unsigned int m_defaultVoiceAttackChargeTimeout;
    float m_defaultMaxDistanceForEngaged;
    unsigned int m_defaultEngagedStateTimeout;
    int m_animationSharingCap;
    float m_animationSharingFrameTolerance;
    float m_animationSharingSpeedTolerance;
    float m_animationSharingWorryThreshold;
    float m_animationSharingDrasticThreshold;
#ifdef _STLP_INTERNAL_VECTOR_H
    _STL::vector<AsciiString> field0C54;
#else
    unsigned char storage0C54[0xC];
#endif
    unsigned int field0C60;
    unsigned char field0C64;
    unsigned char field0C65;
    unsigned char field0C66;
    unsigned char field0C67;
    unsigned char field0C68;
    unsigned char field0C69;
    bool m_taintOn;
    unsigned char field0C6B;
    unsigned char field0C6C;
    unsigned char field0C6D;
    unsigned char field0C6E;
    unsigned char field0C6F;
    unsigned int field0C70;
    unsigned char field0C74;
    unsigned char field0C75;
    unsigned char storage0C76[0x2];
    int field0C78;
    unsigned char field0C7C;
    unsigned char field0C7D;
    unsigned char storage0C7E[0x2];
    unsigned int field0C80;
    unsigned char storage0C84[0x4];
    unsigned int field0C88;
    unsigned char field0C8C;
    unsigned char storage0C8D[0x3];
    unsigned int field0C90;
    unsigned int field0C94;
    unsigned char field0C98;
    unsigned char storage0C99[0x3];
    unsigned int field0C9C;
    unsigned int field0CA0;
    unsigned char field0CA4;
    unsigned char storage0CA5[0x27];
    unsigned char field0CCC;
    unsigned char storage0CCD[0x3];
    float field0CD0;
    unsigned int field0CD4;
    unsigned char storage0CD8[0x20];
    unsigned char field0CF8;
    unsigned char field0CF9;
    unsigned char field0CFA;
    unsigned char field0CFB;
    unsigned char field0CFC;
    unsigned char field0CFD;
    unsigned char field0CFE;
    unsigned char field0CFF;
    unsigned char field0D00;
    unsigned char field0D01;
    unsigned char storage0D02[0xA];
    unsigned int field0D0C;
    unsigned int field0D10;
    unsigned int field0D14;
    unsigned int field0D18;
    unsigned int field0D1C;
    unsigned int field0D20;
    unsigned char field0D24;
    unsigned char storage0D25[0x3];
    unsigned int field0D28;
    unsigned char field0D2C;
    unsigned char field0D2D;
    unsigned char field0D2E;
    unsigned char field0D2F;
    unsigned char storage0D30[0x4];
    unsigned char field0D34;
    unsigned char field0D35;
    unsigned char field0D36;
    unsigned char storage0D37[0x1];
    AsciiString m_modDir;
    AsciiString m_modBIG;
    float field0D40;
    unsigned char field0D44;
    unsigned char field0D45;
    unsigned char field0D46;
    unsigned char storage0D47[0x1];
    int field0D48;
    AsciiString m_particleCursorAnim2DTemplateName;
    unsigned int m_particleCursorBurstCount;
    GameClientRandomVariable m_particleCursorBurstFactor;
    float m_particleCursorStopBurstFactor;
    unsigned int m_particleCursorBurstFrequency;
    GameClientRandomVariable m_particleCursorParticleLife;
    GameClientRandomVariable m_particleCursorSystemLife;
    GameClientRandomVariable m_particleCursorDriftVelX;
    GameClientRandomVariable m_particleCursorDriftVelY;
    GameClientRandomVariable m_particleCursorVelocityDrag;
    GameClientRandomVariable m_particleCursorParticleSize;
    bool m_particleCursorPerFrameSize;
    unsigned char storage0DB1[0x3];
    int m_particleCursorAlpha;
    ICoord2D m_particleCursorOffset;
    ICoord2D m_progressMovieOffset;
    ICoord2D m_progressMovieSize;
    bool m_useHelpTextSystem;
    bool m_guiTextureFiltering;
    unsigned char storage0DD2[0x2];
    float m_cameraLockHeightDelta;
    float m_cameraTerrainSampleRadiusForHeight;
    bool m_enableHouseColor;
    unsigned char storage0DDD[0x3];
    float m_cameraEaseFactor;
    float field0DE4;
    unsigned char field0DE8;
    unsigned char storage0DE9[0x13];
    int m_goodCommandPointsBonus;
    int m_evilCommandPointsBonus;
    unsigned char storage0E04[0x80];
    int m_initialMaxRingLevel;
    float m_resourceBonusMultiplier;
    int m_goodCommandPointLimit;
    int m_evilCommandPointLimit;
    int m_powerLimit;
    float m_resourceMultiplierLimit;
    unsigned char field0E9C;
    unsigned char field0E9D;
    unsigned char storage0E9E[0x2];
    int field0EA0;
    unsigned char field0EA4;
    unsigned char field0EA5;
    unsigned char field0EA6;
    unsigned char field0EA7;
    float field0EA8;
    float field0EAC;
    ObjectFilter m_treeFadeObjectFilter;
    ObjectFilter m_camouflageDetectorObjectFilter;
    ObjectFilter m_veterancyPipDrawObjectFilter;
    ObjectFilter m_victoryConditionStructureObjectFilter;
    ObjectFilter m_victoryConditionUnitObjectFilter;
    MultiPlayMults m_multiPlayMults;
    float m_handicapBuildSpeed5;
    float m_handicapBuildSpeed10;
    float m_handicapBuildSpeed15;
    float m_handicapBuildSpeed20;
    float m_handicapBuildSpeed25;
    float m_handicapBuildSpeed30;
    float m_handicapBuildSpeed35;
    float m_handicapBuildSpeed40;
    float m_handicapBuildSpeed45;
    float m_handicapBuildSpeed50;
    float m_handicapBuildSpeed55;
    float m_handicapBuildSpeed60;
    float m_handicapBuildSpeed65;
    float m_handicapBuildSpeed70;
    float m_handicapBuildSpeed75;
    float m_handicapBuildSpeed80;
    float m_handicapBuildSpeed85;
    float m_handicapBuildSpeed90;
    float m_handicapBuildSpeed95;
    float m_handicapBuildSpeed100;
#ifdef _STLP_INTERNAL_VECTOR_H
    _STL::vector<AsciiString> field10F4;
#else
    unsigned char storage10F4[0xC];
#endif
    unsigned char field1100;
    unsigned char storage1101[0x3];
    unsigned int field1104;
    int m_blockedByWallLeeway;
    float m_secondsBeforeBaseCheckActive;
    unsigned char field1110;
    unsigned char field1111;
    unsigned char storage1112[0x2];
    AsciiString m_basicTutorialMap;
    AsciiString m_basicTutorialLoadMovie;
    AsciiString m_basicTutorialLoadScreenStillImage;
    AsciiString m_basicTutorialLoadScreenVoiceTrack;
    AsciiString m_basicTutorialLoadScreenMusicTrack;
    unsigned char storage1128[0xC];
    unsigned int m_basicTutorialMillisecondsAfterStartToStartFadeUp;
    AsciiString m_advancedTutorialMap;
    AsciiString m_advancedTutorialLoadMovie;
    AsciiString m_advancedTutorialLoadScreenStillImage;
    AsciiString m_advancedTutorialLoadScreenVoiceTrack;
    AsciiString m_advancedTutorialLoadScreenMusicTrack;
    unsigned char storage114C[0xC];
    unsigned int m_advancedTutorialMillisecondsAfterStartToStartFadeUp;
    unsigned int field115C;
    unsigned int field1160;
    unsigned int field1164;
    ObjectFilter m_objectsThatScore;
    float m_scoreKeeper_UnitsBuiltMultiplier;
    float m_scoreKeeper_UnitsDestroyedMultiplier;
    float m_scoreKeeper_StructuresBuiltMultiplier;
    float m_scoreKeeper_StructuresDestroyedMultiplier;
    float m_scoreKeeper_HeroesVettedMultiplier;
    float m_scoreKeeper_UnitsVettedMultiplier;
    float m_scoreKeeper_ObjectivesCompletedMultiplier;
    float m_scoreKeeper_SuppliesCollectedMultiplier;
    float m_scoreKeeper_PowerPointsMultiplier;
    float m_scoreKeeper_RegionCommandPointsMultiplier;
    float m_scoreKeeper_RegionResourcesMultiplier;
    float m_scoreKeeper_RegionPowerPointsMultiplier;
    float m_scoreKeeper_TimeTakenMultiplier;
    float m_scoreKeeper_TimeTakenMaximumScore;
    float m_scoreKeeper_TimeTakenMinimumScore;
    float m_scoreKeeper_TotalVictoryRequiredScore;
    float m_scoreKeeper_NormalVictoryRequiredScore;
    float m_scoreKeeper_NormalVictoryRequiredObjectivesPercentage;
    float m_scoreKeeper_SkillPointsMultiplier;
    float m_scoreKeeper_PlayerEliminatedMultiplier;
    unsigned char field11BC;
    unsigned char storage11BD[0x3];
    unsigned int m_tintUnitIfPathingForMoreThan;
    float m_clampedLOSHeightForCastleStructures;
    unsigned char field11C8;
    unsigned char field11C9;
    bool m_planningModeEnabled;
    unsigned char field11CB;
    unsigned int m_reinvisibityDelay;
    float m_invisibilityOpacityMin;
    float m_invisibilityOpacityMax;
    unsigned int m_invisibilityOpacityCycleFrames;
    unsigned int m_builderFadeOutTime;
    unsigned int m_builderFadeInTime;
    float m_builderMoveFromNewStructureDistance;
    unsigned int m_maxPathfindCellsPerFrame;
    unsigned int m_maxCellsFindMeleeEngagementLocation;
    unsigned int m_maxCellsAdjustDestination;
    unsigned int m_maxCellsAdjustHordeMeleeDestination;
    unsigned int m_maxCellsAdjustTargetDestination;
    unsigned int m_maxCellsAdjustToPossibleDestination;
    unsigned int m_maxCellsAdjustToMeleeDestination;
    unsigned int m_maxCellsAdjustToNearestGroundCell;
    unsigned int m_maxCellsAdjustToNearestValidCell;
    unsigned int m_maxCellsPatchPath;
    unsigned int m_maxCellsFindPathLimit;
    unsigned int m_maxCellsFindAttackPath;
    unsigned int m_maxCellsFindAttackPathSideways;
    unsigned int m_maxCellsToExamineTowardsGoal;
    float m_maxCastleRadius;
    float m_garrisonedRangeMultiplier;
    unsigned int field1228;
    int m_numMinutesBeforePlayersCanTransferMoney;
    unsigned int m_maxNumMembersToForceToImmediatelyEnter;
    unsigned int m_waitToForceMemberToEnterDelay;
    unsigned int field1238;
    unsigned char field123C;
    unsigned char field123D;
    unsigned char storage123E[0x2];
    AsciiString field1240;
    UnicodeString field1244;
    AsciiString m_picturePath;
    AsciiString m_userDataLeafName;
    GlobalData * m_next;
};

extern GlobalData *TheWritableGlobalData;

#endif
