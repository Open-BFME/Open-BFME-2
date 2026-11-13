// cl: /MD
// ?rva002B280C@Rva002B280C@@QAE_NPAUArg54@@@Z @0x002B280C 40B.
// Chain on 0x002B254F with one arg: if this->check==0 return true else
// global lookup virtual +0x14 on the arg.
// Evidence: retail call 0x2B254F/test al je true/mov ecx[g_00E02D6C]/call 0x3B8BAA/
// push [esp+4]/mov edx[eax]/mov ecx eax/call [edx+14]/test al je end/mov al 1/ret 4.
// Callers at 0x002B283F 0x005E914E 0x005F56D0. ecx passes through from thiscall.
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

#include "../../Include/Common/Rva002B254F.h"

#include "../../Include/Common/LivingWorldCampaignManager.h"

#include "../../Include/Common/Arg54.h"

class LookupVirt14
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual bool check(Arg54 *a);
};

#include "../../Include/Common/Rva002B280C.h"

bool Rva002B280C::rva002B280C(Arg54 *army)
{
	if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0)
	{
		void *campaign = ((LivingWorldCampaignManager *)TheCampaignManager)->rva003B8BAA();
		if (!((LookupVirt14 *)campaign)->check(army))
			return false;
	}
	return true;
}
