// cl: /DNDEBUG /MD /EHsc
// ??0Rva005E54D5@@QAE@HHH@Z @0x005E54D5 34B
// Derived ctor (a, b, c): forwards (a, b, 0, c) to base 0x005F3E93 (pinned,
// 4 args ret 0x10) then installs its own vtable. No extra members beyond base.
// Pushes in retail: c, 0, b, a so base sees (a, b, 0, c). Address-derived.
class Rva005F3E93
{
public:
	Rva005F3E93(int a, int b, int c, int d);
	virtual ~Rva005F3E93();
};

class Rva005E54D5 : public Rva005F3E93
{
public:
	Rva005E54D5(int a, int b, int c);
	virtual ~Rva005E54D5();
};

Rva005E54D5::Rva005E54D5(int a, int b, int c)
	: Rva005F3E93(a, b, 0, c)
{
}
