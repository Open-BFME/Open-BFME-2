// ??0Rva0056B372@@QAE@PAX00@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD /EHsc
//
// ??0Rva0056B372@@QAE@PAX00@Z @0x0056B372 103B.
// EH constructor (three args): run the pinned 0x0056AD80 initializer,
// store 0x00BFDF68 into the +0x14 struct, capture arg2/arg3, install vftables,
// append the +0x14 struct to the arg2 list via rowed 0x005A0B4C, then fill
// +0x1C/+0x20. Empty base with external dtor supplies the frame. Honest
// address-derived name.
class Rva0056AD80
{
public:
	void rva0056AD80(void *arg) throw();
};

struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *item);
};

extern "C" const void *const vtbl_00C6D348[];
extern "C" const void *const vtbl_00C6D30C[];
extern "C" const void *const vtbl_00C6D2FC[];

class Rva0056B372Base
{
public:
	~Rva0056B372Base();
};

class Rva0056B372 : public Rva0056B372Base
{
public:
	Rva0056B372(void *arg1, void *arg2, void *arg3);
};

Rva0056B372::Rva0056B372(void *arg1, void *arg2, void *arg3)
{
	((Rva0056AD80 *)this)->rva0056AD80(arg1);
	*(volatile int *)((char *)this + 0x14) = 0x00BFDF68;
	*(void **)((char *)this + 0x18) = arg2;
	*(unsigned int *)this = ((unsigned int)vtbl_00C6D348);
	*(unsigned int *)((char *)this + 8) = ((unsigned int)vtbl_00C6D30C);
	*(unsigned int *)((char *)this + 0x14) = ((unsigned int)vtbl_00C6D2FC);
	((Rva005A0B4CList *)((char *)arg2 + 4))->append((Rva002BA8F1Listener *)((char *)this + 0x14));
	*(void **)((char *)this + 0x1C) = arg3;
	*(unsigned char *)((char *)this + 0x20) = 0;
}
