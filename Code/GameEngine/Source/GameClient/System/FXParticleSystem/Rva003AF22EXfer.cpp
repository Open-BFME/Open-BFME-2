// cl: /MD
// ?xfer@Rva003AF22E@@MAEXPAVXfer@@@Z retail 0x0055EA8E 31 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x0081C884 (class of rowed copy ctor
// ??0Rva003AF22E@@QAE@ABV0@@Z): Version1 plus GameClientRandomVariable member
// at +0x1C via rowed xferRandomVariable 0x306183. No base call. Precedent:
// Rva00499F45Xfer.cpp (?xfer@Rva00499F45@@MAEXPAVXfer@@@Z).
class Xfer
{
public:
	void Version1();
};

class GameClientRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);

class Rva003AF22E
{
public:
	char m_pad[0x18];
	GameClientRandomVariable m_var;

protected:
	virtual void xfer(Xfer *xfer);
};

void Rva003AF22E::xfer(Xfer *xfer)
{
	xfer->Version1();
	xferRandomVariable(*xfer, m_var);
}
