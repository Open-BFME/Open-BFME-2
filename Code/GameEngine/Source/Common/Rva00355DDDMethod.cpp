// cl: /MD /EHsc
// ?rva00355DDD@Rva003560ED@@QAEXXZ @0x00355DDD 23B
// vslot 3 (offset 0xC) of 0x00814EA4 (class of rowed dtor 0x003560ED); calls TheDisplay slot68 then clears +8
// Target evidence: same vtable as ??1Rva003560ED 0x003560ED; neighbours 0x00355DC5 0x00355EE1 same cl; no callers
class Display
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03(); virtual void d04();
	virtual void d05(); virtual void d06(); virtual void d07(); virtual void d08(); virtual void d09();
	virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
	virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
	virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
	virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
	virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
	virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44();
	virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
	virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54();
	virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59();
	virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64();
	virtual void d65(); virtual void d66(); virtual void d67(); virtual void slot68();
};

extern Display *TheDisplay;

class Rva003560ED
{
public:
	void rva00355DDD();
private:
	char m_pad[8];
	int m_08;
};

void Rva003560ED::rva00355DDD()
{
	TheDisplay->slot68();
	m_08 &= 0;
}
