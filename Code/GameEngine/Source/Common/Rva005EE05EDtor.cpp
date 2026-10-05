// cl: /O1 /MD
// ??1Rva005EE05E@@UAE@XZ @0x005EE05E 14B
// Dtor stores vtable 0x008786A8 then tail-jmps to member clear at +4 through
// rowed 0x005EDFF5. Evidence: pin ??1Rva005EE05E, vtable immediate, rowed
// clear, callers deleting dtor plus thunk.
class Rva005EDFF5
{
public:
	void clear();
};

class Rva005EE05E
{
public:
	virtual ~Rva005EE05E();
private:
	Rva005EDFF5 m_04;	// +4
};

Rva005EE05E::~Rva005EE05E()
{
	m_04.clear();
}
