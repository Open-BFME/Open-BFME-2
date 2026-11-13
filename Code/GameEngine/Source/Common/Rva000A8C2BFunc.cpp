// cl: /MD
// The stream-holder member transfers the saved position through the serializer.
// Its receiver is unused; the packet contains three consecutive DWORDs.
#include "../../Include/Common/TwoBytes.h"

class Rva000A8C2BObj
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10(TwoBytes *t);
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28(int *p);
	virtual void s29();
	virtual void s30();
	virtual void s31(int *p);
};

class Rva000A8C2B
{
public:
	void rva000A8C2B(Rva000A8C2BObj *obj, int *ptr);
};

void Rva000A8C2B::rva000A8C2B(Rva000A8C2BObj *obj, int *ptr)
{
	TwoBytes t;
	t.a = 1;
	t.b = 1;
	obj->s10(&t);
	obj->s28(ptr + 2);
	obj->s31(ptr);
	obj->s31(++ptr);
}
