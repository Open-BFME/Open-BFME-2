// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x003C4145 (RVA 0x003C4145) size 117: BfmeApplierBH apply power at team pos.
// Evidence: ScriptEngine 0xDFE16C getTeamNamed then Team hasAnyObjects then rva0039E5B9 Coord3D then SpecialPowerStore 0xE02D4C findSpecialPowerTemplate then bfmeApplyBH pin 0x3C069B.
#include "ascii_string.h"

class Team;
struct Coord3D
{
public:
	float x;
	float y;
	float z;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool b);
};

extern class ScriptEngine *TheScriptEngine;

class Team
{
public:
	bool hasAnyObjects(bool b);
	void rva0039E5B9(Coord3D *p);
};

class SpecialPowerTemplate;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class BfmeSubBH
{
public:
	char m_pad[4];
};

class BfmeApplierBH
{
public:
	void rva003C4145(void *owner, const AsciiString &powerName, const AsciiString &teamName);
	void bfmeApplyBH(void *owner, void *found, BfmeSubBH *sub) throw();
};

void BfmeApplierBH::rva003C4145(void *owner, const AsciiString &powerName, const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team == 0)
		return;
	if (!team->hasAnyObjects(false))
		return;
	Coord3D pos;
	team->rva0039E5B9(&pos);
	const SpecialPowerTemplate *found = TheSpecialPowerStore->findSpecialPowerTemplate(powerName);
	if (found == 0)
		return;
	bfmeApplyBH(owner, (void *)found, (BfmeSubBH *)&pos);
}
