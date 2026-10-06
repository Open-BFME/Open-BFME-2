// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D36D8@Rva002D36D8@@QAEHXZ retail 0x002D36D8 29 bytes. Null-guarded
// int check loading inner pointer at +0xC8 via mid pointer at +0x10 then
// calling rowed forwarder 0x005CC208 and testing its byte result. Evidence:
// callers 0x0031E35D and 0x00405CC3; same /O1 as neighbours 0x002D3627 and
// 0x002D36F5; callee ?rva005CC208@Rva005CC208@@UAEXXZ rowed in
// VtableVirtualForwarders.cpp. Declared here as used (bool) since retail
// tests al after the call while the row says void.
class Rva005CC208
{
public:
	virtual bool rva005CC208();
};

struct Rva002D36D8Mid
{
	char m_pad[0xC8];
	Rva005CC208 *m_ptr;
};

class Rva002D36D8
{
public:
	int rva002D36D8();
private:
	char m_pad[0x10];
	Rva002D36D8Mid *m_mid;
};

int Rva002D36D8::rva002D36D8()
{
	Rva005CC208 *p = m_mid->m_ptr;
	if (p != 0)
	{
		if (p->Rva005CC208::rva005CC208() != false)
			return 1;
	}
	return 0;
}
