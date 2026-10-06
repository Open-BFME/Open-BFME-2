// cl: /MD /EHsc
//
// ?rva00342120@Rva00341F99@@UAEXH@Z, retail 0x00342120, 55 bytes.
// Slot 5 (offset 0x14) of vtable 0x00811850 (class of ??1Rva00341F99@@UAE@XZ,
// rowed in Rva00341F99Dtor.cpp, same // cl: line) and also of twin vtable
// 0x008117F0 (class of ??1Rva00341E70@@UAE@XZ); both slots share this body.
// Shape: delete m_ptr20 when present through slot-0
// scalarDeletingDestructor(0) plus operator delete with the null->0 ternary
// (rowed ??3@YAXPAX@Z 0x0002FD60, caller cleanup via pop ecx), null it with
// `and [m],0`, then chase m_ptr18+0x14+0x258 and call vtable slot 0x1F0.
// The 4-byte arg (ret 4) is never read; int/void are code-neutral guesses.
// Chain types are TU-local pads: only the slot indices and offsets are
// evidence-backed. Family context (TurretStateMachine members at +0x18/+0x20)
// per Rva00341E70VSlot.cpp.

void __cdecl operator delete(void *ptr);

class Rva00341F99Slot5Member
{
public:
	virtual void *scalarDeletingDestructor(unsigned int flags);
};

class Slot5Final
{
public:
	virtual void _s5p000();
	virtual void _s5p001();
	virtual void _s5p002();
	virtual void _s5p003();
	virtual void _s5p004();
	virtual void _s5p005();
	virtual void _s5p006();
	virtual void _s5p007();
	virtual void _s5p008();
	virtual void _s5p009();
	virtual void _s5p010();
	virtual void _s5p011();
	virtual void _s5p012();
	virtual void _s5p013();
	virtual void _s5p014();
	virtual void _s5p015();
	virtual void _s5p016();
	virtual void _s5p017();
	virtual void _s5p018();
	virtual void _s5p019();
	virtual void _s5p020();
	virtual void _s5p021();
	virtual void _s5p022();
	virtual void _s5p023();
	virtual void _s5p024();
	virtual void _s5p025();
	virtual void _s5p026();
	virtual void _s5p027();
	virtual void _s5p028();
	virtual void _s5p029();
	virtual void _s5p030();
	virtual void _s5p031();
	virtual void _s5p032();
	virtual void _s5p033();
	virtual void _s5p034();
	virtual void _s5p035();
	virtual void _s5p036();
	virtual void _s5p037();
	virtual void _s5p038();
	virtual void _s5p039();
	virtual void _s5p040();
	virtual void _s5p041();
	virtual void _s5p042();
	virtual void _s5p043();
	virtual void _s5p044();
	virtual void _s5p045();
	virtual void _s5p046();
	virtual void _s5p047();
	virtual void _s5p048();
	virtual void _s5p049();
	virtual void _s5p050();
	virtual void _s5p051();
	virtual void _s5p052();
	virtual void _s5p053();
	virtual void _s5p054();
	virtual void _s5p055();
	virtual void _s5p056();
	virtual void _s5p057();
	virtual void _s5p058();
	virtual void _s5p059();
	virtual void _s5p060();
	virtual void _s5p061();
	virtual void _s5p062();
	virtual void _s5p063();
	virtual void _s5p064();
	virtual void _s5p065();
	virtual void _s5p066();
	virtual void _s5p067();
	virtual void _s5p068();
	virtual void _s5p069();
	virtual void _s5p070();
	virtual void _s5p071();
	virtual void _s5p072();
	virtual void _s5p073();
	virtual void _s5p074();
	virtual void _s5p075();
	virtual void _s5p076();
	virtual void _s5p077();
	virtual void _s5p078();
	virtual void _s5p079();
	virtual void _s5p080();
	virtual void _s5p081();
	virtual void _s5p082();
	virtual void _s5p083();
	virtual void _s5p084();
	virtual void _s5p085();
	virtual void _s5p086();
	virtual void _s5p087();
	virtual void _s5p088();
	virtual void _s5p089();
	virtual void _s5p090();
	virtual void _s5p091();
	virtual void _s5p092();
	virtual void _s5p093();
	virtual void _s5p094();
	virtual void _s5p095();
	virtual void _s5p096();
	virtual void _s5p097();
	virtual void _s5p098();
	virtual void _s5p099();
	virtual void _s5p100();
	virtual void _s5p101();
	virtual void _s5p102();
	virtual void _s5p103();
	virtual void _s5p104();
	virtual void _s5p105();
	virtual void _s5p106();
	virtual void _s5p107();
	virtual void _s5p108();
	virtual void _s5p109();
	virtual void _s5p110();
	virtual void _s5p111();
	virtual void _s5p112();
	virtual void _s5p113();
	virtual void _s5p114();
	virtual void _s5p115();
	virtual void _s5p116();
	virtual void _s5p117();
	virtual void _s5p118();
	virtual void _s5p119();
	virtual void _s5p120();
	virtual void _s5p121();
	virtual void _s5p122();
	virtual void _s5p123();
	virtual void method1F0();
};

class Slot5Mid
{
public:
	char m_pad00[0x258];
	Slot5Final *m_ptr258;
};

class Rva00341F99Ref18
{
public:
	char m_pad00[0x14];
	Slot5Mid *m_ptr14;
};

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C();

private:
	char m_pad04[8];
};

class Rva00341F99 : public Rva0049B47C
{
public:
	virtual void _s01();
	virtual void _s02();
	virtual void _s03();
	virtual void _s04();
	virtual void rva00342120(int);

private:
	char m_pad0C[0x18 - 0x0C];
	Rva00341F99Ref18 *m_ptr18;
	char m_pad1C[0x20 - 0x1C];
	Rva00341F99Slot5Member *m_ptr20;
};

void Rva00341F99::rva00342120(int)
{
	::operator delete(m_ptr20 != 0 ? m_ptr20->scalarDeletingDestructor(0) : 0);
	m_ptr20 = 0;
	m_ptr18->m_ptr14->m_ptr258->method1F0();
}
