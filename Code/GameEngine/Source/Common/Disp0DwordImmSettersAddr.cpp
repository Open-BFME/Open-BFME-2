// Members of the Disp0DwordImmSetters.cpp family split out while their vftable
// addresses lacked linkable names. Unnamed retail tables below are mapped from
// vftable_map slot targets and relocated to their matched bodies.
//
// Disp0 dword immediate setters: seven-byte __thiscall members with one shape:
//
//     mov dword ptr [ecx],<IMM32> / ret
//
// The dword at `this` itself is set to a hardcoded immediate and nothing is
// read back. The zero-displacement member of the disp8 family
// (Disp8DwordImmSetters.cpp) and the disp32 family
// (DispDwordImmSetters.cpp); MSVC 7.1 uses the C7-01 form when the offset is
// zero, so there is no lead array. Only the class names follow this tree's
// Disp* convention (address-derived Rva<addr>DwordImmSetter, identity
// unrecoverable from 7 bytes). Retail cleans none (`ret`, not `ret 4`), so
// the members take no parameters.
// No // cl: line (defaults match the frameless 7-byte shape).
extern "C" const void *const vtbl_00C67E3C[];  // ??_7Rva0052634F_Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C67E3C=??_7Rva0052634F_Base@@6B@")

extern "C" const void *const vtbl_00BC6EEC[];  // ??_7Rva00082EF5Second@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6EEC=??_7Rva00082EF5Second@@6B@")

extern "C" const void *const vtbl_00C7A974[];  // ??_7Rva00604A42@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C7A974=??_7Rva00604A42@@6B@")

extern "C" const void *const vtbl_00C7A84C[];  // ??_7Rva00602645@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C7A84C=??_7Rva00602645@@6B@")

extern "C" const void *const vtbl_00C780F4[];  // ??_7Rva005E9FA4@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C780F4=??_7Rva005E9FA4@@6B@")

extern "C" const void *const vtbl_00C77D30[];  // ??_7Rva005E567D@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C77D30=??_7Rva005E567D@@6B@")

extern "C" const void *const vtbl_00C7559C[];  // ??_7Rva005D1035@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C7559C=??_7Rva005D1035@@6B@")

extern "C" const void *const vtbl_00C7528C[];  // folded, 2 classes; via ??_7Rva005D078BSecond@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C7528C=??_7Rva005D078BSecond@@6B@")

extern "C" const void *const vtbl_00C75284[];  // ??_7Rva00875284Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C75284=??_7Rva00875284Base@@6B@")

extern "C" const void *const vtbl_00C75278[];  // folded, 3 classes; via ??_7Rva005CF826@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C75278=??_7Rva005CF826@@6B@")

extern "C" const void *const vtbl_00C751A8[];  // ??_7Rva005CE8F5@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C751A8=??_7Rva005CE8F5@@6B@")

extern "C" const void *const vtbl_00C711BC[];  // ??_7Rva0059EB41@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C711BC=??_7Rva0059EB41@@6B@")

extern "C" const void *const vtbl_00C6EE28[];  // folded, 2 classes; via ??_7Base1@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6EE28=??_7Base1@@6B@")

extern "C" const void *const vtbl_00C6EE20[];  // ??_7Base3@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6EE20=??_7Base3@@6B@")

extern "C" const void *const vtbl_00C6E5C4[];  // ??_7Rva005753E9@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E5C4=??_7Rva005753E9@@6B@")

extern "C" const void *const vtbl_00C6ABC0[];  // ??_7Rva0055057D@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6ABC0=??_7Rva0055057D@@6B@")

extern "C" const void *const vtbl_00C6A68C[];  // ??_7Rva00549C74@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6A68C=??_7Rva00549C74@@6B@")

extern "C" const void *const vtbl_00C686BC[];  // ??_7Rva0052B668@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C686BC=??_7Rva0052B668@@6B@")

extern "C" const void *const vtbl_00C62A14[];  // ??_7Rva005D06CBB2@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C62A14=??_7Rva005D06CBB2@@6B@")

extern "C" const void *const vtbl_00C619A0[];  // folded, 2 classes; via ??_7Rva003B7190Record@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C619A0=??_7Rva003B7190Record@@6B@")

extern "C" const void *const vtbl_00C5AEB0[];  // ??_7Rva004BDA0C@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C5AEB0=??_7Rva004BDA0C@@6B@")

extern "C" const void *const vtbl_00C44890[];  // ??_7Rva00468A46@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C44890=??_7Rva00468A46@@6B@")

extern "C" const void *const vtbl_00BFDF68[];  // ??_7Rva0056B126B2@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFDF68=??_7Rva0056B126B2@@6B@")

extern "C" const void *const vtbl_00BFBC9C[];  // ??_7Rva005EEF2FBase0@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFBC9C=??_7Rva005EEF2FBase0@@6B@")

extern "C" const void *const vtbl_00C6AB10[];  // ??_7Rva006609D0Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6AB10=??_7Rva006609D0Base@@6B@")

extern "C" const void *const vtbl_00BC64B0[];  // folded, 2 classes; via ??_7BfmeBaseCC@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC64B0=??_7BfmeBaseCC@@6B@")

extern "C" const void *const vtbl_00C601DC[];  // ??_7Rva004D376A@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C601DC=??_7Rva004D376A@@6B@")

extern "C" const void *const vtbl_00BCF7E8[];  // ??_7Rva00104DB0Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BCF7E8=??_7Rva00104DB0Base@@6B@")

extern "C" const void *const vtbl_00BC5128[];  // ??_7Rva001DA2D5Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC5128=??_7Rva001DA2D5Base@@6B@")

extern "C" const void *const vtbl_00BC745C[];  // ??_7Rva000851F3@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC745C=??_7Rva000851F3@@6B@")
extern "C" const void *const vtbl_00C6B090[];  // ??_7Rva00552C0FBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6B090=??_7Rva00552C0FBase@@6B@")

extern "C" const void *const vtbl_00BC0990[];  // folded, 2 classes; via ??_7DebugIOConBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC0990=??_7DebugIOConBase@@6B@")
extern "C" const void *const vtbl_00BC650C[];  // folded, 4 classes; via ??_7BfmeBaseVVE@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC650C=??_7BfmeBaseVVE@@6B@")
extern "C" const void *const vtbl_00BC6F20[];  // folded, 7 classes; via ??_7Rva0007DF07@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6F20=??_7Rva0007DF07@@6B@")
extern "C" const void *const vtbl_00BCEF94[];  // folded, 3 classes; via ??_7HashableClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BCEF94=??_7HashableClass@@6B@")
extern "C" const void *const vtbl_00BCEFA0[];  // folded, 3 classes; via ??_7BfmeShadowBufferOwnerBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BCEFA0=??_7BfmeShadowBufferOwnerBase@@6B@")
extern "C" const void *const vtbl_00BDBA74[];  // folded, 3 classes; via ??_7Base0_00576C4B@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BDBA74=??_7Base0_00576C4B@@6B@")
extern "C" const void *const vtbl_00BE2B78[];  // folded, 9 classes; via ??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE2B78=??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@")
extern "C" const void *const vtbl_00BE3990[];  // folded, 2 classes; via ??_7BfmeDualVtableReleaseBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE3990=??_7BfmeDualVtableReleaseBase@@6B@")
extern "C" const void *const vtbl_00BFBCBC[];  // folded, 2 classes; via ??_7Rva005F6941Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFBCBC=??_7Rva005F6941Base@@6B@")
extern "C" const void *const vtbl_00C078DC[];  // folded, 4 classes; via ??_7BfmeCtor001B3A20@@6BBfmeCtorVirtualBase001B3A20@@@
#pragma comment(linker, "/alternatename:_vtbl_00C078DC=??_7BfmeCtor001B3A20@@6BBfmeCtorVirtualBase001B3A20@@@")
extern "C" const void *const vtbl_00C3702C[];  // folded, 4 classes; via ??_7Rva0056B0BFB2@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C3702C=??_7Rva0056B0BFB2@@6B@")
extern "C" const void *const vtbl_00C37298[];  // folded, 2 classes; via ??_7Base003F8ED6@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C37298=??_7Base003F8ED6@@6B@")
extern "C" const void *const vtbl_00C4EF80[];  // folded, 7 classes; via ??_7ContainIface34@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4EF80=??_7ContainIface34@@6B@")
extern "C" const void *const vtbl_00C60130[];  // folded, 2 classes; via ??_7MemoryPoolObject@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C60130=??_7MemoryPoolObject@@6B@")
extern "C" const void *const vtbl_00C618CC[];  // folded, 2 classes; via ??_7Rva003A6F70@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C618CC=??_7Rva003A6F70@@6B@")
extern "C" const void *const vtbl_00C6E60C[];  // folded, 2 classes; via ??_7Rva00575E4EBase1@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E60C=??_7Rva00575E4EBase1@@6B@")

extern "C" const void *const vtbl_00BC26E0[];  // ??_7Rva000421C8@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC26E0=??_7Rva000421C8@@6B@")
extern "C" const void *const vtbl_00C089EC[];  // ??_7Rva0030D346@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C089EC=??_7Rva0030D346@@6B@")
extern "C" const void *const vtbl_00C3C970[];  // ??_7Rva004318C6@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C3C970=??_7Rva004318C6@@6B@")
extern "C" const void *const vtbl_00C6A894[];  // ??_7Rva0054F434Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6A894=??_7Rva0054F434Base@@6B@")
extern "C" const void *const vtbl_00C6E788[];  // ??_7Listener00576C4B@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E788=??_7Listener00576C4B@@6B@")
extern "C" const void *const vtbl_00C72B74[];  // ??_7Rva005B253F@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C72B74=??_7Rva005B253F@@6B@")
extern "C" const void *const vtbl_00C75290[];  // ??_7Rva005CF872@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C75290=??_7Rva005CF872@@6B@")

extern "C" const void *const vtbl_00C6E330[];  // ??_7CreateAHeroData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E330=??_7CreateAHeroData@@6B@")

extern "C" const void *const vtbl_00BBC8D4[];  // ??_7_Messages@_STL@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBC8D4=??_7_Messages@_STL@@6B@")
extern "C" const void *const vtbl_00BBE7EC[];  // ??_7DebugCmdInterface@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBE7EC=??_7DebugCmdInterface@@6B@")
extern "C" const void *const vtbl_00BC6730[];  // ??_7FileClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6730=??_7FileClass@@6B@")
extern "C" const void *const vtbl_00BC6778[];  // ??_7FileFactoryClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6778=??_7FileFactoryClass@@6B@")
extern "C" const void *const vtbl_00BC6F24[];  // ??_7Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC6F24=??_7Base@@6B@")
extern "C" const void *const vtbl_00BC93C8[];  // ??_7Rva00782CB0@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC93C8=??_7Rva00782CB0@@6B@")
extern "C" const void *const vtbl_00BD4E24[];  // ??_7StaticSortListClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BD4E24=??_7StaticSortListClass@@6B@")
extern "C" const void *const vtbl_00BD6CB4[];  // ??_7BFME2MotionChannel@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BD6CB4=??_7BFME2MotionChannel@@6B@")
extern "C" const void *const vtbl_00BDBC10[];  // ??_7Rva001DBAA4@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BDBC10=??_7Rva001DBAA4@@6B@")
extern "C" const void *const vtbl_00BE09D0[];  // ??_7ObjectCreationNugget@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE09D0=??_7ObjectCreationNugget@@6B@")
extern "C" const void *const vtbl_00BE714C[];  // ??_7SubsystemSlotBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE714C=??_7SubsystemSlotBase@@6B@")
extern "C" const void *const vtbl_00BED658[];  // ??_7Rva0023A128Link@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BED658=??_7Rva0023A128Link@@6B@")
extern "C" const void *const vtbl_00BFAD38[];  // ??_7DrawableLocoInfo@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFAD38=??_7DrawableLocoInfo@@6B@")
extern "C" const void *const vtbl_00BFB698[];  // ??_7LargeGroupAudioUpdate_B24@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFB698=??_7LargeGroupAudioUpdate_B24@@6B@")
extern "C" const void *const vtbl_00BFDC30[];  // ??_7Rva004F5FD8@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BFDC30=??_7Rva004F5FD8@@6B@")
extern "C" const void *const vtbl_00C02A58[];  // ??_7?$DLListClass@USmudge@@@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C02A58=??_7?$DLListClass@USmudge@@@@6B@")
extern "C" const void *const vtbl_00C02A5C[];  // ??_7?$DLListClass@USmudgeSet@@@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C02A5C=??_7?$DLListClass@USmudgeSet@@@@6B@")
extern "C" const void *const vtbl_00C1980C[];  // ??_7GameSpyPeerMessageQueueInterface@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C1980C=??_7GameSpyPeerMessageQueueInterface@@6B@")
extern "C" const void *const vtbl_00C363B8[];  // ??_7Mem04@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C363B8=??_7Mem04@@6B@")
extern "C" const void *const vtbl_00C3962C[];  // ??_7Rva0045EF90Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C3962C=??_7Rva0045EF90Base@@6B@")
extern "C" const void *const vtbl_00C42518[];  // ??_7SpawnBehaviorInterface@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C42518=??_7SpawnBehaviorInterface@@6B@")
extern "C" const void *const vtbl_00C62888[];  // ??_7BaseA@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C62888=??_7BaseA@@6B@")
extern "C" const void *const vtbl_00C63F9C[];  // ??_7Rva00506B1B@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C63F9C=??_7Rva00506B1B@@6B@")
extern "C" const void *const vtbl_00C6E350[];  // ??_7Rva0057E3DBBase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E350=??_7Rva0057E3DBBase@@6B@")
extern "C" const void *const vtbl_00C6E360[];  // ??_7Rva00575125Second@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E360=??_7Rva00575125Second@@6B@")
extern "C" const void *const vtbl_00C6E5B4[];  // ??_7Rva00575383@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6E5B4=??_7Rva00575383@@6B@")
extern "C" const void *const vtbl_00C70A5C[];  // ??_7Rva0059675ABase@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C70A5C=??_7Rva0059675ABase@@6B@")
extern "C" const void *const vtbl_00C70B80[];  // ??_7Rva005DAA36@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C70B80=??_7Rva005DAA36@@6B@")
extern "C" const void *const vtbl_00C743B8[];  // ??_7Rva005C18F0Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C743B8=??_7Rva005C18F0Base@@6B@")
extern "C" const void *const vtbl_00C74DB8[];  // ??_7Rva005CBA04@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C74DB8=??_7Rva005CBA04@@6B@")
extern "C" const void *const vtbl_00C75C38[];  // ??_7Rva005D6FCC@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C75C38=??_7Rva005D6FCC@@6B@")
extern "C" const void *const vtbl_00C767D4[];  // ??_7Rva005DBCD1@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C767D4=??_7Rva005DBCD1@@6B@")
extern "C" const void *const vtbl_00C77E28[];  // ??_7Rva005E67FE@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C77E28=??_7Rva005E67FE@@6B@")
extern "C" const void *const vtbl_00C77E7C[];  // ??_7Rva005CCC07Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C77E7C=??_7Rva005CCC07Base@@6B@")
extern "C" const void *const vtbl_00C77F44[];  // ??_7Rva002BA8F1Listener@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C77F44=??_7Rva002BA8F1Listener@@6B@")
extern "C" const void *const vtbl_00C79544[];  // ??_7Rva005E4AE2Listener@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C79544=??_7Rva005E4AE2Listener@@6B@")
extern "C" const void *const vtbl_00C7B6AC[];  // ??_7ThreadClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C7B6AC=??_7ThreadClass@@6B@")
extern "C" const void *const vtbl_00CE1E14[];  // ??_7Rva00CE1E14Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00CE1E14=??_7Rva00CE1E14Base@@6B@")
extern "C" const void *const vtbl_00CEFD60[];  // ??_7CullSystemClass@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00CEFD60=??_7CullSystemClass@@6B@")

// vftable_map identifies all 76 slots in these 14 retail tables; each points
// to one of eight matched bodies or the mapped __purecall runtime symbol.
extern "C" void bfmeDisp0Slot_DoXfer(void);
#pragma comment(linker, "/alternatename:_bfmeDisp0Slot_DoXfer=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
extern "C" void bfmeDisp0Slot_SetAnimation(void);
#pragma comment(linker, "/alternatename:_bfmeDisp0Slot_SetAnimation=?Set_Animation@RenderObjClass@@UAEXPAVHAnimClass@@MH@Z")
extern "C" void bfmeDisp0Slot_SkipBadBlock(void);
#pragma comment(linker, "/alternatename:_bfmeDisp0Slot_SkipBadBlock=?SkipBadBlock@Xfer@@UAEXAAVSnapshot@@I@Z")
extern "C" void bfmeDisp0Slot_001F01E8(void);
#pragma comment(linker, "/alternatename:_bfmeDisp0Slot_001F01E8=?rva001F01E8@Rva001F01E8@@QAEXHHHH@Z")
extern "C" void bfmeDisp0Slot_001FF3A9(void);
#pragma comment(linker, "/alternatename:_bfmeDisp0Slot_001FF3A9=?rva001FF3A9@Rva001FF3A9@@UAEXXZ")
extern "C" void bfmeDisp0Slot_005CB26A(void);
#pragma comment(linker, "/alternatename:_bfmeDisp0Slot_005CB26A=?rva005CB26A@Rva005CB26A@@QAEHXZ")
extern "C" void bfmeDisp0Slot_005CC208(void);
#pragma comment(linker, "/alternatename:_bfmeDisp0Slot_005CC208=?rva005CC208@Rva005CC208@@UAEXXZ")
extern "C" void bfmeDisp0Slot_Purecall(void);
#pragma comment(linker, "/alternatename:_bfmeDisp0Slot_Purecall=__purecall")

#define BFME_DISP0_SLOT(FUNCTION) reinterpret_cast<const void *>(FUNCTION)

extern "C" const void *const vtbl_00BFDF8C[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_SetAnimation),
	BFME_DISP0_SLOT(bfmeDisp0Slot_SetAnimation), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer)
};
extern "C" const void *const vtbl_00BC6F04[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer),
	BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock)
};
extern "C" const void *const vtbl_00BC6EC0[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer)
};
extern "C" const void *const vtbl_00C62A20[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock), BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock)
};
extern "C" const void *const vtbl_00BC6F34[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock),
	BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock), BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock)
};
extern "C" const void *const vtbl_00C77BE8[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer),
	BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock), BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock),
	BFME_DISP0_SLOT(bfmeDisp0Slot_SkipBadBlock)
};
extern "C" const void *const vtbl_00BE5114[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_001F01E8)
};
extern "C" const void *const vtbl_00C0DB24[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_001FF3A9),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_005CC208)
};
extern "C" const void *const vtbl_00C37E18[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_001FF3A9),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_005CC208),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_005CB26A)
};
extern "C" const void *const vtbl_00C6CE84[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_SetAnimation)
};
extern "C" const void *const vtbl_00C79428[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer)
};
extern "C" const void *const vtbl_00C75908[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall)
};
extern "C" const void *const vtbl_00C6E344[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer), BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer),
	BFME_DISP0_SLOT(bfmeDisp0Slot_DoXfer)
};
extern "C" const void *const vtbl_00C79760[] = {
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall),
	BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall), BFME_DISP0_SLOT(bfmeDisp0Slot_Purecall)
};

#undef BFME_DISP0_SLOT

class Rva002B228DDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva002B228DDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BFDF8C);
}

class Rva0007DEA1DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0007DEA1DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BC6EEC);
}

class Rva0007DEA8DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0007DEA8DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BC6F04);
}

class Rva0007DE9ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0007DE9ADwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BC6EC0);
}

class Rva004EDFF8DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004EDFF8DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C62A14);
}

class Rva004EDFFFDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004EDFFFDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C62A20);
}

class Rva004EE006DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004EE006DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BC6F34);
}

class Rva0057A235DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057A235DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6EE20);
}

class Rva0057A243DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057A243DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6EE28);
}

class Rva005CF843DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005CF843DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C75284);
}

class Rva005CF84ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005CF84ADwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C7528C);
}

class Rva005E394EDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005E394EDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C77BE8);
}

class Rva000723C0DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000723C0DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BC64B0);
}

class Rva00210CC5DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00210CC5DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BE5114);
}

class Rva00330440DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00330440DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C0DB24);
}

class Rva00468A3FDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00468A3FDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C44890);
}

class Rva004BDA05DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004BDA05DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C5AEB0);
}

class Rva004E14E1DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva004E14E1DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C619A0);
}

class Rva0052AF77DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0052AF77DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C37E18);
}

class Rva005676F4DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005676F4DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6CE84);
}

class Rva0059EB3ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0059EB3ADwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C711BC);
}

class Rva0005CF81FDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005CF81FDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C75278);
}

class Rva000604A68DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000604A68DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C7A974);
}

class Rva00060263EDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00060263EDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C7A84C);
}

class Rva0005F3EE3DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005F3EE3DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C79428);
}

class Rva0005EA2ABDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005EA2ABDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C780F4);
}

class Rva0005E57C9DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005E57C9DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C77D30);
}

class Rva000550576DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000550576DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6ABC0);
}

class Rva00054F91BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00054F91BDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6AB10);
}

class Rva000549C6DDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000549C6DDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6A68C);
}

class Rva00052B588DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva00052B588DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C686BC);
}

class Rva000524F5ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000524F5ADwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C67E3C);
}

class Rva0005D387BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D387BDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C75908);
}

class Rva0005D10D6DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005D10D6DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C7559C);
}

class Rva0005CE8EEDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0005CE8EEDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C751A8);
}
class Rva000579656DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000579656DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BFBC9C);
}
class Rva000574265DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva000574265DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6E344);
}

class Rva0002B221ADwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0002B221ADwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00BFDF68);
}
class Rva005753E2DwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva005753E2DwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C6E5C4);
}

class Rva0057851BDwordImmSetter
{
public:
	void apply();

	unsigned int m_value;
};

void Rva0057851BDwordImmSetter::apply()
{
	m_value = ((unsigned int)vtbl_00C79760);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva005D6FCC@@UAE@XZ=?apply@Rva0005D6FDEDwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1Rva001DBAC3Base@@UAE@XZ=?apply@Rva001DBAC3DwordImmSetter@@QAEXXZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00539926Base@@UAE@XZ=?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1Rva001DBAC3@@UAE@XZ=?apply@Rva001DBAC3DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeDtorTVA@BfmeThingTVA@@QAEXXZ=?apply@Rva00065D180DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1Rva00CE1E14Base@@UAE@XZ=?apply@Rva00065D180DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1BfmeModuleDataSnapshotBase@@UAE@XZ=?apply@Rva0011647BDwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1CountUpTransitionBase@@UAE@XZ=?apply@Rva001DBAC3DwordImmSetter@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeTailSF@BfmeThingSF@@QAEXXZ=?apply@Rva001DBAC3DwordImmSetter@@QAEXXZ")
