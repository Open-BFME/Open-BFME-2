// cl: /O1 /MD

struct Rva005C847BRecord {
	char pad[0x48];
	void method_005C901B();
	void method_005C8F50(int a0, int a1);
	void method_005C90F1(int a0, int a1);
	void method_005C9311(int m14, int a0, float a1);
};

class HostClass005C815B {
public:
	int pad0;
	int pad4;
	Rva005C847BRecord *m_start;
	Rva005C847BRecord *m_finish;
	Rva005C847BRecord *m_endOfStorage;
	int m_14;

	void method_005C815B();
	void method_005C834A(int a0, int a1);
	void method_005C836F(int a0, float a1);
	void method_005C839B(int a0, int a1);
};

void HostClass005C815B::method_005C815B()
{
	for (Rva005C847BRecord *it = m_start; it != m_finish; ++it) {
		it->method_005C901B();
	}
}

void HostClass005C815B::method_005C834A(int a0, int a1)
{
	for (Rva005C847BRecord *it = m_start; it != m_finish; ++it) {
		it->method_005C8F50(a0, a1);
	}
}

void HostClass005C815B::method_005C836F(int a0, float a1)
{
	for (Rva005C847BRecord *it = m_start; it != m_finish; ++it) {
		it->method_005C9311(m_14, a0, a1);
	}
}

class HostClass005C8E0A {
public:
	void rva005C8F17();
};

void HostClass005C815B::method_005C839B(int a0, int a1)
{
	for (Rva005C847BRecord *it = m_start; it != m_finish; ++it) {
		it->method_005C90F1(a0, a1);
	}
}

void Rva005C847BRecord::method_005C901B()
{
	((HostClass005C8E0A *)this)->rva005C8F17();
	*(unsigned short *)((char *)this + 0x44) = 0;
}
