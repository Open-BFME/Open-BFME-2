// cl: /DNDEBUG /MD /EHsc
// ?getSoleHealingBenefactor@Object@@QBE?AW4ObjectID@@XZ, retail 0x0028B204, 26 bytes.
// Object::getSoleHealingBenefactor returns the cached benefactor at +0x3B8 when
// the GameLogic frame is within the expiration at +0x3BC, else INVALID_ID.
// Evidence: BFME1 donor Object.cpp:2200 same shape with +0x2D0/+0x2D4; BFME2
// +0x3B8/+0x3BC from retail immediates; callers at 0x0041BF89 0x00488AFC
// 0x0029C903 compare the result to Object+0x74 m_id exactly where DozerAIUpdate
// and WorkerAIUpdate compare getSoleHealingBenefactor to getID; frame at
// GameLogic+0x40 via Rva002039B6Host; return type W4ObjectID proven by the
// rowed ?getID@Object@@QBE?AW4ObjectID@@XZ at 0x000421C4.
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

class GameLogic
{
public:
	char m_pad[0x40];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;


class Object
{
public:
	ObjectID getSoleHealingBenefactor() const;

private:
	char m_pad00[0x3B8];
	ObjectID m_soleHealingBenefactorID;
	UnsignedInt m_soleHealingBenefactorExpirationFrame;
};

ObjectID Object::getSoleHealingBenefactor() const
{
	UnsignedInt now = TheGameLogic->m_frame;
	if (now > m_soleHealingBenefactorExpirationFrame)
		return INVALID_ID;
	return m_soleHealingBenefactorID;
}
