// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0014F3E7Destroy@@YAXPAVRva0014F3E7@@0PAX@Z retail 0x0014F3E7 26B: destroy range stepping 0x4C calling vtable[0] with 0. Caller 0x0014F8BC dispatcher with tag. Element size matches Rva0014F699 0x4C.

class Rva0014F3E7
{
public:
	virtual void destroy(int);
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
};

void __cdecl Rva0014F3E7Destroy(Rva0014F3E7 *first, Rva0014F3E7 *last, void *tag)
{
	for (; first != last; ++first)
		first->destroy(0);
}

void __cdecl Rva0014F8AEDestroy(Rva0014F3E7 *first, Rva0014F3E7 *last)
{
	char tag;
	Rva0014F3E7Destroy(first, last, (void *)&tag);
}

extern "C" void __cdecl free(void *block);

class Rva0014F8C6
{
public:
	void rva0014F8C6();
private:
	Rva0014F3E7 *m_00;
	Rva0014F3E7 *m_04;
};

void Rva0014F8C6::rva0014F8C6()
{
	Rva0014F8AEDestroy(m_00, m_04);
	Rva0014F3E7 *buf = m_00;
	if (buf != 0)
		free(buf);
}
