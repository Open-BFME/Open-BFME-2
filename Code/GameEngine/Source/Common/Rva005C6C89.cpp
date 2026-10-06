// cl: /MD
class SubTree005C6B83 {
public:
	SubTree005C6B83();
	void clear();
};

class Rva005C6C7B {
public:
	virtual ~Rva005C6C7B();
	Rva005C6C7B();
	void reset();

	bool m_04;
	char m_pad05[3];
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	float m_28;
	float m_2c;
	SubTree005C6B83 m_tree30;
};

Rva005C6C7B::Rva005C6C7B()
	: m_04(0), m_08(0), m_1c(0), m_20(0), m_24(0), m_28(0.0f), m_2c(0.0f)
{
}

void Rva005C6C7B::reset()
{
	m_04 = 0;
	m_08 = 0;
	m_tree30.clear();
	m_18 = 0;
	m_14 = 0;
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;
	m_10 = -500;
	m_0c = -500;
	m_28 = 0.0f;
	m_2c = 0.0f;
}
