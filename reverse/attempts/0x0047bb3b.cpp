// ?rva0047BB3B@Rva0047BB3B@@QAEXPAVObject@@@Z
// partial score=0.72 date=2026-10-06
// cl: /MD
// Target evidence: Ghidra boundary 0x0047BB3B, 48 bytes. A null object returns;
// otherwise bit 1 of Object+0x126 is cleared and the matched notifier
// 0x0028AE6D is called when that bit was set, then the object is forwarded to
// 0x00467AB8. The latter pin records only the direct-call ABI/address; its
// 726-byte target body and identity remain unclaimed.
class Object {
public:
	char opaque00[0x126];
	unsigned char flag126Bit0 : 1;
	volatile unsigned char flag126Bit1 : 1;
	unsigned char flag126OtherBits : 6;
	void rva0028AE6D();
};

class Rva00467AB8 {
public:
	void rva00467AB8(Object *object);
};

class Rva0047BB3B {
public:
	void rva0047BB3B(Object *object);
};

void Rva0047BB3B::rva0047BB3B(Object *object)
{
	if (object == 0) {
		return;
	}
	if (object->flag126Bit1 != 0) {
		object->flag126Bit1 = 0;
		object->rva0028AE6D();
	}
	((Rva00467AB8 *)this)->rva00467AB8(object);
}
