// ?ParseConditionDataChunk@Condition@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.99 date=2026-10-05
// ?ParseConditionDataChunk@Condition@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// cl: /Ireference/shims/bfme2_ascii /Gy /DNDEBUG /MD
// BFME1 donor 6583b3c1: Condition_ParseConditionDataChunk_Thunk.cpp.
// Target callback registered as Condition by OrCondition parser 3B7587.
// BFME2 layout 50 bytes, template bound CA, internal key +10, two flags
// at +4C/+4D, and versions 2/6 parameter repairs are read from native709.
// ParameterChangesVer2 values verified in target data at RVA9C10DC.
// Shared 24-byte Template and 12-byte remapper emitted before the parser
// retain native caller register usage; /Gy makes these common copies.
// Remaining dependency: Parameter::ReadParameter @3B5CA1 (banked 516B).

typedef int Int;
typedef bool Bool;
typedef unsigned short DataChunkVersionType;
enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "ascii_string.h"

class Rva00333B02 { public: void rva00333B02(AsciiString); };
class Rva0034FF50 { public: __declspec(noinline) void checkAndSet(); int m_val0; };
void Rva0034FF50::checkAndSet() { if (m_val0 == 15) m_val0 = 61; }

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	DataChunkVersionType version;
	Int dataSize;
};

class DataChunkInput
{
public:
	Int readInt();
	NameKeyType readNameKey();
	DataChunkVersionType getChunkVersion();
	Bool atEndOfChunk();
};

class Parameter
{
public:
	enum ParameterType
	{
		OBJECT_TYPE = 0x0f,
		SIDE = 0x0b,
		SURFACES_ALLOWED = 0x25,
		TEMPLATE_REMAP_TYPE = 0x3d
	};

	Parameter(ParameterType type, Int value = 0) throw();

	static Parameter *ReadParameter(DataChunkInput &file);

	__forceinline ParameterType getParameterType() const
	{
		return m_paramType;
	}

	__forceinline void friend_setString(AsciiString text)
	{
		((Rva00333B02 *)this)->rva00333B02(text);
	}
	__forceinline void friend_setParameterType(ParameterType type)
	{
		((Rva0034FF50 *)this)->checkAndSet();
	}

private:
	ParameterType m_paramType;
	bool m_initialized;
	Int m_int;
	float m_real;
	AsciiString m_string;
	struct Coord3D
	{
		float x;
		float y;
		float z;
	} m_coord;
	struct ObjectStatusMask
	{
		__forceinline ObjectStatusMask() : m_low(0), m_high(0) {}
		unsigned int m_low;
		unsigned int m_high;
	} m_objectStatus;
};

class Template
{
public:
	Int getNumParameters() const { return m_numParameters; }
	__declspec(noinline) Parameter::ParameterType getParameterType(Int index) const;
	char m_prefix[0x10];
	NameKeyType m_internalNameKey;
	char m_middle[0x34];
	Int m_numParameters;
	Parameter::ParameterType m_parameters[12];
};
Parameter::ParameterType Template::getParameterType(Int index) const
{
	if (index >= 0 && index < m_numParameters) return m_parameters[index];
	return (Parameter::ParameterType)0;
}
class ConditionTemplate : public Template {};
class ScriptEngine { public: const ConditionTemplate *getConditionTemplate(Int type) throw(); };

extern ScriptEngine *TheScriptEngine;

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

class Condition : public MemoryPoolObject
{
public:
	virtual ~Condition();

	enum ConditionType
	{
		CONDITION_FALSE = 0,
		SKIRMISH_SPECIAL_POWER_READY = 0x55,
		NUM_ITEMS = 0xca
	};

	Condition() throw();

	static Bool __cdecl ParseConditionDataChunk(DataChunkInput &file,
		DataChunkInfo *info, void *userData);

	__forceinline ConditionType getConditionType() const
	{
		return m_conditionType;
	}

	__forceinline Condition *getNext() const
	{
		return m_nextAndCondition;
	}

	__forceinline Int getNumParameters() const
	{
		return m_numParms;
	}

	__forceinline void setNextCondition(Condition *condition)
	{
		m_nextAndCondition = condition;
	}

private:
	ConditionType m_conditionType;
	Int m_numParms;
	Parameter *m_parms[12];
	Condition *m_nextAndCondition;
	Int m_hasWarnings;
	Int m_customData;
	unsigned int m_customFrame;
	Bool m_flag4C;
	Bool m_flag4D;
	char m_pad[2];
};

class OrCondition
{
public:
	__forceinline Condition *getFirstAndCondition() const
	{
		return m_firstAnd;
	}

	__forceinline void setFirstAndCondition(Condition *condition)
	{
		m_firstAnd = condition;
	}

private:
	void *m_vtable;
	OrCondition *m_nextOr;
	Condition *m_firstAnd;
};

static int ParameterChangesVer2[] =
{
	7, 17, 18, 41, 40, 42, 43, -1
};

Bool __cdecl Condition::ParseConditionDataChunk(DataChunkInput &file,
	DataChunkInfo *info, void *userData)
{
	Condition *pCondition = new Condition;
	OrCondition *pOr = (OrCondition *)userData;
	pCondition->m_conditionType = (ConditionType)file.readInt();
	const ConditionTemplate *ct =
		TheScriptEngine->getConditionTemplate(pCondition->m_conditionType);
	Bool match = false;
	if (info->version >= 4)
	{
		NameKeyType key = file.readNameKey();
		Int i;
		if (ct && ct->m_internalNameKey == key)
			match = true;
		if (!match) {
		for (i = 0; i < Condition::NUM_ITEMS; ++i)
		{
			ct = TheScriptEngine->getConditionTemplate(i);
			if (key == ct->m_internalNameKey)
			{
				pCondition->m_conditionType = (ConditionType)i;
				match = true; break;
			}
		}
		}
	}
	pCondition->m_numParms = file.readInt();
	Int i;
	for (i = 0; i < pCondition->m_numParms; ++i)
	{
		Parameter *parameter = Parameter::ReadParameter(file);
		pCondition->m_parms[i] = parameter;
		if (parameter->getParameterType() != Parameter::OBJECT_TYPE)
			continue;
		if (ct->getNumParameters() > i &&
			ct->getParameterType(i) == Parameter::TEMPLATE_REMAP_TYPE)
		{
			parameter->friend_setParameterType(Parameter::TEMPLATE_REMAP_TYPE);
		}
	}
	if (info->version >= 5)
	{
		pCondition->m_flag4C = file.readInt() != 0;
		pCondition->m_flag4D = file.readInt() != 0;
	}
	else
	{
		pCondition->m_flag4C = true;
		pCondition->m_flag4D = false;
	}
	if (!match)
	{
		ct = TheScriptEngine->getConditionTemplate(CONDITION_FALSE);
		pCondition->m_conditionType = CONDITION_FALSE;
		while (pCondition->m_numParms > 0)
		{
			--pCondition->m_numParms;
			Parameter *parameter = pCondition->m_parms[pCondition->m_numParms];
			if (parameter)
				delete parameter;
		}
	}

	if (file.getChunkVersion() < 2)
	{
		for (Int j = 0; ParameterChangesVer2[j] != -1; ++j)
		{
			if (pCondition->m_conditionType == (ConditionType)ParameterChangesVer2[j])
			{
				pCondition->m_parms[pCondition->m_numParms] =
					new Parameter(Parameter::SURFACES_ALLOWED, 3);
				pCondition->m_numParms = 3;
			}
		}
	}
	else if (file.getChunkVersion() < 6)
	{
		for (Int j = 0; ParameterChangesVer2[j] != -1; ++j)
		{
			if (pCondition->m_conditionType == (ConditionType)ParameterChangesVer2[j])
			{
				delete pCondition->m_parms[pCondition->m_numParms-1];
				pCondition->m_parms[pCondition->m_numParms-1] = new Parameter(Parameter::SURFACES_ALLOWED, 0);
			}
		}
	}
	switch (pCondition->getConditionType())
	{
		case SKIRMISH_SPECIAL_POWER_READY:
			if (pCondition->m_numParms == 1)
			{
				pCondition->m_numParms = 2;
				pCondition->m_parms[1] = pCondition->m_parms[0];
				pCondition->m_parms[0] = new Parameter(Parameter::SIDE, 0);
				((Rva00333B02 *)pCondition->m_parms[0])->rva00333B02(AsciiString("<This Player>"));
			}
			break;
	}
	if (ct->getNumParameters() != pCondition->m_numParms)
	{
		ct = TheScriptEngine->getConditionTemplate(CONDITION_FALSE);
		pCondition->m_conditionType = CONDITION_FALSE;
		while (pCondition->m_numParms > 0)
		{
			--pCondition->m_numParms;
			Parameter *parameter = pCondition->m_parms[pCondition->m_numParms];
			if (parameter)
				delete parameter;
		}
	}
	Condition *pLast = pOr->getFirstAndCondition();
	while (pLast && pLast->getNext())
		pLast = pLast->getNext();
	if (pLast)
		pLast->setNextCondition(pCondition);
	else
		pOr->setFirstAndCondition(pCondition);
	return true;
}
