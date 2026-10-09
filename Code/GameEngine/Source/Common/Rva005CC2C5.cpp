// cl: /MD
// ?rva005CC2C5@Rva005CC2C5@@QAEXH@Z @0x005CC2C5 23B unregister calls rowed 0x002B7250 erase with this then clears holder.
// Evidence: callee rowed 0x002B7250; holder at +8 with list at +4; ret 4 one int param; no callers.
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
struct Holder002B7250
{
    virtual void slot00();
    virtual void slot04();
    virtual void slot08(unsigned char flag);
	Rva002B7250 m_list04;
};
struct Rva0042D6D6PtrChaseField { int get() const; };
struct Rva002BA8F1Listener { char opaque[4]; };
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *p); };

class Rva005CC2C5
{
public:
	void rva005CC2C5(int dummy);
    void rva005CC2DC();
private:
	char m_pad[4];
    Rva0042D6D6PtrChaseField *m_source04;
	Holder002B7250 *m_holder08;
    unsigned char m_flag0C;
};
void Rva005CC2C5::rva005CC2C5(int /*dummy*/)
{
	m_holder08->m_list04.rva002B7250((CreateAHeroData *)this);
	m_holder08 = 0;
}

// Native47B5CC2DC..5CC30B RET0. Byte argument ABI (MOV DL; PUSH EDX) proves
// the notification takes the low byte rather than an integer flag.
void Rva005CC2C5::rva005CC2DC()
{
    if (m_holder08) return;
    int value = m_source04->get();
    m_holder08 = (Holder002B7250 *)value;
    if (!value) return;
    ((Rva005A0B4CList *)((char *)value + 4))->append((Rva002BA8F1Listener *)this);
    m_holder08->slot08(m_flag0C);
}
