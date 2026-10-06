// cl: /DNDEBUG /MD /EHsc
//
// ?rva00261B7E@Rva002611F2@@UAE_NPAVObject@@@Z retail 0x00261B7E 125 bytes.
// Vslot 1 filter checking arg template flags 0x108 0x10E plus this obj
// controlling player plus provider slot 0x4C plus this flag plus arg
// template 0x110 plus provider null plus rowed isAbleToAttack returning
// bool. Evidence is vtable plus ctor layout plus rowed callees.

class Player;
class ObjectTemplate;
class Provider;

class ObjectTemplate
{
public:
	char m_pad00[0x108];
	unsigned char m_108;
	char m_pad109[0x10E - 0x109];
	unsigned char m_10E;
	char m_pad10F[0x110 - 0x10F];
	unsigned char m_110;
};

class Provider
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual int Check(Player *p);
};

class Object
{
public:
	virtual void dummy();
	Player *getControllingPlayer() const;
	bool isAbleToAttack() const;
	ObjectTemplate *m_template04;
	char m_pad08[0x250 - 8];
	Provider *m_provider250;
};

class Player
{
public:
	char m_pad[0x5C];
	int m_field5C;
};

class Rva002611F2Base
{
public:
	Rva002611F2Base() : m_base4(0) {}
	~Rva002611F2Base();
private:
	int m_base4;
};

class Rva002611F2 : public Rva002611F2Base
{
public:
	virtual void dummy();
	virtual bool rva00261B7E(Object *obj);
private:
	Object *m_obj;
	bool m_flag;
};

bool Rva002611F2::rva00261B7E(Object *obj)
{
	ObjectTemplate *t = obj->m_template04;
	if ((t->m_108 & 0x80) == 0)
		goto success;
	if ((t->m_10E & 0x80) != 0)
		goto success;
	Player *pThis = m_obj->getControllingPlayer();
	if (pThis == 0)
		goto fail;
	Provider *prov = obj->m_provider250;
	int ok = prov ? prov->Check(pThis) : 0;
	if (ok)
		goto flag_check;
	if (obj->getControllingPlayer() == 0)
		goto fail;
flag_check:
	if (m_flag != 0)
		goto success;
	if ((obj->m_template04->m_110 & 1) != 0)
		goto success;
	if (obj->m_provider250 == 0)
		goto fail;
	if (obj->isAbleToAttack())
		goto success;
	goto fail;
success:
	return true;
fail:
	return false;
}
