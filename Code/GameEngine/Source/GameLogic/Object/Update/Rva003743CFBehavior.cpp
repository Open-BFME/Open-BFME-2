// cl: /DNDEBUG /MD
//
// ?rva003743CF@Rva003743CF@@QAEXPAX_N@Z @0x003743CF 79B.
// BehaviorModule method: esi=[ecx+8] is Object*, calls Object::setStatus
// row 0x0023DB0E. Object+4 flag test bit 0x20 at +0x115 gates a virtual
// at [esi+0x250]+0x110 taking (callback, struct, 1); the callback at
// 0x003743BB repeats the setStatus on each object it is handed.
enum ObjectStatusTypes
{
	OBJECT_STATUS_PLACEHOLDER = 0
};
struct Rva003743CFParam
{
	int m_00;
	bool m_04;
};
class Rva003743CF250
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f30();
	virtual void f31();
	virtual void f32();
	virtual void f33();
	virtual void f34();
	virtual void f35();
	virtual void f36();
	virtual void f37();
	virtual void f38();
	virtual void f39();
	virtual void f40();
	virtual void f41();
	virtual void f42();
	virtual void f43();
	virtual void f44();
	virtual void f45();
	virtual void f46();
	virtual void f47();
	virtual void f48();
	virtual void f49();
	virtual void f50();
	virtual void f51();
	virtual void f52();
	virtual void f53();
	virtual void f54();
	virtual void f55();
	virtual void f56();
	virtual void f57();
	virtual void f58();
	virtual void f59();
	virtual void f60();
	virtual void f61();
	virtual void f62();
	virtual void f63();
	virtual void f64();
	virtual void f65();
	virtual void f66();
	virtual void f67();
	virtual void f68(void (__cdecl *func)(class Object *obj, void *userData), Rva003743CFParam *b, int c);
};
class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);
private:
	unsigned char m_pad00[4];
	const void *m_04;
	unsigned char m_pad08[0x250 - 0x08];
	Rva003743CF250 *m_250;
};
// Contain-iterate callback 0x003743BB (20B): apply the same status change to
// each contained object.
void __cdecl Rva003743BB(Object *obj, void *userData)
{
	Rva003743CFParam *param = (Rva003743CFParam *)userData;
	obj->setStatus((ObjectStatusTypes)param->m_00, param->m_04);
}

class Rva003743CF
{
public:
	void rva003743CF(void *p, bool b);
private:
	unsigned char m_pad00[8];
	Object *m_object;
};
void Rva003743CF::rva003743CF(void *p, bool b)
{
	Object *object = m_object;
	const void *flagObj = *(const void *const *)((const char *)object + 4);
	if ((*((const unsigned char *)flagObj + 0x115) & 0x20) != 0)
	{
		int status = *(int *)p;
		Rva003743CF250 *target = *(Rva003743CF250 **)((char *)object + 0x250);
		Rva003743CFParam param;
		param.m_00 = status;
		param.m_04 = b;
		target->f68(Rva003743BB, &param, 1);
	}
	object->setStatus(*(ObjectStatusTypes *)p, b);
}
