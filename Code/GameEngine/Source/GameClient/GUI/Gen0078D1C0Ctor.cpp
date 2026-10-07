// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Adapted from Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameClient/GUI/Gen0078D1C0Ctor.cpp.
// Native 0x00104EBF..0x00104F16: sentence at +4; following fields at
// C8, CC, D0, D4 and D5. Its matched destructor calls the sentence
// destructor at 0x00157C70 on the same +4 member.

class Gen0078D1C0Base
{
public:
	virtual ~Gen0078D1C0Base() {}
};

class Render2DSentenceClass
{
public:
	Render2DSentenceClass();
	~Render2DSentenceClass();
	virtual void Reset();
private:
	char m_unreconstructed[0xC0];
};

class Gen0078D1C0 : public Gen0078D1C0Base
{
public:
	Gen0078D1C0();
	virtual ~Gen0078D1C0();
private:
	Render2DSentenceClass m_sentence;
	int m_first;
	int m_second;
	unsigned int m_color;
	bool m_firstFlag;
	bool m_secondFlag;
};

Gen0078D1C0::Gen0078D1C0()
{
	m_second = 0;
	m_first = 0;
	m_firstFlag = false;
	m_secondFlag = false;
	m_color = 0x00FFFFFF;
}
