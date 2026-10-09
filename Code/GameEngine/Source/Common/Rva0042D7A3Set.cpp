// cl: /MD
// ?rva0042D7A3@Rva0042D7A3@@QAEXPAVEndTurnButtonImpl@StrategicHUD@@@Z @0x0042D7A3 35B: set holder at +0 clearing old via dtor plus delete.
// Evidence: calls rowed dtor 0x005794ED plus rowed delete 0x0002FD60; caller 0x0042DAF0; prev Rva0042D71ACond.
namespace StrategicHUD
{
class EndTurnButtonImpl
{
public:
	~EndTurnButtonImpl();
};
}

class Rva0042D7A3
{
public:
	void rva0042D7A3(StrategicHUD::EndTurnButtonImpl *newPtr);
	void rva0042D7C6();
private:
	StrategicHUD::EndTurnButtonImpl *m_00;
};

void operator delete(void *p);

void Rva0042D7A3::rva0042D7A3(StrategicHUD::EndTurnButtonImpl *newPtr)
{
	StrategicHUD::EndTurnButtonImpl *old = m_00;
	if (newPtr == old)
		return;
	m_00 = newPtr;
	if (old == 0)
		return;
	old->StrategicHUD::EndTurnButtonImpl::~EndTurnButtonImpl();
	operator delete(old);
}

void Rva0042D7A3::rva0042D7C6()
{
	StrategicHUD::EndTurnButtonImpl *old = m_00;
	m_00 = 0;
	if (old == 0)
		return;
	old->StrategicHUD::EndTurnButtonImpl::~EndTurnButtonImpl();
	operator delete(old);
}
