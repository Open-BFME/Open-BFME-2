// cl: /DNDEBUG /MD /EHsc
// ?rva0055EECB@Rva0055EECB@@QAEXPAVXfer@@@Z 0x0055EECB 110B. Version-gated xfer:
// a two-byte version record (1, 3) is transferred first, then the +0x10 and +0x4
// members, the RandomVariable at +0x14 through the matched xferRandomVariable,
// and the +0x20 and +0x21 members once the version reaches 2 and 3.
class GameClientRandomVariable;

class Xfer
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
	virtual void s28(void *p);
	virtual void v2C();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3C();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4C();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5C();
	virtual void s60(void *p);
	virtual void v64();
	virtual void v68();
	virtual void v6C();
	virtual void s70(void *p);
	virtual void v74();
	virtual void v78();
	virtual void v7C();
	virtual void v80();
	virtual void v84();
	virtual void v88();
	virtual void v8C();
	virtual void s90(void *p);
};

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &value);

struct Rva0055EECBVersion
{
	unsigned char current;
	unsigned char stored;
};

class Rva0055EECB
{
public:
	void rva0055EECB(Xfer *xfer);
private:
	unsigned char m_pad00[4];
	unsigned char m4[0x0C]; // +0x04
	unsigned char m10[4]; // +0x10
	unsigned char m14[0x0C]; // +0x14
	unsigned char m20[2]; // +0x20
};

void Rva0055EECB::rva0055EECB(Xfer *xfer)
{
	Rva0055EECBVersion version;
	version.current = 1;
	version.stored = 3;
	xfer->s28(&version);
	xfer->s70(&m10);
	xfer->s60(&m4);
	xferRandomVariable(*xfer, *reinterpret_cast<GameClientRandomVariable *>(&m14));
	if (version.stored >= 2)
		xfer->s90(&m20[0]);
	if (version.stored >= 3)
		xfer->s90(&m20[1]);
}
