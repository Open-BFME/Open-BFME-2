// cl: /MD
// Target evidence: Ghidra boundary 0x00479BA1, 36 bytes. The wrapper calls
// 0x00463509 with ECX=this+0x20 and (object,false), then calls the matched
// 0x00588E20 with ECX=this+0x9E0 and the same object. Only those subobject
// offsets are claimed; the owning class name remains address-derived.
// The 0x00463509 pin records the call ABI and address, not the blocked target's
// unresolved OpenContain identity.
class Object;

class Rva00463509 {
public:
	void removeFromContain(Object *object, bool flag);
};

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
class Rva00479BA1
{
public:
	void rva00479BA1(Object *object);
};

void Rva00479BA1::rva00479BA1(Object *object)
{
	((Rva00463509 *)((char *)this + 0x20))->removeFromContain(object, false);
	((Rva0047A040Base9E0 *)((char *)this + 0x9E0))->rva00588E20(object);
}
