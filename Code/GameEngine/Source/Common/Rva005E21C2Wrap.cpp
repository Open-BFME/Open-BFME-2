// cl: /DNDEBUG /MD
// ?rva005E21C2@Rva005E21C2@@QAEXXZ @0x005E21C2 41B.
// Calls empty 0x00B3FD0 (pinned empty), then checks +0x28 vs +0x10 getter
// 0x005CB265 (pinned UAEHXZ) and tail-jmps to rowed 0x005CB260 on match.
// Address-derived; same shape as 0x005E0D9C plus leading empty call.
#include "../../Include/Common/Rva000B3FD0Empty.h"

#include "../../Include/Common/Rva005CB265.h"

#include "../../Include/Common/Rva005CB260.h"

class Rva005E21C2
{
public:
	void rva005E21C2();
protected:
	unsigned char m_pad[0x10];
	Rva005CB265 *m_10;
	unsigned char m_pad2[0x28 - 0x14];
	int m_28;
};

void Rva005E21C2::rva005E21C2()
{
	((Rva000B3FD0Empty *)this)->rva000B3FD0Empty();
	int v = m_28;
	if (v == 0)
		return;
	int r = m_10->Rva005CB265::rva005CB265();
	if (r != v)
		return;
	((Rva005CB260 *)m_10)->rva005CB260();
}
