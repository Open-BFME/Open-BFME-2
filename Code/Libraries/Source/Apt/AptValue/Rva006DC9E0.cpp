// cl: /MD
// ?rva006DC9E0@Rva006DC9E0@@QAEHXZ @0x006DC9E0 123B
// Evidence: thiscall no args returns int (xor 0 / mov 1); calls GetString 0x5E/0x64,
// Rva0070A5C0::Find via global 0x00E18650, virtual slot 3 (0xC) twice plus this slot 3
// and node walk via +8 with edi/ebx sentinels from +0xC fields; callers 0x006DFBF8 0x0070857A.
// Started from reverse/attempts/0x006dc9e0.cpp (score 0.94, true-epilogue
// duplicated inline vs shared plus extra loop je-mov-test 130 vs 123).
class EAStringC;
EAStringC *__cdecl Rva0070B4F0GetString(int eSC);

class BfmeN1034;
class Rva0070A5C0
{
public:
	BfmeN1034 *rva0070A5C0(int k);
};
extern Rva0070A5C0 *g_00E18650;

struct Mid
{
	char pad8[8];
	void *field8;
	void *fieldC;
};

struct VirtObj
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual Mid *virt3();
};

class Rva006DC9E0
{
public:
	int rva006DC9E0();
};

int Rva006DC9E0::rva006DC9E0()
{
	EAStringC *s1 = Rva0070B4F0GetString(0x5E);
	BfmeN1034 *f1 = g_00E18650->rva0070A5C0((int)s1);
	Mid *m1 = ((VirtObj *)f1)->virt3();
	void *edi = m1->fieldC;
	EAStringC *s2 = Rva0070B4F0GetString(0x64);
	BfmeN1034 *f2 = g_00E18650->rva0070A5C0((int)s2);
	Mid *m2 = ((VirtObj *)f2)->virt3();
	void *ebx = m2->fieldC;
	if ((void *)this == edi)
		goto ret_true;
	VirtObj *self = (VirtObj *)this;
	Mid *m = self->virt3();
	if (!m)
		return 0;
	do {
		VirtObj *node = (VirtObj *)m->field8;
		if (!node)
			return 0;
		if ((void *)node == edi)
			goto ret_true;
		if ((void *)node == ebx)
			return 0;
		m = node->virt3();
	} while (m != 0);
	return 0;
ret_true:
	return 1;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00E18650@@3PAVRva0070A5C0@@A=?g_00E18650@@3VEAStringC@@A")
