// cl: /MD
// ?rva0007E02A@Rva0007E02A@@QAEPAXPAX@Z @ 0x0007E02A (16B): __thiscall forwarder
// to vtable slot 3; pushes out-param then calls [eax+0xC] and returns the same
// pointer. Evidence: callers 0x0007E6F6/0x0030D111 pass stack locals for a
// 12-byte fill; slot 3 matches xfer position but class remains opaque.

class Rva0007E02A {
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void slot3(void *out);
public:
	void *rva0007E02A(void *out);
};

void *Rva0007E02A::rva0007E02A(void *out)
{
	slot3(out);
	return out;
}
