// cl: /MD
// ?rva0023D26F@Rva0023D26F@@QAEX_N@Z, retail 0x0023D26F, 48 bytes.
// push esi mov esi ecx vcall +0x24 inc [esi+0x38] TheNetwork null-check vcall +0x38 byte [esi+0x3c]=0 cond byte [esi+0x9d]=1 ret 4.
// Evidence: leaf lane; callers 0x002BE596 0x002BE674 0x00377B30; global VA 0xdfea28 TheNetwork; members +0x38 +0x3c +0x9d.
#include "../../Include/GameNetwork/NetworkInterfaceClass.h"
extern NetworkInterface *TheNetwork;
class Rva0023D26F
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	void rva0023D26F(bool flag);
private:
	char m_pad04[0x34];
	int m_38;
	unsigned char m_3c;
	char m_pad3d[0x9d - 0x3d];
	unsigned char m_9d;
};
void Rva0023D26F::rva0023D26F(bool flag)
{
	++m_38;
	v09();
	if (TheNetwork != 0)
		TheNetwork->startNewSession();
	m_3c = 0;
	if (flag)
		m_9d = 1;
}
