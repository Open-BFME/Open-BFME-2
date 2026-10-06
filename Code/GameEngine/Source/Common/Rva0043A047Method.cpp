// cl: /DNDEBUG /MD /O1
// Target 0x0043A047 (79 bytes; Ghidra boundary FUN_0083a047) takes a pointer
// in EAX/stack and uses virtual slots 10, 30, and 1 on it. Slot 30 receives
// this+0x14. If the two-byte slot-10 result's second byte is at least 2, the
// slot-1 result selects a direct helper at 0x00439F3F or 0x00438FF4. The
// receiver, helper identities, and field meanings remain address-derived.

class RvaInterface0043A047
{
public:
	virtual void slot00() = 0;
	virtual bool slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10(unsigned char *out) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30(unsigned char *out) = 0;
};

class Rva00439F3F
{
public:
	void rva00439F3F(void *argument);
};

class Rva00438FF4
{
public:
	void rva00438FF4(void *argument);
};

class Rva0043A047
{
	unsigned char m_pad000[0x14];
	unsigned char m_opaqueOutput[4];

public:
	void method(void *argument);
};

void Rva0043A047::method(void *argument)
{
	unsigned char state[2];
	state[0] = 1;
	state[1] = 2;
	((RvaInterface0043A047 *)argument)->slot10(state);
	if (state[1] >= 2)
	{
		((RvaInterface0043A047 *)argument)->slot30(&m_opaqueOutput[0]);
		if (((RvaInterface0043A047 *)argument)->slot01())
			((Rva00439F3F *)this)->rva00439F3F(argument);
		else
			((Rva00438FF4 *)this)->rva00438FF4(argument);
	}
}
