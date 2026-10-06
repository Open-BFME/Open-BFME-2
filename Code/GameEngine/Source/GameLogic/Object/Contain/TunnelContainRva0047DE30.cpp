// cl: /MD
// ?rva0047DE30@TunnelContain@@UAEXXZ, retail 0x0047DE30, 60 bytes.
// TunnelContain chain method: virtual slot03 check then controlling-player 0x2E8 manager rva004F56FC add of m_object plus flag bytes at +0x9B0/+0x9B1.
// Layout: 8-base OpenContain family per TunnelContainRva0047DCDF (Iface34 at +0x34) so [esi-0x2C] is B00 m_object at +8; Player m_2E8 is Rva004F56FC per Rva004F56FCAdd caller 0x0047DE30; slot03 bool tentative. Evidence: chain via 0x004F56FC plus neighbours DCDF DF44.
class Thing;
class ModuleData;
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
};
class Rva004F56FC
{
public:
	void rva004F56FC(Object *obj);
};
class Player
{
public:
	unsigned char m_pad000[0x2E8];
	Rva004F56FC *m_2E8;
};
struct B00 { virtual void f00(); const ModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); int m_14; int m_18; Object *m_1C; };
struct B20 { virtual void f20(); };
struct B24 { virtual void f24(); };
struct B28 { virtual void f28(); };
struct B2C { virtual void f2C(); };
struct B30 { virtual void f30(); };
class ContainIface34
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual bool s03();
	virtual void rva0047DE30();
};
class TunnelContain
	: public B00, public B0C, public B10, public B20, public B24, public B28, public B2C, public B30
	, public ContainIface34
{
public:
	virtual void rva0047DE30();
private:
	char m_pad9AC[0x9AC];
	unsigned char m_flag9B0;
	unsigned char m_flag9B1;
};
void TunnelContain::rva0047DE30()
{
	if (!s03())
		return;
	m_flag9B0 = 0;
	Player *player = m_object->getControllingPlayer();
	if (player == 0)
		return;
	Rva004F56FC *mgr = player->m_2E8;
	if (mgr == 0)
		return;
	mgr->rva004F56FC(m_object);
	m_flag9B1 = 1;
}
