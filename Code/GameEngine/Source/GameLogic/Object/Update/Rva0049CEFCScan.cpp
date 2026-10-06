// cl: /MD

extern "C" void _WriteBarrier(void);
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_WriteBarrier, _ReadWriteBarrier)
//
// ?Rva0049CEFCScan@@YAXPAX@Z, retail 0x0049CEFC, 41 bytes.
// Leaf free function: null early-out, then walks a null-terminated pointer
// array at +0x244, calling the +0x0C subobject virtual at slot 0x70 and
// stopping on the first nonzero return. Single caller at 0x00391953.
// Prev 0x0049CDF9 is Rva0049D1B1::Check, next 0x0049CF9E is a disp8 getter.

class CheckIface
{
public:
	virtual void u00();
	virtual void u01();
	virtual void u02();
	virtual void u03();
	virtual void u04();
	virtual void u05();
	virtual void u06();
	virtual void u07();
	virtual void u08();
	virtual void u09();
	virtual void u10();
	virtual void u11();
	virtual void u12();
	virtual void u13();
	virtual void u14();
	virtual void u15();
	virtual void u16();
	virtual void u17();
	virtual void u18();
	virtual void u19();
	virtual void u20();
	virtual void u21();
	virtual void u22();
	virtual void u23();
	virtual void u24();
	virtual void u25();
	virtual void u26();
	virtual void u27();
	virtual int Check();
};

struct Outer
{
	int m_00;
	int m_04;
	int m_08;
	CheckIface m_iface;
};

struct Parent
{
	char m_pad[0x244];
	Outer **m_list;
};

void __cdecl Rva0049CEFCScan(void *arg)
{
	if (!arg)
	{
		_WriteBarrier();
		return;
	}
	Parent *parent = (Parent *)arg;
	Outer **pp = parent->m_list;
	while (*pp != 0)
	{
		if ((*pp)->m_iface.Check() != 0)
			break;
		++pp;
	}
	_ReadWriteBarrier();
	return;
}
