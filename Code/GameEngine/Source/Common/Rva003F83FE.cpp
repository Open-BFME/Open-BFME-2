// cl: /Ireference/shims/bfme2_ascii /MD
// LivingWorldTutorial::SessionTask::getRegionParam (WorldBuilder name, LivingWorldTutorial.cpp line 437: region lookup of the indexed +0x0C parameter).
//
// was ?rva003F83FE@Rva003F83FE@@QAEPAXH@Z @0x003F83FE 31B.
// Index AsciiString array at +0xC and forward via rowed Rva002104B6.
// Evidence: rowed rva002104B6 0x002104B6; global g_009FEF10 +0xb0;
// callers at 0x003F8421 0x003F88FB 0x003F8957 0x003F8A35 0x003F8AD6 0x003F8B34
// 0x003F8CA6; same +0xC array as neighbours Rva003F83D9 Rva003F8443.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"

class Rva002104B6
{
public:
	void *rva002104B6(void *p);
};

class Rva002BA8F1Logic
{
public:
	char m_pad[0xb0];
	Rva002104B6 *m_b0;
};

class LivingWorldTutorial
{
public:
	class SessionTask;
};
class LivingWorldTutorial::SessionTask
{
public:
	void *getRegionParam(int i);
private:
	char m_pad00[0x0C];
	AsciiString *m_arr0C;
};

void *LivingWorldTutorial::SessionTask::getRegionParam(int i)
{
	AsciiString *arr = m_arr0C;
	int j = i;
	Rva002104B6 *h = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_b0;
	return h->rva002104B6(arr + j);
}
