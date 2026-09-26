// cl: /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmeanimobj /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Rva001A5460@Animatable3DObjClass@@UAEXPAV1@@Z, RVA 0x001A5460, 75B. Virtual slot 59 (offset 0xEC) of vtable 0x007D6D10 (class of ??0Animatable3DObjClass@@QAE@PBD@Z in animobj.cpp). Evidence: vtable slot 59; member +0xFC is _bfme_a3o_v0 slave master (HTree at +0xF8 IsTreeValid at +0xF4 CurMotionMode at +0x100 ModeAnim.Motion at +0x104 frameRateMultiplier at +0x11C); validation via slot 58 Get_HTree (0x19F010); REF_PTR_SET with Add_Ref Release_Ref Delete_This slot 0; no direct callees; donor BFME1 animobj.h slave Update_Sub_Object_Transforms at 0x1A5900 slot 42.
// TU-local vtable shim places Get_HTree at slot 58 and Rva at slot 59; layout pad puts _slave at +0xFC with NumRefs at +4.
class HTreeClass;
class RefCountShim
{
public:
	virtual void Delete_This() = 0;
	void Add_Ref() { ++NumRefs; }
	void Release_Ref()
	{
		if (--NumRefs == 0) {
			Delete_This();
		}
	}
private:
	int NumRefs;
};
class Animatable3DObjClass : public RefCountShim
{
public:
	virtual ~Animatable3DObjClass() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual const HTreeClass *Get_HTree() const = 0;
	virtual void Rva001A5460(Animatable3DObjClass *master) = 0;
private:
	char _pad[0xEC];
	bool IsTreeValid;
	HTreeClass *HTree;
	Animatable3DObjClass *_slave;
};
void Animatable3DObjClass::Rva001A5460(Animatable3DObjClass *master)
{
	if (master) {
		if (!master->Get_HTree()) {
			master = 0;
		}
	}
	if (master != _slave) {
		if (master) {
			master->Add_Ref();
		}
		if (_slave) {
			_slave->Release_Ref();
		}
		_slave = master;
	}
}
