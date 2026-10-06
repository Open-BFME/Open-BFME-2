// cl: /EHs-c-
// ??0Rva003ADE58@@QAE@ABV0@@Z @0x003ADE58 64B MI copy via rowed base 0x003ADEBF plus rowed member 0x003ADE98 with derived vptrs. Evidence: callees rowed; caller 0x003ADE39; prev 0x003ADDEC next 0x003ADE98.
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
class Rva003ADEBF : public V3Vt01111D90, public V3Second08
{
public:
	Rva003ADEBF(const Rva003ADEBF &other);
};
class Rva003ADE98
{
public:
	Rva003ADE98(const Rva003ADE98 &other);
	virtual ~Rva003ADE98();
	int m04;
	char m08;
	char m09;
};
class Rva003ADE58 : public Rva003ADEBF, public Rva003ADE98
{
public:
	Rva003ADE58(const Rva003ADE58 &other);
};
Rva003ADE58::Rva003ADE58(const Rva003ADE58 &other)
	: Rva003ADEBF(other)
	, Rva003ADE98(other)
{
}
