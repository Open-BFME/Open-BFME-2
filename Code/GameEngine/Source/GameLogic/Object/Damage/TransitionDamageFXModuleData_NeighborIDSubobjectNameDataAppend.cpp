// ?NeighborIDSubobjectNameDataAppend@TransitionDamageFXModuleData@@SAXPAVINI@@PAX1PBX@Z
// cl: /DBFME_ASCII_DTOR_DECL /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Source/Common
// stlport
//
// ?NeighborIDSubobjectNameDataAppend@TransitionDamageFXModuleData@@SAXPAVINI@@PAX1PBX@Z @0x004BA817 460B
// Evidence: BFME1 donor reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFXModuleDataParseRubbleNeighbor.cpp NeighborIDSubobjectNameDataAppend; retail strings "NeighborOffset" "OCLOffset" "OCL" "SubObject" plus "bad colon spacing, or unexpected token in TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend"; callees rowed getNextTokenOrNull 0x0002DEED getNextSubToken 0x0002E06B scanReal 0x0002EDA5 parseObjectCreationList 0x00338A6F getNextToken 0x0002DF97 vector<AsciiString> push_back 0x0002DBE6 and dtor 0x0002CC70 plus StringBase PBD ctor 0x00037BA0 and releaseBuffer 0x00036410 plus default ctor 0x004BA1B2 and vector<Rva004BA1D0> push_back 0x004BA7E0; layout int plus vector<AsciiString> at +4 plus OCL plus Neighbor plus OCLOffset matches Rva004BA1D0 44B record.
typedef int Int;
typedef float Real;

template <typename T> struct BfmeStringData;

#include "ascii_string.h"

#include <vector>

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include <string.h>

namespace _STL
{
// Bind the appends and the element-vector teardown to their rowed workers.
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString &value);
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
}

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getNextSubToken(const char *expected);
	const char *getSepsColon() const { return m_sepsColon; }
	float scanReal(const char *token);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static void parseParticleSystemTemplate(INI *ini, void *instance, void *store, const void *userData);

private:
	char m_unreconstructed[0x420];
	const char *m_sepsColon;
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
	char *mFailureMessage; // +0x00
	int m_argCount; // +0x04
};

// The independently rowed initializer builds only the first sixteen bytes.
// Its ManTheWalls owner has an Object-pointer vector, so the transition
// record's AsciiString-vector lifetime needs a separate local view.
class Rva004BA1B2
{
public:
	Rva004BA1B2();
	int m_objectID;
protected:
	void *m_vectorStorage[3];
};
class TransitionNeighborRecord_RV : public Rva004BA1B2
{
public:
	~TransitionNeighborRecord_RV() { subObjects().~vector(); }
	__forceinline _STL::vector<AsciiString> &subObjects()
	{ return *reinterpret_cast<_STL::vector<AsciiString> *>(m_vectorStorage); }
	const void *m_ocl;
	Coord3D m_neighborOffset;
	Coord3D m_oclOffset;
};

class ObjectCreationList;
class Rva004BA1D0
{
public:
	Rva004BA1D0(const Rva004BA1D0 &other);
	int m_objectID; // +0x00
	_STL::vector<AsciiString> m_subObjects; // +0x04
	const ObjectCreationList *m_ocl; // +0x10
	Coord3D m_neighborOffset; // +0x14
	Coord3D m_oclOffset; // +0x20
};

class Rva004BA1C8;

struct TransitionDamageFXRecordA
{
	void *m_value;
	unsigned char m_locType;
	unsigned char m_pad05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_pad0D[3];
	float m_loc[3];
};

struct TransitionDamageFXRecordB
{
	void *m_value;
	unsigned char m_locType;
	unsigned char m_pad05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_pad0D[3];
	float m_loc[3];
};

struct TransitionDamageFXRecordC
{
	void *m_value;
	unsigned char m_locType;
	unsigned char m_pad05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_pad0D[3];
	float m_loc[3];
};

// BFME1 supplies the string/vector semantic lead. Native callbacks 4B9C46
// and 577998 independently prove a zeroed, owned word at record offset 8;
// both four-element header arrays use the vector constructor closure256646
// and string-vector destructor2CC70. The original record names are unknown.
typedef _STL::vector<AsciiString> TransitionSmallVec;

enum TransitionDamageFXExtent
{
	BODYDAMAGETYPE_COUNT = 4,
	DAMAGE_MODULE_MAX_FX = 12
};

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData();
};

class INI;

class TransitionDamageFXModuleData : public UpdateModuleData
{
public:
	TransitionDamageFXModuleData();
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static void parseParticleSystem(INI *ini, void *instance, void *store, const void *userData);
	static void NeighborIDSubobjectNameDataAppend(INI *ini, void *instance, void *store, const void *userData);

private:
	const void *m_vtable;
	unsigned int m_unused04;
	int m_damageFXTypes;
	TransitionDamageFXRecordA m_fxList[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];
	int m_damageOCLTypes;
	TransitionDamageFXRecordB m_ocl[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];
	int m_damageParticleTypes;
	TransitionDamageFXRecordC m_particleSystem[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];
	TransitionSmallVec m_unkFD4[4];
	TransitionSmallVec m_unk1004[4];
	_STL::vector<Rva004BA1C8> m_tail;
};

void TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend(INI *ini, void *instance, void *store, const void *)
{
	TransitionNeighborRecord_RV neighbor;
	neighbor.m_objectID = 0;
	neighbor.m_ocl = 0;
	neighbor.m_neighborOffset.z = 0.0f;
	neighbor.m_neighborOffset.y = 0.0f;
	neighbor.m_neighborOffset.x = 0.0f;
	neighbor.m_oclOffset.z = 0.0f;
	neighbor.m_oclOffset.y = 0.0f;
	neighbor.m_oclOffset.x = 0.0f;

	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token != 0)
	{
		do
		{
			if (_strcmpi(token, "NeighborOffset") == 0)
			{
				neighbor.m_neighborOffset.x = ini->scanReal(ini->getNextSubToken("X"));
				neighbor.m_neighborOffset.y = ini->scanReal(ini->getNextSubToken("Y"));
				neighbor.m_neighborOffset.z = ini->scanReal(ini->getNextSubToken("Z"));
			}
			else if (_strcmpi(token, "OCLOffset") == 0)
			{
				neighbor.m_oclOffset.x = ini->scanReal(ini->getNextSubToken("X"));
				neighbor.m_oclOffset.y = ini->scanReal(ini->getNextSubToken("Y"));
				neighbor.m_oclOffset.z = ini->scanReal(ini->getNextSubToken("Z"));
			}
			else if (_strcmpi(token, "OCL") == 0)
				INI::parseObjectCreationList(ini, instance, (void *)&neighbor.m_ocl, 0);
			else if (_strcmpi(token, "SubObject") == 0)
			{
				AsciiString subObject(ini->getNextToken(0));
				neighbor.subObjects().push_back(subObject);
			}
			else
				throw INIException(3, "bad colon spacing, or unexpected token in TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend");

			token = ini->getNextTokenOrNull(ini->getSepsColon());
		} while (token != 0);
	}

	((_STL::vector<Rva004BA1D0> *)store)->push_back(*(Rva004BA1D0 *)&neighbor);
}
