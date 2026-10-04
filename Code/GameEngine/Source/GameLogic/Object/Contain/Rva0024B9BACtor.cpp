// cl: /O1 /MD /DNDEBUG
//
// ??0Rva0024B9BA@@QAE@XZ @0x0024B9BA 18B.
// Frameless derived ctor over rowed HordeContainModuleData base 0x00475C9A;
// the compiler installs vtable 0x00C465F8 (same VA as the
// AODHordeContainModuleData vtable) right after the base call. Sits between
// HorseHordeContain (0x0024B97F) and HordeTransportContain (0x0024B9CC)
// instance factories; honest Rva name since AOD default ctor already rowed
// at 0x0047A2E1.
//
// Target-owned slot view: retail's table at 0x00C465F8 holds 31 code
// pointers (tools/vftable_map.py); each slot is declared in order and bound
// to the ledger name at its retail target, so the vftable this unit emits
// carries retail's slots. Slot 0 is the scalar deleting destructor 0x0025361E;
// the rest are the folded ModuleData defaults (empty, false, true, name and
// zero returners). Original method names and signatures are not recovered.

class HordeContainModuleData
{
public:
	HordeContainModuleData();
	// Polymorphic base (its vptr is at +0); its own table is not emitted here.
	virtual void slot00();
};

class Rva0024B9BA : public HordeContainModuleData
{
public:
	Rva0024B9BA();
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
};

#pragma comment(linker, "/alternatename:?slot00@Rva0024B9BA@@UAEXXZ=??_GRva0047A724@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?slot01@Rva0024B9BA@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot02@Rva0024B9BA@@UAEXXZ=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:?slot03@Rva0024B9BA@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?slot04@Rva0024B9BA@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot05@Rva0024B9BA@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot06@Rva0024B9BA@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot07@Rva0024B9BA@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot08@Rva0024B9BA@@UAEXXZ=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
#pragma comment(linker, "/alternatename:?slot09@Rva0024B9BA@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot10@Rva0024B9BA@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot11@Rva0024B9BA@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot12@Rva0024B9BA@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot13@Rva0024B9BA@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot14@Rva0024B9BA@@UAEXXZ=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:?slot15@Rva0024B9BA@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot16@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot17@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot18@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot19@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot20@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot21@Rva0024B9BA@@UAEXXZ=??0Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?slot22@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot23@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot24@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot25@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot26@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot27@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot28@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot29@Rva0024B9BA@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?slot30@Rva0024B9BA@@UAEXXZ=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")

Rva0024B9BA::Rva0024B9BA()
	: HordeContainModuleData()
{
}
