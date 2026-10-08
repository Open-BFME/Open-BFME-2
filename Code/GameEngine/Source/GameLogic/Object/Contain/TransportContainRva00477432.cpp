// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00477432@Rva00477432@@QAEXPAVObject@@H@Z, retail 0x00477432..0x0047748E
// (92 bytes, RET 8): slot 58 of TransportContain's contain-interface vtable
// (the B8 base), the transport twin of the rowed garrison handler 0x00479DCD.
// The outer contain starts 0x20 bytes before this interface. An object the
// +0xFD record knows (rowed 0x00588B8A) goes through the outer 0x004770DE
// and its entry is told through slots 74 and 4 (with 1); otherwise an object
// with status 0x26 goes to 0x00477365, any other to 0x004770DE (both not yet
// rowed; pinned). WorldBuilder's twin (0x0119FCF0) is unnamed.

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
};

class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *key);
};

class Rva00477432Outer
{
public:
	void rva004770DE(Object *obj);
	void rva00477365(Object *obj);
};

class Rva00477432Entry
{
public:
#define V(n) virtual void pad##n();
	V(0)
#undef V
	virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(int value);
#define V(n) virtual void pad##n();
	V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73)
#undef V
	virtual void slot74();
};

class Rva00477432
{
public:
	void rva00477432(Object *obj, int unused);
private:
	Rva00477432Outer *outer() { return reinterpret_cast<Rva00477432Outer *>(reinterpret_cast<char *>(this) - 0x20); }

	unsigned char m_pad00[0xFD];
	Rva0047A040Base9E0 m_recordFD;			// +0xFD
};

void Rva00477432::rva00477432(Object *obj, int /*unused*/)
{
	Rva00477432Entry *entry = static_cast<Rva00477432Entry *>(m_recordFD.rva00588B8A(obj));
	if (entry)
	{
		outer()->rva004770DE(obj);
		entry->slot74();
		entry->slot4(1);
	}
	else if (obj->testStatus(OBJECT_STATUS_26))
		outer()->rva00477365(obj);
	else
		outer()->rva004770DE(obj);
}
