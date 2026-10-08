// cl: /DNDEBUG /MD
// ?rva006F1530@@YAXPAVBfmeAptValue006DCD20@@@Z @0x006F1530 63B
//
// Apt predicate-to-bool conversion helper. Calls the rowed isXmlNode()
// (0x006DBDE0) and, when its checked cast carries a non-null inner at +0x20,
// publishes (inner->slot9() != 0) through the rowed MakeBool (0x006D88C0);
// otherwise publishes false.
//
// Two distinct compiler barriers keep BOTH MakeBool calls out of tail position
// (MSVC would otherwise reuse the incoming argument slot and jmp): the shared
// false path uses _WriteBarrier, which does not fold into one shared call the
// way a second _ReadWriteBarrier does.
extern "C" void _ReadWriteBarrier(void);
extern "C" void _ReadBarrier(void);
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#pragma intrinsic(_ReadBarrier)
#pragma intrinsic(_WriteBarrier)

class Rva006F1530Inner
{
public:
	virtual void *s0();
	virtual void *s1();
	virtual void *s2();
	virtual void *s3();
	virtual void *s4();
	virtual void *s5();
	virtual void *s6();
	virtual void *s7();
	virtual void *s8();
	virtual void *slot9();
};

class BfmeAptValue006DCD20
{
public:
	virtual void vtableSlot0();
	int isXmlNode() const;
	BfmeAptValue006DCD20 *rva006DD220();

private:
	char m_pad[0x1C];

public:
	Rva006F1530Inner *m_inner20;	// +0x20
};

class AptValue;
// The value maker is the rowed AptBoolean::Create.
class AptBoolean
{
public:
	static AptValue *Create(bool value);
};

void rva006F1530(BfmeAptValue006DCD20 *obj)
{
	if ((unsigned char)obj->isXmlNode()) {
		BfmeAptValue006DCD20 *p = obj->rva006DD220();
		Rva006F1530Inner *inner = p->m_inner20;
		if (inner) {
			AptBoolean::Create(inner->slot9() != 0);
			_ReadWriteBarrier();
			return;
		}
	}
	AptBoolean::Create(false);
	_WriteBarrier();
}
