// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Parameter::ReadParameter, retail 0x003B5CA1..0x003B5EA5 (516 bytes).
// Identity: registered Condition parser 0x003B6D92 and script-action parser
// 0x003B5EA5 call this static parameter factory with a DataChunkInput reference.
// Semantic donor: GeneralsMD ScriptEngine/Scripts.cpp, reviewed in BFME1
// dae380faa5f6fa536eec8d6ebbe877321d4cb51d. This is reconstructed C++, not the
// BFME1 lifted thunk. Prior bank 0x003b5ca1 supplied the initial reconstruction.
// Retail establishes the 0x28-byte allocation, constructor 0x003B333A,
// type/initialized/int/real/string offsets 0/4/8/C/10, coord setter 0x003B27E2,
// BODY_STATE conversion through BitFlags<101>, and the KIND_OF migration loop.
// Layout is a measured view; unused tail fields carry no donor identity claim.
// Target omits the donor's object/upgrade migration branches. The CASH_GENERATOR
// case is a retail addition. Preserve the native legacy-name loop, including
// its SMALL_MISSILE comparison against each iteration of the name table.
// An early exit before KIND_OF gives MSVC the native late EBX save; ordinary
// AsciiString assignment gives the native copy-call scheduling and unwind state.
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

#include "Coord3D.h"

class DataChunkInput
{
public:
	Int readInt();
	float readReal();
	AsciiString readAsciiString();
};

template <unsigned int N>
class BitFlags
{
public:
	static Int getSingleBitFromName(const char *token);
};

extern const char *TheKindOfBitNames[];

enum ErrorCode
{
	ERROR_BASE = 0xdead0001,
	ERROR_BUG = (ERROR_BASE + 0x0000)
};

enum
{
	COORD3D_PARAM = 0x10,
	KIND_OF_PARAM = 0x1B,
	BODY_STATE_PARAM = 0x29
};

class Parameter
{
public:
	enum ParameterType
	{
		INT_TYPE = 0
	};

	Parameter(ParameterType type, Int val = 0);
	static Parameter *ReadParameter(DataChunkInput &file);

	ParameterType getParameterType() const { return m_paramType; }

protected:
	void setCoord3D(const Coord3D *pLoc);

private:
	ParameterType m_paramType; // +0x00
	Bool m_initialized; // +0x04
	char m_pad[3]; // +0x05
	Int m_int; // +0x08
	float m_real; // +0x0C
	AsciiString m_string; // +0x10
	Coord3D m_coord; // +0x14
	unsigned int m_tail0; // +0x20
	unsigned int m_tail1; // +0x24
};

Parameter *Parameter::ReadParameter(DataChunkInput &file)
{
	Parameter *pParm = new Parameter((ParameterType)file.readInt());
	pParm->m_initialized = true;
	if (pParm->getParameterType() == (ParameterType)COORD3D_PARAM) {
		Coord3D pos;
		pos.x = file.readReal();
		pos.y = file.readReal();
		pos.z = file.readReal();
		pParm->setCoord3D(&pos);
	} else {
		pParm->m_int = file.readInt();
		pParm->m_real = file.readReal();
		pParm->m_string = file.readAsciiString();
	}

	if (pParm->getParameterType() == (ParameterType)BODY_STATE_PARAM) {
		const char *tok = pParm->m_string.str();
		pParm->m_int = BitFlags<101>::getSingleBitFromName(tok);
	}

	if (pParm->getParameterType() != (ParameterType)KIND_OF_PARAM) return pParm;
	AsciiString &str = pParm->m_string;
	StringBase<char> &s = (StringBase<char> &)str;
	if (!s.isEmpty()) {
		Bool found = false;
		for (Int i = 0; TheKindOfBitNames[i]; ++i) {
			if (s.compareNoCase(TheKindOfBitNames[i]) == 0) {
				pParm->m_int = i;
				return pParm;
			}
			if (s.compareNoCase("CRUSHER") == 0) {
				pParm->m_int = i;
				return pParm;
			}
			if (s.compareNoCase("CRUSHABLE") == 0) {
				pParm->m_int = i;
				return pParm;
			}
			if (s.compareNoCase("OVERLAPPABLE") == 0) {
				pParm->m_int = i;
				return pParm;
			}
			if (s.compareNoCase("CASH_GENERATOR") == 0) {
				str.format("SUPPLY_GATHERING_CENTER");
				found = true;
				break;
			}
			if (s.compareNoCase("MISSILE") == 0) {
				str.format("SMALL_MISSILE");
				for (i = 0; TheKindOfBitNames[i]; ++i) {
					if (s.compareNoCase("SMALL_MISSILE") == 0) {
						pParm->m_int = i;
						found = true;
						break;
					}
				}
			}
		}
		if (!found) {
			throw ERROR_BUG;
		}
	} else {
		s.set(TheKindOfBitNames[pParm->m_int]);
	}
	return pParm;
}
