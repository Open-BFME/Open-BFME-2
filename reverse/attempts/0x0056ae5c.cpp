// ??0Rva0056AE5C@@QAE@PAX00@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /MD /EHsc
//
// ??0Rva0056AE5C@@QAE@PAX00@Z @0x0056AE5C 78B.
// EH constructor (three args): run the pinned 0x0056AD80 initializer on the
// first argument, install the 0x00C6D0A8 vftable at +0 and the 0x00C6D06C
// vftable at +8, then run pinned 0x002B2702 on the g_00DFEF10 singleton with
// (1, third, second) under EH state 0. Empty base with external dtor supplies
// the frame and single state. Honest address-derived name.
class Rva0056AD80
{
public:
	void rva0056AD80(void *arg) throw();
};

class Rva002B2702
{
public:
	void rva002B2702(void *a, void *b, int c);
};

extern Rva002B2702 *g_00DFEF10;

extern "C" const void *const vtbl_00C6D0A8[];
extern "C" const void *const vtbl_00C6D06C[];

class Rva0056AE5CBase
{
public:
	~Rva0056AE5CBase();
};

class Rva0056AE5C : public Rva0056AE5CBase
{
public:
	Rva0056AE5C(void *arg1, void *arg2, void *arg3);
};

Rva0056AE5C::Rva0056AE5C(void *arg1, void *arg2, void *arg3)
{
	((Rva0056AD80 *)this)->rva0056AD80(arg1);
	*(unsigned int *)this = ((unsigned int)vtbl_00C6D0A8);
	*(unsigned int *)((char *)this + 8) = ((unsigned int)vtbl_00C6D06C);
	g_00DFEF10->rva002B2702(arg2, arg3, 1);
}
