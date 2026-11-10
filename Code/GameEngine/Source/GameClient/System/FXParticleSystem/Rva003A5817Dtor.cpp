// cl: /MD
// ??1Rva003AEEB3@@UAE@XZ @0x003A5817 39B: derived dtor two null-guarded vptr stores plus tail-jmp to head base.
// Evidence: stores extern 0x00C1C780 at +0x18/+0x14 via neg sbb and tail-jmp to rowed ??1DefaultModuleHeadBase 0x003A57E7; donor stash 0x003a5817 score 0.92; callers include 0x003AEEFF and thunks.
extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];  // folded, 35 classes

extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");

#pragma intrinsic(_ReadWriteBarrier)

#include "../../../../Include/Common/RvaSmartPtr12.h"
#include "../../../../Include/GameClient/DefaultModuleHeadBase.h"
class __declspec(novtable) Rva003AEEB3 : public DefaultModuleHeadBase
{
public:
	virtual ~Rva003AEEB3();
};
Rva003AEEB3::~Rva003AEEB3()
{
	unsigned char *b18 = this ? (unsigned char *)this + 0x18 : 0;
	*(volatile unsigned int *)b18 = (unsigned int)&__identifier("??_7Rva003F498ACallback@@6B@");
	unsigned char *b14 = this ? (unsigned char *)this + 0x14 : 0;
	*(volatile unsigned int *)b14 = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
}
