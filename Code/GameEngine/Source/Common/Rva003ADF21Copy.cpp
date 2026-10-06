// cl: /EHs-c-
// ??0Rva003ADF21@@QAE@ABV0@@Z @0x003ADF21 64B MI copy via rowed base 0x003ADFDB plus rowed member 0x003ADF61 with derived vptrs. Evidence: callees rowed; caller 0x003ADF02; same 64B shape as 0x003ADE58.
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
Rva003ADF21::Rva003ADF21(const Rva003ADF21 &other)
	: Rva003ADFDB(other)
	, Rva003ADF61(other)
{
}
