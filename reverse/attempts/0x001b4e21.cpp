// ?Rva001B4E21Get@@YA_EPAXPAX@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /MD
// ?Rva001B4E21Get@@YA_EPAXPAX@Z RVA 0x001B4E21 40B
// Evidence: unlock lane; callers 0x001B509F 0x001B50D8 in 0x001B505F; free function ret 8
//   with vtable slot 0x10 call on arg1 with m_4 guard set/cleared around it.

class Rva001B4E21Arg
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual bool v4(void *arg);
	unsigned char m_4;
};

// ?Rva001B4E21Get@@YA_EPAXPAX@Z present-unmatched
unsigned char Rva001B4E21Get(void *arg1, void *arg2)
{
	Rva001B4E21Arg *obj = (Rva001B4E21Arg *)arg1;
	unsigned char result = 0;
	obj->m_4 = 1;
	if (obj->v4(arg2))
		result++;
	obj->m_4 = 0;
	return result;
}
