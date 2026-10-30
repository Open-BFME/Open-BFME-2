// cl: /MD
// Target evidence: Ghidra boundary 0x00479CF6, 50 bytes. It tests the result
// of the matched 0x00462785 at this-0x28. On true it passes that subobject to
// 0x00588E44 through this+0x9B8; on false it calls vtable slot 32 on this-8
// with value 2. The 0x00588E44 pin records only its direct-call ABI/address;
// its 285-byte body and identity remain unresolved.
class Rva00462785 {
public:
	int rva00462785();
};

class Object;

class Rva0047A040Base9E0
{
public:
	Rva0047A040Base9E0();
	bool rva00588D24(void *a, Object *b);
	void rva00588D99(Object *obj);
	void rva00588E20(Object *object);
	void rva00588E44(void *argument);
	void *rva00588B8A(void *key);
	int m_nextFrame; // +0x00
};
class Rva00479CF6Dispatch {
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
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
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32(int value) = 0;
};

class Rva00479CF6 {
public:
	void rva00479CF6(int unused);
};

void Rva00479CF6::rva00479CF6(int unused)
{
	Rva00462785 *predicate = (Rva00462785 *)((char *)this - 0x28);
	if ((unsigned char)predicate->rva00462785() != 0) {
		((Rva0047A040Base9E0 *)((char *)this + 0x9B8))->rva00588E44(predicate);
	} else {
		((Rva00479CF6Dispatch *)((char *)this - 8))->slot32(2);
	}
}
