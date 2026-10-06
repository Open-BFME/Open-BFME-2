// cl: /MD
// ?Rva0058731DCheck@@YAPAVRva0058731DHost@@PAV1@H@Z @0x0058731D 88B: verify
// via vtable slot 30 with an int out-param seeded to 4; on change format an
// XferException and throw it, else invoke vtable slot 19 four times with a
// stride-8 argument and return the host.
// Evidence: callers 0x00588B51; throw idiom plus slot-N virtual pattern from
// Code/Libraries/Source/xfer/xfer_load.cpp; rowed _bfmeFormatText 0x0060C36E
// plus pinned _CxxThrowException 0x00629094 plus XferException's throw information.
// Neighbours 0x00587311 0x00587375.
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	void *text;
	int tag;
};


class Rva0058731DHost
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19(int value);
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
	virtual void slot30(int *count);
};

Rva0058731DHost *Rva0058731DCheck(Rva0058731DHost *host, int base)
{
	int n = 4;
	int count = 4;
	host->slot30(&count);
	if (count != 4)
	{
		throw XferException(0, 0);
	}
	int value = base;
	do
	{
		host->slot19(value);
		value += 8;
	} while (--n != 0);
	return host;
}
