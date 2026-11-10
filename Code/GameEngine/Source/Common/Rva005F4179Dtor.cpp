// cl: /Ob2 /EHsc /MD
// ??1Rva005F4179@@UAE@XZ @ 0x005F4179 54B
// Evidence: retail EH_prolog scope 0x007A51B4 store 0x00C79448 at [this] state 0 lea ecx [esi+8] call rowed ?clear@Rva005F4096@@QAEXXZ @0x005F4096 then store base 0x00BC6F20; same 54B shape as rowed ??1Rva005E129B@@UAE@XZ @0x005E129B; vtable slot 0x00C79448#0; caller 0x005F41BA deleting dtor.
// Constructor005F412B..005F4179 is the shared virtual base constructed by
// native ArmyDetailsPanel icon constructors005E39F3/005E3BD5/005E3C90.
// The primary vtable00879448 already names Rva005F4179 through its54B
// complete destructor. Native base+4 starts at zero; the owned leaf at+8
// comes from a24B allocation and rowed constructor005F3F73(this, clip).
// The leaf's entire39B body performs only member stores, so it cannot throw
// a C++ exception under /EHsc. Its nonthrowing declaration preserves the
// native absence of an allocation-delete EH state. Original class names
// and the clip's application type remain unknown.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
class AptMovieClipFrame;

class Rva005F3F73 {
public:
    Rva005F3F73(void *, void *) throw();
private:
    char storage[0x18];
};
class Rva005F4096
{
public:
	void clear();
    Rva005F4096(Rva005F3F73 *p) : m_ptr(p) {}
private:
    Rva005F3F73 *m_ptr;
};

class Rva005F4179Base
{
public:
	Rva005F4179Base() : m_04(0) {}
	virtual ~Rva005F4179Base() {}
protected:
	int m_04;
};

class Rva005F4179 : public Rva005F4179Base
{
public:
	Rva005F4179(void *clip);
    virtual ~Rva005F4179();
	virtual void slot01() = 0;
	virtual TreeHintRef00217D4C CreateMovieClip(AptMovieClipFrame *) = 0;
	virtual TreeHintRef00217D4C rva005F4710();
	virtual void DoUpdate();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
private:
	Rva005F4096 m_08;
};

Rva005F4179::~Rva005F4179()
{
	m_08.clear();
}

Rva005F4179::Rva005F4179(void *clip) : m_08(new Rva005F3F73(this, clip)) {}
