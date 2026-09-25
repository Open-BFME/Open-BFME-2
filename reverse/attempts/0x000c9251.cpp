// ?init@OrnamentData@@QAEXXZ
// partial score=0.96 date=2026-09-25
// Probe: OrnamentData::init.
class OrnamentData
{
public:
	void init();

private:
	float m_00;
	float m_04;
	float m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
};

void OrnamentData::init()
{
	m_00 = 1.0f;
	m_04 = 1.0f;
	m_08 = 1.0f;
	m_0C = 0;
	m_10 = 1;
	m_14 = 1;
	m_18 = 1;
	m_1C = -1;
	m_20 = -1;
	m_24 = 0;
}

void useIt(OrnamentData *p)
{
	p->init();
}
