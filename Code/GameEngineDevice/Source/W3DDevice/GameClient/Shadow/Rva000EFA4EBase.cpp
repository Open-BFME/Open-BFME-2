// cl: /O1 /arch:SSE /GX- /MD
// Target EFA4E/132 initializes the observed 0x58-byte object prefix.
// Native return is zero in EAX; all witnessed constructor callers ignore it.
// Use a void address-derived initializer rather than assert a C++ constructor.
// F0F2B/F0F19 and109D8C reuse this prefix; F0F2B extends through64 and
// stores the BCEFA0 dispatch table. Shadow-family relation is an inference
// from those callers and the separately recovered buffer-owner units.
// Target facts: Vec3 copies at8/14, scalar/flag stores4..54, float1.0
// at BBB8D8. Original class name and complete object size remain unknown.
// Adapted from banked native reconstruction reverse/attempts/0x000efa4e.cpp;
// two-byte constructor-return mismatch resolved by the target's void ABI.
struct RvaVec3
{
	float x;
	float y;
	float z;
};

class Rva000EFA4E
{
public:
	void initialize();
private:
	char m_pad00[4];
	unsigned char m_04;
	unsigned char m_05;
	char m_pad06[2];
	RvaVec3 m_08;
	RvaVec3 m_14;
	float m_20;
	int m_24;
	int m_28;
	int m_2C;
	unsigned char m_30;
	char m_pad31[3];
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
};

void Rva000EFA4E::initialize()
{
	RvaVec3 tmp;
	tmp.x = 0.0f;
	tmp.y = 0.0f;
	tmp.z = 0.0f;
	m_28 = -1;
	m_24 = -1;
	m_08 = tmp;
	tmp.x = 0.0f;
	tmp.y = 0.0f;
	tmp.z = 1.0f;
	m_14 = tmp;
	m_04 = 1;
	m_05 = 0;
	m_20 = 0.0f;
	m_2C = 0xFF;
	m_30 = 1;
	m_34 = 0;
	m_38 = 0;
	m_3C = -1;
	m_40 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4C = 0;
	m_50 = 0;
	m_54 = 0;
}
