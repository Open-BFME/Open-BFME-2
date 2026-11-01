// cl: /DNDEBUG /MD /EHsc
// ?rva005748F2@Rva005748F2@@QAEXXZ retail 0x005748F2 30 bytes.
// Holder at +0x54 with flag at +0x58; null ptr returns; flag set tail-calls
// virtual slot1 on the held pointer else tail-jmps to pinned clear.
// Evidence: pinned ?clear@Rva000AD6F4@@QAEXXZ at 0x000AD6F4; caller 0x00575038
// calls it then clears [esi+0x58]; cmp eax -1 in 0x005E5920 style sentinels.
class Pointee
{
public:
	virtual void slot0(int);
	virtual void slot1();
};

#include "../../../Include/Common/Rva000AD6F4.h"

class Rva005748F2
{
public:
	void rva005748F2();

private:
	char m_pad[0x54];
	Rva000AD6F4 m_holder;
	bool m_flag;
};

void Rva005748F2::rva005748F2()
{
	Pointee *pointee = (Pointee *)m_holder.m_ptr;
	if (!pointee)
		return;
	if (m_flag)
		pointee->slot1();
	else
		m_holder.clear();
}
