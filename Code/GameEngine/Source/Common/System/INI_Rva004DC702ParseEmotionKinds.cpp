// cl: /DNDEBUG /MD /GX-
// Emotion kind parsers (retail 0x004DC702 66 bytes and 0x004DC745 66 bytes).
// Both read a token through the rowed getNextToken at 0x002DF97; a null
// token fills an INIException through the INIException(int, const char *, ...) constructor at
// 0x002F681 (AIKindOfFromName precedent: local plus code plus literal) and
// throws through the pinned _CxxThrowException at 0x00629094 with the shared
// INI throwinfo at 0xCFE2FC (parseColorInt anchor precedent). Otherwise the
// token resolves through the rowed BitFlags getSingleBitFromName (Emotion
// names at 0x004DC696, AI-state names at 0x004DC6CC) into the store int. The
// twins differ only in the table callee and the message literal. They serve
// the Type and AIState entries of the Emotion table at 0x861310. The
// callback names stay address-derived; the owning struct is BFME2-new
// (no BFME1 donor).

extern "C" int strcmp(const char *, const char *);

struct INIException
{
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

struct EmotionThrowInfoAnchor { int a; int b; int c; int d; };
static const EmotionThrowInfoAnchor emotionThrowInfoAnchor = { 0, 0, 0, 0 };

template <unsigned N> class BitFlags
{
public:
	static int getSingleBitFromName(const char *name);
};

class INI
{
public:
	char padding[0x420];
	const char *separators;
	static void Rva004B6481_ParseAnim(INI *, void *, void *, const void *);
	const char *getNextToken(const char *seps);
	static void Rva004DC702_ParseEmotionType(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004DC745_ParseAIState(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva004DC702_ParseEmotionType@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004DC702_ParseEmotionType(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken(0);
	if (token != 0) {
		*(int *)store = BitFlags<12>::getSingleBitFromName(token);
		return;
	}
	INIException e(3, "Emotion type expected.");
	_CxxThrowException(&e, (const _s__ThrowInfo *)&emotionThrowInfoAnchor); __assume(0);
}

// ?Rva004DC745_ParseAIState@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004DC745_ParseAIState(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken(0);
	if (token != 0) {
		*(int *)store = BitFlags<6>::getSingleBitFromName(token);
		return;
	}
	INIException e(3, "Emotion AI type expected.");
	_CxxThrowException(&e, (const _s__ThrowInfo *)&emotionThrowInfoAnchor); __assume(0);
}

// Retail 0x004B6481..0x004B64E4 requires the ModelConditionState keyword
// before resolving the following model-condition name.
void INI::Rva004B6481_ParseAnim(INI *ini, void *, void *store, const void *)
{
    const char *token = ini->getNextToken(ini->separators);
    if (token && strcmp(token, "ModelConditionState") == 0) {
        *(int *)store = BitFlags<304>::getSingleBitFromName(ini->getNextToken(0));
        return;
    }
    INIException e(3, "AnimState expected for TransportContain::iniParseAnim");
    _CxxThrowException(&e, (const _s__ThrowInfo *)&emotionThrowInfoAnchor); __assume(0);
}
