// cl: /DNDEBUG /MD /GX
//
// ??0HordeTransportContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00477003, 149 bytes. Behavior-side ctor (rowed instance factory
// 0x24B9CC news 0x128 with this pinned 2-arg ctor as its sole raw caller
// at 0x24B9F6; a derived contain ctor at 0x47D25E shares the base call).
//
// Shape: EH prologue via /GX plus the declared-only base dtor over the
// pinned TransportContain base 0x468559, a Coord2D member at +0x11D built
// in the init-list (rowed 0-arg ctor 0x47A6A9; declared here without a
// dtor so no unwind state is added), the three derived vtable installs
// plus six secondaries, an int minus-1000 at +0x120 and a zero byte at
// +0x124 through pointer casts into the member tail (the rowed Coord2D is
// eight bytes so both overlap it), and no setWakeFrame tail. The base
// runs to +0x11D. Row supersedes the ctor pin.

extern "C" const void *const __identifier("??_7AODHordeContain@@6BIface0C@@@")[];  // folded vftable 0x00C441B8 (6 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7TransportContain@@6BB8@@@")[];  // folded vftable 0x00C45CEC (2 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7HordeSiegeEngineContain@@6BIface24@@@")[];  // folded vftable 0x00C46064 (12 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7AODHordeContain@@6BIfaceFC@@@")[];  // folded vftable 0x00C47834 (5 classes), by its data-ledger name
extern "C" const void *const __identifier("??_7AODHordeContain@@6BIface2C@@@")[];  // folded vftable 0x00C58790 (55 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7HordeSiegeEngineContain@@6BIface28@@@")[];  // vftable 0x00C45D2C
extern "C" const void *const __identifier("??_7HordeSiegeEngineContain@@6BIface10@@@")[];  // vftable 0x00C45EA8

// Retail table 0x00C45CFC (12 slots), stored by the constructor below. Own the
// complete initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?isExitBusy@TransportContain@@UBE_NXZ")();
void __identifier("?rva00466D93@Rva00466D93@@UAEHPBVThingTemplate@@PAVObject@@@Z")();
void __identifier("?exitObjectViaDoor@HordeTransportContain@@UAEXPAVObject@@W4ExitDoorType@@@Z")();
void __identifier("?rva005F267E@Rva0086EE20@@UAEXHM@Z")();
void __identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z")();
void __identifier("?exitObjectInAHurry@OpenContain@@UAEXPAVObject@@@Z")();
void __identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ")();
void __identifier("?rva0046255E@SlaughterHordeContain@@QAEXPBUCoord3D0046255E@@@Z")();
void __identifier("?rva00462579@Rva00462579@@QAEPAURva00462579Block@@XZ")();
void __identifier("?getNaturalRallyPoint@OpenContain@@UBE_NAAUCoord3D@@_N@Z")();
void __identifier("?rva004624C1@Rva004624C1@@QAE_NPAURva00597372Triple@@PAM@Z")();
void __identifier("?slot02@OpenContain@@UAEXXZ")();
}
extern const void *const g_00C45CFC[12] = {
	(const void *)&__identifier("?isExitBusy@TransportContain@@UBE_NXZ"), //  0 0x00466DA9
	(const void *)&__identifier("?rva00466D93@Rva00466D93@@UAEHPBVThingTemplate@@PAVObject@@@Z"), //  1 0x00466D93
	(const void *)&__identifier("?exitObjectViaDoor@HordeTransportContain@@UAEXPAVObject@@W4ExitDoorType@@@Z"), //  2 0x004775FD
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
// Retail table 0x00C45D30 (94 slots), stored by the constructor below. Own the
// complete initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("?rva0046261B@SlaughterHordeContain@@UAEX_N@Z")();
void __identifier("?get@Rva004647CDLeaField@@QBEPAXXZ")();
void __identifier("?winNextTab@GameWindow@@QAEHXZ")();
void __identifier("?containReactToTransformChange@OpenContain@@UAEXXZ")();
void __identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ")();
void __identifier("?slot08@OpenContainModuleData@@UBE_NXZ")();
void __identifier("?get@Rva0046294EByteChaseField@@QBEEXZ")();
void __identifier("?slot02@OpenContain@@UAEXXZ")();
void __identifier("?rva004639D5@Rva004639D5@@UAEHH@Z")();
void __identifier("?rva00464FC7@SlaughterHordeContain@@UAE_NPAXH@Z")();
void __identifier("?rva0046322C@Rva0046322C@@QAEHXZ")();
void __identifier("?slot2@PlanningPhaseBuildingSelection@StrategicInGameUI@@UAEHPAX@Z")();
void __identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z")();
void __identifier("?rva0046781F@Rva0046781F@@QAEXPAVObject@@_N@Z")();
void __identifier("?onRemoving@Rva00467AB8@@QAEXPAVObject@@@Z")();
void __identifier("?onCapture@TransportContain@@WCA@AEXHH@Z")();
void __identifier("?rva00462504@SlaughterHordeContain@@UAEXXZ")();
void __identifier("?rva00479C0C@HordeGarrisonContain@@UAEXPAVObject@@PAXPAUDamageInfoInput00462516@@@Z")();
void __identifier("?rva0050B238@HordeTransportContain@@UAEXPAVObject@@_N@Z")();
void __identifier("?getContainMax@RiderChangeContain@@UBEHXZ")();
void __identifier("?Rva004647F0Adjust@@YIPAXPAX@Z")();
void __identifier("?rva00465011@HordeTransportContain@@UAEXPAVObject@@@Z")();
void __identifier("?rva00465078@OpenContainActionIface@@UAEXW4CommandSourceType@@@Z")();
void __identifier("?rva00463138@OpenContainActionIface@@UAEXXZ")();
void __identifier("?isValidContainerFor@HordeTransportContain@@UAE_NPAVObject@@_N1@Z")();
void __identifier("?addToContain@HordeTransportContain@@UAEXPAVObject@@@Z")();
void __identifier("?addToContainList@OpenContain@@UAEXPAVObject@@@Z")();
void __identifier("?rva00477432@Rva00477432@@QAEXPAVObject@@H@Z")();
void __identifier("?removeAllContained@OpenContain@@UAEX_N@Z")();
void __identifier("?rva0046274C@SlaughterHordeContain@@UAEXPAXH0@Z")();
void __identifier("?rva00462CE1@SlaughterHordeContain@@UAEPAVBfmeObject872Header@@PAV2@H@Z")();
void __identifier("?rva00462B4A@Rva00462B4A@@QAE_NXZ")();
void __identifier("?rva00462B93@SlaughterHordeContain@@UAE_NPBVRva00462B93Arg@@@Z")();
void __identifier("?rva00462BFF@OpenContainActionIface@@UBEDPBVObject@@0@Z")();
void __identifier("?get@Rva00467F2CDwordField@@QBEHXZ")();
void __identifier("?Rva004647D1Get@@YAMXZ")();
void __identifier("?rva004628AB@OpenContainActionIface@@UAE_NHH@Z")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?rva004631FA@SlaughterHordeContain@@UAE_NH@Z")();
void __identifier("?rva0046731A@Rva0046731A@@QAEXPAVObject@@@Z")();
void __identifier("?rva004673C0@TransportContain@@UAEXXZ")();
void __identifier("?rva004632E0@HordeTransportContain@@UAEXPAVObject@@@Z")();
void __identifier("?enable@Rva0047709EByteOneSetter@@QAEXXZ")();
void __identifier("?set@Rva00464810ByteSlot@@QAEXE@Z")();
void __identifier("?rva00462735@Rva00462735@@QAEXXZ")();
void __identifier("?get@Rva00462CD3Sub@@QBE_NXZ")();
void __identifier("?onContaining@TransportContain@@UAEXPAVObject@@_N@Z")();
void __identifier("?rva004631C9@SlaughterHordeContain@@UAEXXZ")();
void __identifier("?rva004635EC@SlaughterHordeContain@@UAEXP6AXPAVObject@@PAX@Z1H@Z")();
void __identifier("?rva00462DE0@Rva00462DE0@@QAEHPAVRva2225E0Filter@@@Z")();
void __identifier("?rva004647D8@Rva004647D8@@QAEPAXPAX@Z")();
void __identifier("?rva004624EB@Rva004624EB@@UAE?AURva00462465@@XZ")();
void __identifier("?get@Rva005C4AFDDwordField@@QBEHXZ")();
void __identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z")();
void __identifier("?rva0041BA5C@Rva0041BA5C@@QAE_NHHH@Z")();
void __identifier("?rva00463291@OpenContainActionIface@@UAEPAVObject@@PAVRva2225E0Filter@@@Z")();
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
void __identifier("?rva004776E7@HordeTransportContain@@QAEXPBURva004776E7UpgradeMask@@_N@Z")();
}
extern const void *const g_00C45D30[94] = {
	(const void *)&__identifier("?rva0046261B@SlaughterHordeContain@@UAEX_N@Z"), //  0 0x0046261B
	(const void *)&__identifier("?get@Rva004647CDLeaField@@QBEPAXXZ"), //  1 0x004647CD
	(const void *)&__identifier("?winNextTab@GameWindow@@QAEHXZ"), //  2 0x000D43D0
	(const void *)&__identifier("?containReactToTransformChange@OpenContain@@UAEXXZ"), //  3 0x004624E3
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  4 0x0047A699
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  5 0x0047A699
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  6 0x0047A699
	(const void *)&__identifier("?slot08@OpenContainModuleData@@UBE_NXZ"), //  7 0x0050B5C6
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  8 0x0047A699
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), //  9 0x0047A699
	(const void *)&__identifier("?winNextTab@GameWindow@@QAEHXZ"), // 10 0x000D43D0
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
	(const void *)&__identifier("?rva0046781F@Rva0046781F@@QAEXPAVObject@@_N@Z"), // 22 0x0046781F
	(const void *)&__identifier("?onRemoving@Rva00467AB8@@QAEXPAVObject@@@Z"), // 23 0x00467AB8
	(const void *)&__identifier("?onCapture@TransportContain@@WCA@AEXHH@Z"), // 24 0x00467F33
	(const void *)&__identifier("?rva00462504@SlaughterHordeContain@@UAEXXZ"), // 25 0x00462504
	(const void *)&__identifier("?rva00479C0C@HordeGarrisonContain@@UAEXPAVObject@@PAXPAUDamageInfoInput00462516@@@Z"), // 26 0x00479C0C
	(const void *)&__identifier("?rva0050B238@HordeTransportContain@@UAEXPAVObject@@_N@Z"), // 27 0x00477121
	(const void *)&__identifier("?getContainMax@RiderChangeContain@@UBEHXZ"), // 28 0x0047E4EE
	(const void *)&__identifier("?Rva004647F0Adjust@@YIPAXPAX@Z"), // 29 0x004647F0
	(const void *)&__identifier("?winNextTab@GameWindow@@QAEHXZ"), // 30 0x000D43D0
	(const void *)&__identifier("?winNextTab@GameWindow@@QAEHXZ"), // 31 0x000D43D0
	(const void *)&__identifier("?rva00465011@HordeTransportContain@@UAEXPAVObject@@@Z"), // 32 0x004772B8
	(const void *)&__identifier("?rva00465078@OpenContainActionIface@@UAEXW4CommandSourceType@@@Z"), // 33 0x00465078
	(const void *)&__identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z"), // 34 0x0047A69C
	(const void *)&__identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z"), // 35 0x0047A69C
	(const void *)&__identifier("?rva00463138@OpenContainActionIface@@UAEXXZ"), // 36 0x00463138
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), // 37 0x000B3FD0
	(const void *)&__identifier("?isValidContainerFor@HordeTransportContain@@UAE_NPAVObject@@_N1@Z"), // 38 0x004771EB
	(const void *)&__identifier("?addToContain@HordeTransportContain@@UAEXPAVObject@@@Z"), // 39 0x004773D6
	(const void *)&__identifier("?addToContainList@OpenContain@@UAEXPAVObject@@@Z"), // 40 0x004638F1
	(const void *)&__identifier("?rva00477432@Rva00477432@@QAEXPAVObject@@H@Z"), // 41 0x00477432
	(const void *)&__identifier("?removeAllContained@OpenContain@@UAEX_N@Z"), // 42 0x004635C0
	(const void *)&__identifier("?rva0046274C@SlaughterHordeContain@@UAEXPAXH0@Z"), // 43 0x0046274C
	(const void *)&__identifier("?rva00462CE1@SlaughterHordeContain@@UAEPAVBfmeObject872Header@@PAV2@H@Z"), // 44 0x00462CE1
	(const void *)&__identifier("?rva00462B4A@Rva00462B4A@@QAE_NXZ"), // 45 0x00462B4A
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), // 46 0x0047A699
	(const void *)&__identifier("?rva00462B93@SlaughterHordeContain@@UAE_NPBVRva00462B93Arg@@@Z"), // 47 0x00462B93
	(const void *)&__identifier("?rva00462BFF@OpenContainActionIface@@UBEDPBVObject@@0@Z"), // 48 0x00462BFF
	(const void *)&__identifier("?onDamage@OpenContain@@UAEXPAVDamageInfo@@@Z"), // 49 0x0047A69C
	(const void *)&__identifier("?slot08@OpenContainModuleData@@UBE_NXZ"), // 50 0x0050B5C6
	(const void *)&__identifier("?get@Rva00467F2CDwordField@@QBEHXZ"), // 51 0x00467F2C
	(const void *)&__identifier("?slot08@OpenContainModuleData@@UBE_NXZ"), // 52 0x0050B5C6
	(const void *)&__identifier("?Rva004647D1Get@@YAMXZ"), // 53 0x004647D1
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), // 54 0x0047A699
	(const void *)&__identifier("?rva004628AB@OpenContainActionIface@@UAE_NHH@Z"), // 55 0x004628AB
	(const void *)&__identifier("?winNextTab@GameWindow@@QAEHXZ"), // 56 0x000D43D0
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // 57 0x005CB9FF
	(const void *)&__identifier("?rva004631FA@SlaughterHordeContain@@UAE_NH@Z"), // 58 0x004631FA
	(const void *)&__identifier("?rva0046731A@Rva0046731A@@QAEXPAVObject@@@Z"), // 59 0x0046731A
	(const void *)&__identifier("?rva004673C0@TransportContain@@UAEXXZ"), // 60 0x004673C0
	(const void *)&__identifier("?rva004632E0@HordeTransportContain@@UAEXPAVObject@@@Z"), // 61 0x0047710B
	(const void *)&__identifier("?enable@Rva0047709EByteOneSetter@@QAEXXZ"), // 62 0x0047709E
	(const void *)&__identifier("?set@Rva00464810ByteSlot@@QAEXE@Z"), // 63 0x00464810
	(const void *)&__identifier("?rva00462735@Rva00462735@@QAEXXZ"), // 64 0x00462735
	(const void *)&__identifier("?get@Rva00462CD3Sub@@QBE_NXZ"), // 65 0x00462CD3
	(const void *)&__identifier("?onContaining@TransportContain@@UAEXPAVObject@@_N@Z"), // 66 0x00463191
	(const void *)&__identifier("?rva004631C9@SlaughterHordeContain@@UAEXXZ"), // 67 0x004631C9
	(const void *)&__identifier("?rva004635EC@SlaughterHordeContain@@UAEXP6AXPAVObject@@PAX@Z1H@Z"), // 68 0x004635EC
	(const void *)&__identifier("?rva00462DE0@Rva00462DE0@@QAEHPAVRva2225E0Filter@@@Z"), // 69 0x00462DE0
	(const void *)&__identifier("?rva004647D8@Rva004647D8@@QAEPAXPAX@Z"), // 70 0x004647D8
	(const void *)&__identifier("?rva004624EB@Rva004624EB@@UAE?AURva00462465@@XZ"), // 71 0x004624EB
	(const void *)&__identifier("?winNextTab@GameWindow@@QAEHXZ"), // 72 0x000D43D0
	(const void *)&__identifier("?get@Rva005C4AFDDwordField@@QBEHXZ"), // 73 0x005C4AFD
	(const void *)&__identifier("?winNextTab@GameWindow@@QAEHXZ"), // 74 0x000D43D0
	(const void *)&__identifier("?winNextTab@GameWindow@@QAEHXZ"), // 75 0x000D43D0
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // 76 0x0050B5F1
	(const void *)&__identifier("?rva0041BA5C@Rva0041BA5C@@QAE_NHHH@Z"), // 77 0x0041BA5C
	(const void *)&__identifier("?rva0041BA5C@Rva0041BA5C@@QAE_NHHH@Z"), // 78 0x0041BA5C
	(const void *)&__identifier("?rva00463291@OpenContainActionIface@@UAEPAVObject@@PAVRva2225E0Filter@@@Z"), // 79 0x00463291
	(const void *)&__identifier("?shouldDoOnBuildComplete@OpenContain@@UBE_NXZ"), // 80 0x0047A699
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
	(const void *)&__identifier("?rva004776E7@HordeTransportContain@@QAEXPBURva004776E7UpgradeMask@@_N@Z")  // 93 0x004776E7
};
// Retail table 0x00C45EB8 (31 slots), stored by the constructor below. Own the
// complete initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp
// s_10 precedent): each slot names a matched row at retail's slot target, taken
// by address and never called through these erased signatures.
extern "C" {
void __identifier("??_GHordeTransportContain@@UAEPAXI@Z")();
void __identifier("?rva00479D68@Rva00479D68@@QAEXXZ")();
void __identifier("?Rva00477098Get@@YAHXZ")();
void __identifier("?xfer@HordeTransportContain@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@HordeTransportContain@@UBE?AW4NameKeyType@@XZ")();
void __identifier("?slot02@OpenContain@@UAEXXZ")();
void __identifier("?onDelete@OpenContain@@UAEXXZ")();
void __identifier("?onCapture@TransportContain@@UAEXHH@Z")();
void __identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
void __identifier("?removeFromContainList@OpenContain@@UAEXPAVObject@@@Z")();
void __identifier("?rva00466E58@Rva00466E58@@QBEEH@Z")();
void __identifier("?rva00477BA2@HordeTransportContain@@QAEXPAVOldContain@@PAVObject@@@Z")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?monitorConditionChanges@OpenContain@@MAEXXZ")();
void __identifier("?redeployOccupants@HordeTransportContain@@QAEXXZ")();
void __identifier("?rva00464EE7@OpenContain@@UAE_NPAVObject@@@Z")();
void __identifier("?doLoadSound@OpenContain@@MAEXXZ")();
void __identifier("?doUnloadSound@OpenContain@@MAEXXZ")();
void __identifier("?rva00462E3A@Rva00462E3A@@QAEXPAVObject@@HH@Z")();
void __identifier("?killRidersWhoAreNotFreeToExit@TransportContain@@MAEXXZ")();
void __identifier("?privateRedeployOccupants@OpenContain@@AAEXPBV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PAV?$map@HHU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@3@@Z")();
void __identifier("?isSpecificRiderFreeToExit@TransportContain@@MAE_NPAVObject@@@Z")();
void __identifier("?createPayload@TransportContain@@QAEXXZ")();
void __identifier("?rva0046740C@TransportContain@@MAEXXZ")();
void __identifier("?letRidersUpgradeWeaponSet@TransportContain@@MAEXXZ")();
}
extern const void *const g_00C45EB8[31] = {
	(const void *)&__identifier("??_GHordeTransportContain@@UAEPAXI@Z"), //  0 0x004771CA
	(const void *)&__identifier("?rva00479D68@Rva00479D68@@QAEXXZ"), //  1 0x00479D68
	(const void *)&__identifier("?Rva00477098Get@@YAHXZ"), //  2 0x00477098
	(const void *)&__identifier("?xfer@HordeTransportContain@@MAEXPAVXfer@@@Z"), //  3 0x0047714A
	(const void *)&__identifier("?getModuleNameKey@HordeTransportContain@@UBE?AW4NameKeyType@@XZ"), //  4 0x00477185
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), //  5 0x000B3FD0
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), //  6 0x000B3FD0
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), //  7 0x000B3FD0
	(const void *)&__identifier("?onDelete@OpenContain@@UAEXXZ"), //  8 0x00464120
	(const void *)&__identifier("?onCapture@TransportContain@@UAEXHH@Z"), //  9 0x004672B7
	(const void *)&__identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ"), // 10 0x000D43D0
	(const void *)&__identifier("?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ"), // 11 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // 12 0x0022C4CB
	(const void *)&__identifier("?removeFromContainList@OpenContain@@UAEXPAVObject@@@Z"), // 13 0x00462F75
	(const void *)&__identifier("?rva00466E58@Rva00466E58@@QBEEH@Z"), // 14 0x00466E58
	(const void *)&__identifier("?rva00477BA2@HordeTransportContain@@QAEXPAVOldContain@@PAVObject@@@Z"), // 15 0x00477BA2
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // 16 0x005CB9FF
	(const void *)&__identifier("?monitorConditionChanges@OpenContain@@MAEXXZ"), // 17 0x00462C72
	(const void *)&__identifier("?redeployOccupants@HordeTransportContain@@QAEXXZ"), // 18 0x00477513
	(const void *)&__identifier("?rva00464EE7@OpenContain@@UAE_NPAVObject@@@Z"), // 19 0x00464EE7
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // 20 0x005CB9FF
	(const void *)&__identifier("?doLoadSound@OpenContain@@MAEXXZ"), // 21 0x0046279C
	(const void *)&__identifier("?doUnloadSound@OpenContain@@MAEXXZ"), // 22 0x0046282B
	(const void *)&__identifier("?slot02@OpenContain@@UAEXXZ"), // 23 0x000B3FD0
	(const void *)&__identifier("?rva00462E3A@Rva00462E3A@@QAEXPAVObject@@HH@Z"), // 24 0x00462E3A
	(const void *)&__identifier("?killRidersWhoAreNotFreeToExit@TransportContain@@MAEXXZ"), // 25 0x00467F3B
	(const void *)&__identifier("?privateRedeployOccupants@OpenContain@@AAEXPBV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@PAV?$map@HHU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@3@@Z"), // 26 0x00465972
	(const void *)&__identifier("?isSpecificRiderFreeToExit@TransportContain@@MAE_NPAVObject@@@Z"), // 27 0x004671AC
	(const void *)&__identifier("?createPayload@TransportContain@@QAEXXZ"), // 28 0x004670D6
	(const void *)&__identifier("?rva0046740C@TransportContain@@MAEXXZ"), // 29 0x0046740C
	(const void *)&__identifier("?letRidersUpgradeWeaponSet@TransportContain@@MAEXXZ")  // 30 0x0046760D
};

class Thing;
class ModuleData;

// Retail's Coord2D with its out-of-line empty default constructor (0x0047A6A9)
// and no destructor, so the member adds no unwind state.
#define COORD2D_VIEW_EXTERN_CTOR
#include "../../../../../Libraries/Include/Lib/Coord2DCtorView.h"

#pragma pack(push, 1)
class TransportContain
{
public:
	TransportContain(Thing *thing, const ModuleData *moduleData);
	~TransportContain();

protected:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	void *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_20;
	const void *m_24;
	const void *m_28;
	const void *m_2C;
	const void *m_30;
	const void *m_34;
	unsigned char m_pad38[0xFC - 0x38];
	const void *m_FC;
	unsigned char m_pad100[0x11D - 0x100];
};

class HordeTransportContain : public TransportContain
{
public:
	HordeTransportContain(Thing *thing, const ModuleData *moduleData);

private:
	Coord2D m_11D;
};
#pragma pack(pop)

// ??0HordeTransportContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x00477003
HordeTransportContain::HordeTransportContain(Thing *thing, const ModuleData *moduleData)
	: TransportContain(thing, moduleData), m_11D()
{
	m_vtable = (const void *)(unsigned int)&g_00C45EB8;
	m_secondary0C = (const void *)((unsigned int)__identifier("??_7AODHordeContain@@6BIface0C@@@"));
	m_secondary10 = (const void *)((unsigned int)__identifier("??_7HordeSiegeEngineContain@@6BIface10@@@"));
	m_20 = (const void *)(unsigned int)&g_00C45D30;
	m_24 = (const void *)((unsigned int)__identifier("??_7HordeSiegeEngineContain@@6BIface24@@@"));
	m_28 = (const void *)((unsigned int)__identifier("??_7HordeSiegeEngineContain@@6BIface28@@@"));
	m_2C = (const void *)((unsigned int)__identifier("??_7AODHordeContain@@6BIface2C@@@"));
	m_30 = (const void *)(unsigned int)&g_00C45CFC;
	m_34 = (const void *)((unsigned int)__identifier("??_7TransportContain@@6BB8@@@"));
	m_FC = (const void *)((unsigned int)__identifier("??_7AODHordeContain@@6BIfaceFC@@@"));
	*(int *)((char *)&m_11D + 3) = -1000;
	*(unsigned char *)((char *)&m_11D + 7) = 0;
}
