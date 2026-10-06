// ?NeighborIDSubobjectNameDataAppend@TransitionDamageFXModuleData@@SAXPAVINI@@PAX1PBX@Z
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?NeighborIDSubobjectNameDataAppend@TransitionDamageFXModuleData@@SAXPAVINI@@PAX1PBX@Z @0x004BA817 460B
// Evidence: BFME1 donor reference/open-bfme-1/game/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFXModuleDataParseRubbleNeighbor.cpp NeighborIDSubobjectNameDataAppend; retail strings "NeighborOffset" "OCLOffset" "OCL" "SubObject" plus "bad colon spacing, or unexpected token in TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend"; callees rowed getNextTokenOrNull 0x0002DEED getNextSubToken 0x0002E06B scanReal 0x0002EDA5 parseObjectCreationList 0x00338A6F getNextToken 0x0002DF97 vector<AsciiString> push_back 0x0002DBE6 and dtor 0x0002CC70 plus StringBase PBD ctor 0x00037BA0 and releaseBuffer 0x00036410 plus default ctor 0x004BA1B2 and vector<Rva004BA1D0> push_back 0x004BA7E0; layout int plus vector<AsciiString> at +4 plus OCL plus Neighbor plus OCLOffset matches Rva004BA1D0 44B record.
typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

template <typename T> struct BfmeStringData;

#include "ascii_string.h"

namespace _STL
{
template <typename T> class allocator
{
};

template <typename T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
	~vector();

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getNextSubToken(const char *expected);
	const char *getSepsColon() const { return m_sepsColon; }
	float scanReal(const char *token);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);

private:
	char m_unreconstructed[0x420];
	const char *m_sepsColon;
};

class INIException
{
public:
	INIException(int code, const char *format, ...);
	INIException(const INIException &other);
	~INIException();

private:
	char *m_failureMessage;
	int m_argCount;
};

class Rva004BA1B2
{
public:
	Rva004BA1B2();
	int m_objectID;
	_STL::vector<AsciiString> m_subObjects;
	const void *m_ocl;
	Coord3D m_neighborOffset;
	Coord3D m_oclOffset;
};

class Rva004BA1D0
{
private:
	int m_objectID;
	_STL::vector<AsciiString> m_subObjects;
	const void *m_ocl;
	Coord3D m_neighborOffset;
	Coord3D m_oclOffset;
};

class TransitionDamageFXModuleData
{
public:
	static void NeighborIDSubobjectNameDataAppend(INI *ini, void *instance, void *store, const void *userData);
};

void TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend(INI *ini, void *instance, void *store, const void *)
{
	Rva004BA1B2 neighbor;
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
				neighbor.m_subObjects.push_back(subObject);
			}
			else
				throw INIException(3, "bad colon spacing, or unexpected token in TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend");

			token = ini->getNextTokenOrNull(ini->getSepsColon());
		} while (token != 0);
	}

	((_STL::vector<Rva004BA1D0> *)store)->push_back(*(Rva004BA1D0 *)&neighbor);
}
