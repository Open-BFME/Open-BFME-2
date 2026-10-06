// cl: /DNDEBUG /MD /EHsc
//
// ?Rva00306769Forward@@YGXPAX@Z, retail 0x00306769, 25 bytes.
// Free __stdcall helper with one argument: loads the manager pointer at
// 0x009FF080, returns when it or the argument is null, otherwise
// tail-jumps to the manager's virtual at slot 25 (offset 0x64).
// Sole caller is the Snapshot-subclass dtor ??1Rva000D1BA6 at 0x000D1BA6
// (passes its own this after setting vtable 0x007CE310). Both the manager
// class and the free function use honest address-derived names: the
// manager's identity is unproven.

extern class G00DFF080Obj *g_00DFF080;

class Rva009FF080Manager
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25(void *arg) = 0;
};

#define TheRva009FF080Manager (*(Rva009FF080Manager **)&g_00DFF080)

void __stdcall Rva00306769Forward(void *arg)
{
	Rva009FF080Manager *manager = TheRva009FF080Manager;
	if (manager == 0)
		return;
	if (arg == 0)
		return;
	manager->_slot25(arg);
}
