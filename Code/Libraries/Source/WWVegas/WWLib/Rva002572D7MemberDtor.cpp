// cl: /MD
// ??1Rva002572D7Member@@QAE@XZ @0x002572D7 23B
// Non-virtual dtor: clears intrusive list via rowed 0x00256F84 then frees head at +0 via rowed _free 0x00030830.
// Evidence: callers 0x002574B7 and jmp 0x00257464; LINK BONUS name; callee rows.
class Rva00256F84
{
public:
	void rva00256F84();
protected:
	void *m_head00;
};

extern "C" void __cdecl free(void *block);

class Rva002572D7Member : public Rva00256F84
{
public:
	~Rva002572D7Member();
};

Rva002572D7Member::~Rva002572D7Member()
{
	rva00256F84();
	if (m_head00 != 0)
		free(m_head00);
}
