// cl: /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Phase-indexed FX/OCL list FieldParse procs of three structure modules. Each
// reads a phase name through the member scanIndexList (explicit null seps),
// then appends every following token's FXList / ObjectCreationList to the
// per-phase vector (0xC-byte STLport vectors, rowed push_back fold 0x004DFCB0).
// Target evidence (FieldParse table, phase-name table, vector base):
//   StructureCollapseUpdateModuleData  table 0x00C52790 (buildFieldParse 0x004A4BF7)
//       FXList 0x004A4B31  m_fxs  +0x90   OCL 0x004A4B94  m_ocls +0x54   names 0x00DCBC8C
//   RubbleRiseUpdateModuleData         table 0x00C52960 (buildFieldParse 0x004A5486)
//       FXList 0x004A53BF  m_fxs  +0x88   OCL 0x004A5424  m_ocls +0x58   names 0x00DCBCE0
//   StructureToppleUpdateModuleData    table 0x00C52BD8 (buildFieldParse 0x004A651B)
//       OCL 0x004A646B  +0x70                                           names 0x00DCBD30
// The StructureCollapseUpdate pair are Zero Hour's StructureCollapseUpdate.cpp
// file statics parseFXList / parseOCL; RubbleRise (a BFME 2 module of the
// same shape) is given the same names. All are scoped to their module data
// class so the ledger names stay unique. The Topple OCL list is a BFME 2
// addition and keeps an address-derived name.

#include <vector>

#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	int scanIndexList(const char *token, const char *const *names);
	static void parseReal(INI *ini, void *instance, void *value, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *value, const void *userData);
};

class FXList;
class ObjectCreationList;

struct AngleFXInfo
{
	float angle;
	FXList *fxList;
};

typedef _STL::vector<AngleFXInfo> AngleFXInfoVector;

// The retail 8-byte vector append is rowed under this established ABI spelling.
struct BfmeE8
{
	int a;
	int b;
};

namespace _STL
{
template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(const BfmeE8 &);
}

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};
extern FXListStore *TheFXListStore;

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList(const char *name) const;
};
extern ObjectCreationListStore *TheObjectCreationListStore;

typedef _STL::vector<const FXList *> FXListVec;
typedef _STL::vector<const ObjectCreationList *> OCLVec;

extern const char *TheStructureCollapsePhaseNames[];	// VA 0x00DCBC8C
extern const char *TheRubbleRisePhaseNames[];		// VA 0x00DCBCE0
extern const char *TheStructureTopplePhaseNames[];	// VA 0x00DCBD30

class StructureCollapseUpdateModuleData
{
public:
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseOCL(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_unreconstructed_00[0x54];
	OCLVec m_ocls[5];		// +0x54
	FXListVec m_fxs[5];		// +0x90
};

class RubbleRiseUpdateModuleData
{
public:
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseOCL(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_unreconstructed_00[0x58];
	OCLVec m_ocls[4];		// +0x58
	FXListVec m_fxs[4];		// +0x88
};

class StructureToppleUpdateModuleData
{
public:
	static void rva004A646B(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_unreconstructed_00[0x70];
	OCLVec m_ocls[3];		// +0x70, indexed by phase
	unsigned int m_oclCount[3];	// +0x94
	unsigned char fxbones[0x0C];	// +0xA0
	AngleFXInfoVector angleFX;	// +0xAC
};

// ?parseAngleFX@@YAXPAVINI@@PAX1PBX@Z
void parseAngleFX(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	StructureToppleUpdateModuleData *self = (StructureToppleUpdateModuleData *)instance;
	AngleFXInfo info;
	INI::parseReal(ini, instance, &(info.angle), NULL);
	info.angle = info.angle * 3.14159265359f / 180.0f; // convert from degrees to radians.
	INI::parseFXList(ini, instance, &(info.fxList), NULL);
	((_STL::vector<BfmeE8> *)&self->angleFX)->push_back(*(const BfmeE8 *)&info);
}

// ?parseFXList@StructureCollapseUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z
void StructureCollapseUpdateModuleData::parseFXList(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	StructureCollapseUpdateModuleData *self = (StructureCollapseUpdateModuleData *)instance;
	int phase = ini->scanIndexList(ini->getNextToken(NULL), TheStructureCollapsePhaseNames);
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const FXList *fxl = TheFXListStore->findFXList(token);	// could be null! this is OK!
		self->m_fxs[phase].push_back(fxl);
	}
}

// ?parseOCL@StructureCollapseUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z
void StructureCollapseUpdateModuleData::parseOCL(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	StructureCollapseUpdateModuleData *self = (StructureCollapseUpdateModuleData *)instance;
	int phase = ini->scanIndexList(ini->getNextToken(NULL), TheStructureCollapsePhaseNames);
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *ocl = TheObjectCreationListStore->findObjectCreationList(token);	// could be null! this is OK!
		self->m_ocls[phase].push_back(ocl);
	}
}

// ?parseFXList@RubbleRiseUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z
void RubbleRiseUpdateModuleData::parseFXList(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	RubbleRiseUpdateModuleData *self = (RubbleRiseUpdateModuleData *)instance;
	int phase = ini->scanIndexList(ini->getNextToken(NULL), TheRubbleRisePhaseNames);
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const FXList *fxl = TheFXListStore->findFXList(token);	// could be null! this is OK!
		self->m_fxs[phase].push_back(fxl);
	}
}

// ?parseOCL@RubbleRiseUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z
void RubbleRiseUpdateModuleData::parseOCL(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	RubbleRiseUpdateModuleData *self = (RubbleRiseUpdateModuleData *)instance;
	int phase = ini->scanIndexList(ini->getNextToken(NULL), TheRubbleRisePhaseNames);
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *ocl = TheObjectCreationListStore->findObjectCreationList(token);	// could be null! this is OK!
		self->m_ocls[phase].push_back(ocl);
	}
}

// ?rva004A646B@StructureToppleUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z
void StructureToppleUpdateModuleData::rva004A646B(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	StructureToppleUpdateModuleData *self = (StructureToppleUpdateModuleData *)instance;
	int phase = ini->scanIndexList(ini->getNextToken(NULL), TheStructureTopplePhaseNames);
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *ocl = TheObjectCreationListStore->findObjectCreationList(token);	// could be null! this is OK!
		self->m_ocls[phase].push_back(ocl);
	}
}
