// cl: /DNDEBUG /MD
// ??0Rva005641BB@@QAE@ABVRvaSmartPtr12@@H@Z, retail 0x005641BB, 50 bytes.
// Derived ctor: forwards (smart,int) to the rowed base
// ??0Rva003AEEB3@@QAE@ABVRvaSmartPtr12@@H@Z at 0x0055BEE9, bool pair at
// +0x1C/+0x1D via inline second base, final vtables through real inheritance.
// Evidence: calls 0x0055BEE9 at 0x005641C6; callers at 0x00564207/0x00564918.

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

class Rva003AEEB3 : public DefaultModuleHeadBase, public DefaultModuleSecondBase, public DefaultModuleThirdBase
{
public:
	Rva003AEEB3(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva003AEEB3();
};

struct BoolPair14
{
	BoolPair14() : m_1C(true), m_1D(true) {}
	bool m_1C;
	bool m_1D;
};

class Rva005641BB : public Rva003AEEB3, public BoolPair14
{
public:
	Rva005641BB(const RvaSmartPtr12 &smart, int i);
	~Rva005641BB();
};

Rva005641BB::Rva005641BB(const RvaSmartPtr12 &smart, int i)
	: Rva003AEEB3(smart, i), BoolPair14()
{
}
