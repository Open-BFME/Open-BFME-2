// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// ?clone@Rva003AE43F@@QBEPAV1@XZ @0x003AE408 55B
// ?clone@Rva003AEB9C@@QBEPAV1@XZ @0x003AEB65 55B
// ?clone@Rva003AECE6@@QBEPAV1@XZ @0x003AECE6 88B
// ?clone@Rva003AE928@@QBEPAV1@XZ @0x003AE8F1 55B
// ??0Rva003AE928@@QAE@ABV0@@Z @0x003AE928 38B
// ??0Rva003AE94E@@QAE@ABV0@@Z @0x003AE94E 105B
//
// Particle-module template clone slots: allocate the class's own size and
// copy-construct it from the receiver, under the EH frame /EHsc gives a
// new-expression whose constructor can throw. The same shape as the rowed
// clones in Rva003AE4E5Clone.cpp and Rva003AE683Clone.cpp; sizes are the `new`
// operands and the copy constructors are the rowed ones in
// ParticleModuleInfoCopyCtors.cpp and ConcreteModuleTemplateCopyCtors.cpp.
//
// 0x003AECE6 constructs a class whose own copy constructor was inlined: one
// call to the rowed 0x003AED3E copy constructor, then its four subobject
// vtables at +0, +0x14, +0x18 and +0x1C. /O1 does not inline a constructor a
// new-expression guards, so it is spelled __forceinline (as in
// ModuleTemplateCloneSlots.cpp).
//
// 0x003AE8F1 (0x00C1CAD4#177) clones a 0x2C-byte class whose two copy
// constructors are unrowed and land here too: 0x003AE928 forwards to 0x003AE94E
// and stamps its three vtables; 0x003AE94E is the GpuDrawModuleInfo sibling of
// the rowed 0x003AE6A9 in Rva003AE6A9CopyCtor.cpp (same rowed 0x003AF50D base,
// same inlined intermediate, the rowed GpuDrawModuleInfo copy at +0x18 instead
// of RenderObjectDrawModuleInfo, and no trailing int).
//
// All are address-named after their copy constructors or their own slot; the
// vtables are 0x00C1CAD4#87, 0x00C1CE54#6 and 0x00C1CE54#43.

class Rva003AE43F
{
public:
	Rva003AE43F( const Rva003AE43F &other );
	Rva003AE43F *clone() const;

private:
	char m_storage[ 0x1c ];
};

Rva003AE43F *Rva003AE43F::clone() const
{
	return new Rva003AE43F( *this );
}

class Rva003AEB9C
{
public:
	Rva003AEB9C( const Rva003AEB9C &other );
	Rva003AEB9C *clone() const;

private:
	char m_storage[ 0x40 ];
};

Rva003AEB9C *Rva003AEB9C::clone() const
{
	return new Rva003AEB9C( *this );
}

// Retail's tables, each slot the ledger row at the native address. These constructors store them
// themselves because the compiler's own tables would name members nothing defines yet.
extern "C" {
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("??_ERva003ABA4C@@WBI@AEPAXI@Z")();
void __identifier("??_ERva003ACEF7@@WBI@AEPAXI@Z")();
void __identifier("??_GRva003ABA4C@@UAEPAXI@Z")();
void __identifier("??_GRva003ACB6F@@UAEPAXI@Z")();
void __identifier("??_GRva003ACEF7@@UAEPAXI@Z")();
void __identifier("?Rva003A5572@Rva003AED3E@@UAEXXZ")();
void __identifier("?Rva003ABBF5Get@@YAHXZ")();
void __identifier("?clone@Rva003AE928@@QBEPAV1@XZ")();
void __identifier("?clone@Rva003AECE6@@QBEPAV1@XZ")();
void __identifier("?doParticles@GpuDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z")();
void __identifier("?get@Rva00094A98FloatField@@QBEMXZ")();
void __identifier("?getData@NetWrapperCommandMsg@@QAEPAEXZ")();
void __identifier("?getDataLength@NetWrapperCommandMsg@@QAEIXZ")();
void __identifier("?rva003A5757@Rva003A5757@@UAEXPAVXfer@@@Z")();
void __identifier("?rva003AD03B@Rva003AD03BTemplate@@UAEPAVRva003AD03BModule@@I@Z")();
void __identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ")();
void __identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ")();
void __identifier("?rva0056394A@Rva0056394A@@QAE?AVAsciiString@@XZ")();
void __identifier("?xfer@Rva003AE928@@UAEXPAVXfer@@@Z")();
void __identifier("?xfer@Rva003AE94E@@WBI@AEXPAVXfer@@@Z")();
}

// VA 0x00C1CEF8
extern "C" const void *const __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot0@@@")[4] = {
	(const void *)&__identifier("??_GRva003ACB6F@@UAEPAXI@Z"), // slot 0, RVA 0x003AD3F7
	(const void *)&__identifier("?Rva003A5572@Rva003AED3E@@UAEXXZ"), // slot 1, RVA 0x003A5572
	(const void *)&__identifier("?clone@Rva003AECE6@@QBEPAV1@XZ"), // slot 2, RVA 0x003AECE6
	(const void *)&__identifier("?rva003A5757@Rva003A5757@@UAEXPAVXfer@@@Z"), // slot 3, RVA 0x003A5757
};

// VA 0x00C1C608
extern "C" const void *const __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot1@@@")[1] = {
	(const void *)&__identifier("?rva003AD03B@Rva003AD03BTemplate@@UAEPAVRva003AD03BModule@@I@Z"), // slot 0, RVA 0x003AD03B
};

// VA 0x00C1BFB4: the compiler table the FX units emit there (slot 0 is getClass).
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$06@1@@")[];

// Native Wind constructor operand0x003A58DC independently binds this
// existing compiler table at0x0081CEE8. Its slot identities still need the bridge.
extern "C" const void *const __identifier("??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50WindInfoBase@1@@")[4];

// VA 0x00C1D588
extern "C" const void *const g_gpuDrawBaseTable00[11] = {
	(const void *)&__identifier("??_GRva003ABA4C@@UAEPAXI@Z"), // slot 0, RVA 0x003AE9BF
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 1, RVA 0x000B3FD0
	(const void *)&_purecall, // slot 2, RVA 0x0003B810
	(const void *)&__identifier("?xfer@Rva003AE928@@UAEXPAVXfer@@@Z"), // slot 3, RVA 0x00563965
	(const void *)&__identifier("?doParticles@GpuDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z"), // slot 4, RVA 0x005639A4
	(const void *)&__identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ"), // slot 5, RVA 0x00560ABA
	(const void *)&__identifier("?rva0056394A@Rva0056394A@@QAE?AVAsciiString@@XZ"), // slot 6, RVA 0x0056394A
	(const void *)&__identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ"), // slot 7, RVA 0x0055C44F
	(const void *)&__identifier("?getData@NetWrapperCommandMsg@@QAEPAEXZ"), // slot 8, RVA 0x0030F2C7
	(const void *)&__identifier("?getDataLength@NetWrapperCommandMsg@@QAEIXZ"), // slot 9, RVA 0x0030D377
	(const void *)&__identifier("?get@Rva00094A98FloatField@@QBEMXZ"), // slot 10, RVA 0x00094A98
};

// VA 0x00C1C780: the shared one-pure-slot table, which the FX units emit as
// CategoryModuleInfo<N>'s, one name for each category folded there.
extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];

// VA 0x00C1D5B4
extern "C" const void *const g_gpuDrawBaseTable18[4] = {
	(const void *)&__identifier("??_ERva003ABA4C@@WBI@AEPAXI@Z"), // slot 0, RVA 0x003AE9B7
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 1, RVA 0x000B3FD0
	(const void *)&__identifier("?Rva003ABBF5Get@@YAHXZ"), // slot 2, RVA 0x003ABBF5
	(const void *)&__identifier("?xfer@Rva003AE94E@@WBI@AEXPAVXfer@@@Z"), // slot 3, RVA 0x003ABBFB
};

// VA 0x00C1CD90
extern "C" const void *const g_gpuDrawTable00[11] = {
	(const void *)&__identifier("??_GRva003ACEF7@@UAEPAXI@Z"), // slot 0, RVA 0x003ACEDB
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 1, RVA 0x000B3FD0
	(const void *)&__identifier("?clone@Rva003AE928@@QBEPAV1@XZ"), // slot 2, RVA 0x003AE8F1
	(const void *)&__identifier("?xfer@Rva003AE928@@UAEXPAVXfer@@@Z"), // slot 3, RVA 0x00563965
	(const void *)&__identifier("?doParticles@GpuDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z"), // slot 4, RVA 0x005639A4
	(const void *)&__identifier("?rva00560ABA@Rva00560ABA@@QAE?AVAsciiString@@XZ"), // slot 5, RVA 0x00560ABA
	(const void *)&__identifier("?rva0056394A@Rva0056394A@@QAE?AVAsciiString@@XZ"), // slot 6, RVA 0x0056394A
	(const void *)&__identifier("?rva0055C44F@Rva0055C44F@@QAEHXZ"), // slot 7, RVA 0x0055C44F
	(const void *)&__identifier("?getData@NetWrapperCommandMsg@@QAEPAEXZ"), // slot 8, RVA 0x0030F2C7
	(const void *)&__identifier("?getDataLength@NetWrapperCommandMsg@@QAEIXZ"), // slot 9, RVA 0x0030D377
	(const void *)&__identifier("?get@Rva00094A98FloatField@@QBEMXZ"), // slot 10, RVA 0x00094A98
};

// VA 0x00C1C290: the compiler table the FX units emit there (slot 0 is getClass).
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?GPU_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?GPU_DRAW_MODULE_NAME@2@3QBDBVGpuDrawModule@2@VGpuDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@")[];

// VA 0x00C1CD80
extern "C" const void *const g_gpuDrawTable18[4] = {
	(const void *)&__identifier("??_ERva003ACEF7@@WBI@AEPAXI@Z"), // slot 0, RVA 0x003ABC03
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 1, RVA 0x000B3FD0
	(const void *)&__identifier("?Rva003ABBF5Get@@YAHXZ"), // slot 2, RVA 0x003ABBF5
	(const void *)&__identifier("?xfer@Rva003AE94E@@WBI@AEXPAVXfer@@@Z"), // slot 3, RVA 0x003ABBFB
};

class Rva003AED3E
{
public:
	Rva003AED3E( const Rva003AED3E &other );

private:
	char m_storage00[ 0x20 ];
};

class Rva003AECE6 : public Rva003AED3E
{
public:
	__forceinline Rva003AECE6( const Rva003AECE6 &other ) : Rva003AED3E( other )
	{
		*(const void *const **)((char *)this + 0x00) = __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot0@@@");
		*(const void *const **)((char *)this + 0x14) = __identifier("??_7Rva003AECE6@@6BRva003AECE6Slot1@@@");
		*(const void *const **)((char *)this + 0x18) = __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$06@1@@");
		*(const void *const **)((char *)this + 0x1C) = __identifier("??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50WindInfoBase@1@@");
	}
	Rva003AECE6 *clone() const;

private:
	char m_storage[ 0x64 - sizeof( Rva003AED3E ) ];
};

Rva003AECE6 *Rva003AECE6::clone() const
{
	return new Rva003AECE6( *this );
}

class RvaSmartPtr12_3AE94E
{
public:
	RvaSmartPtr12_3AE94E( const RvaSmartPtr12_3AE94E &that );
	~RvaSmartPtr12_3AE94E();

private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class ModuleInfoSecondBase_3AE94E
{
public:
	virtual ~ModuleInfoSecondBase_3AE94E();
};

class ModuleInfoHeadBase_3AE94E
{
public:
	ModuleInfoHeadBase_3AE94E( const ModuleInfoHeadBase_3AE94E &other )
		: m_smart( other.m_smart )
		, m_int10( other.m_int10 )
	{
	}
	virtual ~ModuleInfoHeadBase_3AE94E();

	RvaSmartPtr12_3AE94E m_smart;
	int m_int10;
};

class Rva003AF50D : public ModuleInfoHeadBase_3AE94E, public ModuleInfoSecondBase_3AE94E
{
public:
	Rva003AF50D( const Rva003AF50D &other );
	virtual ~Rva003AF50D();
};

class ParticleModule005F2CA0 : public Rva003AF50D
{
public:
    ParticleModule005F2CA0(void *, void *);
	__forceinline ParticleModule005F2CA0( const ParticleModule005F2CA0 &other )
		: Rva003AF50D( other )
	{
	}
	virtual ~ParticleModule005F2CA0();
};

#define BFME_SNAPSHOT_CONSTRUCTOR_ONLY
#include "../../../../Include/GameClient/GpuDrawModuleInfo.h"

class __declspec(novtable) Rva003AE94E : public ParticleModule005F2CA0, public FXParticleSystem::GpuDrawModuleInfo
{
public:
	Rva003AE94E( const Rva003AE94E &other );
    Rva003AE94E(void *, void *);
};

Rva003AE94E::Rva003AE94E( const Rva003AE94E &other )
	: ParticleModule005F2CA0( other )
	, FXParticleSystem::GpuDrawModuleInfo( (const FXParticleSystem::GpuDrawModuleInfo &)other )
{
	*(const void *const **)((char *)this + 0x18) = g_gpuDrawBaseTable18;
	*(const void *const **)((char *)this + 0x00) = g_gpuDrawBaseTable00;
	*(const void *const **)((char *)this + 0x14) = __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@");
}

class __declspec(novtable) Rva003AE928 : public Rva003AE94E
{
public:
	Rva003AE928( const Rva003AE928 &other );
	Rva003AE928 *clone() const;
};

Rva003AE928::Rva003AE928( const Rva003AE928 &other )
	: Rva003AE94E( other )
{
	*(const void *const **)((char *)this + 0x00) = g_gpuDrawTable00;
	*(const void *const **)((char *)this + 0x14) = __identifier("??_7?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?GPU_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?GPU_DRAW_MODULE_NAME@2@3QBDBVGpuDrawModule@2@VGpuDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@");
	*(const void *const **)((char *)this + 0x18) = g_gpuDrawTable18;
}

Rva003AE928 *Rva003AE928::clone() const
{
	return new Rva003AE928( *this );
}

struct GpuInput3CAF {char unknown00[12];int frames,framesPerRow;AsciiString detail;float speed;};
Rva003AE94E::Rva003AE94E(void *first,void *second):ParticleModule005F2CA0(first,second),FXParticleSystem::GpuDrawModuleInfo(){
 *(const void *const **)((char *)this + 0x00) = g_gpuDrawBaseTable00;
 *(const void *const **)((char *)this + 0x14) = __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@");
 *(const void *const **)((char *)this + 0x18) = g_gpuDrawBaseTable18;
 const GpuInput3CAF &input=*(const GpuInput3CAF *)second;
 m_04=input.frames;
 m_08=input.framesPerRow;
 m_0C=input.detail;
 m_10=input.speed;
}

__declspec(noinline) FXParticleSystem::GpuDrawModuleInfo::GpuDrawModuleInfo():m_04(1),m_08(1){m_10=1.0f;}
