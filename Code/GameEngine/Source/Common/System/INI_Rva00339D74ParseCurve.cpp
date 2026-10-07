// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /GX- /Oi-
// ?Rva00339D74ParseCurve@@YAXPAVINI@@PAX1PBX@Z @0x00339D74 167B evidence: REF Radius Opacity Angle slots; calls getNextToken erase sscanf Curve-set FunctionCurve-parse INIException.
struct BfmePod16 { int a[4]; };
namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
public:
	void *m_start;
	void *m_finish;
	void *m_end;
	BfmePod16 *erase(BfmePod16 *first, BfmePod16 *last);
};
}
class INI
{
public:
	const char *getNextToken(const char *seps);
};
class Rva00504EADCurve
{
public:
	void set(float time, float value, float inTangent, float outTangent);
	int m_a;
	int m_b;
};
class Rva0006AF00FunctionCurve : public Rva00504EADCurve
{
public:
	void parse(INI *ini);
	_STL::vector<BfmePod16, _STL::allocator<BfmePod16> > m_keys;
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
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buffer, const char *format, ...);
extern "C" int __cdecl strcmp(const char *a, const char *b);
// ?Rva00339D74ParseCurve@@YAXPAVINI@@PAX1PBX@Z
void Rva00339D74ParseCurve(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken(0);
	Rva0006AF00FunctionCurve *fc = (Rva0006AF00FunctionCurve *)store;
	_STL::vector<BfmePod16, _STL::allocator<BfmePod16> > &vec = fc->m_keys;
	vec.erase((BfmePod16 *)vec.m_start, (BfmePod16 *)vec.m_finish);
	fc->m_a = 0;
	fc->m_b = 0;
	float f;
	if (sscanf(token, "%f", &f) == 1) {
		fc->set(0.0f, f, 0.0f, 0.0f);
		return;
	}
	if (strcmp(token, "FCurve") == 0) {
		fc->parse(ini);
	} else {
		throw INIException(5, "'FCurve' expected");
	}
}
