// cl: /DNDEBUG /MD
// ?rva00528BDD@Rva00528BDD@@QAEXXZ retail 0x00528BDD 36B
// Evidence: UI invoke via 0x00222A8B with HideCostModifierUpgradeInterface plus global 0x009FE4CC; clears +4; callers 0x00528F30 0x0052914B
#include "../../Include/Common/Rva00222A8BTarget.h"

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00528BDD
{
public:
	void rva00528BDD();
private:
	void *m_owner;
	bool m_flag04;
};

void Rva00528BDD::rva00528BDD()
{
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_owner, "HideCostModifierUpgradeInterface", 0, 0, 0, 0, 0, 0);
	m_flag04 = false;
}

#include "../../Include/Common/Rva00528B98.h"

void Rva00528B98::rva00528B98()
{
	if (!m_flag04)
		return;
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_owner, "HideRankInterface", 0, 0, 0, 0, 0, 0);
	m_flag04 = false;
}

class Rva00528BC1
{
public:
	Rva00528BC1 *rva00528BC1(void *p);
private:
	void *m_ptr;
	unsigned char m_04;
	unsigned char m_05;
	unsigned char m_06;
	int m_08;
	int m_0C;
};

Rva00528BC1 *Rva00528BC1::rva00528BC1(void *p)
{
	m_ptr = p;
	m_04 = 0;
	m_05 = 0;
	m_06 = 0;
	m_08 = 0;
	m_0C = 0;
	return this;
}
