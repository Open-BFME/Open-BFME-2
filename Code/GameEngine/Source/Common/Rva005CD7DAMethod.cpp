// cl: /MD
//
// ?rva005CD7DA@Rva005CD7DA@@QAEXXZ retail 0x005CD7DA 39B conditional get plus two virtuals.
// Evidence: +4 PtrChase get 0x0042D6AE rowed +C bool early-out; virtuals +0x18 noargs and +4 with 0 on get result.
class Rva0042D6AEPtrChaseField
{
public:
	int get() const;
};
struct Subscribable005CD7DA
{
	virtual void f0();
	virtual void f1(int v);
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
};
class Rva005CD7DA
{
public:
	virtual ~Rva005CD7DA() {}
	void rva005CD7DA();
private:
	Rva0042D6AEPtrChaseField *m_4;
	void *m_8;
	bool m_C;
};
void Rva005CD7DA::rva005CD7DA()
{
	if (m_C == 0)
		return;
	int v = m_4->get();
	Subscribable005CD7DA *obj = (Subscribable005CD7DA *)v;
	if (obj == 0)
		return;
	obj->f6();
	obj->f1(0);
}
