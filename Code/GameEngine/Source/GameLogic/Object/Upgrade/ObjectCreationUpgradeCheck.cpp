// cl: /MD
// ?rva004B4130@Rva004B4130@@QAE_NPAVRva00406F9C@@@Z @0x004B4130 121B: upgrade mask check.
// Clears two 0x80 buffers via rowed 0x001EAE6F, fills via virtual +0x2C,
// returns false if buf80 all zero, if buf100 intersects mask via rowed
// 0x00406F9C, then dispatches on virtual +0x34 to rowed 0x002AA292 or rowed
// 0x00406F9C with mask as this and buf80 as other. Slot 2 of 0x00857660,
// class of ObjectCreationUpgrade ctor. Chain from 0x00406F9C.
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

class Rva002AA292
{
public:
	bool rva002AA292(const int *mask) const;
private:
	int m_bits[32];
};

class Rva004B4130
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
	virtual void v12();
	virtual bool v13();
	bool rva004B4130(Rva00406F9C *mask);
};

bool Rva004B4130::rva004B4130(Rva00406F9C *mask)
{
	Rva00406F9C buf100;
	Rva00406F9C buf80;
	((Rva001EAE6FHelper *)&buf80)->clear80();
	((Rva001EAE6FHelper *)&buf100)->clear80();
	v11(&buf80, &buf100);
	for (unsigned i = 0; i < 32; ++i) {
		if (buf80.m_data[i] != 0)
			goto haveBits;
	}
	return false;
haveBits:
	if (buf100.rva00406F9C(mask))
		return false;
	if (v13())
		return ((Rva002AA292 *)mask)->rva002AA292((const int *)&buf80);
	return mask->rva00406F9C(&buf80);
}
