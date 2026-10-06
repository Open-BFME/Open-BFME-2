// cl: /MD
//
// ?xfer@Rva00589051@@MAEXPAVXfer@@@Z retail 0x00589051 40B xfer with single
// ObjectID at +0x14. Evidence: Version1 via rowed 0x000053EE then base
// ?xfer@BehaviorModule@@QAEXPAVXfer@@@Z via rowed 0x004C9C7D then
// ?XferObjectID@@YAXPAVXfer@@PAW4ObjectID@@@Z via rowed 0x003060B2 with
// add esi 0x14; sole direct caller at 0x00484FCD; between
// ??_GRva00484EF4 and ??1Rva00589079. Identity stays honest address name.

class Xfer
{
public:
	void Version1();
};

class BehaviorModule
{
public:
	virtual void anchor();
	void xfer(Xfer *xfer);
	unsigned int m_04;
	void *m_object;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva00589051 : public BehaviorModule
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad[0x08];
	ObjectID m_14;
};

void Rva00589051::xfer(Xfer *xfer)
{
	xfer->Version1();
	BehaviorModule::xfer(xfer);
	XferObjectID(xfer, &m_14);
}
