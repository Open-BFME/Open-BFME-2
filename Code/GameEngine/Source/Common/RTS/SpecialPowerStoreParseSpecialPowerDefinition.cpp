// cl: /O1 /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Target3B15D6..3B17F3 (541B) SpecialPowerStore::parseSpecialPowerDefinition.
// Reference: Zero Hour Common/RTS/SpecialPower.cpp; clean BFME1 donor
// SpecialPowerStoreParseSpecialPowerDefinition.cpp at9cbfb551fe20dae985f91f2319d8997287b6a705.
// Target facts: DefaultSpecialPower/error strings; TheSpecialPowerStoreE02D4C;
// rowed find3B11D2/29B6EB ctor3B140E copy3B1337 set3B0FAC; template80B;
// store vectorC/id18; override next4/flag8; tableDC0E78 via existing getter3B0FA0.
// Donor semantics: named creation or final override; copy under existing guard;
// duplicate INIException; initialize from target field table. Full hot/EH exact.
// Typed pointer-vector ABI uses existing ModuleData provider4DFCB0. Binding
// pointer by reference preserves the target escaping local without a new pin.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

class INIException {
public: INIException(int,const char*,...); INIException(const INIException&); ~INIException();
char *mFailureMessage; int m_argumentCount;
};
#include "string_base.h"

typedef unsigned int UnsignedInt;
typedef bool Bool;

struct FieldParse;

// Raised only while an override is being copied over its original.
extern unsigned char g_00E01EA8;			// 0x012ED611

#include "ascii_string.h"
inline const char *specialPowerNameText(const AsciiString &name) {
 const char *data=*(const char *const *)&name;
 return data ? data+8 : "";
}
// BFME keeps the load type at INI+0x08.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );
	int getLoadType() const { return m_loadType; }

private:
	int m_unmodelled00;
	int m_unmodelled04;
	int m_loadType;
};

enum { INI_LOAD_CREATE_OVERRIDES = 2 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	void setNextOverride( Overridable *nextOverride ) { m_nextOverride = nextOverride; }
	void markAsOverride() { m_isOverride = true; }

private:
	Overridable *m_nextOverride;				// +0x04
	Bool m_isOverride;					// +0x08
};

class Rva003B1101 { public:
 Rva003B1101(); Rva003B1101 &operator=(const Rva003B1101 &other);
 char data[0x80];
};
class Rva003B0FAC { public: void rva003B0FAC(const AsciiString &,int); };
class ModuleData;
// ZH SpecialPower.h is the semantic guide; target template size80/name10/id14.
class SpecialPowerTemplate : public Overridable
{
public:
	

	static const FieldParse *getFieldParse() { return m_specialPowerFieldParse; }
	void friend_setNameAndID( const AsciiString &name, UnsignedInt id )
	{
		((Rva003B0FAC *)this)->rva003B0FAC(name,id);
	}

private:
 static const FieldParse m_specialPowerFieldParse[];
	char m_unknown0C[4];
 AsciiString m_name; // +0x10
	UnsignedInt m_id;					// +0x14
	char m_unmodelled18[ 0x80 - 0x18 ];			// target allocation80
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

protected:
	int m_unmodelled04;
 AsciiString m_name;
};

// ZH SpecialPower.h is the semantic guide; target template size80/name10/id14.
class SpecialPowerStore : public SubsystemInterface
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate( AsciiString name );
	static void parseSpecialPowerDefinition( INI *ini );

protected:
	SpecialPowerTemplate *findSpecialPowerTemplatePrivate( AsciiString name );

	_STL::vector<const ModuleData *> m_specialPowerTemplates;	// target +0x0C
	UnsignedInt m_nextSpecialPowerID;				// target +0x18
};

extern SpecialPowerStore *TheSpecialPowerStore;

void SpecialPowerStore::parseSpecialPowerDefinition( INI *ini )
{
	// read the name
	AsciiString name = ini->getNextToken();

	SpecialPowerTemplate* specialPower = TheSpecialPowerStore->findSpecialPowerTemplatePrivate( name );

	if ( ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES )
	{
		if (specialPower)
		{
			SpecialPowerTemplate* child = (SpecialPowerTemplate*)specialPower->friend_getFinalOverride();
			specialPower = (SpecialPowerTemplate *)new Rva003B1101;
			g_00E01EA8 = true;
			*(Rva003B1101 *)specialPower = *(Rva003B1101 *)child;
			g_00E01EA8 = false;
			child->setNextOverride(specialPower);
			specialPower->markAsOverride();
		}
		else
		{
			specialPower = (SpecialPowerTemplate *)new Rva003B1101;
			const SpecialPowerTemplate *defaultTemplate = TheSpecialPowerStore->findSpecialPowerTemplate( "DefaultSpecialPower" );
			if( defaultTemplate )
			{
				g_00E01EA8 = true;
				*(Rva003B1101 *)specialPower = *(const Rva003B1101 *)defaultTemplate;
				g_00E01EA8 = false;
			}
			specialPower->friend_setNameAndID(name, ++TheSpecialPowerStore->m_nextSpecialPowerID);
			specialPower->markAsOverride();
			TheSpecialPowerStore->m_specialPowerTemplates.push_back((const ModuleData *const &)specialPower);
		}
	}
	else
	{
		if (specialPower)
		{
			throw INIException( 3, "Special power '%s' already defined", specialPowerNameText(name) );
		}
		else
		{
			specialPower = (SpecialPowerTemplate *)new Rva003B1101;
			const SpecialPowerTemplate *defaultTemplate = TheSpecialPowerStore->findSpecialPowerTemplate( "DefaultSpecialPower" );
			if( defaultTemplate )
			{
				g_00E01EA8 = true;
				*(Rva003B1101 *)specialPower = *(const Rva003B1101 *)defaultTemplate;
				g_00E01EA8 = false;
			}
			specialPower->friend_setNameAndID(name, ++TheSpecialPowerStore->m_nextSpecialPowerID);
			TheSpecialPowerStore->m_specialPowerTemplates.push_back((const ModuleData *const &)specialPower);
		}
	}

	// parse the ini definition
	if (specialPower) ini->initFromINI( specialPower, specialPower->getFieldParse() );
}
