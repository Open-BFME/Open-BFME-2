// cl: /EHsc
// ??0Rva0055F9B4@@QAE@ABVRvaSmartPtr12@@H@Z, retail 0x0055F9B4, 171 bytes.

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

struct Block12
{
	int v0;
	int v1;
	int v2;
};

struct CopySource
{
	unsigned char pad[0x0c];
	Block12 b0;
	Block12 b1;
	Block12 b2;
	Block12 b3;
	Block12 b4;
	int extra;
	Block12 b5;
	Block12 b6;
	Block12 b7;
};

class Rva0055F9B4 : public Rva0055F98A, public FXParticleSystem::DefaultUpdateModuleInfo
{
public:
	Rva0055F9B4(const RvaSmartPtr12 &smart, int x);
	virtual ~Rva0055F9B4();
};

Rva0055F9B4::Rva0055F9B4(const RvaSmartPtr12 &smart, int x)
	: Rva0055F98A(smart, x), DefaultUpdateModuleInfo()
{
	const CopySource *src = (const CopySource *)x;
	*(Block12 *)((char *)this + 0x20) = *(const Block12 *)((const char *)src + 0x0c);
	*(Block12 *)((char *)this + 0x2c) = *(const Block12 *)((const char *)src + 0x18);
	*(Block12 *)((char *)this + 0x38) = *(const Block12 *)((const char *)src + 0x24);
	*(Block12 *)((char *)this + 0x44) = *(const Block12 *)((const char *)src + 0x30);
	*(Block12 *)((char *)this + 0x50) = *(const Block12 *)((const char *)src + 0x3c);
	*(int *)((char *)this + 0x5c) = *(const int *)((const char *)src + 0x48);
	*(Block12 *)((char *)this + 0x60) = *(const Block12 *)((const char *)src + 0x4c);
	*(Block12 *)((char *)this + 0x6c) = *(const Block12 *)((const char *)src + 0x58);
	*(Block12 *)((char *)this + 0x78) = *(const Block12 *)((const char *)src + 0x64);
}
