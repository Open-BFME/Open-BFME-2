// ?rva00575C15@Rva00575C15@@QAE_NPBX@Z
// partial score=0.84 date=2026-10-07
// Target evidence: body at 0x00575C15 reads this+0x28, dispatches virtual slot 2,
// then calls 0x005CD8F7 on this+0x30, 0x005CD690 on this+0x40, and 0x005CBC95
// on this. Names below encode those call destinations; class purpose is unknown.
class Rva00575C15Dispatch
{
public:
	virtual int gap0();
	virtual int gap1();
	virtual int check(const void *arg);
};
class Rva005CD8F7Call { public: int rva005CD8F7(const void *arg); };
class Rva005CD690Call { public: int rva005CD690(const void *arg); };
class Rva005CBC95Call { public: bool rva005CBC95(const void *arg); };
class Rva00575C15
{
public:
	bool rva00575C15(const void *arg);
};
bool Rva00575C15::rva00575C15(const void *arg)
{
	Rva00575C15Dispatch *dispatch = *(Rva00575C15Dispatch **)((char *)this + 0x28);
	return (dispatch && dispatch->check(arg) == 1)
		|| ((Rva005CD8F7Call *)((char *)this + 0x30))->rva005CD8F7(arg) == 1
		|| ((Rva005CD690Call *)((char *)this + 0x40))->rva005CD690(arg) == 1
		|| ((Rva005CBC95Call *)this)->rva005CBC95(arg);
}
