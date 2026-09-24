// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// Reused from reference/open-bfme-1/Code/GameEngine/Source/Common/MultiPlayMultParseCallbacks.cpp.
// PC FieldParse row VA 0xBE9C10 binds MultiPlayMoneyMult to RVA 0x235AB6,
// GlobalData+0xEC4. PC writes MP1..MP8 at subobject+0..0x1C; setter at
// RVA 0x2358E2 independently proves signed slot-1 bounds [0,20).
// Changes from donor: INI +0x420, member scanReal, twenty-slot arrays, /O1 SSE.
// MultiPlayMults is the donor's descriptive facade, not a recovered type spelling.
// Full 336-byte body verified through final ret; no Xbox bytes count as recovery.
typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl _strcmpi( const char *, const char * );

// INI layout follows the verified PC token/scanner bodies; colon separators at +0x420.
class INI
{
public:
	const char *getNextToken( const char *seps );
	const char *getNextTokenOrNull( const char *seps );
	const char *getSepsColon( void ) const { return m_sepsColon; }
	Real scanReal( const char *token );
	static void parseInt( INI *ini, void *instance, void *store, const void *userData );

	char m_unreconstructed_000[ 0x420 ];
	const char *m_sepsColon;
};

class MultiPlayMults
{
public:
	MultiPlayMults();

	void setMoneyMult( Int slot, Real value )
	{
		Int index = slot - 1;
		if ( index >= 0 && index < 20 )
			m_money[ index ] = value;
	}





	// PC arrays: +0, +0x50, +0xA0, +0xF0, +0x140, +0x190; twenty slots each.
	Real m_money[ 20 ];
	Real m_unitXP[ 20 ];
	Real m_buildingXP[ 20 ];
	Real m_unitSpeed[ 20 ];
	Real m_buildingSpeed[ 20 ];
	// BFME 2's sixth multiplier table: the constructor initialises it with
	// the others, but no setter or getter in this block reaches it.
	Real m_sixthMult[ 20 ];
};

// ??0MultiPlayMults@@QAE@XZ @0x2358A2
// Every multiplier starts at 1.0 for all twenty player slots.
MultiPlayMults::MultiPlayMults()
{
	for ( Int i = 0; i < 20; ++i )
	{
		m_money[ i ] = 1.0f;
		m_unitXP[ i ] = 1.0f;
		m_buildingXP[ i ] = 1.0f;
		m_unitSpeed[ i ] = 1.0f;
		m_buildingSpeed[ i ] = 1.0f;
		m_sixthMult[ i ] = 1.0f;
	}
}

// GlobalData keyword "MultiPlayMoneyMult", PC GlobalData offset 0xEC4
void parseMultiPlayMoneyMult( INI *ini, void *, void *store, const void * )
{
	MultiPlayMults *mults = (MultiPlayMults *)store;
	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	while ( token )
	{
		const char *valueToken = ini->getNextToken( ini->getSepsColon() );
		if ( valueToken )
		{
			Real value = ini->scanReal( valueToken );
			if ( !_strcmpi( token, "MP1" ) )
				mults->setMoneyMult( 1, value );
			else if ( !_strcmpi( token, "MP2" ) )
				mults->setMoneyMult( 2, value );
			else if ( !_strcmpi( token, "MP3" ) )
				mults->setMoneyMult( 3, value );
			else if ( !_strcmpi( token, "MP4" ) )
				mults->setMoneyMult( 4, value );
			else if ( !_strcmpi( token, "MP5" ) )
				mults->setMoneyMult( 5, value );
			else if ( !_strcmpi( token, "MP6" ) )
				mults->setMoneyMult( 6, value );
			else if ( !_strcmpi( token, "MP7" ) )
				mults->setMoneyMult( 7, value );
			else if ( !_strcmpi( token, "MP8" ) )
				mults->setMoneyMult( 8, value );

			token = ini->getNextTokenOrNull( ini->getSepsColon() );
		}
	}
}

// ?parseCommandPoints@@YAXPAVINI@@PAX1PBX@Z @0x23528E
// FieldParse callback for the Good/EvilCommandPoints[AI|MPn] GlobalData
// entries (rows from RVA 0x7E99E4): two consecutive ints per side.
void parseCommandPoints( INI *ini, void *instance, void *store, const void *userData )
{
	INI::parseInt( ini, instance, store, userData );
	INI::parseInt( ini, instance, (Int *)store + 1, userData );
}
