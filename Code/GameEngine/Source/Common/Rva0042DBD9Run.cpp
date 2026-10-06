// cl: /MD
// ?run@Rva0042DBD9Host@@QAEXH@Z @0x0042DBD9 43B: member reset plus two conditional null-forwarding calls via rowed clear 0x002D38D1 and rowed setters 0x005785A2 and 0x005796B3. Evidence: lea +0x18 plus test/je with push-0 calls; ret-4 single unused arg.
class Rva002D38D1
{
public:
	void clear();
};
namespace StrategicHUD {
class Palantir;
}

class StrategicHUD::Palantir
{
public:
	void rva005785A2(void *p);
};
class Rva005796B3
{
public:
	void rva005796B3(void *p);
};
class Rva0042DBD9Host
{
public:
	void run(int dummy);
private:
	char m_00[0x18];
	Rva002D38D1 m_18;
	char m_gap[0x24 - 0x18 - 4];
	StrategicHUD::Palantir *m_24;
	char m_gap2[0x2C - 0x24 - 4];
	Rva005796B3 *m_2C;
};
void Rva0042DBD9Host::run(int dummy)
{
	(void)dummy;
	m_18.clear();
	if (m_24 != 0)
		m_24->rva005785A2(0);
	if (m_2C != 0)
		m_2C->rva005796B3(0);
}
