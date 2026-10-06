// cl: /DNDEBUG /MD /EHs-c-
// ??0Rva003ABD81@@QAE@ABVRvaSmartPtr12@@H@Z, retail 0x003ABD81, 49 bytes.
// Empty derived of the rowed ??0Rva0055F9B4@@QAE@ABVRvaSmartPtr12@@H@Z at
// 0x0055F9B4: forwards (smart, x) then re-stamps the four vftables
// (+0 0x00C1C5BC, +0x14 0x00C1C5B8, +0x18 s_slot3E4first, +0x1C 0x00C1CE88).
// Same empty-body shape as sibling 0x003ABD20 via rowed base 0x0055F197;
// all vtable dwords are DIR32 sites. Caller at 0x003AD010.

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

class Rva0055F98A : public Rva003AEEB3
{
public:
	Rva0055F98A(const RvaSmartPtr12 &smart, int i);
	virtual ~Rva0055F98A();
};

class GameClientRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

namespace FXParticleSystem
{
class DefaultUpdateModuleInfo
{
public:
	DefaultUpdateModuleInfo();
	virtual ~DefaultUpdateModuleInfo();
	GameClientRandomVariable m_var0;
	GameClientRandomVariable m_var1;
	GameClientRandomVariable m_var2;
	GameClientRandomVariable m_var3;
	GameClientRandomVariable m_var4;
	int m_extra;
	GameClientRandomVariable m_var5;
	GameClientRandomVariable m_var6;
	GameClientRandomVariable m_var7;
};
}

class Rva0055F9B4 : public Rva0055F98A, public FXParticleSystem::DefaultUpdateModuleInfo
{
public:
	Rva0055F9B4(const RvaSmartPtr12 &smart, int x);
	virtual ~Rva0055F9B4();
};

class Rva003ABD81 : public Rva0055F9B4
{
public:
	__declspec(noinline) Rva003ABD81(const RvaSmartPtr12 &smart, int x);
	virtual ~Rva003ABD81();
};

Rva003ABD81::Rva003ABD81(const RvaSmartPtr12 &smart, int x)
	: Rva0055F9B4(smart, x)
{
}
