// cl: /MD

// ?rva0004263F@Rva0004263F@@QAEXMMMMH@Z @0x0004263F 72B
// Unlock: missing callee of 9 free functions; callers at 0x000440DD 0x0004412D
// 0x000441E4 in FUN_00444018 pass 4 floats + int through to virtuals.
// Sequence: vtable+0xD4, then vtable+0xE4(float x4 int), then vtable+0x100.
// Prev/next are disp8 trivial getters/setters with TU default flags.

class Rva0004263F
{
	virtual void _M_slot_00();
	virtual void _M_slot_01();
	virtual void _M_slot_02();
	virtual void _M_slot_03();
	virtual void _M_slot_04();
	virtual void _M_slot_05();
	virtual void _M_slot_06();
	virtual void _M_slot_07();
	virtual void _M_slot_08();
	virtual void _M_slot_09();
	virtual void _M_slot_10();
	virtual void _M_slot_11();
	virtual void _M_slot_12();
	virtual void _M_slot_13();
	virtual void _M_slot_14();
	virtual void _M_slot_15();
	virtual void _M_slot_16();
	virtual void _M_slot_17();
	virtual void _M_slot_18();
	virtual void _M_slot_19();
	virtual void _M_slot_20();
	virtual void _M_slot_21();
	virtual void _M_slot_22();
	virtual void _M_slot_23();
	virtual void _M_slot_24();
	virtual void _M_slot_25();
	virtual void _M_slot_26();
	virtual void _M_slot_27();
	virtual void _M_slot_28();
	virtual void _M_slot_29();
	virtual void _M_slot_30();
	virtual void _M_slot_31();
	virtual void _M_slot_32();
	virtual void _M_slot_33();
	virtual void _M_slot_34();
	virtual void _M_slot_35();
	virtual void _M_slot_36();
	virtual void _M_slot_37();
	virtual void _M_slot_38();
	virtual void _M_slot_39();
	virtual void _M_slot_40();
	virtual void _M_slot_41();
	virtual void _M_slot_42();
	virtual void _M_slot_43();
	virtual void _M_slot_44();
	virtual void _M_slot_45();
	virtual void _M_slot_46();
	virtual void _M_slot_47();
	virtual void _M_slot_48();
	virtual void _M_slot_49();
	virtual void _M_slot_50();
	virtual void _M_slot_51();
	virtual void _M_slot_52();
	virtual void _M_slot_53();
	virtual void _M_slot_54();
	virtual void _M_slot_55();
	virtual void _M_slot_56();
	virtual void _M_slot_57(float a, float b, float c, float d, int e);
	virtual void _M_slot_58();
	virtual void _M_slot_59();
	virtual void _M_slot_60();
	virtual void _M_slot_61();
	virtual void _M_slot_62();
	virtual void _M_slot_63();
	virtual void _M_slot_64();
public:
	void rva0004263F(float a, float b, float c, float d, int e);
};

void Rva0004263F::rva0004263F(float a, float b, float c, float d, int e)
{
	_M_slot_53();
	_M_slot_57(a, b, c, d, e);
	_M_slot_64();
}
