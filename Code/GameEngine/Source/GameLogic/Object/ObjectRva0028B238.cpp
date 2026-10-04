// cl: /O1 /DNDEBUG /MD /EHsc /G7
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
	void rva0028B238(bool flag);
	Player *getControllingPlayer() const;
private:
	char m_pad00[0x43C];
	bool m_43C;
};
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
