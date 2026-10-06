// cl: /MD
// ??1Rva003AEEB3@@UAE@XZ @0x003A5817 39B: derived dtor two null-guarded vptr stores plus tail-jmp to head base.
// Evidence: stores extern s_slot3E4first at +0x18/+0x14 via neg sbb and tail-jmp to rowed ??1DefaultModuleHeadBase 0x003A57E7; donor stash 0x003a5817 score 0.92; callers include 0x003AEEFF and thunks.
extern "C" const void *const vtbl_00C1C780[];  // folded, 35 classes; via ??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C1C780=??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")

extern "C" char s_slot3E4first;

#pragma intrinsic(_ReadWriteBarrier)

struct RvaSmartPtr12
{
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};
class DefaultModuleHeadBase
{
public:
	virtual ~DefaultModuleHeadBase();
private:
	RvaSmartPtr12 m_smart;
	int m_int10;
};
class __declspec(novtable) Rva003AEEB3 : public DefaultModuleHeadBase
{
public:
	virtual ~Rva003AEEB3();
};
Rva003AEEB3::~Rva003AEEB3()
{
	unsigned char *b18 = this ? (unsigned char *)this + 0x18 : 0;
	*(volatile unsigned int *)b18 = (unsigned int)&s_slot3E4first;
	unsigned char *b14 = this ? (unsigned char *)this + 0x14 : 0;
	*(volatile unsigned int *)b14 = ((unsigned int)vtbl_00C1C780);
}
