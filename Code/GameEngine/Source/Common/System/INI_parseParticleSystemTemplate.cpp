// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseParticleSystemTemplate@INI@@SAXPAV1@PAX1PBX@Z, retail 0x003395BB, 116 bytes.
// Dedicated TU (same INI parser family as INI_parseFXList.cpp).
//
// Zero Hour's INI::parseParticleSystemTemplate (Common/INI/INI.cpp): look the
// token up in TheParticleSystemManager (0x00DFDD04) and store it unless the
// lookup failed or the token is "None". The compare is msvcr71!_strcmpi through
// the IAT (0xBBA518).

class ParticleSystemTemplate;

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	~StringBase();

private:
	StringBase(const T *s);
	T *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
};

extern ParticleSystemManager *TheParticleSystemManager;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseParticleSystemTemplate(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// ?parseParticleSystemTemplate@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseParticleSystemTemplate(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	const ParticleSystemTemplate *pSystemT = TheParticleSystemManager->findTemplate(AsciiString(token));
	if (pSystemT && _strcmpi(token, "None") != 0)
		*(const ParticleSystemTemplate **)store = pSystemT;
	else
		*(const ParticleSystemTemplate **)store = 0;
}
