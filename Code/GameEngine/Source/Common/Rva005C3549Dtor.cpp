// cl: /MD /EHsc
// ??1Rva005C3549@@UAE@XZ retail 0x005C3549 54B
// Evidence: vtable 0x00874478 then clear 0x000AD6F4 on +8 then vtable 0x007C6F20; callers 0x00568617 0x005C367E
class Rva005C3549;

// Allocation size and constructor ABI come from 5C361D/5C3697. The callee
// installs C74434, whose rowed destructor is Rva005C33D2. Inputs stay opaque.
class Rva005C33D2
{
public:
	Rva005C33D2(Rva005C3549 *owner, void *first, void *second, void *third);
	virtual ~Rva005C33D2();
private:
	char storage[0x18];
};

// Target 5C361D reads two pointer-sized words; the original type is unknown.
struct Rva005C3549Inputs
{
	void *first;
	void *second;
};

class Rva000AD6F4
{
public:
	void clear();
	__forceinline void setNew(Rva005C33D2 *value) { pointer = value; }
private:
	Rva005C33D2 *pointer;
};

class Rva005C3549Base
{
public:
	__forceinline Rva005C3549Base() : m04(0) {}
	virtual ~Rva005C3549Base() {}
protected:
	int m04;
};

class Rva005C3549 : public Rva005C3549Base
{
public:
	Rva005C3549(void *first, void *second, void *third);
	Rva005C3549(void *first, const Rva005C3549Inputs &inputs);
	virtual ~Rva005C3549();
private:
	Rva000AD6F4 m08;
};

// 92B target constructor: zero count +4; allocate 1C; store owner at +8.
Rva005C3549::Rva005C3549(void *first, void *second, void *third)
{
	m08.setNew(new Rva005C33D2(this, first, second, third));
}

// 94B sibling uses the same implementation with the two-word input pair.
Rva005C3549::Rva005C3549(void *first, const Rva005C3549Inputs &inputs)
{
	m08.setNew(new Rva005C33D2(this, first, inputs.first, inputs.second));
}

Rva005C3549::~Rva005C3549()
{
	m08.clear();
}
