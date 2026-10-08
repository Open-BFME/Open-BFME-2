// cl: (none -- build.py base flags)
//
// ?bfmeGo1020M@BfmeM1020@@QAEXH@Z at retail 0x0051E3A3 (32B). Trimmed port of
// the Open-BFME-1 BfmeConv1020 donor: only the served bfmeGo1020M body is
// carried (sibling bfmeGo1020G/H/I stay with the donor file until their own
// rows land). Single drift vs BFME1 (b1 0x005701D0): the state member sits
// at +0x27C here against +0x258 there, so the pad runs 0x27C wide. The
// register call is virtual at slot 49 here (call [eax+0xC4]); the donor
// spells it direct, so five pad virtuals continue the VN pattern ahead of
// a virtual Reg.

class BfmeM1020;

class BfmeN1020
{
public:
	virtual void bfmeVN01020();
	virtual void bfmeVN11020();
	virtual void bfmeVN21020();
	virtual void bfmeVN31020();
	virtual void bfmeVN41020();
	virtual void bfmeVN51020();
	virtual void bfmeVN61020();
	virtual void bfmeVN71020();
	virtual void bfmeVN81020();
	virtual void bfmeVN91020();
	virtual void bfmeVN101020();
	virtual void bfmeVN111020();
	virtual void bfmeVN121020();
	virtual void bfmeVN131020();
	virtual void bfmeVN141020();
	virtual void bfmeVN151020();
	virtual void bfmeVN161020();
	virtual void bfmeVN171020();
	virtual void bfmeVN181020();
	virtual void bfmeVN191020();
	virtual void bfmeVN201020();
	virtual void bfmeVN211020();
	virtual void bfmeVN221020();
	virtual void bfmeVN231020();
	virtual void bfmeVN241020();
	virtual void bfmeVN251020();
	virtual void bfmeVN261020();
	virtual void bfmeVN271020();
	virtual void bfmeVN281020();
	virtual void bfmeVN291020();
	virtual void bfmeVN301020();
	virtual void bfmeVN311020();
	virtual void bfmeVN321020();
	virtual void bfmeVN331020();
	virtual void bfmeVN341020();
	virtual void bfmeVN351020();
	virtual void bfmeVN361020();
	virtual void bfmeVN371020();
	virtual void bfmeVN381020();
	virtual void bfmeVN391020();
	virtual void bfmeVN401020();
	virtual void bfmeVN411020();
	virtual void bfmeVN421020();
	virtual void bfmeVN431020();
	virtual void bfmeVN441020();
	virtual void bfmeVN451020();
	virtual void bfmeVN461020();
	virtual void bfmeVN471020();
	virtual void bfmeVN481020();
	virtual void bfmeReg1020(BfmeM1020 *p);
};

extern class GameWindowManager *TheWindowManager;

class BfmeM1020
{
public:
	void bfmeGo1020M(int unused);

	char m_bfmePad[0x27C];
	int m_bfmeState;
};

void BfmeM1020::bfmeGo1020M(int unused)
{
	(void)unused;
	(*(BfmeN1020 **)&TheWindowManager)->bfmeReg1020(this);
	m_bfmeState = 1;
}
