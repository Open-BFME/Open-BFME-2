// cl: /arch:SSE /G7 /O1 /DNDEBUG /MD /EHsc
// 0x003AEE16 149B unlock: copy ctor with LifeEvent base at +0x20 plus word +0x1c
// plus int +0x38 plus byte +0x3c. align_diff exact 149B/0 structural (only vtable
// relocs); gate fails with word-vs-pre-vptr order swapped (target word before
// pre-stores, gate compiled vptr before word). Intermediate forceinline over Rva
// base folds 3 pre-stores; callees rowed 0x003AEEB3 0x003A9900. Needs EH/vptr
// order lever for volatile word vs intermediate vptrs. t=20 model=muse-03
class RvaSmartPtr12;
struct Rva005648FEInput;
class GameClientRandomVariable {public:float getValue()const;int mode;float minimum,maximum;};
class FXList;
class Rva0056468E {public:const FXList *rva0056468E();};
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
class Rva005641BB : public Rva003AEEB3, public WordHolder3AEE16
{
public:
	Rva005641BB(const RvaSmartPtr12&,int);
	__forceinline Rva005641BB(const Rva005641BB &other)
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
	TerrainCollisionModuleInfo();
	TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &other);
	virtual ~TerrainCollisionModuleInfo();
public:
 // Existing info constructor56459E independently places string04 and mode/range08.
 void*unknown04;GameClientRandomVariable eventTime;bool flag;char unknown15[3];const FXList*cached;
};
}
class Rva003AEE16 : public Rva005641BB, public FXParticleSystem::LifeEventModuleInfo
{
public:
	Rva003AEE16(const Rva003AEE16 &other);
	virtual ~Rva003AEE16();
private:
	int m_38;
	unsigned char m_3c;
};
Rva003AEE16::Rva003AEE16(const Rva003AEE16 &other)
	: Rva005641BB(other)
	, FXParticleSystem::LifeEventModuleInfo((const FXParticleSystem::LifeEventModuleInfo &)other)
	, m_38(other.m_38)
	, m_3c(other.m_3c)
{
}
// ??1Rva003AEE16@@UAE@XZ present-unmatched
Rva003AEE16::~Rva003AEE16() {}

class Rva003AF076 : public Rva005641BB, public FXParticleSystem::TerrainCollisionModuleInfo
{
public:
	Rva003AF076(const Rva003AF076 &other);
 Rva003AF076(const RvaSmartPtr12&,const Rva005648FEInput&);
	virtual ~Rva003AF076();
private:
	int m_3c;
	unsigned char m_40;
};
Rva003AF076::Rva003AF076(const Rva003AF076 &other)
	: Rva005641BB(other)
	, FXParticleSystem::TerrainCollisionModuleInfo((const FXParticleSystem::TerrainCollisionModuleInfo &)other)
	, m_3c(other.m_3c)
	, m_40(other.m_40)
{
}
// ??1Rva003AF076@@UAE@XZ present-unmatched
Rva003AF076::~Rva003AF076() {}

// ??0Gen005ED0D0@@QAE@PAVHost005ED050@@@Z @0x003AF049 45B: derived ctor calling rowed base 0x003AF076 then own 4 vptrs.
// Evidence: calls 0x003AF076 rowed copy then stores at +0/+0x14/+0x18/+0x20 DIR32;
// same 45B shape as rowed Gen005EDB10 @0x003AF645 calling 0x003AF672; caller 0x003AF012 create;
// LINK BONUS 1 file 110B; Q4 size 0x44 matches Rva003AF076 size.
class Host005ED050;
class Gen005ED0D0 : public Rva003AF076
{
public:
	Gen005ED0D0(Host005ED050 *owner);
	virtual ~Gen005ED0D0();
};

Gen005ED0D0::Gen005ED0D0(Host005ED050 *owner)
	: Rva003AF076(*(const Rva003AF076 *)owner)
{
}

struct Rva005648FEInput {char unknown00[8];bool a,b;char unknown0A[10];GameClientRandomVariable eventTime;bool flag;};
// Native5648FE..56499B, owner established by existing Rva003AF076 vtable
// and copy ctor3AF076. Target base5641BB, info20/time28/cache38/count3C/active40.
Rva003AF076::Rva003AF076(const RvaSmartPtr12&smart,const Rva005648FEInput&input)
 :Rva005641BB(smart,(int)&input),FXParticleSystem::TerrainCollisionModuleInfo()
{
 eventTime=input.eventTime;
 cached=((Rva0056468E*)((char*)&input+0xC))->rva0056468E();
 flag=input.flag;
 ((bool*)&m_word)[0]=input.a;
 ((bool*)&m_word)[1]=input.b;
 m_3c=(int)eventTime.getValue();
 m_40=true;
}
