// cl: /MD /EHsc
//
// ??1Rva006003FC@@UAE@XZ @0x006003FC 54B and ??_GRva006003FC@@UAEPAXI@Z
// @0x006004A5 28B. Dual-vtable dtor: stores derived vtable 0x0087A638,
// calls member dtor ??1Rva00600084@@UAE@XZ at +8, then stores base vtable
// 0x007C6F20 inline via the empty base dtor. Same recipe as
// BfmeDualVtableReleaseDtor.cpp. Evidence: ctor 0x00600432 stores the same
// 0x0087A638; deleting dtor 0x006004A5 calls 0x006003FC then operator
// delete; callers 0x005FB1D6/0x006004A8 plus jmp thunks 0x005FB20A/0x005FB3DF.

class Rva00600084
{
public:
	virtual ~Rva00600084();
};

class Rva006003FCBase
{
public:
	__forceinline ~Rva006003FCBase() {}
	virtual void keep() {}
};

class Rva006003FC : public Rva006003FCBase
{
public:
	virtual ~Rva006003FC();

private:
	int m_pad04;
	Rva00600084 m_member08;
};

Rva006003FC::~Rva006003FC()
{
}
