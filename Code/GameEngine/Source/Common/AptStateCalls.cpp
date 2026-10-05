// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Apt panel state toggles: each calls the panel's Apt function through the
// rowed Rva005FB5E6AptCall wrapper. The arguments are TheRva00222A8BTarget,
// the panel's level and name fields, the function and "_show" or "_hide".
// A flag records the state. The value-setting halves defer to the rowed free
// setters Rva0057A5A8Set (TimeRemaining) and Rva005EF096Set (CommandPoints),
// which receive the name field's address as their team pointer slot.
// Function and argument names are the retail strings; class names are
// address-derived.
//
// ?rva0057A861@Rva0057A861@@QAEXH@Z  @0x0057A861 92B  SetTimeRemainingState _show + value
// ?rva0057A8BD@Rva0057A861@@QAEXXZ   @0x0057A8BD 60B  SetTimeRemainingState _hide
// ?rva005EF2BE@Rva005EF2BE@@QAEXHH@Z @0x005EF2BE 105B SetCommandPointsState value + _show
// ?rva005EF327@Rva005EF2BE@@QAEXXZ   @0x005EF327 63B  SetCommandPointsState _hide
#include "ascii_string.h"

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

struct Rva0057A5A8Team;
void Rva0057A5A8Set(int level, Rva0057A5A8Team **ppTeam, int totalSeconds);

struct Rva005EF096Outer;
void Rva005EF096Set(int level, Rva005EF096Outer *outer, int a, int b);

class Rva0057A861
{
public:
	void rva0057A861(int seconds);
	void rva0057A8BD();
private:
	char m_pad00[8];
	unsigned int m_level;		// +0x08
	StringBase<char> m_name;	// +0x0C
	char m_pad10[0x34];
	int m_seconds;				// +0x44
	bool m_shown;				// +0x48
};

void Rva0057A861::rva0057A861(int seconds)
{
	if (!m_shown)
	{
		Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "SetTimeRemainingState", "_show");
		m_shown = true;
	}
	if (seconds != m_seconds)
	{
		Rva0057A5A8Set(m_level, (Rva0057A5A8Team **)&m_name, seconds);
		m_seconds = seconds;
	}
}

void Rva0057A861::rva0057A8BD()
{
	if (m_shown)
	{
		Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "SetTimeRemainingState", "_hide");
		m_shown = false;
	}
}

class Rva005EF2BE
{
public:
	void rva005EF2BE(int a, int b);
	void rva005EF327();
private:
	unsigned int m_level;		// +0x00
	StringBase<char> m_name;	// +0x04
	char m_pad08[0x2C];
	int m_a;					// +0x34
	int m_b;					// +0x38
	char m_pad3C;
	bool m_shown;				// +0x3D
	bool m_3E;					// +0x3E
};

void Rva005EF2BE::rva005EF2BE(int a, int b)
{
	if (a != m_a || b != m_b)
	{
		Rva005EF096Set(m_level, (Rva005EF096Outer *)&m_name, a, b);
		m_a = a;
		m_b = b;
	}
	if (!m_shown)
	{
		Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "SetCommandPointsState", "_show");
		m_shown = true;
	}
}

void Rva005EF2BE::rva005EF327()
{
	if (m_shown)
	{
		Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "SetCommandPointsState", "_hide");
		m_shown = false;
		m_3E = false;
	}
}

// ?rva005FFC8B@Rva005FFC8B@@QAEXABUTreeHintRef00217D4C@@@Z @0x005FFC8B 64B:
// store the reference through its rowed assignment 0x002174A4, then
// CreateArmyPanel "garrison" through the same wrapper (level +4, name +8).
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	void *m_ref;
};

class Rva005FFC8B
{
public:
	void rva005FFC8B(const TreeHintRef00217D4C &ref);
private:
	char m_pad00[4];
	unsigned int m_level;		// +0x04
	StringBase<char> m_name;	// +0x08
	char m_pad0C[0x10];
	TreeHintRef00217D4C m_ref;	// +0x1C
};

void Rva005FFC8B::rva005FFC8B(const TreeHintRef00217D4C &ref)
{
	m_ref = ref;
	Rva005FB5E6AptCall(TheRva00222A8BTarget, (void *)m_level, m_name.str(), "CreateArmyPanel", "garrison");
}
