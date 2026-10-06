// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva0009FDBD@@QAE@PAX@Z @0x0009FDBD 24B ctor installing vtable 0x007C8C80.
// Evidence: calls base ??0Rva0009FD78@@QAE@PAX@Z 0x0009FD60 with same void* arg then stores vtable; caller 0x0008F986 in 0x0008F95F.
class Rva0009FD78 {
public:
	Rva0009FD78(void *context);
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual int dispatch();
};

class Rva0009FDBD : public Rva0009FD78 {
public:
	Rva0009FDBD(void *context);
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual int dispatch();
};

Rva0009FDBD::Rva0009FDBD(void *context) : Rva0009FD78(context)
{
}
