// cl: /DNDEBUG /MD /EHsc
// Retail 0x00539172, 55B: true when any element served by virtual slots
// 13 (count) and 14 (element at index) carries the given id at +0xB0.

struct Rva00539172Element
{
	char m_pad[0xB0];
	int m_id;
};

class Rva00539172List
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual int count();
	virtual Rva00539172Element *at(int index);
	bool contains(int id);
};

bool Rva00539172List::contains(int id)
{
	int n = count();
	for (int i = 0; i < n; ++i)
	{
		if (at(i)->m_id == id)
			return true;
	}
	return false;
}
