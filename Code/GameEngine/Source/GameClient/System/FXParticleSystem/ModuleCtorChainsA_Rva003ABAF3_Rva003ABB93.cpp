// cl: /MD /Ireference/shims/moduledata
// Split from ModuleCtorChainsA_Rva003ABAF3.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Split from ModuleCtorChainsA.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// ??0Rva003ABAC3@@QAE@PAX0@Z @0x003ABAC3 42B
// ??0Rva003ABAF3@@QAE@PAX0@Z @0x003ABAF3 42B
// ??0Rva003ABB23@@QAE@PAX0@Z @0x003ABB23 42B
// ??0Rva003ABB93@@QAE@PAX0@Z @0x003ABB93 42B
// ??0Rva003ABBCB@@QAE@PAX0@Z @0x003ABBCB 42B
// ??0Rva003ABC6E@@QAE@PAX0@Z @0x003ABC6E 49B
// ??0Rva003ABCB5@@QAE@PAX0@Z @0x003ABCB5 49B
// ??0Rva003ABE40@@QAE@PAX0@Z @0x003ABE40 49B
// ??0Rva003ABE8D@@QAE@PAX0@Z @0x003ABE8D 49B
// ??0Rva003ABDC8@@QAE@PAX0@Z @0x003ABDC8 49B
// ??0Rva003ABECC@@QAE@PAX0@Z @0x003ABECC 49B
// ??0Rva003ACDA0Module@@QAE@PAXPAVRva003AD71BTemplate@@@Z @0x003ACDA0 42B
// ??0Rva003ACE5CModule@@QAE@PAXPAVRva003AD80BTemplate@@@Z @0x003ACE5C 42B
// ??0Rva003ABB53@@QAE@PAX0@Z @0x003ABB53 42B
// ??0Rva003ABDF9@@QAE@PAX0@Z @0x003ABDF9 49B
// ??0Rva005E7420Object@@QAE@PAXPAVV3HostRva005E7420@@@Z @0x003ACE2D 42B
// ??0Rva003ACEFCModule@@QAE@PAXPAVRva003AD886Template@@@Z @0x003ACEFC 49B
// ??0Rva003AD0CAModule@@QAE@PAXPAVRva003AD9BBTemplate@@@Z @0x003AD0CA 49B
// ??0Rva003AD100Module@@QAE@PAXPAVRva003AD9F7Template@@@Z @0x003AD100 49B
// ??0Rva005E7AD0Object@@QAE@PAXPAVV3HostRva005E7AD0@@@Z @0x003AD136 49B
// ??0Rva005E76E0Object@@QAE@PAXPAVV3HostRva005E76E0@@@Z @0x003ACE8B 42B
// ??0Rva003ACDCFModule@@QAE@PAXPAVRva003AD757Template@@@Z @0x003ACDCF 42B
// ??0Rva003ACDFEModule@@QAE@PAXPAVRva003AD793Template@@@Z @0x003ACDFE 42B
// ??0Rva003ACF32Module@@QAE@PAXPAVRva003AD8C5Template@@@Z @0x003ACF32 49B
// ??0Rva003ACFCFModule@@QAE@PAXPAVRva003AD904Template@@@Z @0x003ACFCF 49B
// ??0Rva003AD005Module@@QAE@PAXPAVRva003AD940Template@@@Z @0x003AD005 49B
// ??0Rva003AD094Module@@QAE@PAXPAVRva003AD97FTemplate@@@Z @0x003AD094 49B
// ??0Rva003AD278Module@@QAE@PAXPAVRva003ADB21Template@@@Z @0x003AD278 49B
// ??0Rva003AD2B3Module@@QAE@PAXPAVRva003ADB44Template@@@Z @0x003AD2B3 49B
// ??0Rva003AD38BModule@@QAE@PAXPAVRva003ADBD0Template@@@Z @0x003AD38B 49B
//
// Particle-module constructor chains, two links each. Every body forwards its
// two stack arguments to one base constructor, then stamps the vtables of its
// three or four subobjects at +0, +0x14, +0x18 and +0x1C (Rva003ACD71Ctor.cpp
// and Rva003AD355ModuleCtor.cpp are landed members of the same family, written
// the same way). The module constructors are the ones the slot-2 template
// factories in ModuleTemplateFactorySlots.cpp call (pinned there); each calls
// one of the six intermediate constructors below, or an already-rowed one, and
// each intermediate calls a rowed module constructor. Call targets, store
// offsets and vtable addresses are read from retail; every class is
// address-named and no identity is inferred beyond the rowed callees.

extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AF47D@@6BModuleInfoSecondBase@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE4E5@@6B@")[];
// The retail table at RVA 0x0081C388: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AD273@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?xfer@ObjectModule@@QAEXPAVXfer@@@Z")();
void __identifier("?doParticles@StreakDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ")();
void __identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ")();
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?Rva004647D1Get@@YAMXZ")();
}
extern const void *const g_00C1C388[11];
// The retail table at RVA 0x0081C3C8: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AD273@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?xfer@ObjectModule@@QAEXPAVXfer@@@Z")();
void __identifier("?doParticles@QuadDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ")();
void __identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ")();
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?Rva004647D1Get@@YAMXZ")();
}
// Owned by ModuleCtorChainsA_Rva003ABAF3.cpp (data_rows); declared only here.
extern const void *const g_00C1C3C8[11];
// The retail table at RVA 0x0081C404: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AD273@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?xfer@ObjectModule@@QAEXPAVXfer@@@Z")();
void __identifier("?doParticles@ButterflyDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ")();
void __identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ")();
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?Rva004647D1Get@@YAMXZ")();
}
// Owned by ModuleCtorChainsA_Rva003ABAF3.cpp (data_rows); declared only here.
extern const void *const g_00C1C404[11];
// The retail table at RVA 0x0081C538: 1 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?CreateModule@Rva003AC93ETemplate@@UAEPAVRva003AC93EModule@@I@Z")();
}
extern const void *const g_00C1C538[1];
// The retail table at RVA 0x0081C53C: 7 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?rva0055B951@Rva0055B951@@UAEXPAVXfer@@@Z")();
void __identifier("?rva003ABCE6@Rva003ABCE6Forwarder@@QAEXH@Z")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
void __identifier("?rva003ABD04@Rva003ABD04@@QAE?AURva00SlotFloat2@@XZ")();
}
extern const void *const g_00C1C53C[7];
extern "C" const void *const __identifier("??_7Rva003ABD20@@6BDefaultModuleSecondBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003ABD81@@6BDefaultModuleSecondBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot1@@@")[];
extern "C" const void *const __identifier("??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50PrimaryBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AEDE9@@6BDefaultModuleSecondBase_3AEE16@@@")[];
// The retail table at RVA 0x0081C620: 4 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ACB74@@UAEPAXI@Z")();
void __identifier("?rva0056405C@Rva0056405C@@QAEXXZ")();
int __cdecl _purecall(void);
void __identifier("?rva00563ED1@Rva00563ED1@@UAEXPAVXfer@@@Z")();
}
extern const void *const g_00C1C620[4];
extern "C" const void *const __identifier("??_7Rva003AF89A@@6BRva003AF8C7B1C@@@")[];
// The retail table at RVA 0x0081C6DC: 8 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AD2AE@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?DoXfer@Rva0055DB41@@UAEXAAVXfer@@@Z")();
void __identifier("?rva0055CD70@Rva0055CD70@@QAEXMMM@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?rva003ABEFD@Rva003ABEFD@@QAEMXZ")();
void __identifier("?getPosition@LightningEmissionModule@FXParticleSystem@@UAE?AUCoord3D@@MMHH@Z")();
}
// Owned by ModuleCtorChainsA_Rva003ABAF3.cpp (data_rows); declared only here.
extern const void *const g_00C1C6DC[8];
extern "C" const void *const __identifier("??_7Rva003AF47D@@6BIntermediate3AFC6FC@@@")[];
extern "C" const void *const __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AF47D@@6BEmissionVolumeInfo4AA@FXParticleSystem@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF57F@@6BLineEmissionVolumeInfo@FXParticleSystem@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE4E5@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AE56F@@6B@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE56F@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AE5F9@@6B@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE5F9@@6BDefaultModuleHeadBase@@@")[];

// The retail table at RVA 0x0081CDF0: 7 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?clone@Rva003AEADD@@QBEPAV1@XZ")();
void __identifier("?rva0055B951@Rva0055B951@@UAEXPAVXfer@@@Z")();
void __identifier("?rva003ABCE6@Rva003ABCE6Forwarder@@QAEXH@Z")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
void __identifier("?rva003ABD04@Rva003ABD04@@QAE?AURva00SlotFloat2@@XZ")();
}
extern const void *const g_00C1CDF0[7];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003ABD20@@6B@")[];
// The retail table at RVA 0x0081CE64: 9 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?clone@Rva003AEB9C@@QBEPAV1@XZ")();
void __identifier("?xfer@Rva0055EF39@@UAEXPAVXfer@@@Z")();
void __identifier("?get@Rva00094A9CFloatField@@QBEMXZ")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
void __identifier("?rva003ABD6B@Rva003ABD6B@@QAE?AURva00SlotFloat2@@XZ")();
void __identifier("?get@Rva0045310DByteField@@QBEEXZ")();
void __identifier("?get@Rva003ABD51ByteField@@QBEEXZ")();
}
extern const void *const g_00C1CE64[9];
extern "C" const void *const __identifier("??_7Rva003ABD81@@6B@")[];
// The retail table at RVA 0x0081CE98: 12 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?clone@Rva003AEC5E@@QBEPAV1@XZ")();
void __identifier("?rva0055F710@Rva0055F710@@UAEXPAVXfer@@@Z")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
void __identifier("?getSolution@PartitionSolver@@QBEABV?$vector@U?$pair@W4ObjectID@@W41@@_STL@@V?$allocator@U?$pair@W4ObjectID@@W41@@_STL@@@2@@_STL@@XZ")();
void __identifier("?getAttackSoundsVector@AudioEventInfo@@QBEABV?$vector@URvaPair001D9F62@@V?$allocator@URvaPair001D9F62@@@_STL@@@_STL@@XZ")();
void __identifier("?get@Rva003F3FE4LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva0008BCC8LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva0053998CLeaField@@QBEPAXXZ")();
void __identifier("?get@Rva003EE704LeaField@@QBEPAXXZ")();
void __identifier("?getSoundsVector@AudioEventInfo@@QBEABV?$vector@URvaPair001D9F62@@V?$allocator@URvaPair001D9F62@@@_STL@@@_STL@@XZ")();
}
extern const void *const g_00C1CE98[12];
extern "C" const void *const __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot3@@@")[];
extern "C" const void *const __identifier("??_7Rva003AEDE9@@6B@")[];
extern "C" const void *const __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot0@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF47D@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF57F@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF89A@@6BRva003AF8C7B00@@@")[];
extern "C" const void *const __identifier("??_7Rva003AF89A@@6BRva003AF8C7B18@@@")[];
// The retail table at RVA 0x0081C444: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ACED6@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?rva00562945@Rva00562945@@UAEXPAVXfer@@@Z")();
void __identifier("?doParticles@RenderObjectDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?rva00562BF7@Rva00562BF7Owner@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ")();
void __identifier("?get@Rva003F3FCEDwordField@@QBEHXZ")();
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?Rva004647D1Get@@YAMXZ")();
}
extern const void *const g_00C1C444[11];
extern "C" const void *const __identifier("??_7Rva003AE683@@6B@")[];
extern const void *const g_00C1C620[];
extern "C" const void *const __identifier("??_7Rva003AEDE9@@6BDefaultModuleSecondBase_3AEE16@@@")[];
extern "C" const void *const __identifier("??_7Rva003AEDE9@@6B@")[];
extern "C" const void *const __identifier("??_7Rva003AE683@@6BModuleInfoHeadBase_3AE683@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
// The retail table at RVA 0x0081CDCC: 5 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?clone@?$DefaultModule@$00@FXParticleSystem@@UBEPAV12@XZ")();
void __identifier("?rva0055B30F@Rva0055B30F@@UAEXPAVXfer@@@Z")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
}
extern const void *const g_00C1CDCC[5];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AEDE9@@6BDefaultModuleHeadBase_3AEE16@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
// The retail table at RVA 0x0081CF38: 12 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?clone@Rva003AEF6E@@QBEPAV1@XZ")();
void __identifier("?rva00562233@Rva00562233@@UAEXPAVXfer@@@Z")();
void __identifier("?get@Rva003EE704LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva0030BBA5LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva00308156LeaGetter@@QBEPAXXZ")();
void __identifier("?get@Rva003ABE71LeaGetter@@QBEPAXXZ")();
void __identifier("?get@Rva003ABE78LeaGetter@@QBEPAXXZ")();
}
extern const void *const g_00C1CF38[12];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Gen005ED0D0@@6BDefaultModuleHeadBase_3AEE16@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva005EBCC0Object@@6BV3Slot0@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE928@@6BModuleInfoHeadBase_3AE94E@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?GPU_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?GPU_DRAW_MODULE_NAME@2@3QBDBVGpuDrawModule@2@VGpuDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@")[];
// The retail table at RVA 0x0081C488: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003AD273@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?rva00561527@Rva00561527@@UAEXPAVXfer@@@Z")();
void __identifier("?doParticles@LightningDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva004BD9CB@Rva004BD9CB@@UBE?AVAsciiString@@XZ")();
void __identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ")();
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?Rva004647D1Get@@YAMXZ")();
}
// Owned by ModuleCtorChainsA_Rva003ABAF3.cpp (data_rows); declared only here.
extern const void *const g_00C1C488[11];
extern "C" const void *const __identifier("??_7Rva005EBCC0Object@@6BV3Slot2@@@")[];
// The retail table at RVA 0x0081C4C8: 11 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ACEF7@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?xfer@Rva003AE928@@UAEXPAVXfer@@@Z")();
void __identifier("?doParticles@GpuDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva0056394A@Rva0056394A@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ")();
void __identifier("?get@Bfme939Helper@@QBEHXZ")();
void __identifier("?getDataLength@NetWrapperCommandMsg@@QAEIXZ")();
void __identifier("?get@Rva00094A98FloatField@@QBEMXZ")();
}
extern const void *const g_00C1C4C8[11];
extern "C" const void *const __identifier("??_7Rva003AE928@@6B@")[];
// The retail table at RVA 0x0081C504: 6 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?rva003AC8D7@Rva003AC8D7Host@@UAEPAVRva003AC8D7Object@@I@Z")();
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?rva0055B30F@Rva0055B30F@@UAEXPAVXfer@@@Z")();
void __identifier("?get@Rva004F5FA3LeaGetter@@QBEPAXXZ")();
}
extern const void *const g_00C1C504[6];

// The retail table at RVA 0x0081C640: 13 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?rva003ACA93@Rva003ACA93Host@@UAEPAVRva003ACA93Object@@I@Z")();
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
int __cdecl _purecall(void);
void __identifier("?rva00562233@Rva00562233@@UAEXPAVXfer@@@Z")();
void __identifier("?get@Rva003EE704LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva0030BBA5LeaField@@QBEPAXXZ")();
void __identifier("?get@Rva00308156LeaGetter@@QBEPAXXZ")();
void __identifier("?get@Rva003ABE71LeaGetter@@QBEPAXXZ")();
void __identifier("?get@Rva003ABE78LeaGetter@@QBEPAXXZ")();
}
extern const void *const g_00C1C640[13];
// The retail table at RVA 0x0081CF28: 4 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_ERva003ABD81@@WBM@AEPAXI@Z")();
void __identifier("??1?$_STLP_alloc_proxy@PAPAVObject@@PAV1@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ")();
void __identifier("?name@Rva003ABE7FNamed@@QBEPBDXZ")();
void __identifier("?rva00562233@Rva00562233@@WBM@AEXPAVXfer@@@Z")();
}
extern const void *const g_00C1CF28[4] = {
	(const void *)&__identifier("??_ERva003ABD81@@WBM@AEPAXI@Z"), // slot 0 0x003ABDC0
	(const void *)&__identifier("??1?$_STLP_alloc_proxy@PAPAVObject@@PAV1@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?name@Rva003ABE7FNamed@@QBEPBDXZ"), // slot 2 0x003ABE7F
	(const void *)&__identifier("?rva00562233@Rva00562233@@WBM@AEXPAVXfer@@@Z"), // slot 3 0x003ABE85
};
// The retail table at RVA 0x0081C6A4: 4 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ACB74@@UAEPAXI@Z")();
void __identifier("?rva005645FE@Rva005645FE@@QAEXXZ")();
int __cdecl _purecall(void);
void __identifier("?rva005644A9@Rva005644A9@@UAEXPAVXfer@@@Z")();
}
extern const void *const g_00C1C6A4[4];
extern "C" const void *const __identifier("??_7Gen005ED0D0@@6BDefaultModuleSecondBase_3AEE16@@@")[];
extern "C" const void *const __identifier("??_7Gen005ED0D0@@6B@")[];

struct Rva0055BF4BSrc;
class RvaSmartPtr12;

namespace FXParticleSystem
{
class ParticleSystem;
template <class T> class TrackingPtr;
class DefaultModuleTemplate7;
class LightningEmissionModuleTemplate;
class PointEmissionVolumeModuleTemplate;

class Rva005FEAD0DefaultModule7
{
public:
	Rva005FEAD0DefaultModule7(TrackingPtr<ParticleSystem> &system, const DefaultModuleTemplate7 *moduleTemplate);
};

class LightningEmissionModule
{
public:
	LightningEmissionModule(TrackingPtr<ParticleSystem> &system, const LightningEmissionModuleTemplate *moduleTemplate);
};

class LightningDrawModuleTemplate;
class LightningDrawModule
{
public:
	LightningDrawModule(TrackingPtr<ParticleSystem> &system, const LightningDrawModuleTemplate *moduleTemplate);
};
}

struct Rva005648FEInput;
struct Rva005641EDInput;
struct DrawInfo2;
class Rva005634F7 { public: Rva005634F7(void *a, DrawInfo2 *b); };
class Rva003AE94E { public: Rva003AE94E(void *a, void *b); };

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "Common/Snapshot.h"
class __declspec(novtable) Rva003AEEB3
{
public:
    virtual ~Rva003AEEB3();
    virtual void rva000B3FD0() = 0;
    virtual void *rva003ABC6ESlot2() = 0;
    virtual void DoXfer(Xfer &) = 0;
private: char m_unmodelled_04[0x1C - 4];
};
class Rva0055B266 { public: virtual void rva0055B266(Xfer *); };
class __declspec(novtable) Rva003AEA42 : public Rva003AEEB3, public Snapshot
{
public:
    Rva003AEA42(const RvaSmartPtr12 &a, int b);
    virtual ~Rva003AEA42();
};
class Rva003AEF9B { public: Rva003AEF9B(const RvaSmartPtr12 &a, int b); };
class Rva003AF076 { public: Rva003AF076(const RvaSmartPtr12 &a, const Rva005648FEInput &b); };

class Rva003AE50B { public: Rva003AE50B(void *a, void *b); };
class Rva00560A1B { public: Rva00560A1B(void *a, void *b); };
class Rva003AE61F { public: Rva003AE61F(void *a, void *b); };
class Rva003ACC7C { public: Rva003ACC7C(void *a, void *b); };
class Rva0055B8CD { public: virtual void rva0055B8CD(Xfer *); };
class __declspec(novtable) Rva0055BF4B : public Rva003AEEB3, public Snapshot {
public: Rva0055BF4B(const RvaSmartPtr12 &a, const Rva0055BF4BSrc *b);
virtual ~Rva0055BF4B();
};
class Rva003ABD20 { public: Rva003ABD20(const RvaSmartPtr12 &a, int b); };
class Rva003ABD81 { public: Rva003ABD81(const RvaSmartPtr12 &a, int b); };
struct Rva005641EDInput;
// Borrowed footprint of the existing constructor/copy owner. Its native
// fields extend through byte+0x3C; four-byte alignment gives a0x40 footprint.
// this declaration only calls that provider and emits no base lifetime code.
class Rva003AEE16
{
public:
    Rva003AEE16(const RvaSmartPtr12 &, const Rva005641EDInput &);
private:
    unsigned int m_unmodeled[0x40 / 4];
};
class Rva003ACC4B
{
public:
	Rva003ACC4B(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> &system,
		const FXParticleSystem::PointEmissionVolumeModuleTemplate *moduleTemplate);
};

#define STAMP(off, vtable) (*(const void **)((char *)this + (off)) = (const void *)(vtable))

// ---- intermediate constructors over rowed module constructors ----

class Rva003ABAC3 : public Rva003AE50B
{
public:
	Rva003ABAC3(void *a, void *b);
};


class Rva003ABAF3 : public Rva00560A1B
{
public:
	Rva003ABAF3(void *a, void *b);
};


class Rva003ABB23 : public Rva003AE61F
{
public:
	Rva003ABB23(void *a, void *b);
};


class Rva003ABCB5 : public Rva0055BF4B
{
public:
 Rva003ABCB5(void *a, void *b);
 virtual ~Rva003ABCB5();
 virtual void rva000B3FD0();
 virtual void LoadPostProcess() {}
 virtual const char *GetSnapshotName() { return "DefaultModule<CAT_COLOR>"; }
 virtual void DoXfer(Xfer &stream);
};
void Rva003ABCB5::DoXfer(Xfer &stream) {
 stream.Version1();
 reinterpret_cast<Rva0055B8CD *>((char *)this+0x1C)->Rva0055B8CD::rva0055B8CD(&stream);
}

Rva003ABCB5::Rva003ABCB5(void *a, void *b)
	: Rva0055BF4B(*(const RvaSmartPtr12 *)a, (const Rva0055BF4BSrc *)b)
{
	STAMP(0x00, g_00C1C53C);
	STAMP(0x14, g_00C1C538);
	STAMP(0x18, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x1C, __identifier("??_7Rva003ABCB5@@6BSnapshot@@@"));
}

class Rva003ABDC8 : public FXParticleSystem::Rva005FEAD0DefaultModule7
{
public:
	Rva003ABDC8(void *a, void *b);
};


// Native 0x003ABDF9..0x003ABE2A,49B RET8: forwards both arguments to the
// independently recovered Rva003AEE16 constructor at0x005641ED and installs
// four target vtables at+0/+0x14/+0x18/+0x20. The neighbouring ctor pattern
// is a structural guide; the target call and stores establish this relation.
// The derived class identity remains address-derived. No donor name is claimed.
class Rva003ABDF9 : public Rva003AEE16
{
public:
    Rva003ABDF9(void *a, void *b);
};


class Rva003ABECC : public FXParticleSystem::LightningEmissionModule
{
public:
	Rva003ABECC(void *a, void *b);
};


// ---- module constructors the template factories call ----

class Rva003AD71BTemplate;
class Rva003ACDA0Module : public Rva003ABAC3
{
public:
	Rva003ACDA0Module(void *a, Rva003AD71BTemplate *b);
};


class Rva003AD757Template;
class Rva003ACDCFModule : public Rva003ABAF3
{
public:
	Rva003ACDCFModule(void *a, Rva003AD757Template *b);
};


class Rva003AD793Template;
class Rva003ACDFEModule : public Rva003ABB23
{
public:
	Rva003ACDFEModule(void *a, Rva003AD793Template *b);
};


class Rva003AD8C5Template;
class Rva003ACF32Module : public Rva003ABCB5
{
public:
	Rva003ACF32Module(void *a, Rva003AD8C5Template *b);
};

Rva003ACF32Module::Rva003ACF32Module(void *a, Rva003AD8C5Template *b)
	: Rva003ABCB5(a, b)
{
	STAMP(0x00, g_00C1CDF0);
	STAMP(0x14, g_00C1C538);
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x1C, __identifier("??_7Rva003ABCB5@@6BSnapshot@@@"));
}

class Rva003AD904Template;
class Rva003ACFCFModule : public Rva003ABD20
{
public:
	Rva003ACFCFModule(void *a, Rva003AD904Template *b);
};


class Rva003AD940Template;
class Rva003AD005Module : public Rva003ABD81
{
public:
	Rva003AD005Module(void *a, Rva003AD940Template *b);
};


class Rva003AD97FTemplate;
class Rva003AD094Module : public Rva003ABDC8
{
public:
	Rva003AD094Module(void *a, Rva003AD97FTemplate *b);
};


class Rva003ADB21Template;
class Rva003AD278Module : public Rva003ACC4B
{
public:
	Rva003AD278Module(void *a, Rva003ADB21Template *b);
};


class Rva003ADB44Template;
class Rva003AD2B3Module : public Rva003ACC7C
{
public:
	Rva003AD2B3Module(void *a, Rva003ADB44Template *b);
};


class Rva003ADBD0Template;
class Rva003AD38BModule : public Rva003ABECC
{
public:
	Rva003AD38BModule(void *a, Rva003ADBD0Template *b);
};


// ---- five more intermediate constructors (same shape, rowed bases) ----

class Rva003ABB93 : public FXParticleSystem::LightningDrawModule
{
public:
	Rva003ABB93(void *a, void *b);
};

Rva003ABB93::Rva003ABB93(void *a, void *b)
	: FXParticleSystem::LightningDrawModule(*(FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> *)a,
		(const FXParticleSystem::LightningDrawModuleTemplate *)b)
{
	STAMP(0x00, g_00C1C488);
	STAMP(0x14, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x18, __identifier("??_7Rva005EBCC0Object@@6BV3Slot2@@@"));
}

class Rva003ABBCB : public Rva003AE94E
{
public:
	Rva003ABBCB(void *a, void *b);
};


class Rva003ABC6E : public Rva003AEA42
{
public:
    Rva003ABC6E(void *a, void *b);
    virtual ~Rva003ABC6E();
    virtual void rva000B3FD0();
    virtual void LoadPostProcess() {}
    virtual const char *GetSnapshotName() { return "DefaultModule<CAT_ALPHA>"; }
    virtual void DoXfer(Xfer &stream);
};
void Rva003ABC6E::DoXfer(Xfer &stream)
{
    stream.Version1();
    reinterpret_cast<Rva0055B266 *>((char *)this + 0x1C)->Rva0055B266::rva0055B266(&stream);
}

Rva003ABC6E::Rva003ABC6E(void *a, void *b)
	: Rva003AEA42(*(const RvaSmartPtr12 *)a, (int)b)
{
	STAMP(0x00, g_00C1C504 + 1);
	STAMP(0x14, g_00C1C504);
	STAMP(0x18, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x1C, __identifier("??_7Rva003ABC6E@@6BSnapshot@@@"));
}

class Rva003ABE40 : public Rva003AEF9B
{
public:
	Rva003ABE40(void *a, void *b);
};

Rva003ABE40::Rva003ABE40(void *a, void *b)
	: Rva003AEF9B(*(const RvaSmartPtr12 *)a, (int)b)
{
	STAMP(0x00, g_00C1C640 + 1);
	STAMP(0x14, g_00C1C640);
	STAMP(0x18, __identifier("??_7?$CategoryModuleTemplate@$05@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@"));
	STAMP(0x1C, g_00C1CF28);
}

class Rva003ABE8D : public Rva003AF076
{
public:
	Rva003ABE8D(void *a, void *b);
};


// ---- the two module constructors over 0x003ABB93 and 0x003ABBCB, under the
// names their factory call sites (0x003AD80B, 0x003AD84A) pin ----

class Rva003AD80BTemplate;
class Rva003ACE5CModule : public Rva003ABB93
{
public:
	Rva003ACE5CModule(void *a, Rva003AD80BTemplate *b);
};

Rva003ACE5CModule::Rva003ACE5CModule(void *a, Rva003AD80BTemplate *b)
	: Rva003ABB93(a, b)
{
	STAMP(0x00, __identifier("??_7Rva005EBCC0Object@@6BV3Slot0@@@"));
	STAMP(0x14, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x18, __identifier("??_7Rva005EBCC0Object@@6BV3Slot2@@@"));
}

class V3HostRva005E76E0;
class Rva005E76E0Object : public Rva003ABBCB
{
public:
	Rva005E76E0Object(void *a, V3HostRva005E76E0 *b);
};


// ---- two more intermediates over rowed bases, then the five module
// constructors their factory call sites pin ----

class Rva003ABB53 : public Rva005634F7
{
public:
	Rva003ABB53(void *a, void *b);
};


class V3HostRva005E7420;
class Rva005E7420Object : public Rva003ABB53
{
public:
	Rva005E7420Object(void *a, V3HostRva005E7420 *b);
};


class Rva003AD886Template;
class Rva003ACEFCModule : public Rva003ABC6E
{
public:
	Rva003ACEFCModule(void *a, Rva003AD886Template *b);
};

Rva003ACEFCModule::Rva003ACEFCModule(void *a, Rva003AD886Template *b)
	: Rva003ABC6E(a, b)
{
	STAMP(0x00, g_00C1CDCC);
	STAMP(0x14, g_00C1C504);
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x1C, __identifier("??_7Rva003ABC6E@@6BSnapshot@@@"));
}

class Rva003AD9BBTemplate;
class Rva003AD0CAModule : public Rva003ABDF9
{
public:
	Rva003AD0CAModule(void *a, Rva003AD9BBTemplate *b);
};


class Rva003AD9F7Template;
class Rva003AD100Module : public Rva003ABE40
{
public:
	Rva003AD100Module(void *a, Rva003AD9F7Template *b);
};

Rva003AD100Module::Rva003AD100Module(void *a, Rva003AD9F7Template *b)
	: Rva003ABE40(a, b)
{
	STAMP(0x00, g_00C1CF38);
	STAMP(0x14, g_00C1C640);
	STAMP(0x18, __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@@FXParticleSystem@@@FXParticleSystem@@6BSecondaryModuleBase@1@@"));
	STAMP(0x1C, g_00C1CF28);
}

class V3HostRva005E7AD0;
class Rva005E7AD0Object : public Rva003ABE8D
{
public:
	Rva005E7AD0Object(void *a, V3HostRva005E7AD0 *b);
};

