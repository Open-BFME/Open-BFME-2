// cl: /DNDEBUG /MD
//
// ??0RiderChangeContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0047E268,
// 120 bytes. Behavior ctor over the pinned SiegeEngineContain base 0x47C21E
// with four zeros at +0x138/+0x13C/+0x140/+0x144 and ten vtable stores at
// +0/+0xC/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34/+0xFC (address-of
// TU-local dummies, DIR32-masked). The rowed name getter at 0x47E325
// proves the class; the rowed instance factory 0x24BD28 (news 0x148) is
// the sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

// Retail table 0x00C47A00 (33 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRiderChangeContain@@UAEPAXI@Z")();
void __identifier("?rva0047E38F@Rva0047E38F@@QAEXXZ")();
void __identifier("?name@RiderChangeContain@@QBEPBDXZ")();
void __identifier("?xfer@RiderChangeContain@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@RiderChangeContain@@UBE?AW4NameKeyType@@XZ")();
void __identifier("?slot02@OpenContain@@UAEXXZ")();
void __identifier("?onDelete@SiegeEngineContain@@UAEXXZ")();
void __identifier("?rva0047E33F@Rva0047E33F@@UAEXHH@Z")();
void __identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
void __identifier("?removeFromContainList@SiegeEngineContain@@UAEXPAVObject@@@Z")();
void __identifier("?rva00466E58@Rva00466E58@@QBEEH@Z")();
void __identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?monitorConditionChanges@OpenContain@@MAEXXZ")();
void __identifier("?redeployOccupants@SiegeEngineContain@@QAEXXZ")();
void __identifier("?rva00464EE7@OpenContain@@UAE_NPAVObject@@@Z")();
void __identifier("?doLoadSound@OpenContain@@MAEXXZ")();
void __identifier("?doUnloadSound@OpenContain@@MAEXXZ")();
void __identifier("?rva00462E3A@Rva00462E3A@@QAEXPAVObject@@HH@Z")();
void __identifier("?rva0047E330@Rva0047E330@@QAEXXZ")();
void __identifier("?privateRedeployOccupants@OpenContain@@AAEXPBV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PAV?$map@HHU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@3@@Z")();
void __identifier("?rva0047B993@Rva0047B993Contain@@QAE_NPAVObject@@@Z")();
void __identifier("?rva0047E32B@Rva0047E32B@@QAEXXZ")();
void __identifier("?rva0046740C@TransportContain@@MAEXXZ")();
void __identifier("?letRidersUpgradeWeaponSet@TransportContain@@MAEXXZ")();
void __identifier("?get@Rva0006E01DDwordField@@QBEHXZ")();
void __identifier("?getContainerPipsToShow@RiderChangeContain@@UAE_NAAH0@Z")();
}
static const void *const s_vtable[33] = {
	(const void *)&__identifier("??_GRiderChangeContain@@UAEPAXI@Z"), //  0 0x0047E4FF
	(const void *)&__identifier("?rva0047E38F@Rva0047E38F@@QAEXXZ"), //  1 0x0047E38F
	(const void *)&__identifier("?name@RiderChangeContain@@QBEPBDXZ"), //  2 0x0047E325
	(const void *)&__identifier("?xfer@RiderChangeContain@@MAEXPAVXfer@@@Z"), //  3 0x0047E357
	(const void *)&__identifier("?getModuleNameKey@RiderChangeContain@@UBE?AW4NameKeyType@@XZ"), //  4 0x0047E2E0
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), //  5 0x000B3FD0
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), //  6 0x000B3FD0
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), //  7 0x000B3FD0
	(const void *)&__identifier("?onDelete@SiegeEngineContain@@UAEXXZ"), //  8 0x0047BB6B
	(const void *)&__identifier("?rva0047E33F@Rva0047E33F@@UAEXHH@Z"), //  9 0x0047E33F
	(const void *)&__identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ"), // 10 0x000D43D0
	(const void *)&__identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ"), // 11 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // 12 0x0022C4CB
	(const void *)&__identifier("?removeFromContainList@SiegeEngineContain@@UAEXPAVObject@@@Z"), // 13 0x0047BD4C
	(const void *)&__identifier("?rva00466E58@Rva00466E58@@QBEEH@Z"), // 14 0x00466E58
	(const void *)&__identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z"), // 15 0x0050B238
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // 16 0x005CB9FF
	(const void *)&__identifier("?monitorConditionChanges@OpenContain@@MAEXXZ"), // 17 0x00462C72
	(const void *)&__identifier("?redeployOccupants@SiegeEngineContain@@QAEXXZ"), // 18 0x0047C2F2
	(const void *)&__identifier("?rva00464EE7@OpenContain@@UAE_NPAVObject@@@Z"), // 19 0x00464EE7
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // 20 0x005CB9FF
	(const void *)&__identifier("?doLoadSound@OpenContain@@MAEXXZ"), // 21 0x0046279C
	(const void *)&__identifier("?doUnloadSound@OpenContain@@MAEXXZ"), // 22 0x0046282B
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), // 23 0x000B3FD0
	(const void *)&__identifier("?rva00462E3A@Rva00462E3A@@QAEXPAVObject@@HH@Z"), // 24 0x00462E3A
	(const void *)&__identifier("?rva0047E330@Rva0047E330@@QAEXXZ"), // 25 0x0047E330
	(const void *)&__identifier("?privateRedeployOccupants@OpenContain@@AAEXPBV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PAV?$map@HHU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@3@@Z"), // 26 0x00465972
	(const void *)&__identifier("?rva0047B993@Rva0047B993Contain@@QAE_NPAVObject@@@Z"), // 27 0x0047E335: jmp 0x0047B993, named by its target
	(const void *)&__identifier("?rva0047E32B@Rva0047E32B@@QAEXXZ"), // 28 0x0047E32B
	(const void *)&__identifier("?rva0046740C@TransportContain@@MAEXXZ"), // 29 0x0046740C
	(const void *)&__identifier("?letRidersUpgradeWeaponSet@TransportContain@@MAEXXZ"), // 30 0x0046760D
	(const void *)&__identifier("?get@Rva0006E01DDwordField@@QBEHXZ"), // 31 0x0006E01D
	(const void *)&__identifier("?getContainerPipsToShow@RiderChangeContain@@UAE_NAAH0@Z")  // 32 0x0047E344
};
extern "C" const void *const __identifier("??_7AODHordeContain@@6BIface0C@@@")[];
// Retail table 0x00C479F0 (3 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?rva047E59E@Rva047E59E@@QAEXXZ")();
void __identifier("?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0L@@@XZ")();
void __identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z")();
}
static const void *const s_secondary10[3] = {
	(const void *)&__identifier("?rva047E59E@Rva047E59E@@QAEXXZ"), //  0 0x0047E59E
	(const void *)&__identifier("?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0L@@@XZ"), //  1 0x00253376
	(const void *)&__identifier("?rva0044DF8D@UpdateModule@@UAEXW4UpdateSleepTime@@@Z")  //  2 0x0044DF8D
};
// Retail table 0x00C47878 (94 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?rva0046261B@SlaughterHordeContain@@UAEX_N@Z")();
void __identifier("?get@Rva004647CDLeaField@@QBEPAXXZ")();
void __identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ")();
void __identifier("?containReactToTransformChange@OpenContain@@UAEXXZ")();
void __identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ")();
void __identifier("?slot08@OpenContainModuleData@@UBE_NXZ")();
void __identifier("?rva0047EA58@RiderChangeContain@@UAEPAVObject@@XZ")();
void __identifier("?get@Rva0046294EByteChaseField@@QBEEXZ")();
void __identifier("?slot02@OpenContain@@UAEXXZ")();
void __identifier("?rva004639D5@Rva004639D5@@UAEHH@Z")();
void __identifier("?rva00464FC7@SlaughterHordeContain@@UAE_NPAXH@Z")();
void __identifier("?rva0046322C@Rva0046322C@@QAEHXZ")();
void __identifier("?slot2@PlanningPhaseBuildingSelection@StrategicInGameUI@@UAEHPAX@Z")();
void __identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z")();
void __identifier("?onContaining@RiderChangeContain@@UAEXPAVObject@@_N@Z")();
void __identifier("?onRemoving@RiderChangeContain@@UAEXPAVObject@@@Z")();
void __identifier("?rva0047E33F@Rva0047E33F@@WCA@AEXHH@Z")();
void __identifier("?rva00462504@SlaughterHordeContain@@UAEXXZ")();
void __identifier("?rva00462516@SlaughterHordeContain@@QAEXPAX0PAUDamageInfoInput00462516@@@Z")();
void __identifier("?rva00468657@Rva00468657@@QAEXPAVObject@@_N@Z")();
void __identifier("?getContainMax@RiderChangeContain@@UBEHXZ")();
void __identifier("?Rva004647F0Adjust@@YIPAXPAX@Z")();
void __identifier("?rva00465011@OpenContainActionIface@@UAEXPAVObject@@@Z")();
void __identifier("?rva00465078@OpenContainActionIface@@UAEXW4CommandSourceType@@@Z")();
void __identifier("?rva0047BE23@Rva0047BDED@@QAEXH@Z")();
void __identifier("?rva00463138@OpenContainActionIface@@UAEXXZ")();
void __identifier("?isValidContainerFor@RiderChangeContain@@UAE_NPAVObject@@_N1@Z")();
void __identifier("?addToContain@OpenContain@@UAEXPAVObject@@@Z")();
void __identifier("?addToContainList@SiegeEngineContain@@UAEXPAVObject@@@Z")();
void __identifier("?removeFromContain@Rva00463509@@QAEXPAVObject@@_N@Z")();
void __identifier("?removeAllContained@Rva0047BDED@@QAEX_N@Z")();
void __identifier("?rva0046274C@SlaughterHordeContain@@UAEXPAXH0@Z")();
void __identifier("?rva0047CAEB@Rva0047CAEBOwner@@QAEPAVBfmeObject872Header@@PAV2@PAVObject@@@Z")();
void __identifier("?rva00462B4A@Rva00462B4A@@QAE_NXZ")();
void __identifier("?get@Rva0047CB3FSub@@QBE_NXZ")();
void __identifier("?rva00462B93@SlaughterHordeContain@@UAE_NPBVRva00462B93Arg@@@Z")();
void __identifier("?rva00462BFF@OpenContainActionIface@@UBEDPBVObject@@0@Z")();
void __identifier("?get@Rva00467F2CDwordField@@QBEHXZ")();
void __identifier("?rva0047CADB@SiegeEngineContain@@UAEMXZ")();
void __identifier("?rva004628AB@OpenContainActionIface@@UAE_NHH@Z")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?rva004631FA@SiegeEngineContain@@UAE_NH@Z")();
void __identifier("?rva0046731A@Rva0046731A@@QAEXPAVObject@@@Z")();
void __identifier("?rva004673C0@TransportContain@@UAEXXZ")();
void __identifier("?getClosestRider@OpenContain@@UAEPAVObject@@PBUCoord3D@@@Z")();
void __identifier("?set@Rva00464810ByteSlot@@QAEXE@Z")();
void __identifier("?rva00462735@Rva00462735@@QAEXXZ")();
void __identifier("?get@Rva00462CD3Sub@@QBE_NXZ")();
void __identifier("?onContaining@Rva0047BEF8@@UAEXPAVObject@@_N@Z")();
void __identifier("?rva0047BEC9@SiegeEngineContain@@QAEXXZ")();
void __identifier("?iterateContained@Rva0047BE4C@@QAEXP6AXPAVObject@@PAX@Z1H@Z")();
void __identifier("?rva00462DE0@Rva00462DE0@@QAEHPAVRva2225E0Filter@@@Z")();
void __identifier("?rva004647D8@Rva004647D8@@QAEPAXPAX@Z")();
void __identifier("?rva004624EB@SiegeEngineContain@@UAEXAAURva0046247DPair@@@Z")();
void __identifier("?friend_getRider@RiderChangeContain@@UBEPBVObject@@XZ")();
void __identifier("?get@Rva005C4AFDDwordField@@QBEHXZ")();
void __identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z")();
void __identifier("?rva0041BA5C@Rva0041BA5C@@QAE_NHHH@Z")();
void __identifier("?rva00463291@OpenContainActionIface@@UAEPAVObject@@PAVRva2225E0Filter@@@Z")();
void __identifier("?get@Rva0047C033ByteField@@QBEEXZ")();
void __identifier("?get@Rva003F3FCEDwordField@@QBEHXZ")();
void __identifier("?rva004642D3@SlaughterHordeContain@@UAEXXZ")();
void __identifier("?set@Rva004647FDByteSlot@@QAEXE@Z")();
void __identifier("?rva0046333B@Rva0046333B@@QAE_NPAH00000@Z")();
void __identifier("?get@Rva00464825DwordField@@QBEHXZ")();
void __identifier("?rva004626CA@OpenContain@@UAEPBUCoord3D@@XZ")();
void __identifier("?rva004626AF@OpenContainActionIface@@UAEPBUCoord3D@@XZ")();
void __identifier("?get@Rva00464829AddDwordField@@QBEHXZ")();
void __identifier("?rva0046480A@Rva0046480A@@QAEHH@Z")();
void __identifier("?rva004625BB@SlaughterHordeContain@@UAE_NPAXH@Z")();
void __identifier("?rva004625F0@SlaughterHordeContain@@UAEXPAX@Z")();
void __identifier("?rva00462955@OpenContainActionIface@@UAE_NPAVObject@@H@Z")();
void __identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z")();
}
static const void *const s_secondary20[94] = {
	(const void *)&__identifier("?rva0046261B@SlaughterHordeContain@@UAEX_N@Z"), //  0 0x0046261B
	(const void *)&__identifier("?get@Rva004647CDLeaField@@QBEPAXXZ"), //  1 0x004647CD
	(const void *)&__identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ"), //  2 0x000D43D0
	(const void *)&__identifier("?containReactToTransformChange@OpenContain@@UAEXXZ"), //  3 0x004624E3
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  4 0x0047A699
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  5 0x0047A699
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  6 0x0047A699
	(const void *)&__identifier("?slot08@OpenContainModuleData@@UBE_NXZ"), //  7 0x0050B5C6
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  8 0x0047A699
	(const void *)&__identifier("?slot08@OpenContainModuleData@@UBE_NXZ"), //  9 0x0050B5C6
	(const void *)&__identifier("?rva0047EA58@RiderChangeContain@@UAEPAVObject@@XZ"), // 10 0x0047EA58
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), // 11 0x0047A699
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), // 12 0x0047A699
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), // 13 0x0047A699
	(const void *)&__identifier("?get@Rva0046294EByteChaseField@@QBEEXZ"), // 14 0x0046294E
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), // 15 0x000B3FD0
	(const void *)&__identifier("?rva004639D5@Rva004639D5@@UAEHH@Z"), // 16 0x004639D5
	(const void *)&__identifier("?rva00464FC7@SlaughterHordeContain@@UAE_NPAXH@Z"), // 17 0x00464FC7
	(const void *)&__identifier("?rva0046322C@Rva0046322C@@QAEHXZ"), // 18 0x0046322C
	(const void *)&__identifier("?slot2@PlanningPhaseBuildingSelection@StrategicInGameUI@@UAEHPAX@Z"), // 19 0x005DAA6C
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), // 20 0x000B3FD0
	(const void *)&__identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z"), // 21 0x0047A69C
	(const void *)&__identifier("?onContaining@RiderChangeContain@@UAEXPAVObject@@_N@Z"), // 22 0x0047E5D4
	(const void *)&__identifier("?onRemoving@RiderChangeContain@@UAEXPAVObject@@@Z"), // 23 0x0047E7CF
	(const void *)&__identifier("?rva0047E33F@Rva0047E33F@@WCA@AEXHH@Z"), // 24 0x0047E39A
	(const void *)&__identifier("?rva00462504@SlaughterHordeContain@@UAEXXZ"), // 25 0x00462504
	(const void *)&__identifier("?rva00462516@SlaughterHordeContain@@QAEXPAX0PAUDamageInfoInput00462516@@@Z"), // 26 0x00462516
	(const void *)&__identifier("?rva00468657@Rva00468657@@QAEXPAVObject@@_N@Z"), // 27 0x00468657
	(const void *)&__identifier("?getContainMax@RiderChangeContain@@UBEHXZ"), // 28 0x0047E4EE
	(const void *)&__identifier("?Rva004647F0Adjust@@YIPAXPAX@Z"), // 29 0x004647F0
	(const void *)&__identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ"), // 30 0x000D43D0
	(const void *)&__identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ"), // 31 0x000D43D0
	(const void *)&__identifier("?rva00465011@OpenContainActionIface@@UAEXPAVObject@@@Z"), // 32 0x00465011
	(const void *)&__identifier("?rva00465078@OpenContainActionIface@@UAEXW4CommandSourceType@@@Z"), // 33 0x00465078
	(const void *)&__identifier("?rva0047BE23@Rva0047BDED@@QAEXH@Z"), // 34 0x0047BE23
	(const void *)&__identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z"), // 35 0x0047A69C
	(const void *)&__identifier("?rva00463138@OpenContainActionIface@@UAEXXZ"), // 36 0x00463138
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), // 37 0x000B3FD0
	(const void *)&__identifier("?isValidContainerFor@RiderChangeContain@@UAE_NPAVObject@@_N1@Z"), // 38 0x0047E520
	(const void *)&__identifier("?addToContain@OpenContain@@UAEXPAVObject@@@Z"), // 39 0x00464830
	(const void *)&__identifier("?addToContainList@SiegeEngineContain@@UAEXPAVObject@@@Z"), // 40 0x0047C07F
	(const void *)&__identifier("?removeFromContain@Rva00463509@@QAEXPAVObject@@_N@Z"), // 41 0x00463509
	(const void *)&__identifier("?removeAllContained@Rva0047BDED@@QAEX_N@Z"), // 42 0x0047BDED
	(const void *)&__identifier("?rva0046274C@SlaughterHordeContain@@UAEXPAXH0@Z"), // 43 0x0046274C
	(const void *)&__identifier("?rva0047CAEB@Rva0047CAEBOwner@@QAEPAVBfmeObject872Header@@PAV2@PAVObject@@@Z"), // 44 0x0047CAEB
	(const void *)&__identifier("?rva00462B4A@Rva00462B4A@@QAE_NXZ"), // 45 0x00462B4A
	(const void *)&__identifier("?get@Rva0047CB3FSub@@QBE_NXZ"), // 46 0x0047CB3F
	(const void *)&__identifier("?rva00462B93@SlaughterHordeContain@@UAE_NPBVRva00462B93Arg@@@Z"), // 47 0x00462B93
	(const void *)&__identifier("?rva00462BFF@OpenContainActionIface@@UBEDPBVObject@@0@Z"), // 48 0x00462BFF
	(const void *)&__identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z"), // 49 0x0047A69C
	(const void *)&__identifier("?slot08@OpenContainModuleData@@UBE_NXZ"), // 50 0x0050B5C6
	(const void *)&__identifier("?get@Rva00467F2CDwordField@@QBEHXZ"), // 51 0x00467F2C
	(const void *)&__identifier("?slot08@OpenContainModuleData@@UBE_NXZ"), // 52 0x0050B5C6
	(const void *)&__identifier("?rva0047CADB@SiegeEngineContain@@UAEMXZ"), // 53 0x0047BAE7
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), // 54 0x0047A699
	(const void *)&__identifier("?rva004628AB@OpenContainActionIface@@UAE_NHH@Z"), // 55 0x004628AB
	(const void *)&__identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ"), // 56 0x000D43D0
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // 57 0x005CB9FF
	(const void *)&__identifier("?rva004631FA@SiegeEngineContain@@UAE_NH@Z"), // 58 0x0047CDCE
	(const void *)&__identifier("?rva0046731A@Rva0046731A@@QAEXPAVObject@@@Z"), // 59 0x0046731A
	(const void *)&__identifier("?rva004673C0@TransportContain@@UAEXXZ"), // 60 0x004673C0
	(const void *)&__identifier("?getClosestRider@OpenContain@@UAEPAVObject@@PBUCoord3D@@@Z"), // 61 0x004632E0
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), // 62 0x000B3FD0
	(const void *)&__identifier("?set@Rva00464810ByteSlot@@QAEXE@Z"), // 63 0x00464810
	(const void *)&__identifier("?rva00462735@Rva00462735@@QAEXXZ"), // 64 0x00462735
	(const void *)&__identifier("?get@Rva00462CD3Sub@@QBE_NXZ"), // 65 0x00462CD3
	(const void *)&__identifier("?onContaining@Rva0047BEF8@@UAEXPAVObject@@_N@Z"), // 66 0x0047BEF8
	(const void *)&__identifier("?rva0047BEC9@SiegeEngineContain@@QAEXXZ"), // 67 0x0047BEC9
	(const void *)&__identifier("?iterateContained@Rva0047BE4C@@QAEXP6AXPAVObject@@PAX@Z1H@Z"), // 68 0x0047BE4C
	(const void *)&__identifier("?rva00462DE0@Rva00462DE0@@QAEHPAVRva2225E0Filter@@@Z"), // 69 0x00462DE0
	(const void *)&__identifier("?rva004647D8@Rva004647D8@@QAEPAXPAX@Z"), // 70 0x004647D8
	(const void *)&__identifier("?rva004624EB@SiegeEngineContain@@UAEXAAURva0046247DPair@@@Z"), // 71 0x0047C018
	(const void *)&__identifier("?friend_getRider@RiderChangeContain@@UBEPBVObject@@XZ"), // 72 0x0047EA26
	(const void *)&__identifier("?get@Rva005C4AFDDwordField@@QBEHXZ"), // 73 0x005C4AFD
	(const void *)&__identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ"), // 74 0x000D43D0
	(const void *)&__identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ"), // 75 0x000D43D0
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // 76 0x0050B5F1
	(const void *)&__identifier("?rva0041BA5C@Rva0041BA5C@@QAE_NHHH@Z"), // 77 0x0041BA5C
	(const void *)&__identifier("?rva0041BA5C@Rva0041BA5C@@QAE_NHHH@Z"), // 78 0x0041BA5C
	(const void *)&__identifier("?rva00463291@OpenContainActionIface@@UAEPAVObject@@PAVRva2225E0Filter@@@Z"), // 79 0x00463291
	(const void *)&__identifier("?get@Rva0047C033ByteField@@QBEEXZ"), // 80 0x0047C033
	(const void *)&__identifier("?get@Rva003F3FCEDwordField@@QBEHXZ"), // 81 0x003F3FCE
	(const void *)&__identifier("?rva004642D3@SlaughterHordeContain@@UAEXXZ"), // 82 0x004642D3
	(const void *)&__identifier("?set@Rva004647FDByteSlot@@QAEXE@Z"), // 83 0x004647FD
	(const void *)&__identifier("?rva0046333B@Rva0046333B@@QAE_NPAH00000@Z"), // 84 0x0046333B
	(const void *)&__identifier("?get@Rva00464825DwordField@@QBEHXZ"), // 85 0x00464825
	(const void *)&__identifier("?rva004626CA@OpenContain@@UAEPBUCoord3D@@XZ"), // 86 0x004626CA
	(const void *)&__identifier("?rva004626AF@OpenContainActionIface@@UAEPBUCoord3D@@XZ"), // 87 0x004626AF
	(const void *)&__identifier("?get@Rva00464829AddDwordField@@QBEHXZ"), // 88 0x00464829
	(const void *)&__identifier("?rva0046480A@Rva0046480A@@QAEHH@Z"), // 89 0x0046480A
	(const void *)&__identifier("?rva004625BB@SlaughterHordeContain@@UAE_NPAXH@Z"), // 90 0x004625BB
	(const void *)&__identifier("?rva004625F0@SlaughterHordeContain@@UAEXPAX@Z"), // 91 0x004625F0
	(const void *)&__identifier("?rva00462955@OpenContainActionIface@@UAE_NPAVObject@@H@Z"), // 92 0x00462955
	(const void *)&__identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z")  // 93 0x0050B238
};
extern "C" const void *const __identifier("??_7HordeSiegeEngineContain@@6BIface24@@@")[];
extern "C" const void *const __identifier("??_7AODHordeContain@@6BIface28@@@")[];
extern "C" const void *const __identifier("??_7AODHordeContain@@6BIface2C@@@")[];
// Retail table 0x00C47848 (12 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ")();
void __identifier("?rva00466D93@Rva00466D93@@UAEHPBVThingTemplate@@PAVObject@@@Z")();
void __identifier("?exitObjectViaDoor@SiegeEngineContain@@UAEXPAVObject@@W4ExitDoorType@@@Z")();
void __identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z")();
void __identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z")();
void __identifier("?exitObjectInAHurry@OpenContain@@UAEXPAVObject@@@Z")();
void __identifier("?rva0046255E@SlaughterHordeContain@@QAEXPBUCoord3D0046255E@@@Z")();
void __identifier("?rva00462579@Rva00462579@@QAEPAURva00462579Block@@XZ")();
void __identifier("?getNaturalRallyPoint@OpenContain@@UBE_NAAUCoord3D@@_N@Z")();
void __identifier("?rva004624C1@Rva004624C1@@QAE_NPAURva00597372Triple@@PAM@Z")();
void __identifier("?slot02@OpenContain@@UAEXXZ")();
}
static const void *const s_secondary30[12] = {
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  0 0x0047A699
	(const void *)&__identifier("?rva00466D93@Rva00466D93@@UAEHPBVThingTemplate@@PAVObject@@@Z"), //  1 0x0047E33A: jmp 0x00466D93, named by its target
	(const void *)&__identifier("?exitObjectViaDoor@SiegeEngineContain@@UAEXPAVObject@@W4ExitDoorType@@@Z"), //  2 0x0047C4F2
	(const void *)&__identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z"), //  3 0x0050B238
	(const void *)&__identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z"), //  4 0x0047A69C
	(const void *)&__identifier("?exitObjectInAHurry@OpenContain@@UAEXPAVObject@@@Z"), //  5 0x004656DF
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  6 0x0047A699
	(const void *)&__identifier("?rva0046255E@SlaughterHordeContain@@QAEXPBUCoord3D0046255E@@@Z"), //  7 0x0046255E
	(const void *)&__identifier("?rva00462579@Rva00462579@@QAEPAURva00462579Block@@XZ"), //  8 0x00462579
	(const void *)&__identifier("?getNaturalRallyPoint@OpenContain@@UBE_NAAUCoord3D@@_N@Z"), //  9 0x0046363F
	(const void *)&__identifier("?rva004624C1@Rva004624C1@@QAE_NPAURva00597372Triple@@PAM@Z"), // 10 0x004624C1
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ")  // 11 0x000B3FD0
};
// Retail table 0x00C47838 (4 slots), stored by the constructor below. Own the
// complete initialized table instead of a zero-int stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?loadPostProcess@BaseUpgrade@@MAEXXZ")();
void __identifier("?forward@Rva00466E0A@@UAEXXZ")();
void __identifier("?slot02@OpenContain@@UAEXXZ")();
void __identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ")();
}
static const void *const s_secondary34[4] = {
	(const void *)&__identifier("?loadPostProcess@BaseUpgrade@@MAEXXZ"), //  0 0x00497805
	(const void *)&__identifier("?forward@Rva00466E0A@@UAEXXZ"), //  1 0x00466E0A
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), //  2 0x000B3FD0
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ")  //  3 0x0047A699
};
extern "C" const void *const __identifier("??_7AODHordeContain@@6BIfaceFC@@@")[];

// Opaque SiegeEngineContain base (0x138); ctor resolves to its pin.
class Xfer;
class SiegeEngineContain
{
public:
	SiegeEngineContain(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	char m_unrecovered04[ 0x138 - 0x04 ]; // +0x04
};

class RiderChangeContain : public SiegeEngineContain
{
public:
	RiderChangeContain(Thing *thing, const ModuleData *moduleData);

private:
	int m_138;
	int m_13C;
	int m_140;
	unsigned char m_144;
};

// ??0RiderChangeContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x0047E268
RiderChangeContain::RiderChangeContain(Thing *thing, const ModuleData *moduleData) :
	SiegeEngineContain(thing, moduleData)
{
	m_138 = 0;
	m_13C = 0;
	m_144 = 0;
	m_140 = 0;
	*(const void **)this = &s_vtable;
	*(const void **)((char *)this + 0xC) = __identifier("??_7AODHordeContain@@6BIface0C@@@");
	*(const void **)((char *)this + 0x10) = &s_secondary10;
	*(const void **)((char *)this + 0x20) = &s_secondary20;
	*(const void **)((char *)this + 0x24) = __identifier("??_7HordeSiegeEngineContain@@6BIface24@@@");
	*(const void **)((char *)this + 0x28) = __identifier("??_7AODHordeContain@@6BIface28@@@");
	*(const void **)((char *)this + 0x2C) = __identifier("??_7AODHordeContain@@6BIface2C@@@");
	*(const void **)((char *)this + 0x30) = &s_secondary30;
	*(const void **)((char *)this + 0x34) = &s_secondary34;
	*(const void **)((char *)this + 0xFC) = __identifier("??_7AODHordeContain@@6BIfaceFC@@@");
}
