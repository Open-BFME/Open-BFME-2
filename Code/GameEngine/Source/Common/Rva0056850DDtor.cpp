// cl: /O1 /arch:SSE /G7 /MD
// ??1Rva0056850D@@QAE@XZ @0x0056850D 26B: public non-virtual dtor deletes
// m_value (named Impl destructor 0x0056820D) via operator delete 0x0002FD60 then
// nulls it; caller 0x0056860C in Rva005685EE dtor; LINK BONUS name; real size
// 26B of served 127B (rest is separate ctor at 0x00568527).
// Destructor-only view: the holder operates on a pointer; no allocation,
// sizeof, field access or claim about Impl's extent occurs in this unit.
// WB and the native observer tables establish the nonvirtual destructor.
// Its scalar delete wrapper 0x00568323 is emitted here by this actual consumer,
// replacing the independent neutral family copy without another class view.
class InGameToggleStanceCommandButton {
public:
 class Impl { public: ~Impl(); };
};

class Rva0056850D
{
public:
	~Rva0056850D();

private:
	InGameToggleStanceCommandButton::Impl *m_value;
};

Rva0056850D::~Rva0056850D()
{
	InGameToggleStanceCommandButton::Impl *tmp = m_value;
	m_value = 0;
	delete tmp;
}
