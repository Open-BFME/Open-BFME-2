// cl: /DNDEBUG /MD /EHs-c-
// ??0Rva0055B5BF@@QAE@ABVRvaSmartPtr12@@H@Z retail 0x0055B5BF 42B: same shape
// as ??0Rva003AEEB3@@QAE@ABVRvaSmartPtr12@@H@Z via rowed base 0x0055BEE9 with
// own vtable 0x00C1D5E8 plus second/third 0x00C1C780; caller at 0x0055B603.
// ??0Rva0055BF21@@QAE@ABVRvaSmartPtr12@@H@Z retail 0x0055BF21 42B: own vtable
// 0x00C1D638 plus second/third 0x00C1C780 via rowed base 0x0055BEE9; callers
// at 0x0055BF65 0x0055F1B1.
// ??0Rva0055F98A@@QAE@ABVRvaSmartPtr12@@H@Z retail 0x0055F98A 42B: own vtable
// 0x00C1D6C8 plus second/third 0x00C1C780 via rowed base 0x0055BEE9; callers
// at 0x0055F9CE 0x005624F8. All vtable dwords are DIR32 sites.

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	~RvaSmartPtr12();

private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class DefaultModuleSecondBase
{
public:
	virtual ~DefaultModuleSecondBase();
};

class DefaultModuleThirdBase
{
public:
	virtual ~DefaultModuleThirdBase();
};

class DefaultModuleHeadBase
{
public:
	DefaultModuleHeadBase(const RvaSmartPtr12 &smart, int i);
	virtual ~DefaultModuleHeadBase();

	RvaSmartPtr12 m_smart;
	int m_int10;
};

class Rva003AEEB3 : public DefaultModuleHeadBase, public DefaultModuleSecondBase,
	public DefaultModuleThirdBase
{
public:
	Rva003AEEB3(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva003AEEB3();
};

class Rva0055B5BF : public Rva003AEEB3
{
public:
	__declspec(noinline) Rva0055B5BF(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva0055B5BF();
};

class Rva0055BF21 : public Rva003AEEB3
{
public:
	__declspec(noinline) Rva0055BF21(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva0055BF21();
};

class Rva0055F98A : public Rva003AEEB3
{
public:
	__declspec(noinline) Rva0055F98A(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva0055F98A();
};

Rva0055B5BF::Rva0055B5BF(const RvaSmartPtr12 &smart, int i)
	: Rva003AEEB3(smart, i)
{
}

Rva0055BF21::Rva0055BF21(const RvaSmartPtr12 &smart, int i)
	: Rva003AEEB3(smart, i)
{
}

Rva0055F98A::Rva0055F98A(const RvaSmartPtr12 &smart, int i)
	: Rva003AEEB3(smart, i)
{
}
