// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva004C63DE@SiegeDeployHordeSpecialPower@@UAEXABUVector3@@@Z, retail
// 0x004C63DE, 17 bytes. Virtual slot 14 (offset 0x38) of vtable 0x0085DD94:
// 12-byte copy to +0x3C (three floats m_3C/m_40/m_44 in the ctor TU) via
// three movsd string moves.
//
// Donor: SiegeDeployHordeSpecialPowerCtor.cpp (same // cl: plus int at +0x38
// plus floats at +0x3C/+0x40/+0x44 plus int at +0x48; the 12-byte member is
// modelled here as Vector3 to get the struct copy). No calls, no EH, frameless
// leaf with esi/edi preserves. Honest address name: slot index is the proof.

struct Vector3
{
	float x;
	float y;
	float z;
};

class SiegeDeployHordeSpecialPower
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void Rva004C63DE(const Vector3 &arg) = 0;

private:
	unsigned char m_pad04[0x38];
	Vector3 m_vec3C;
};

void SiegeDeployHordeSpecialPower::Rva004C63DE(const Vector3 &arg)
{
	m_vec3C = arg;
}
