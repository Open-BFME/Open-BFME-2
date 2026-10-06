// cl: /EHs-c-
// ??0Rva003ADE32@@QAE@ABV0@@Z @0x003ADE32 38B derived copy via rowed base 0x003ADE58 with three derived vptrs. Evidence: callee rowed; caller 0x003ADE27; chain from 0x003ADE58.
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
class Rva003ADE32 : public Rva003ADE58
{
public:
	Rva003ADE32(const Rva003ADE32 &other);
};
Rva003ADE32::Rva003ADE32(const Rva003ADE32 &other)
	: Rva003ADE58(other)
{
}
