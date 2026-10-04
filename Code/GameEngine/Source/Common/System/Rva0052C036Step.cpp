// cl: /O1 /DNDEBUG /MD /GX-
// ?rva0052C036@Rva0052C036@@QAE_NXZ @0x0052C036 54B: advance index at +8 toward limit at +18 over 0xB8 stride array at +0xC else clamp and notify.
// Evidence: callers 0x003B8CAC tail-jmp via array at +0x14 and 0x0052C9F9 tail-jmp; callees rowed 0x003EF2FF Rva003EF13E plus pin 0x0056696F bfmeEnter plus g_009FE1C8; stride 0xB8 matches Rva0052BCE7Elem; neighbours Rva0052BF33DestroyTagged and Rva0052C06CGet.
class Rva003EF13E
{
public:
	void rva003EF2FF();
};

class Rva0021294A
{
public:
	char m_pad[0x268];
	Rva003EF13E *m_268;
};

extern Rva0021294A *g_009FE1C8;

class Glo012F1024Item
{
public:
	void bfmeEnter();
};

class Rva0052C036
{
public:
	bool rva0052C036();
private:
	char m_pad0[8];
	int m_8;
	char *m_c;
	char m_pad10[8];
	int m_18;
};

bool Rva0052C036::rva0052C036()
{
	++m_8;
	if (m_8 > m_18) {
		m_8 = m_18;
		g_009FE1C8->m_268->rva003EF2FF();
		return false;
	}
	((Glo012F1024Item *)((char *)m_c + m_8 * 0xB8))->bfmeEnter();
	return true;
}
