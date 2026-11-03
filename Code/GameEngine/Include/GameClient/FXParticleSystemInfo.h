// FILE: FXParticleSystemInfo.h ///////////////////////////////////////////////////////////////////
// Desc:   FXParticleSystem::ParticleSystemInfo, the base of ParticleSystem and ParticleSystemTemplate. Not registered yet.
//
// Target facts (RVAs unless marked VA):
//  - ParticleSystemInfo (exports): ctor 0x001F4E82 stores VA 0x00BBB5C8 (??_7, RVA 0x007BB5C8),
//    copy ctor 0x00002459, assignment 0x0000200D, dtor 0x0000240E. Its table holds the vector
//    deleting dtor 0x000025B2 (element 0x9C: sizeof 0x9C), LoadPostProcess 0x000B3FD0,
//    GetSnapshotName 0x00001272 ("FXParticleSystemInfo", VA 0x00BBB530) and DoXfer(Xfer &) 0x001F4F5A.
//  - Base fields: ctor 0x001F4E82 stores +0x04, +0x08/+0x0C/+0x7C (1), the strings +0x10/+0x68/+0x78,
//    random variables +0x14/+0x28/+0x34/+0x44/+0x50/+0x5C, +0x20/+0x24/+0x40, the triple +0x6C,
//    bytes +0x80..+0x84, the region +0x88 and +0x98; assignment 0x0000200D also copies byte +0x85.
//    Exported ParticleSystemTemplate accessors read the same base: getParticleType 0x001DB0A8 (+0x0C,
//    enum FXParticleSystem::ParticleType), getTextureFilename 0x0000261E (+0x10), getUV 0x0055C414
//    and setUV 0x00001278 (+0x88, Region2D). DoXfer passes +0x08 to XferParticleShaderType, +0x0C to
//    XferParticleType and +0x7C to XferParticlePriorityType. 0x001F55A8 converts +0x14's getValue to
//    an integer (0x001F57ED) and adds +0x34's to +0x180 (0x001F5806), as Zero Hour's
//    generateParticleInfo does with m_lifetime, m_startSizeRate and m_accumulatedSizeBonus.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef CANONICAL_FXPARTICLESYSTEMINFO_H
#define CANONICAL_FXPARTICLESYSTEMINFO_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/Region2D.h"
#include "GameClientRandomVariable.h"

class Xfer;

namespace FXParticleSystem
{

enum ParticleType;
class ParticleSystemTemplate;

//-------------------------------------------------------------------------------------------------
class ParticleSystemInfo : public Snapshot
{
public:
	ParticleSystemInfo();										// 0x001F4E82
	ParticleSystemInfo(const ParticleSystemInfo &that);			// 0x00002459
	ParticleSystemInfo &operator=(const ParticleSystemInfo &that);	// 0x0000200D
	virtual ~ParticleSystemInfo();								// 0x0000240E (slot 0: 0x000025B2)

#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
	virtual void LoadPostProcess();								// slot 1, 0x000B3FD0
#else
	virtual void loadPostProcess();								// slot 1, 0x000B3FD0
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
	virtual const char *GetSnapshotName();						// slot 2, 0x00001272
#else
	virtual const char *GetSnapshotName() const;				// slot 2, 0x00001272
#endif
#else
	virtual void crc(Xfer *xfer);								// slot 2, 0x00001272
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
	virtual void DoXfer(Xfer &xfer);							// slot 3, 0x001F4F5A
#else
	virtual void DoXfer(Xfer *xfer);							// slot 3, 0x001F4F5A
#endif
#else
	virtual void xfer(Xfer *xfer);								// slot 3, 0x001F4F5A
#endif

	bool m_isOneShot;										// +0x04
	unsigned int m_shaderType;								// +0x08
	ParticleType m_particleType;							// +0x0C
	AsciiString m_particleTypeName;							// +0x10
	GameClientRandomVariable m_lifetime;					// +0x14
	unsigned int m_systemLifetime;							// +0x20
	unsigned int m_24;										// +0x24
	GameClientRandomVariable m_28;							// +0x28
	GameClientRandomVariable m_startSizeRate;				// +0x34
	unsigned int m_40;										// +0x40
	GameClientRandomVariable m_44;							// +0x44
	GameClientRandomVariable m_50;							// +0x50
	GameClientRandomVariable m_initialDelay;				// +0x5C
	AsciiString m_slaveSystemName;							// +0x68
	Coord3D m_slavePosOffset;								// +0x6C
	AsciiString m_attachedSystemName;						// +0x78
	unsigned int m_priority;								// +0x7C
	unsigned char m_80;										// +0x80
	unsigned char m_81;										// +0x81
	unsigned char m_82;										// +0x82
	unsigned char m_83;										// +0x83
	unsigned char m_84;										// +0x84
	unsigned char m_85;										// +0x85
	Region2D m_uv;											// +0x88
	unsigned int m_98;										// +0x98
};

}	// namespace FXParticleSystem

#endif // CANONICAL_FXPARTICLESYSTEMINFO_H
