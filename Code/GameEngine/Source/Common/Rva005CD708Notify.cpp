// cl: /MD
//
// ?rva005CD708@Rva005CD708@@QAEXXZ retail 0x005CD708 47B lazy notify.
// Evidence: get 0x0042D6C6 via +0x4; cache +0x8; append 0x005A0B4C via +4; virtual [eax+8] with +0xC.
class Rva0042D6C6PtrChaseField
{
public:
	int get() const;
};

struct Rva002BA8F1Listener
{
	char m_pad[4];
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
private:
	char m_pad[12];
};

struct NotifyI
{
	virtual void f0();
	virtual void f1();
	virtual void f2(unsigned char v);
};

struct VNode : public NotifyI
{
	Rva005A0B4CList m_list;
};

class Rva005CD708 : public Rva002BA8F1Listener
{
public:
	void rva005CD708();
private:
	Rva0042D6C6PtrChaseField *m_4;
	NotifyI *m_8;
	unsigned char m_C;
};

void Rva005CD708::rva005CD708()
{
	if (m_8 != 0)
		return;
	int v = m_4->get();
	m_8 = (NotifyI *)v;
	if (v == 0)
		return;
	((VNode *)v)->m_list.append((Rva002BA8F1Listener *)this);
	m_8->f2(m_C);
}
