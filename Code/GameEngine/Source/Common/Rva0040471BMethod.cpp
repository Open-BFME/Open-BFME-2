// cl: /O1 /arch:SSE /G7 /MD
// ?rva0040471B@Rva0040471B@@QAEXPAVRva0040471BXfer@@@Z retail 0x0040471B 65B
// Identity is address-derived; the call sites at 0x004057F5 and 0x00405872
// establish a thiscall serializer with an interface pointer argument. The
// five consecutive xfer destinations and dispatch slots come from retail.
class Rva0040471BXfer
{
public:
	virtual void slot00(void *) = 0;
	virtual void slot01(void *) = 0;
	virtual void slot02(void *) = 0;
	virtual void slot03(void *) = 0;
	virtual void slot04(void *) = 0;
	virtual void slot05(void *) = 0;
	virtual void slot06(void *) = 0;
	virtual void slot07(void *) = 0;
	virtual void slot08(void *) = 0;
	virtual void slot09(void *) = 0;
	virtual void slot10(void *) = 0;
	virtual void slot11(void *) = 0;
	virtual void slot12(void *) = 0;
	virtual void slot13(void *) = 0;
	virtual void slot14(void *) = 0;
	virtual void slot15(void *) = 0;
	virtual void slot16(void *) = 0;
	virtual void slot17(void *) = 0;
	virtual void slot18(void *) = 0;
	virtual void slot19(void *) = 0;
	virtual void slot20(void *) = 0;
	virtual void slot21(void *) = 0;
	virtual void slot22(void *) = 0;
	virtual void slot23(void *) = 0;
	virtual void slot24(void *) = 0;
	virtual void slot25(void *) = 0;
	virtual void slot26(void *) = 0;
	virtual void slot27(void *) = 0;
	virtual void slot28(void *) = 0;
};

class Rva0040471B
{
public:
	void rva0040471B(Rva0040471BXfer *xfer);
	unsigned int m_values[5];
};

void Rva0040471B::rva0040471B(Rva0040471BXfer *xfer)
{
	Rva0040471B *self = this;
	xfer->slot27(self);
	xfer->slot28(&self->m_values[1]);
	xfer->slot28(&self->m_values[2]);
	xfer->slot28(&self->m_values[3]);
	xfer->slot28(&self->m_values[4]);
}
