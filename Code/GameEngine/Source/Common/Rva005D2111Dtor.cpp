// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva005D2111@@UAE@XZ retail 0x005D2111 87B virtual dtor stores derived vtables then cond erase via 0x002B7250 then base 0x005CCDDD. Evidence: deleting-dtor caller 0x005D2168 vtable 0x00C75790#0 rowed erase callee pinned base.
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
struct Holder005D2111
{
	int m00;
	int m04;
	Rva002B7250 m08;
};
class Rva005CCDDD
{
public:
	virtual ~Rva005CCDDD();
protected:
	int m04;
	int m08;
};
class SecondBase005D2111
{
public:
	virtual ~SecondBase005D2111();
protected:
	int m04;
};
// ??1SecondBase005D2111@@UAE@XZ present-unmatched
inline SecondBase005D2111::~SecondBase005D2111()
{
}
class Rva005D2111 : public Rva005CCDDD, public SecondBase005D2111
{
public:
	virtual ~Rva005D2111();
private:
	Holder005D2111 *m_holder;
};
Rva005D2111::~Rva005D2111()
{
	if (m_holder)
		m_holder->m08.rva002B7250((CreateAHeroData *)(SecondBase005D2111 *)this);
}
