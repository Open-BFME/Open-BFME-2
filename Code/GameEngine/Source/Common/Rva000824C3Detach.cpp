// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc
//
// 0x000824C3 family: detach-key-and-clear manager bodies. Retail passes
// (this == 0xD0 ? null : this) as the erase key to the rowed
// Rva002B7250::rva002B7250 then clears the manager slot. Identity of the
// host class is unproven; the name is address-derived.

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

class Rva000824C3Host
{
public:
	void rva000824C3(int unused);
private:
	char m_pad[0x54];
	Rva002B7250 *m_mgr;
};

void Rva000824C3Host::rva000824C3(int unused)
{
	(void)unused;
	Rva002B7250 *mgr = m_mgr;
	char *diff = (char *)this - 0xD0;
	CreateAHeroData *key = (diff != 0) ? (CreateAHeroData *)this : 0;
	mgr->rva002B7250(key);
	m_mgr = 0;
}
