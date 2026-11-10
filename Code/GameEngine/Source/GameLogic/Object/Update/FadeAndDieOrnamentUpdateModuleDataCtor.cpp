// cl: /O1 /DNDEBUG /MD /GX
//
// FadeAndDieOrnamentUpdateModuleData file-unit (parse first; the ctor
// remains pinned for a follow-up).
//
// ?buildFieldParse@FadeAndDieOrnamentUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0025438C, 17 bytes. Single-table parse proc (table (unsigned int)&g_00BF2358)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.
//
// ??0FadeAndDieOrnamentUpdateModuleData@@QAE@XZ, retail 0x002555AC,
// 85 bytes. MD ctor: vtable 0x00BF3740 plus AttachToTargetBone string at
// +0x08 (inline-zero plus clear through the rowed 0x36410 fold, Topple
// precedent; its declared-only dtor arms EH state 1: retail's unwind
// funclet 0x00771D0C destroys +0x08 through 0x0048BA39) plus Envelope
// OrnamentData at +0x0C (trivial: no destructor, no unwind state; explicit
// init through the pinned 0xC9251 leaf, then and-zero of the +0x0C/+0x24
// dwords) plus
// FollowTarget at +0x34 set to true. The empty UpdateModuleData base
// (inline-empty ctor plus declared-only dtor) advances EH state 0 with no
// emitted code (Topple precedent). Field identity is the own table at
// (unsigned int)&g_00BF2358 (AttachToTargetBone at +0x08, Envelope at +0x0C,
// FollowTarget at +0x34). The rowed factory at 0x255601 news 0x38.

extern "C" const void *const vtbl_00BF3740[];  // ??_7Rva0025558E@@6B@

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct OrnamentData
{
	OrnamentData *init() throw();

	unsigned char m_pad[0x0C];
	int m_inner0C;
	unsigned char m_pad10[0x14];
	int m_inner24;
};

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData();
};

class MultiIniFieldParse;
struct FieldParse;

#include "../../../../Include/Common/INI/FieldParse.h"
#include "../../../../Include/Common/INI/INI.h"

// The proc's FieldParse table, read from retail (it was a 1-byte zero placeholder).
// Retail parses FollowTarget with the envelope parser as well; kept as retail has it.
// Retail VA 0x00BF2358: 3 fields and the zero sentinel.
extern const FieldParse g_00BF2358[] = {
	{ "AttachToTargetBone", &INI::parseAsciiString, 0, 0x8 },
	{ "Envelope", &INI::Rva00338E52_ParseEnvelope, 0, 0xC },
	{ "FollowTarget", &INI::Rva00338E52_ParseEnvelope, 0, 0x34 },
	{ 0, 0, 0, 0 }
};

class FadeAndDieOrnamentUpdateModuleData : public UpdateModuleData
{
public:
	FadeAndDieOrnamentUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	const void *m_vtable;
	unsigned int m_unused04;
	AsciiString m_attachToTargetBone; // +0x08
	OrnamentData m_envelope; // +0x0C
	bool m_followTarget; // +0x34
};

// ?buildFieldParse@FadeAndDieOrnamentUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0025438C
void FadeAndDieOrnamentUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(reinterpret_cast<const FieldParse *>((unsigned int)&g_00BF2358), 0);
}

// ??0FadeAndDieOrnamentUpdateModuleData@@QAE@XZ @0x002555AC
inline FadeAndDieOrnamentUpdateModuleData::FadeAndDieOrnamentUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(((unsigned int)vtbl_00BF3740)))
	, m_attachToTargetBone()
{
	OrnamentData *envelope = &m_envelope;
	envelope->init();
	envelope->m_inner0C &= 0;
	envelope->m_inner24 &= 0;
	m_attachToTargetBone.clear();
	m_followTarget = true;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeFadeAndDieOrnamentUpdateModuleDataInlineAnchor@@YAXPAVFadeAndDieOrnamentUpdateModuleData@@@Z absent-from-retail
void _bfmeFadeAndDieOrnamentUpdateModuleDataInlineAnchor(FadeAndDieOrnamentUpdateModuleData *fadeAndDieOrnamentUpdateModuleData)
{
    fadeAndDieOrnamentUpdateModuleData->FadeAndDieOrnamentUpdateModuleData::FadeAndDieOrnamentUpdateModuleData();
}
#pragma inline_depth()
