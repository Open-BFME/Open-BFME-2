// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHs-c- /O1 /arch:SSE /G7 /Ireference/open-bfme-1/game/GameEngine/Source/Common/INI /Ireference/shims/iniexception
// ?parseKey@Rva0006AF00FunctionCurve@@SAXPAVINI@@PAX1PBX@Z at retail RVA 0x005050EA; donor identity and callback role are established by the BFME1 FunctionCurve parser, while target token handling, tangent helper, and addKey call are established by retail bytes.

typedef float Real;

#include "Common/INIException.h"

class INI
{
public:
	const char *getNextSubToken( const char *expected );
	const char *getNextToken( const char *separators );
	const char *getNextTokenOrNull( const char *separators );
	const char *getSeps( void ) const { return m_seps; }
	Real scanReal( const char *token );

private:
	char m_padding[ 0x420 ];
	const char *m_seps;
};

class Rva00504F09FunctionCurve
{
public:
	void addKey( Real time, Real value, const Real *inTangent,
		const Real *outTangent );
};

double Rva005046B0ScanTangentAngle( INI *ini, const char *token );

class Rva0006AF00FunctionCurve
{
public:
	static void parseKey( INI *ini, void *instance, void *store,
		const void *userData );
};

// ?parseKey@Rva0006AF00FunctionCurve@@SAXPAVINI@@PAX1PBX@Z
void Rva0006AF00FunctionCurve::parseKey( INI *ini, void *, void *,
	const void *userData )
{
	Real time = ini->scanReal( ini->getNextSubToken( "T" ) );
	Real value = ini->scanReal( ini->getNextSubToken( "V" ) );
	const Real *inTangent = 0;
	const Real *outTangent = 0;
	Real inValue;
	Real outValue;
	int count;

	for ( count = 0; count < 2; ++count )
	{
		const char *token = ini->getNextTokenOrNull( ini->getSeps() );
		if ( token == 0 )
			break;

		if ( inTangent == 0 && token[ 0 ] == 'I' && token[ 1 ] == 0 )
		{
			inValue = Rva005046B0ScanTangentAngle(
				ini, ini->getNextToken( ini->getSeps() ) );
			inTangent = &inValue;
		}
		else if ( outTangent == 0 && token[ 0 ] == 'O' && token[ 1 ] == 0 )
		{
			outValue = Rva005046B0ScanTangentAngle(
				ini, ini->getNextToken( ini->getSeps() ) );
			outTangent = &outValue;
		}
		else
			throw INIException( 3, "'I' or 'O' expected, and only one of them" );
	}

	((Rva00504F09FunctionCurve *)userData)->addKey( time, value,
		inTangent, outTangent );
}
