// cl: /DNDEBUG /MD
// ??0Rva005747DA@@QAE@HH@Z retail 0x005747DA 31B
// Derived ctor of rowed base Rva005746AF (0x005746AF): passes first int arg
// to base, stores second int arg at +0x10 and overwrites vtable with 0x0086E3CC.
// Evidence: call to rowed 0x005746AF, vtable store at [this], ret 8 two args,
// sole caller at 0x0057488B; neighbours share /O1. Honest Rva name.
class Rva005746AF
{
public:
	Rva005746AF(int arg);
	virtual ~Rva005746AF();
private:
	int m_04;
	unsigned long m_08;
	int m_0C;
};

class Rva005747DA : public Rva005746AF
{
public:
	Rva005747DA(int a1, int a2);
	virtual ~Rva005747DA();
private:
	int m_10;
};
Rva005747DA::Rva005747DA(int a1, int a2)
	: Rva005746AF(a1)
	, m_10(a2)
{
}
