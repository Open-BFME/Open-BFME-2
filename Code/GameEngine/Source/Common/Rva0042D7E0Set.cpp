// cl: /MD
// ?rva0042D7E0@Rva0042D7E0@@QAEXPAVStatsDisplayImpl@StrategicHUD@@@Z @0x0042D7E0 35B: set holder at +0 clearing old via dtor plus delete.
// Evidence: calls rowed dtor 0x00579AB7 plus rowed delete 0x0002FD60; caller 0x0042DF98; sibling Rva0042D7A3Set.
namespace StrategicHUD {
class StatsDisplayImpl;
}

class StrategicHUD::StatsDisplayImpl
{
public:
	virtual ~StatsDisplayImpl();
};

void operator delete(void *p);

class Rva0042D7E0
{
public:
	void rva0042D7E0(StrategicHUD::StatsDisplayImpl *newPtr);
	void rva0042D803();
private:
	StrategicHUD::StatsDisplayImpl *m_00;
};

void Rva0042D7E0::rva0042D7E0(StrategicHUD::StatsDisplayImpl *newPtr)
{
	StrategicHUD::StatsDisplayImpl *old = m_00;
	if (newPtr == old)
		return;
	m_00 = newPtr;
	if (old == 0)
		return;
	old->StrategicHUD::StatsDisplayImpl::~StatsDisplayImpl();
	operator delete(old);
}

void Rva0042D7E0::rva0042D803()
{
	StrategicHUD::StatsDisplayImpl *old = m_00;
	m_00 = 0;
	if (old == 0)
		return;
	old->StrategicHUD::StatsDisplayImpl::~StatsDisplayImpl();
	operator delete(old);
}
