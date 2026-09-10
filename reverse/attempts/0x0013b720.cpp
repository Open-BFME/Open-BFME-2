// ?Set_Force_Visible@RenderObjClass@@UAEXH@Z
// partial score=0.95 date=2026-09-10
// cl: /O2 /G7 /DNDEBUG /MD
//
// RenderObjClass::Set_Force_Visible, retail 0x0013B720, 73 bytes.
// Dedicated TU. Virtual Is_Force_Visible at +0x1A0; Scene at +0x78;
// Bits at +0x10. Changing visibility notifies Scene with type 4.

class RenderObjClass;

class SceneClass
{
public:
	virtual void reserved_0();
	virtual void reserved_1();
	virtual void reserved_2();
	virtual void reserved_3();
	virtual void reserved_4();
	virtual void reserved_5();
	virtual void reserved_6();
	virtual void reserved_7();
	virtual void reserved_8();
	virtual void reserved_9();
	virtual void reserved_10();
	virtual void reserved_11();
	virtual void reserved_12();
	virtual void reserved_13();
	virtual void Register(RenderObjClass *obj, int for_what);
	virtual void Unregister(RenderObjClass *obj, int for_what);
};

class RenderObjClass
{
public:
	virtual void reserved_0();
	virtual void reserved_1();
	virtual void reserved_2();
	virtual void reserved_3();
	virtual void reserved_4();
	virtual void reserved_5();
	virtual void reserved_6();
	virtual void reserved_7();
	virtual void reserved_8();
	virtual void reserved_9();
	virtual void reserved_10();
	virtual void reserved_11();
	virtual void reserved_12();
	virtual void reserved_13();
	virtual void reserved_14();
	virtual void reserved_15();
	virtual void reserved_16();
	virtual void reserved_17();
	virtual void reserved_18();
	virtual void reserved_19();
	virtual void reserved_20();
	virtual void reserved_21();
	virtual void reserved_22();
	virtual void reserved_23();
	virtual void reserved_24();
	virtual void reserved_25();
	virtual void reserved_26();
	virtual void reserved_27();
	virtual void reserved_28();
	virtual void reserved_29();
	virtual void reserved_30();
	virtual void reserved_31();
	virtual void reserved_32();
	virtual void reserved_33();
	virtual void reserved_34();
	virtual void reserved_35();
	virtual void reserved_36();
	virtual void reserved_37();
	virtual void reserved_38();
	virtual void reserved_39();
	virtual void reserved_40();
	virtual void reserved_41();
	virtual void reserved_42();
	virtual void reserved_43();
	virtual void reserved_44();
	virtual void reserved_45();
	virtual void reserved_46();
	virtual void reserved_47();
	virtual void reserved_48();
	virtual void reserved_49();
	virtual void reserved_50();
	virtual void reserved_51();
	virtual void reserved_52();
	virtual void reserved_53();
	virtual void reserved_54();
	virtual void reserved_55();
	virtual void reserved_56();
	virtual void reserved_57();
	virtual void reserved_58();
	virtual void reserved_59();
	virtual void reserved_60();
	virtual void reserved_61();
	virtual void reserved_62();
	virtual void reserved_63();
	virtual void reserved_64();
	virtual void reserved_65();
	virtual void reserved_66();
	virtual void reserved_67();
	virtual void reserved_68();
	virtual void reserved_69();
	virtual void reserved_70();
	virtual void reserved_71();
	virtual void reserved_72();
	virtual void reserved_73();
	virtual void reserved_74();
	virtual void reserved_75();
	virtual void reserved_76();
	virtual void reserved_77();
	virtual void reserved_78();
	virtual void reserved_79();
	virtual void reserved_80();
	virtual void reserved_81();
	virtual void reserved_82();
	virtual void reserved_83();
	virtual void reserved_84();
	virtual void reserved_85();
	virtual void reserved_86();
	virtual void reserved_87();
	virtual void reserved_88();
	virtual void reserved_89();
	virtual void reserved_90();
	virtual void reserved_91();
	virtual void reserved_92();
	virtual void reserved_93();
	virtual void reserved_94();
	virtual void reserved_95();
	virtual void reserved_96();
	virtual void reserved_97();
	virtual void reserved_98();
	virtual void reserved_99();
	virtual void reserved_100();
	virtual void reserved_101();
	virtual void reserved_102();
	virtual void reserved_103();
	virtual int Is_Force_Visible(void) const;
	virtual void Set_Force_Visible(int onoff);

private:
	unsigned char pad04[0x0C];
	unsigned long Bits;
	unsigned char pad14[0x78 - 0x14];
	SceneClass *Scene;
};

void RenderObjClass::Set_Force_Visible(int onoff)
{
	int was = Is_Force_Visible() != 0;
	int now = onoff != 0;
	if (now == was)
		return;
	SceneClass *scene = Scene;
	volatile unsigned long &bits = Bits;
	bits &= 0xFFFF7FFFul;
	if (scene == 0)
		return;
	if (onoff)
		scene->Register(this, 4);
	else
		scene->Unregister(this, 4);
}
