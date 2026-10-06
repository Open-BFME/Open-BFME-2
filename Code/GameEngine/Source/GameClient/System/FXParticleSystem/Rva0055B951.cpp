// cl: /MD
//
// ?rva0055B951@Rva0055B951@@UAEXPAVXfer@@@Z, retail 0x0055B951, 28 bytes.
// Evidence: slot 3 of 0x0081CDF0 and 0x0081D60C (DoXfer); calls Version1
// rowed 0x000053EE then inner ?rva0055B8CD rowed 0x0055B8CD at +0x1C;
// caller jmp at 0x003ABCF7; Ghidra FUN_0095b951 28B.
class Xfer
{
public:
	void Version1();
};

class Rva0055B8CD
{
public:
	virtual void rva0055B8CD(Xfer *xfer);
};

class Rva0055B951
{
	char m_pad[0x18];
	Rva0055B8CD m_inner;
public:
	virtual void rva0055B951(Xfer *xfer);
};

void Rva0055B951::rva0055B951(Xfer *xfer)
{
	xfer->Version1();
	m_inner.Rva0055B8CD::rva0055B8CD(xfer);
}
