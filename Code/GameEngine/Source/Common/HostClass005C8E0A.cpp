// cl: /MD

class TargetObj005C8DBF {
public:
	void method_005C8DBF(float val);
	void method_005C902A(float val);
};

struct Element005C8E0A {
	TargetObj005C8DBF *m_obj;
	int m_pad4;
	float m_val;
};

class HostClass005C8E0A {
public:
	char pad[0x38];
	Element005C8E0A *m_start;
	Element005C8E0A *m_finish;

	void method_005C8E0A();
	void method_005C9069();
};

void HostClass005C8E0A::method_005C8E0A()
{
	for (Element005C8E0A *it = m_start; it != m_finish; ++it) {
		it->m_obj->method_005C8DBF(it->m_val);
	}
}

void HostClass005C8E0A::method_005C9069()
{
	for (Element005C8E0A *it = m_start; it != m_finish; ++it) {
		it->m_obj->method_005C902A(it->m_val);
	}
}
