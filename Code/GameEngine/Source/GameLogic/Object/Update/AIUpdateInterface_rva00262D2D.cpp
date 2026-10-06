// cl: /DNDEBUG /MD
//
// ?rva00262D2D@AIUpdateInterface@@QAEXXZ, retail 0x00262D2D, 19 bytes.
// AIUpdateInterface leaf: destroyPath then virtual slot 0x60 with 2. Callee
// destroyPath 0x00262A8A is rowed. Slot identity unproven so honest
// address-derived name. No other callees.

class AIUpdateInterface
{
public:
	virtual void s00();
	virtual void s04();
	virtual void s08();
	virtual void s0C();
	virtual void s10();
	virtual void s14();
	virtual void s18();
	virtual void s1C();
	virtual void s20();
	virtual void s24();
	virtual void s28();
	virtual void s2C();
	virtual void s30();
	virtual void s34();
	virtual void s38();
	virtual void s3C();
	virtual void s40();
	virtual void s44();
	virtual void s48();
	virtual void s4C();
	virtual void s50();
	virtual void s54();
	virtual void s58();
	virtual void s5C();
	virtual void s60(int v);
	void destroyPath();
	void rva00262D2D();
};

void AIUpdateInterface::rva00262D2D()
{
	destroyPath();
	s60(2);
}
