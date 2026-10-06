// cl: /O1 /DNDEBUG /MD /EHsc
// 0x003AEE16 149B unlock: copy ctor with LifeEvent base at +0x20 plus word +0x1c
// plus int +0x38 plus byte +0x3c. align_diff exact 149B/0 structural (only vtable
// relocs); gate fails with word-vs-pre-vptr order swapped (target word before
// pre-stores, gate compiled vptr before word). Intermediate forceinline over Rva
// base folds 3 pre-stores; callees rowed 0x003AEEB3 0x003A9900. Needs EH/vptr
// order lever for volatile word vs intermediate vptrs. t=20 model=muse-03
class RvaSmartPtr12_3AEE16
{
public:
	RvaSmartPtr12_3AEE16(const RvaSmartPtr12_3AEE16 &that);
	~RvaSmartPtr12_3AEE16();
private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};
class DefaultModuleSecondBase_3AEE16
{
public:
	virtual ~DefaultModuleSecondBase_3AEE16();
};
class DefaultModuleThirdBase_3AEE16
{
public:
	virtual ~DefaultModuleThirdBase_3AEE16();
};
class DefaultModuleHeadBase_3AEE16
{
public:
	__forceinline DefaultModuleHeadBase_3AEE16(const DefaultModuleHeadBase_3AEE16 &other)
		: m_smart(other.m_smart)
		, m_int10(other.m_int10)
	{
	}
	virtual ~DefaultModuleHeadBase_3AEE16();
	RvaSmartPtr12_3AEE16 m_smart;
	int m_int10;
};
class Rva003AEEB3 : public DefaultModuleHeadBase_3AEE16, public DefaultModuleSecondBase_3AEE16, public DefaultModuleThirdBase_3AEE16
{
public:
	Rva003AEEB3(const Rva003AEEB3 &other);
	virtual ~Rva003AEEB3();
};
class WordHolder3AEE16
{
public:
	__forceinline WordHolder3AEE16(const WordHolder3AEE16 &other)
		: m_word(other.m_word)
	{
	}
	unsigned short m_word;
};
class Intermediate3AEE16 : public Rva003AEEB3, public WordHolder3AEE16
{
public:
	__forceinline Intermediate3AEE16(const Intermediate3AEE16 &other)
		: Rva003AEEB3(other)
		, WordHolder3AEE16((const WordHolder3AEE16 &)other)
	{
	}
};
namespace FXParticleSystem {
class LifeEventModuleInfo {
public:
	LifeEventModuleInfo(const LifeEventModuleInfo &other);
	virtual ~LifeEventModuleInfo();
private:
	char m_pad[0x18 - 4];
};
class TerrainCollisionModuleInfo {
public:
	TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &other);
	virtual ~TerrainCollisionModuleInfo();
private:
	char m_pad[0x1c - 4];
};
}
class Rva003AEE16 : public Intermediate3AEE16, public FXParticleSystem::LifeEventModuleInfo
{
public:
	Rva003AEE16(const Rva003AEE16 &other);
	virtual ~Rva003AEE16();
private:
	int m_38;
	unsigned char m_3c;
};
Rva003AEE16::Rva003AEE16(const Rva003AEE16 &other)
	: Intermediate3AEE16(other)
	, FXParticleSystem::LifeEventModuleInfo((const FXParticleSystem::LifeEventModuleInfo &)other)
	, m_38(other.m_38)
	, m_3c(other.m_3c)
{
}
// ??1Rva003AEE16@@UAE@XZ present-unmatched
Rva003AEE16::~Rva003AEE16() {}

class Rva003AF076 : public Intermediate3AEE16, public FXParticleSystem::TerrainCollisionModuleInfo
{
public:
	Rva003AF076(const Rva003AF076 &other);
	virtual ~Rva003AF076();
private:
	int m_3c;
	unsigned char m_40;
};
Rva003AF076::Rva003AF076(const Rva003AF076 &other)
	: Intermediate3AEE16(other)
	, FXParticleSystem::TerrainCollisionModuleInfo((const FXParticleSystem::TerrainCollisionModuleInfo &)other)
	, m_3c(other.m_3c)
	, m_40(other.m_40)
{
}
// ??1Rva003AF076@@UAE@XZ present-unmatched
Rva003AF076::~Rva003AF076() {}
