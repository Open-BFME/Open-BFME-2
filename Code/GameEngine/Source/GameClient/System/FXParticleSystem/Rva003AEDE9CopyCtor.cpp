// cl: /DNDEBUG /MD /GX- /O1 /Ob2
// ??0Rva003AEDE9@@QAE@ABV0@@Z @0x003AEDE9 45B: derived copy calling rowed 0x003AEE16 then own 4 vptrs.
// Evidence: calls 0x003AEE16 then stores at +0/+0x14/+0x18/+0x20 DIR32; primary 0x00C1CF18 second 0x00C1C61C third 0x00C1CA00 fourth 0x00C1CF08; caller 0x003AEDB2; unlocks 0x003AEDB2.
// ??0Rva003AEDE9@@QAE@ABV0@@Z @0x003AEDE9 present-unmatched
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
class Rva003AEDE9 : public Rva003AEE16
{
public:
	Rva003AEDE9(const Rva003AEDE9 &other);
	virtual ~Rva003AEDE9();
};
Rva003AEDE9::Rva003AEDE9(const Rva003AEDE9 &other)
	: Rva003AEE16(other)
{
}
// ??1Rva003AEDE9@@UAE@XZ present-unmatched
Rva003AEDE9::~Rva003AEDE9() {}
