// cl: /O1 /arch:SSE /G7 /MD
//
// ??0Rva005D242F@@QAE@PAURva005D242FLinked@@HPAX1@Z @ 0x005D2405 (42B): ctor of Rva005D242F with
// vtable 0x008757D8. Target evidence: calls rowed base
// ??0Rva005C3F02@@QAE@PAX0@Z at 0x005C40E7 with two pointers then stores
// arg0 at +0x8 and arg1 at +0xC and returns this with ret 16. Base layout
// and vtable shared with Rva005D242FDtor.cpp. Caller at 0x005D28AE.
struct Rva005D242FLinked
{
	int m00, m04, m08, m0C, m10, m14;
	int m18;
};

class Rva005C3F02
{
public:
	virtual ~Rva005C3F02();
	Rva005C3F02(void *a1, void *a2);
protected:
	int m04;
	Rva005D242FLinked *m08;
};

class Rva005D242F : public Rva005C3F02
{
public:
	Rva005D242F(Rva005D242FLinked *a0, int a1, void *a2, void *a3);
	virtual void rva005D2449();
	virtual void rva005D24B1();
private:
	int m0C;
};

Rva005D242F::Rva005D242F(Rva005D242FLinked *a0, int a1, void *a2, void *a3)
	: Rva005C3F02(a2, a3)
{
	m08 = a0;
	m0C = a1;
}
