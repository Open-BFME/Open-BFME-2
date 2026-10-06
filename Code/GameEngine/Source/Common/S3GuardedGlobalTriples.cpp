// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?h00040601@GenAlpha@@QAEXXZ 0x000F0AD7, 16 bytes
// ?h000053B7@GenAlpha@@QAEXXZ 0x000F0AE7, 16 bytes
// ?h000217DD@GenBeta@@QAEXXZ  0x001071EC, 17 bytes
// ?h00005592@GenBeta@@QAEXXZ  0x001071FD, 17 bytes
//
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/S3GuardedGlobalTriples.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os. Each of the four is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text), where BFME 1's own flags do not. Only the four placed
// bodies are defined here; the donor's five S3_TRIPLE free functions are
// omitted, so the unmatched-definition gate passes.
//
// WHAT THE BYTES SHOW for the donor's free functions, which is why these
// members exist at the shapes they do:
//
//     mov ecx,[G1] / test ecx,ecx / je .1 / call <REL32>
//  .1 mov ecx,[G2] / test ecx,ecx / je .2 / call <REL32>
//  .2 mov ecx,[G3] / test ecx,ecx / je .3 / jmp  <REL32>
//  .3 ret
//
// The guard, the order and the tail position are carried from the donor's
// source; the callees it called are declared here but not defined, since
// they are not part of this batch.
//
// IDENTITY IS NOT RECOVERED.  The names are derived from addresses.  The bytes
// cannot say what the three globals point at, whether the three types are
// related, or what any of the fifteen members do -- only that the guard, the
// order, and the tail position are as written.

#define S3_H( ADDR ) __declspec(noinline) void h##ADDR();

struct GenAlphaNode
{
	void *m_vtable;
	bool m_enabled;
	char m_unmodelled[ 0x63 ];
	GenAlphaNode *m_next;
};

struct GenBetaNode
{
	virtual void remove( bool destroy );
	bool m_enabled;
	char m_unmodelled[ 0x67 ];
	GenBetaNode *m_next;
};

class GenAlpha
{
public:
	S3_H(00044062) S3_H(00016AF4) S3_H(00024D2A) S3_H(00040601) S3_H(000053B7)
	GenAlphaNode *m_head;
	void *m_04;
	void *m_08;
};

class GenBeta
{
public:
	S3_H(00015BF4) S3_H(00008ACB) S3_H(00043743) S3_H(000217DD) S3_H(00005592)
	void *m_00;
	void *m_04;
	GenBetaNode *m_head;
};
class GenGamma { public: S3_H(0004AB42) S3_H(000131E2) S3_H(0001FE8D) S3_H(00048C70) S3_H(0000C919) };

extern GenAlpha *TheAlpha;
extern GenGamma *TheGamma;

// 0x01307178 is W3DShadow.cpp's TheW3DShadowHelperManager, so the global is
// spelled by its defining name here.  No header declares the class, so only a
// forward declaration is needed: the five bodies this TU calls are still
// ledger-named GenBeta, and that view is kept through the casts below.
class W3DShadowHelperManager;
extern W3DShadowHelperManager *TheW3DShadowHelperManager;

void GenAlpha::h00040601()
{
	for( GenAlphaNode *node = m_head; node; node = node->m_next )
		node->m_enabled = false;
}

void GenAlpha::h000053B7()
{
	for( GenAlphaNode *node = m_head; node; node = node->m_next )
		node->m_enabled = true;
}

void GenBeta::h000217DD()
{
	for( GenBetaNode *node = m_head; node; node = node->m_next )
		node->m_enabled = false;
}

void GenBeta::h00005592()
{
	for( GenBetaNode *node = m_head; node; node = node->m_next )
		node->m_enabled = true;
}
