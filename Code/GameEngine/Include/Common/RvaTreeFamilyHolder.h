#pragma once
#ifndef BFME2_RVA_TREE_FAMILY_HOLDER_H
#define BFME2_RVA_TREE_FAMILY_HOLDER_H

// Shared ABI view of the four-byte owning header member. Native cleanup at
// RVA 0x0007FAB3 conditionally frees its pointer. The inline definition stays
// in RvaTreeDtorFamily.cpp, where the holder's direct lifetimes are emitted;
// consumers destroy the enclosing trees through their out-of-line destructors.
struct RvaTreeFamilyHeader;

struct RvaTreeFamilyHolder
{
	RvaTreeFamilyHeader *m_ptr;
	inline ~RvaTreeFamilyHolder();
};

typedef char RvaTreeFamilyHolderSizeCheck[sizeof(RvaTreeFamilyHolder) == 4 ? 1 : -1];

#endif
