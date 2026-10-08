// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0059ECD2@Rva0059ECD2@@QAEXH@Z @0x0059ECD2 70B: state 0xA apt ClosePassword flush.
// Retail cmp [esi+0x488] 0xA then AptCall(Target edi virtual-string ClosePassword) sets 1 plus byte 0.
// Evidence: neighbours 0x0059ECAD setter plus 0x0059EE7F clearer share 0x488 member; caller 0x005A6630; callee 0x00524EF4 rowed.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

class GameWindow
{
public:
	int winEnable(bool enable);
};

class Rva0059ECD2Aux
{
public:
	char m_pad00[0x274];
	void *m_level274;
};

class Rva0059ECD2
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual const char *getStr();
	void rva0059ECD2(int unused);
	void rva0059EC72(int unused);
private:
	char m_pad04[0x54];
	Rva0059ECD2Aux *m_p58;
	char m_pad5C[0x42C];
	int m_state488;
	char m_pad48C[0xC];
	GameWindow *m_win498;
	GameWindow *m_win49C;
	unsigned char m_flag4A0;
};

void Rva0059ECD2::rva0059ECD2(int /*unused*/)
{
	if (m_state488 == 0xa) {
		void *level = m_p58->m_level274;
		Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), level, getStr(), "ClosePassword");
		m_state488 = 1;
		m_flag4A0 = 0;
	}
}

void Rva0059ECD2::rva0059EC72(int /*unused*/)
{
	int s = m_state488;
	if (s == 2 || s == 3) {
		m_win498->winEnable(false);
		m_win49C->winEnable(false);
		m_state488 = 4;
	}
}
