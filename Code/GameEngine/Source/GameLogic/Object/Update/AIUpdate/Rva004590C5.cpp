// cl: /DNDEBUG /MD
//
// ?rva004590C5@Rva004590C5@@QAEXXZ, retail 0x004590C5 33B. Chain via 0x0045906E.
// m_20 = m_04->v8 plus rva0045906E(true) on same this plus
// UpdateModule::setWakeFrame(m_08, UPDATE_SLEEP_NONE). Prev 0x45906E.
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

#include "../../../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../../../Include/GameLogic/Module/Rva0045906E.h"

struct Rva004590C5Helper
{
	unsigned char m_pad[8];
	float m_v8;
};

class Rva004590C5 : public UpdateModule
{
public:
	void rva004590C5();
	void rva004590E6();
private:
	float m_20;
};

void Rva004590C5::rva004590C5()
{
	m_20 = ((const Rva004590C5Helper *)getModuleData())->m_v8;
	((Rva0045906E *)this)->rva0045906E(true);
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}

// ?rva004590E6@Rva004590C5@@QAEXXZ, retail 0x004590E6 35B. Chain via 0x0045906E.
// m_20 = 0.0f plus rva0045906E(false) on same this plus
// UpdateModule::setWakeFrame(m_08, UPDATE_SLEEP_FOREVER).
void Rva004590C5::rva004590E6()
{
	m_20 = 0.0f;
	((Rva0045906E *)this)->rva0045906E(false);
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
