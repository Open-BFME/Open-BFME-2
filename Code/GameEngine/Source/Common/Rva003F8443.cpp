// cl: /Ireference/shims/bfme2_ascii /MD
// LivingWorldTutorial::SessionTask::getArmyParam (WorldBuilder name, LivingWorldTutorial.cpp line 464: army lookup of the indexed +0x0C parameter).
//
// was ?rva003F8443@Rva003F8443@@QAEPAURva002E1948Entry@@H@Z @0x003F8443 25B.
// Index AsciiString array at +0xC and find via rowed Rva002B48E1.
// Evidence: chain lane; callee rowed 0x002B48E1; global 0x009FEF10;
// callers at 0x003F8A65 0x003F8AC3 0x003F8C93; unblocks 0x003F88BC.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"

struct Rva002E1948Entry;

class Rva002B48E1
{
public:
	Rva002E1948Entry *rva002B48E1(const AsciiString &name);
};

class LivingWorldTutorial
{
public:
	class SessionTask;
};
class LivingWorldTutorial::SessionTask
{
public:
	Rva002E1948Entry *getArmyParam(int i);
private:
	char m_pad00[0x0C];
	AsciiString *m_arr0C;
};

Rva002E1948Entry *LivingWorldTutorial::SessionTask::getArmyParam(int i)
{
	return (*(Rva002B48E1 **)&TheLivingWorldLogic)->rva002B48E1(m_arr0C[i]);
}
