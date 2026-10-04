// cl: /O1 /DNDEBUG /MD
//
// SlaveWatcherBehavior::xfer, retail 0x00484673 (84 bytes): slot 3 of the
// class's primary vtable 0x00C4A264. Version 1 (the rowed Xfer::Version1)
// over the rowed UpdateModule::xfer, then the watched Object's ID (+0x20)
// and the 1024-bit set at +0x24: while the Xfer's slot 4 answers false the
// set goes through the free helper 0x003064CB (pinned by address; its own
// Version1 block), otherwise through the rowed Rva00291440 packer with the
// Xfer as its byte sink (the second caller of that row besides 0x002977F8).
typedef bool Bool;
class Xfer
{
public:
	virtual ~Xfer();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual Bool slot04();
	void Version1();
};
enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *objectID);
class Sink00291440;
class Rva00291440
{
public:
	void rva00291440(Sink00291440 *sink);
private:
	unsigned int m_bits[32];
};
void rva003064CB(Xfer *xfer, Rva00291440 *bits);
class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	unsigned char m_pad04[0x20 - 0x04];
};
class SlaveWatcherBehavior : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	ObjectID m_watchedID;		// +0x20
	Rva00291440 m_bits;		// +0x24
};
void SlaveWatcherBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	Bool viaHelper = !xfer->slot04();
	XferObjectID(xfer, &m_watchedID);
	if (viaHelper)
		rva003064CB(xfer, &m_bits);
	else
		m_bits.rva00291440((Sink00291440 *)xfer);
}
