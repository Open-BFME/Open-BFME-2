// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
// Native 002AE71D..002AE76B, 78B, RET4. Native Xfer version record
// {1,1}, existing state-pointer worker, same-this float-vector transfer,
// labelled ObjectID +10 and unsigned word +14. Original owner unknown.
class Xfer;
enum ObjectID { INVALID_ID = 0 };
void XferObjectID(Xfer *, ObjectID *);
struct Rva002AE71DVersion {
	Rva002AE71DVersion() : value(1), limit(1) {}
	unsigned char value, limit;
};
class Rva002AE71DXferView {
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10(Rva002AE71DVersion *);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36(unsigned int *);
};
class ObjectFilter { public: void DoXfer(Xfer *); };
class Rva002AE71D {
public:
	void rva002AE71D(Xfer *);
	void rva002ADDD9(Xfer *);
private:
	ObjectFilter *member00;
	char unknown04[0x10 - 4];
	ObjectID id10;
	unsigned int word14;
};

void Rva002AE71D::rva002AE71D(Xfer *xfer)
{
	Rva002AE71DVersion version;
	reinterpret_cast<Rva002AE71DXferView *>(xfer)->slot10(&version);
	member00->DoXfer(xfer);
	rva002ADDD9(xfer);
	XferObjectID(xfer, &id10);
	reinterpret_cast<Rva002AE71DXferView *>(xfer)->slot36(&word14);
}
