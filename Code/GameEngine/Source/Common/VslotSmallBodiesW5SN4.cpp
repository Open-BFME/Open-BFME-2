// cl: /DNDEBUG /MD
//
// Vtable-slot forwarders with no ledger owner, batch W5SN4: each loads a
// member pointer and tail-jumps to a function that is either already rowed
// or pinned in reverse/symbols.csv under an address-derived name with the
// argument count its ret shows. Classes are address-derived and model only
// the member.

typedef int Int;

class Rva0057845C
{
public:
	void rva0057845C(Int a0);
};
class Rva00578513
{
public:
	void rva00578513(Int a0);
private:
	char m_pad00[0x04];
	Rva0057845C *m_04;
};
void Rva00578513::rva00578513(Int a0)
{
	m_04->rva0057845C(a0);
}

class Rva005CB748
{
public:
	void rva005CB748();
};
class Rva005CB852
{
public:
	void rva005CB852();
private:
	char m_pad00[0x04];
	Rva005CB748 *m_04;
};
void Rva005CB852::rva005CB852()
{
	m_04->rva005CB748();
}

class Rva005E2E3A
{
public:
	void rva005E2E3A(Int a0, Int a1);
};
class Rva005E3049
{
public:
	void rva005E3049(Int a0, Int a1);
private:
	char m_pad00[0x04];
	Rva005E2E3A *m_04;
};
void Rva005E3049::rva005E3049(Int a0, Int a1)
{
	m_04->rva005E2E3A(a0, a1);
}

class Rva005ED385
{
public:
	void rva005ED385(Int a0, Int a1);
};
class Rva005ED5BB
{
public:
	void rva005ED5BB(Int a0, Int a1);
private:
	char m_pad00[0x04];
	Rva005ED385 *m_04;
};
void Rva005ED5BB::rva005ED5BB(Int a0, Int a1)
{
	m_04->rva005ED385(a0, a1);
}

class Rva005ED6B9
{
public:
	void rva005ED6B9(Int a0, Int a1);
};
class Rva005ED849
{
public:
	void rva005ED849(Int a0, Int a1);
private:
	char m_pad00[0x04];
	Rva005ED6B9 *m_04;
};
void Rva005ED849::rva005ED849(Int a0, Int a1)
{
	m_04->rva005ED6B9(a0, a1);
}

namespace StrategicHUD
{
class BattlePromptMovieClip
{
public:
	class Impl
	{
	public:
		void rva005F96D4();
	};
};
}
class Rva005F977D
{
public:
	void rva005F977D();
private:
	char m_pad00[0x04];
	StrategicHUD::BattlePromptMovieClip::Impl *m_04;
};
void Rva005F977D::rva005F977D()
{
	m_04->rva005F96D4();
}
