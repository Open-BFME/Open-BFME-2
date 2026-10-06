// cl: /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/System/CrateSystem.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// CrateSystem::parseCrateTemplateDefinition 0x0035CFEA (173B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
// One adaptation read off retail: the AsciiString assignment from a C string
// calls StringBase<char>::set (0x000055F5) directly rather than the rowed
// operator= at 0x000065B8, so it is spelled as set(). The global
// TheCrateSystem is declared extern, not defined.
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: CrateSystem.cpp /////////////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood Feb 2002
// Desc:   System responsible for Crates as code objects - ini, new/delete etc
///////////////////////////////////////////////////////////////////////////////////////////////////

#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>	// before PreRTS.h so node_alloc freelist is used (not NEWALLOC)
// BFME's KindOf list is longer than Zero Hour's, so KindOfMaskType is wider.
// Retail CrateTemplate zeroes six dwords for m_killedByTypeKindof (this+0x18
// through this+0x2F) where ZH's 121-bit mask needs four, which puts BFME's
// KINDOF_COUNT in (160,192]: std::bitset rounds to whole 32-bit words, so any
// count in that range gives the same six. Only the width is provable from
// these bytes - the names past ZH's list are not - so this substitutes a
// width-only KindOfMaskType rather than inventing enumerators. Scoped to this
// translation unit: inputs/reference/shims/bfmekindof/Common/KindOf.h carries the two
// extra names TunnelTracker proves, but it is still four dwords wide.
#define __KINDOF_H_
#include "Common/BitFlags.h"
enum KindOfType
{
	KINDOF_INVALID = -1,
	KINDOF_FIRST = 0,
	KINDOF_COUNT = 192						///< width pin only; see above
};
typedef BitFlags<KINDOF_COUNT>	KindOfMaskType;
#define MAKE_KINDOF_MASK(k) KindOfMaskType(KindOfMaskType::kInit, (k))
#define CLEAR_KINDOFMASK(m) ((m).clear())

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:

#define DEFINE_VETERANCY_NAMES				// for TheVeterancyNames[]

#include "GameLogic/CrateSystem.h"
#include "Common/BitFlagsIO.h"

extern CrateSystem *TheCrateSystem;

// BFME raises this byte while copying a default template as it does for
// override copies (retail address 0x012ED611).
extern Bool TheBfmeOverrideCopyInProgress;


// BFME CrateSystem::~CrateSystem uses polymorphic `delete` (vtbl[0] + flag 1),
// not MemoryPoolObject::deleteInstance(). Pool-glue keeps ~CrateTemplate /
// operator delete protected; a local derived helper is the minimal access path.
namespace {
class CrateTemplateDeleteHelper : public CrateTemplate
{
public:
	static void destroy(CrateTemplate *p)
	{
		delete static_cast<CrateTemplateDeleteHelper *>(p);
	}
};
}


// BFME's reset uses the original three-field Overridable layout and deleting
// destructor, before Zero Hour's memory-pool deleteInstance path.
class BfmeCrateOverrideView
{
public:
	virtual ~BfmeCrateOverrideView();

	BfmeCrateOverrideView *m_nextOverride;
	bool m_isOverride;

	BfmeCrateOverrideView *deleteOverrides()
	{
		if (m_isOverride)
		{
			delete this;
			return NULL;
		}
		if (m_nextOverride)
			m_nextOverride = m_nextOverride->deleteOverrides();
		return this;
	}
};


// BFME keeps m_loadType at INI+0x08; Zero Hour's header puts it at +0x2010
// because of the 8KB read buffer BFME does not have (docs/ini_loading.md).
static INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

// BFME has a fourth INILoadType Zero Hour does not, value 4. Nothing names it.
static const INILoadType INI_LOAD_BFME_TYPE_4 = (INILoadType)4;

void CrateSystem::parseCrateTemplateDefinition(INI* ini)
{
	AsciiString name;

	// read the crateTemplate name. Assignment rather than set(c): BFME inlines
	// strlen and calls the two-argument set, which is what operator= expands to.
	name.set( ini->getNextToken() );	// retail calls StringBase::set (0x000055F5), not the operator= thunk

	CrateTemplate *crateTemplate = TheCrateSystem->friend_findCrateTemplate(name);
	if (crateTemplate == NULL) {
		crateTemplate = TheCrateSystem->newCrateTemplate(name);

		if (retailLoadType(ini) == INI_LOAD_CREATE_OVERRIDES) {
			crateTemplate->markAsOverride();
		}
	} else {
		// Two load types take an override here, not one, and retail loads
		// m_loadType once and compares it twice -- hence the local.
		const INILoadType loadType = retailLoadType(ini);
		if (loadType == INI_LOAD_CREATE_OVERRIDES || loadType == INI_LOAD_BFME_TYPE_4) {
			crateTemplate = TheCrateSystem->newCrateTemplateOverride(crateTemplate);
		}
	}

	// parse the ini weapon definition
	ini->initFromINI(crateTemplate, crateTemplate->getFieldParse());
}


