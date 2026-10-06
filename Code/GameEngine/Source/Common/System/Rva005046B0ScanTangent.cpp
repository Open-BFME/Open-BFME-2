// cl: /DNDEBUG /MD /EHsc /Oi-
// ?Rva005046B0ScanTangentAngle@@YANPAVINI@@PBD@Z 0x005046B0 111B evidence: BFME1 donor Rva000697B0ScanTangentAngle same messages same range check; BFME2 member scanReal plus double tan import; callers 0x00505159 0x00505184 unblocks 0x005050EA
typedef int Int;
typedef float Real;

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

class INI
{
public:
	float scanReal(const char *token);
};

extern "C" double __cdecl tan(double);

#define PI 3.14159265359f

double __cdecl Rva005046B0ScanTangentAngle(INI *ini, const char *token)
{
	Real angle = ini->scanReal(token);
	if (angle > 89.9f)
		throw INIException(3, "Function curve tangent angle value must be less than 89.9 degrees");
	if (angle < -89.9f)
		throw INIException(3, "Function curve tangent angle value must be greater than -89.9 degrees");
	return tan(angle * (PI / 180.0f));
}
