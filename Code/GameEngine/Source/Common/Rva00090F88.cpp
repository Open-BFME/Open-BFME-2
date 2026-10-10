// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
//
// ?rva00090F88@Rva00090F88@@QAE_NPAVRva00090F88Item@@@Z, retail 0x00090F88, 88 bytes.
// Offers an item to its owner: the item's virtual slot 2 is asked to accept the owner's
// slot 12 and slot 11 results (slot 11 takes whether the item's type at +0x24 is 5). On
// acceptance the item is stored at +0x2C and true returned; otherwise the item is released
// through its virtual slot 1 (deleting form, argument 0) into operator delete and false is
// returned. Evidence: target bytes only; the class and slot names are neutral views.

void __cdecl operator delete(void *block);

class Rva00090F88Item
{
public:
	virtual void v00();
	virtual void *destroy(int flags);
	virtual bool accept(int first, int second);
	char m_pad[0x24 - 4];
	int m_type24;
};

class Rva00090F88
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual int slot11(bool flag);
	virtual int slot12();
	bool rva00090F88(Rva00090F88Item *item);
private:
	char m_pad[0x2C - 4];
	Rva00090F88Item *m_item2C;
};

bool Rva00090F88::rva00090F88(Rva00090F88Item *item)
{
	bool flag = false;
	if (item->m_type24 == 5)
		flag = true;
	if (item->accept(slot12(), slot11(flag)))
	{
		m_item2C = item;
		return true;
	}
	::operator delete(item->destroy(0));
	return false;
}
