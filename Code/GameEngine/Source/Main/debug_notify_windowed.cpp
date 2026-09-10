// cl: /O1
//
// Retail RVA 0x00001720, 19 bytes. Free cdecl wrapper that forwards its one
// dword argument to Debug vtable slot 0xB0 on the singleton at 0x00DE0880.
// initializeAppWindows at 0x0000275D is the only call site: it pushes
// runWindowed before the call. Original method spelling at slot 0xB0 is
// unknown; the wrapper name is reconstruction.

class Debug
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual void _M_slot_74();
	virtual void _M_slot_78();
	virtual void _M_slot_7c();
	virtual void _M_slot_80();
	virtual void _M_slot_84();
	virtual void _M_slot_88();
	virtual void _M_slot_8c();
	virtual void _M_slot_90();
	virtual void _M_slot_94();
	virtual void _M_slot_98();
	virtual void _M_slot_9c();
	virtual void _M_slot_a0();
	virtual void _M_slot_a4();
	virtual void _M_slot_a8();
	virtual void _M_slot_ac();
	virtual void _M_slot_b0(unsigned arg);
};

Debug *theDebug;

void bfmeNotifyDebugWindowed(unsigned runWindowed)
{
	theDebug->_M_slot_b0(runWindowed);
}
