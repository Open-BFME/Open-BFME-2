// cl: /MD
//
// Constructors for the opaque Rva003B00D6 single-inheritance chain (see
// OpaqueSingleInheritanceDtors.cpp for the dtors, OpaqueScalarDeletingDtorsB07
// for the deleting dtors). Layouts are read from the bodies below: a
// RvaSmartPtr12 member at +4 (rowed copy ctor at 0x0004CC19) and zeroed words
// at +0x10/+0x14/+0x18. Destructors are only declared (pinned 0x003B00D6 /
// rowed 0x003B0152) so their slots resolve outside this TU; vtable values are
// DIR32 auto-patches.
// ??0Rva003B00D6@@QAE@ABVRvaSmartPtr12@@@Z @0x003B00AA 36B: installs vptr
// 0x00C1D8F0, copies the +4 smart pointer, zeroes +0x10/+0x14/+0x18.
// ??0Rva003B0152@@QAE@ABVRvaSmartPtr12@@@Z @0x003B0134 24B: base-constructs
// Rva003B00D6 from the arg, then installs vptr 0x00C1D950.

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &that);

private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class Rva003B00D6
{
public:
	Rva003B00D6(const RvaSmartPtr12 &src);
	virtual ~Rva003B00D6();

private:
	RvaSmartPtr12 m_sptr04;
	int m_10;
	int m_14;
	int m_18;
};

class Rva003B0152 : public Rva003B00D6
{
public:
	Rva003B0152(const RvaSmartPtr12 &src);
	virtual ~Rva003B0152();
};

Rva003B00D6::Rva003B00D6(const RvaSmartPtr12 &src) :
	m_sptr04(src),
	m_10(0),
	m_14(0),
	m_18(0)
{
}

Rva003B0152::Rva003B0152(const RvaSmartPtr12 &src) :
	Rva003B00D6(src)
{
}

// ??0Rva003B0401@@QAE@ABVRvaSmartPtr12@@@Z @0x003B0835 24B: base-constructs
// the pinned 264B Rva003B0344 ctor (vptr 0x00C1D9B0 class) from the arg, then
// installs vptr 0x00C1DA10. Dtor rowed at 0x003B0401.
class Rva003B0344
{
public:
	Rva003B0344(const RvaSmartPtr12 &src);
	virtual ~Rva003B0344();
};

class Rva003B0401 : public Rva003B0344
{
public:
	Rva003B0401(const RvaSmartPtr12 &src);
	virtual ~Rva003B0401();
};

Rva003B0401::Rva003B0401(const RvaSmartPtr12 &src) :
	Rva003B0344(src)
{
}
