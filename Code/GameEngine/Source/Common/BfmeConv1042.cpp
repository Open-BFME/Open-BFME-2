struct BfmeR1042
{
	char *m_bfmeName;
};

class BfmeSub1042
{
public:
	void bfmeSet1042(char *text, int a, int b);
};


class BfmeC1042
{
public:
	void bfmeGo1042E(BfmeR1042 *rec);

	char m_bfmePad[4];
	BfmeSub1042 m_bfmeSub;
	char m_bfmePad2[0xcf];
	char m_bfmeFlag;
};

// ?bfmeGo1042E@BfmeC1042@@QAEXPAUBfmeR1042@@@Z
void BfmeC1042::bfmeGo1042E(BfmeR1042 *rec)
{
	char *text;

	if (rec->m_bfmeName != 0)
		text = rec->m_bfmeName + 8;
	else
		text = (char *)L"";

	m_bfmeSub.bfmeSet1042(text, 0, 0);
	m_bfmeFlag = 1;
}
