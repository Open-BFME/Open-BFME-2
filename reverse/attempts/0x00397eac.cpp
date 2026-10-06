// ?rva00397EAC@Rva003973EB@@QAEHPAVPlayer@@H@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva00397EAC@Rva003973EB@@QAEHPAVPlayer@@H@Z @0x00397EAC 153B:
// isPlayerAllowedToCapture logging probe, range-17 dump lane.
//
// Calls the rowed 0x3973EB tree check on the same Rva003973EB receiver with
// the (Player*, int) args, remembering arg==controller in bl and the result
// in the dead arg slot. When theLogicRandomLogFile is set, the controller's
// +0x4C castle name (default empty) and the +0x4/+0x64 caller name (default
// empty) plus the +0x74 number go through the rowed _fprintf 0x002CEC42
// with the exact CAMP format. Returns bl & saved as ints.

extern "C" int __cdecl fprintf(void *stream, const char *format, ...);
extern "C" void *theLogicRandomLogFile;

class Player;

struct Rva00397EACNamed
{
	char m_pad08[8]; // +0x00
	char m_name[1]; // +0x08 inline chars
};

struct Rva00397EACOuter
{
	char m_pad00[0x64]; // +0x00
	Rva00397EACNamed *m_named64; // +0x64
};

class Object
{
public:
	Player *getControllingPlayer() const;

public:
	char m_pad00[4];
	void *m_outer04; // +0x04
	char m_pad08[0x74 - 0x08];
	int m_num74; // +0x74
};

class Player
{
	// +0x4c castle holder reached by manual offset below; layout unproven
};

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_frame40; // +0x40
};

extern GameLogic *TheGameLogic;

struct Rva003973EBInner;

class Rva003973EB
{
public:
	bool rva003973EB(Player *p, int dummy);
	int rva00397EAC(Player *a, int b);

private:
	char m_pad00[4];
	Rva003973EBInner *m_inner04; // +0x04
	Object *m_obj08; // +0x08
};

// ?rva00397EAC@Rva003973EB@@QAEHPAVPlayer@@H@Z
int Rva003973EB::rva00397EAC(Player *a, int b)
{
	bool ok;
	Object *obj = m_obj08;
	bool eq = (a == obj->getControllingPlayer());
	ok = rva003973EB(a, b);
	if (theLogicRandomLogFile != 0) {
		Player *player = obj->getControllingPlayer();
		char *castleBase = (char *)player + 0x4c;
		Rva00397EACNamed *castle = *(Rva00397EACNamed **)castleBase;
		const char *castleName = (castle != 0) ? castle->m_name : "";
		Rva00397EACNamed *caller = *(Rva00397EACNamed **)((int)obj->m_outer04 + 0x64);
		const char *callerName = (caller != 0) ? (const char *)caller + 8 : "";
		fprintf(theLogicRandomLogFile,
			"CAMP: Frame %d: Castle %s(%d) ::isPlayerAllowedToCapture() called by %s -- alreadyMyCastle=%d, playerAllowedToCapture=%d",
			TheGameLogic->m_frame40, castleName, obj->m_num74, callerName, eq, ok);
	}
	return eq & ok;
}
