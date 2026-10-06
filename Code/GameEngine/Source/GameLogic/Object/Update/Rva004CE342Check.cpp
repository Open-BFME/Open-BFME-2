// cl: /MD
// ?rva004CE342@Rva004CE342@@QAE_NPAVRva00406F9C@@@Z @0x004CE342 85B: consume-once mask check.
// Clears two 0x80 buffers via rowed 0x001EAE6F, fills via virtual +0x2C,
// returns false if buf80 vs mask via rowed 0x00406F9C is false or byte at
// +4 is zero, else clears byte and returns true. Slot 3 of many Update
// vtables. Chain from 0x00406F9C. Sibling of 0x004B4130 0x004CE2B0.
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
	unsigned m_data[32];
};

class Rva004CE342
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
	bool rva004CE342(Rva00406F9C *mask);
private:
	bool m_b04;
};

bool Rva004CE342::rva004CE342(Rva00406F9C *mask)
{
	Rva00406F9C buf100;
	Rva00406F9C buf80;
	((Rva001EAE6FHelper *)&buf80)->clear80();
	((Rva001EAE6FHelper *)&buf100)->clear80();
	v11(&buf80, &buf100);
	if (!buf80.rva00406F9C(mask))
		return false;
	if (m_b04) {
		m_b04 = false;
		return true;
	}
	return false;
}
