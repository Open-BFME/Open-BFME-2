// cl: /O1 /arch:SSE /MD /DNDEBUG
// Identity: ModuleFactory registers this data class under "CombineHordeSpecialPower" (addModule
// pairs the name with this factory); formerly misnamed AIUpdateInterface.
// Trial: ??0CombineHordeSpecialPower@@QAE@XZ.
// Default ctor over opaque intermediate base 0x004930A0 (pinned); vtable
// plus one trailing float. Factory stub order names it.
class Rva004930A0
{
public:
	Rva004930A0();
	virtual ~Rva004930A0();

protected:
	unsigned char m_pad0[0x7C - 4];
	float m_f7C;
};

// ??1Rva004930A0@@ present-unmatched
Rva004930A0::~Rva004930A0()
{
}

class CombineHordeSpecialPower : public Rva004930A0
{
public:
	CombineHordeSpecialPower();
	virtual ~CombineHordeSpecialPower();

};

static float kF7C = 0.0f;

CombineHordeSpecialPower::CombineHordeSpecialPower()
	: Rva004930A0()
{
	m_f7C = kF7C;
}

// ??1CombineHordeSpecialPower@@ present-unmatched
CombineHordeSpecialPower::~CombineHordeSpecialPower()
{
}
