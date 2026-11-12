// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?rva0056D9C1@Rva0056D9C1@@QAEHHII@Z @0x0056D9C1 78B evidence: REF table slot RVA 0x0086DB48 neighbours deleting dtor; tail-jmp to pinned base 0x0051274F _bfme_AptGameWindow slot2; global g_00DFEF18 VA 0x00DFEF18; msg 0x1b dispatcher returning 1
#include "../../Include/GameClient/_bfme_AptGameWindow.h"

class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;

class HostView
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void slot10(int v);
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
	virtual void w17();
	virtual void w18();
	virtual void w19();
	virtual void slot20(int v);
	char m_pad[0x14];
	unsigned char m_18;
	unsigned char m_19;
};

class Rva0056D9C1
{
public:
	int rva0056D9C1(int a, unsigned int b, unsigned int c);
};

int Rva0056D9C1::rva0056D9C1(int a, unsigned int b, unsigned int c)
{
	if (a != 0x1b)
		return ((_bfme_AptGameWindow *)this)->rva0051274F(a, b, c);
	HostView *hostView = (HostView *)((Rva002D3627Host *)TheLivingWorld);
	if (b != 0) {
		if (hostView->m_19 != 0 && hostView->m_18 != 0)
			return 1;
		hostView->slot20(1);
		((HostView *)((Rva002D3627Host *)TheLivingWorld))->slot10(1);
		return 1;
	} else {
		if (hostView->m_19 == 0)
			return 1;
		hostView->slot10(b);
		return 1;
	}
}
