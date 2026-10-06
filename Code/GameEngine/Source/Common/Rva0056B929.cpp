// cl: /Oy- /MD
// ?rva0056B929@Rva0056B929@@QAEXE@Z @0x0056B929 53B:
// Rva0056B929::rva0056B929 stores arg to +0xc0, reads virtual 0x44 twice,
// notifies via virtual 0x30 when changed. Caller 0x003FDE8C loops over
// array calling this. Vtable slots 0x30/0x44, member 0xc0 from retail.
class Rva0056B929
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2C();
	virtual void v30func(bool v);
	virtual void v34();
	virtual void v38();
	virtual void v3C();
	virtual void v40();
	virtual bool v44func();
private:
	char m_pad[0xC0 - 4];
	unsigned char m_c0;
public:
	void rva0056B929(unsigned char arg);
};
void Rva0056B929::rva0056B929(unsigned char arg)
{
	bool oldVal = v44func();
	m_c0 = arg;
	bool curVal = v44func();
	if (curVal != oldVal)
		v30func(curVal);
}
