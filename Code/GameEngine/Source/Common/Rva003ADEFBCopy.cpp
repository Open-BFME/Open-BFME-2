// cl: /O1 /EHs-c-
// ??0Rva003ADEFB@@QAE@ABV0@@Z @0x003ADEFB 38B derived copy via rowed base 0x003ADF21 with three derived vptrs. Evidence: callee rowed; caller 0x003ADEF0; chain from 0x003ADF21 same shape as 0x003ADE32.
class V3Vt01111D90
{
public:
	virtual void s0();
	virtual ~V3Vt01111D90() {}
	int m04;
};
class V3Second08
{
public:
	virtual void s0();
	virtual ~V3Second08() {}
};
class Rva003ADFDB : public V3Vt01111D90, public V3Second08
{
public:
	Rva003ADFDB(const Rva003ADFDB &other);
};
class Rva003ADF61
{
public:
	Rva003ADF61(const Rva003ADF61 &other);
	virtual ~Rva003ADF61();
	int m04;
	int m08;
	int m0C;
	int m10;
	int m14;
	int m18;
	int m1C;
	int m20;
	int m24;
	int m28;
};
class Rva003ADF21 : public Rva003ADFDB, public Rva003ADF61
{
public:
	Rva003ADF21(const Rva003ADF21 &other);
};
class Rva003ADEFB : public Rva003ADF21
{
public:
	Rva003ADEFB(const Rva003ADEFB &other);
	Rva003ADEFB *rva003ADEDE() const;
};
Rva003ADEFB::Rva003ADEFB(const Rva003ADEFB &other)
	: Rva003ADF21(other)
{
}

// ?rva003ADEDE@Rva003ADEFB@@QBEPAV1@XZ @0x003ADEDE 29B: vtable slot before
// ?rva0055F805 (xfer); allocates 0x38 bytes and copy-constructs this object.
Rva003ADEFB *Rva003ADEFB::rva003ADEDE() const
{
	return new Rva003ADEFB(*this);
}
