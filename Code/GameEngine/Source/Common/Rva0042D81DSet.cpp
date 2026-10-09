// cl: /MD
// ?rva0042D81D@Rva0042D81D@@QAEXPAVChecklistUIImpl@StrategicHUD@@@Z @0x0042D81D 35B: set holder at +0 clearing old via dtor plus delete.
// Evidence: calls rowed dtor 0x0057AD6E plus rowed delete 0x0002FD60; caller 0x0042DA51; sibling Rva0042D7E0Set.
namespace StrategicHUD {class ChecklistUIImpl;}
using StrategicHUD::ChecklistUIImpl;
class StrategicHUD::ChecklistUIImpl
{
public:
	virtual ~ChecklistUIImpl();
};

void operator delete(void *p);

class Rva0042D81D
{
public:
	void rva0042D81D(ChecklistUIImpl *newPtr);
	void rva0042D840();
private:
	ChecklistUIImpl *m_00;
};

void Rva0042D81D::rva0042D81D(ChecklistUIImpl *newPtr)
{
	ChecklistUIImpl *old = m_00;
	if (newPtr == old)
		return;
	m_00 = newPtr;
	if (old == 0)
		return;
	old->ChecklistUIImpl::~ChecklistUIImpl();
	operator delete(old);
}

void Rva0042D81D::rva0042D840()
{
	ChecklistUIImpl *old = m_00;
	m_00 = 0;
	if (old == 0)
		return;
	old->ChecklistUIImpl::~ChecklistUIImpl();
	operator delete(old);
}
