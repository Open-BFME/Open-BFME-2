// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?parseAIKindOfList@@YAXPAVINI@@PBDPAH@Z, retail 0x004E8EA6, 88 bytes.
// Dedicated TU.
//
// Parses an AIKINDOF name list from the INI stream into an int array: the
// first token comes from the throwing getNextToken (an empty list is an
// error) and the rest from getNextTokenOrNull. More than 16 entries throws
// INIException ("In an AIKINDOF list, each type may only appear once",
// retail literal at 0x8627B0 — over 16 names necessarily repeats one of the
// 16 kinds). Sibling of getAIKindOfFromName (same directory); BFME2-added.
//
// Shaping notes:
// - Same /O1 /Oy- /GX- recipe as the sibling mapper TU (frame, no funclets).
// - `__declspec(noreturn)` on _CxxThrowException sinks the fail block last
//   with no dead epilogue (the compiler even pads the int3, matching retail).
//   The sibling TU deliberately keeps the plain declaration: noreturn there
//   is unproven against its landed bytes.
// - The middle parameter is never read by retail (both token calls pass NULL;
//   the first call reuses the just-zeroed loop index for its NULL). It is
//   left unnamed beyond its type; the row notes record this.

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
};

int getAIKindOfFromName(const char *name);

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};


// ?parseAIKindOfList@@YAXPAVINI@@PBDPAH@Z
void parseAIKindOfList(INI *ini, const char * /*seps*/, int *out)
{
	int i = 0;
	const char *token = ini->getNextToken(0);
	while (token != 0) {
		if (i >= 16)
			goto fail;
		out[i] = getAIKindOfFromName(token);
		token = ini->getNextTokenOrNull(0);
		i++;
	}
	return;
fail:
	{
		throw INIException(2, "In an AIKINDOF list, each type may only appear once\n");
	}
}
