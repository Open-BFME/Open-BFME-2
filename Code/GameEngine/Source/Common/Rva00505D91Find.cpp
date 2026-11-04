// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva00505D91@AITacticsGenerator@@AAEPAURva00506909Item@@ABVAsciiString@@@Z, retail 0x00505D91, 51 bytes.
// A private member of the AITacticsGenerator object (AITacticsGenerator.cpp), the
// +0x04 pool sibling of its rowed 0x00505DC4/0x00505DF7/0x00505E2A finders.
// Evidence: search ptr range +0x4 +0x8 for elem whose AsciiString at +0x2c matches arg via rowed compare 0x000069D6 then virtual slot 0x24 else null; caller 0x00506651.
#include <vector>
#include "ascii_string.h"

class Rva00505D91Elem
{
public:
	virtual void dummy0();
	virtual void dummy1();
	virtual void dummy2();
	virtual void dummy3();
	virtual void dummy4();
	virtual void dummy5();
	virtual void dummy6();
	virtual void dummy7();
	virtual void dummy8();
	virtual void *slot9();
	char m_pad[0x2c - 4];
	AsciiString m_2c;
};

class Team;
class Xfer;
struct Rva00506909Gen;
struct Rva00506909Item;
struct Rva00506909Request;

class AITacticsGenerator
{
public:
	void Register(Team *unit);
	void UnRegister(Team *unit);
	AITacticsGenerator(void *owner);
	~AITacticsGenerator();
	void DoXfer(Xfer *xfer);
	void rva005069B4();
	bool activateTactic(Rva00506909Request *request, void *arg);
private:
	Rva00506909Item *rva00505D91(const AsciiString &name);
	Rva00506909Item *rva00505DC4(const AsciiString &name);
	Rva00506909Item *rva00505DF7(const AsciiString &name);
	Rva00506909Item *rva00505E2A(const AsciiString &name);
	void rva00505E5D();
	void rva00505F80();
	void rva00505FD0();
	void updateTactics();
	void rva00506020();
	void rva00505AF1();
	bool rva00506411(void *owner);
	bool rva00506178(Rva00506909Request *request, void *arg);
	bool rva00506265(Rva00506909Request *request, void *arg);
	bool rva0050633B(Rva00506909Request *request, void *arg);

	void *m_owner;					// +0x00
	_STL::vector<Rva00506909Gen *> m_04;
	_STL::vector<Rva00506909Item *> m_10;
	_STL::vector<Rva00506909Gen *> m_1C;
	_STL::vector<Rva00506909Item *> m_28;
	_STL::vector<Rva00506909Gen *> m_34;
	_STL::vector<Rva00506909Item *> m_40;
	_STL::vector<Rva00506909Gen *> m_4C;
	_STL::vector<Rva00506909Item *> m_58;
};

Rva00506909Item *AITacticsGenerator::rva00505D91(const AsciiString &name)
{
	Rva00506909Gen **end = m_04.end();
	for (Rva00506909Gen **it = m_04.begin(); it != end; ++it) {
		AsciiString *asciiString = (AsciiString *)((char *)*it + 0x2c);
		if (asciiString->compare(name) == 0)
			return (Rva00506909Item *)((Rva00505D91Elem *)*it)->slot9();
	}
	return 0;
}
