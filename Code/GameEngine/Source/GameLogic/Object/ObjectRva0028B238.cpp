// cl: /DNDEBUG /MD /EHsc
// ?rva0028B238@Object@@QAEX_N@Z @0x0028B238 45B: Object byte setter at +0x43c forwarding to Player::rva002AB8FB; neighbours ObjectGetSoleHealingBenefactor and ObjectRva0028B265; caller 0x0029354A and 0x003BCC4F; callee getControllingPlayer rowed and rva002AB8FB just landed
class Object;
class Player
{
public:
	void rva002AB8FB(Object *obj, bool flag);
};
class Object
{
public:
	void setCaptured(bool isCaptured);
	void rva0028B238(bool flag);
	Player *getControllingPlayer() const;
private:
	enum
	{
		CAPTURED = (1 << 2)
	};
	char m_pad00[0x438];
	unsigned char m_privateStatus; // +0x438
	char m_pad439[0x43C - 0x439];
	bool m_43C;
};

// ?setCaptured@Object@@QAEX_N@Z @0x0028B21E 26B: Zero Hour's setCaptured
// (release build, so no log in the clear arm) on the private status byte
// at +0x438, whose bit 0 the rowed 0x004DE24B tests as EFFECTIVELY_DEAD;
// 4 is Zero Hour's CAPTURED bit. Directly before rva0028B238.
void Object::setCaptured(bool isCaptured)
{
	if (isCaptured)
		m_privateStatus |= CAPTURED;
	else
		m_privateStatus &= ~CAPTURED;
}
// ?Object::rva0028B238 present-unmatched
void Object::rva0028B238(bool flag)
{
	if (flag == m_43C)
		return;
	m_43C = flag;
	Player *p = getControllingPlayer();
	if (p == 0)
		return;
	p->rva002AB8FB(this, m_43C);
}
