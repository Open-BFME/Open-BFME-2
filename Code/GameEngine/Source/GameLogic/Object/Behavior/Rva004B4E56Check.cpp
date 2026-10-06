// cl: /DNDEBUG /MD
// ?rva004B4E56@Rva004B4E56@@QAEEXZ @0x004B4E56 109B: mask check via Intersect.
// Clears two 0x80 buffers via rowed 0x001EAE6F, fills via virtual +0x2C on +0x10,
// tests [edi+0x284] vs buf2 via rowed 0x00406F9C (false if true), else Player
// via rowed getControllingPlayer 0x0028AFA9 and tests [Player+0x13C] vs buf2
// inverted via neg/sbb/inc. Chain from 0x00406F9C. Caller 0x004B502F.
class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();
private:
	char m_pad[0x80];
};

class Rva00406F9C
{
public:
	bool rva00406F9C(const void *other);
private:
	unsigned m_data[32];
};

class Player
{
public:
	char m_pad[0x13C];
	Rva00406F9C m_mask13C;
};

class Object
{
public:
	virtual void v00();
	Player *getControllingPlayer() const;
private:
	char m_pad04[0x284 - 4];
public:
	Rva00406F9C m_mask284;
};

class Member10
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
	virtual void v11(void *a, void *b);
};

class Rva004B4E56
{
public:
	virtual void v00();
	unsigned char rva004B4E56();
private:
	char m_pad04[4];
	Object *m_obj08;
	int m_pad0C;
	Member10 m_mem10;
};

unsigned char Rva004B4E56::rva004B4E56()
{
	Object *obj = m_obj08;
	Rva001EAE6FHelper buf100;
	Rva001EAE6FHelper buf80;
	buf100.clear80();
	buf80.clear80();
	m_mem10.v11(&buf100, &buf80);
	if (obj->m_mask284.rva00406F9C(&buf80))
		return 0;
	Player *pl = obj->getControllingPlayer();
	return !pl->m_mask13C.rva00406F9C(&buf80);
}
