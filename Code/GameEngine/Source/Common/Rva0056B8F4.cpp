// cl: /Oy- /MD
// ?rva0056B8F4@Rva0056B8F4@@QAEXI@Z @0x0056B8F4 53B:
// Rva0056B8F4::rva0056B8F4 stores arg to +0xbc, reads virtual 0x44 twice,
// notifies via virtual 0x30 when changed. Caller 0x003FDE1A loops over
// array calling this. Vtable slots 0x30/0x44, member 0xbc from retail.
class Rva0056B8F4
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
	char m_pad[0xBC - 4];
	unsigned int m_bc;
public:
	void rva0056B8F4(unsigned int arg);
};
void Rva0056B8F4::rva0056B8F4(unsigned int arg)
{
	bool oldVal = v44func();
	m_bc = arg;
	bool curVal = v44func();
	if (curVal != oldVal)
		v30func(curVal);
}
