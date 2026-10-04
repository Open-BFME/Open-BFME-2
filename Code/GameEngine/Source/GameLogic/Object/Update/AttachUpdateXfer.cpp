// cl: /O1 /DNDEBUG /MD
//
// AttachUpdate::xfer, retail 0x004918AC (102 bytes): slot 3 of the class's
// primary vtable 0x00C4DB20. Version 3 over the UpdateModule base: the
// attached Object's ID (+0x20); before version 2 a dropped bool; from version
// 3 the +0x24 handle through TheEva's 0x001DEC48 (pinned by address; it runs
// its own versioned xfer). The version block is the BFME2 two-byte form the
// rowed Rva0054840AXfer.cpp uses.
typedef unsigned char UnsignedByte;
typedef bool Bool;
struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};
class Xfer
{
public:
	virtual ~Xfer();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35();
	virtual Xfer &xferBool(Bool *value);
};
enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *objectID);
class Eva
{
public:
	void rva001DEC48(Xfer *xfer, int *handle);
};
extern Eva *TheEva;
class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	unsigned char m_pad04[0x20 - 0x04];
};
class AttachUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	ObjectID m_attachedID;		// +0x20
	int m_evaHandle;		// +0x24
};
void AttachUpdate::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 3;
	xfer->xferVersion(&version);
	UpdateModule::xfer(xfer);
	XferObjectID(xfer, &m_attachedID);
	if (version.m_currentVersion < 2)
	{
		Bool dropped = false;
		xfer->xferBool(&dropped);
	}
	if (version.m_currentVersion >= 3)
		TheEva->rva001DEC48(xfer, &m_evaHandle);
}
