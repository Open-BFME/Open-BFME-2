// cl: /DNDEBUG /MD /EHs-c-
// ??0Rva003ABD20@@QAE@ABVRvaSmartPtr12@@H@Z, retail 0x003ABD20, 49 bytes.
// Empty derived of the rowed ??0Rva0055F197@@QAE@ABVRvaSmartPtr12@@H@Z at
// 0x0055F197: forwards (smart, x) then re-stamps the four vftables
// (+0 0x00C1C578, +0x14 0x00C1C574, +0x18 s_slot3E4first, +0x1C 0x00C1CE54).
// Same empty-body shape as the DefaultModuleDerivedSmartCtors trio via rowed
// base 0x0055BEE9; all vtable dwords are DIR32 sites. Caller at 0x003ACFDA.

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

class Rva0055BF21 : public Rva003AEEB3
{
public:
	Rva0055BF21(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva0055BF21();
};

namespace FXParticleSystem
{
class DefaultPhysicsModuleInfo
{
public:
	DefaultPhysicsModuleInfo();
	virtual ~DefaultPhysicsModuleInfo();
};
}

class Rva0055F197 : public Rva0055BF21, public FXParticleSystem::DefaultPhysicsModuleInfo
{
public:
	Rva0055F197(const RvaSmartPtr12 &smart, int x);
	virtual ~Rva0055F197();
private:
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	unsigned char m_3c;
	unsigned char m_3d;
};

class Rva003ABD20 : public Rva0055F197
{
public:
	__declspec(noinline) Rva003ABD20(const RvaSmartPtr12 &smart, int x);
	virtual ~Rva003ABD20();
};

Rva003ABD20::Rva003ABD20(const RvaSmartPtr12 &smart, int x)
	: Rva0055F197(smart, x)
{
}
