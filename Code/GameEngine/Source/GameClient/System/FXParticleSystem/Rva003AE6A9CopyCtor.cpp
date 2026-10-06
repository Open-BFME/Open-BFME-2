// cl: /DNDEBUG /MD /EHsc
// ??0Rva003AE6A9@@QAE@ABV0@@Z @0x003AE6A9 111B
// Copy ctor with RenderObjectDrawModuleInfo base at +0x18 plus int at +0x58.
// Calls rowed base 0x003AF50D then rowed RenderObject copy 0x003A9AD6 with
// neg/sbb/and null-guarded source adjustment to +0x18; vptrs at +0/+0x14/+0x18
// DIR32; +0x58 int copied directly. Intermediate forceinline over Rva base
// folds the 2 pre-stores; caller 0x003AE683 installs own 3 vptrs.
// Evidence: unlock lane; callees rowed; pre/post vptr pattern matches
// Rva003AF5AC 98B family; unblocks 0x003AE683.
class RvaSmartPtr12_3AE6A9
{
public:
	RvaSmartPtr12_3AE6A9(const RvaSmartPtr12_3AE6A9 &that);
	~RvaSmartPtr12_3AE6A9();
private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};
class ModuleInfoSecondBase_3AE6A9
{
public:
	virtual ~ModuleInfoSecondBase_3AE6A9();
};
class ModuleInfoHeadBase_3AE6A9
{
public:
	ModuleInfoHeadBase_3AE6A9(const ModuleInfoHeadBase_3AE6A9 &other)
		: m_smart(other.m_smart)
		, m_int10(other.m_int10)
	{
	}
	virtual ~ModuleInfoHeadBase_3AE6A9();
	RvaSmartPtr12_3AE6A9 m_smart;
	int m_int10;
};
class Rva003AF50D : public ModuleInfoHeadBase_3AE6A9, public ModuleInfoSecondBase_3AE6A9
{
public:
	Rva003AF50D(const Rva003AF50D &other);
	virtual ~Rva003AF50D();
};
class Intermediate3AE6A9 : public Rva003AF50D
{
public:
	__forceinline Intermediate3AE6A9(const Intermediate3AE6A9 &other)
		: Rva003AF50D(other)
	{
	}
	virtual ~Intermediate3AE6A9();
};
namespace FXParticleSystem {
class RenderObjectDrawModuleInfo {
public:
	RenderObjectDrawModuleInfo(const RenderObjectDrawModuleInfo &other);
	virtual ~RenderObjectDrawModuleInfo();
private:
	char m_pad[0x40 - 4];
};
}
class Rva003AE6A9 : public Intermediate3AE6A9, public FXParticleSystem::RenderObjectDrawModuleInfo {
public:
	Rva003AE6A9(const Rva003AE6A9 &other);
	virtual ~Rva003AE6A9();
private:
	int m_58;
};
Rva003AE6A9::Rva003AE6A9(const Rva003AE6A9 &other)
	: Intermediate3AE6A9(other)
	, FXParticleSystem::RenderObjectDrawModuleInfo((const FXParticleSystem::RenderObjectDrawModuleInfo &)other)
	, m_58(other.m_58)
{
}
