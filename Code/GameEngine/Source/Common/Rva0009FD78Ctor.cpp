// cl: /O1
// ??0Rva0009FD78@@QAE@PAX@Z @0x0009FD60 24B ctor installing vtable 0x007C8C54.
// Evidence: calls base ??0Rva0078D310Host@@QAE@PAX@Z 0x00104F8F with same void* arg then stores vtable; dispatch 0x0009FD78 is slot5 of same table; callers 0x0008F925 and 0x0009FDBD.
class Rva0078D310Host {
public:
	Rva0078D310Host(void *context);
	virtual ~Rva0078D310Host();
};

class Rva0009FD78 : public Rva0078D310Host {
public:
	Rva0009FD78(void *context);
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual int dispatch();
};

Rva0009FD78::Rva0009FD78(void *context) : Rva0078D310Host(context)
{
}
