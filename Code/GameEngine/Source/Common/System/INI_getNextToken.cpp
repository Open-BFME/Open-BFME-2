// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?getNextToken@INI@@QAEPBDPBD@Z, retail 0x002DF97, 75 bytes.
// Dedicated TU.
//
// Throwing next-token helper: delegates to getNextTokenOrNull (pinned at
// 0x002DEED, whose 168B BFME2 body reads the default separator set at
// this+0x418 just like this body does) and throws INIException(3,
// "Expected additional data after '%s'") through the shared filler (pinned
// at 0x002F681) plus __CxxThrowException when the stream is exhausted.
// BFME1 ini.cpp shape verbatim; the only BFME2 delta is the default-seps
// member sitting at this+0x418 (BFME1: +0x414).

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	static const char *preprocessMacro(const char *token);
	const char *rva0002E03D(const char *seps, bool *substituted);
private:
	char _pad[0x418];
	const char *m_seps;
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};


// ?getNextToken@INI@@QAEPBDPBD@Z
const char *INI::getNextToken(const char *seps)
{
	const char *token = getNextTokenOrNull(seps);
	if (token == 0) {
		throw INIException(3, "Expected additional data after '%s'", (seps == 0) ? m_seps : seps);
	}
	return token;
}

// ?rva0002E03D@INI@@QAEPBDPBDPA_N@Z @0x0002E03D 46B: INI::getNextTokenOrNull
// then static preprocessMacro (pinned 0x0002D0A9) with a substituted-flag out
// param. Evidence: ecx=this flows into rowed getNextTokenOrNull 0x0002DEED,
// pin-only preprocessMacro per symbols.csv, ret-8 two-arg thiscall shape,
// unblocks caller 0x0026F28B. BFME1 donor INIGetNextToken.cpp throws instead
// of the null path and has no flag; follow retail.
#pragma optimize("y", on)
const char *INI::rva0002E03D(const char *seps, bool *substituted)
{
	const char *token = getNextTokenOrNull(seps);
	if (token != 0) {
		const char *expanded = preprocessMacro(token);
		if (substituted != 0)
			*substituted = (expanded != token);
		return expanded;
	}
	return 0;
}
#pragma optimize("", on)
