// ?getNthPlayerTemplate@PlayerTemplateStore@@QBEPBVPlayerTemplate@@H@Z
// partial score=0.97 date=2026-09-26
// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getNthPlayerTemplate@PlayerTemplateStore@@QBEPBVPlayerTemplate@@H@Z,
// retail 0x001FD3C6, 62 bytes.
//
// Bounds-checked selection from the template vector with override resolution:
// out-of-range (or negative) index yields NULL, otherwise the element's final
// override (the element itself when it has no next override). The first
// override level is tested inline; deeper levels go through the rowed folded
// getFinalOverride span at 0x1E35DF (gen-alias object-symbol).
// Ported from Open-BFME-1
// Code/GameEngine/Source/Common/RTS/PlayerTemplate.cpp (BFME1 lacks the
// override branch; BFME2's PlayerTemplate derives from Overridable, which
// moves m_nameKey to +0x10 and puts m_nextOverride at +0x04).
// BFME2 facts (all retail-measured):
// - The template vector triple sits at +0x0C (start/finish/alloc); size() and
//   operator[] inline to the sub+idiv/imul 0x1DC stride pair, so
//   sizeof(PlayerTemplate) == 0x1DC.
// - The sole out-of-line callee is getFinalOverride (thiscall on the +0x04
//   word); getNextOverride inlines to the mov/test pair.

typedef int Int;

#include <vector>

// ZH Overridable.h: Overridable : MemoryPoolObject {
//   Overridable *m_nextOverride; Bool m_isOverride; ... } with inline
// getNextOverride and out-of-line getFinalOverride. MemoryPoolObject
// contributes the leading word (its vtable), modeled here as one pure slot
// so no vtable is emitted from this TU while m_nextOverride lands at +0x04.
class MemoryPoolObject
{
public:
	virtual void poolPlaceholder() = 0;
};

class Overridable : public MemoryPoolObject
{
public:
	const Overridable *getNextOverride() const { return m_nextOverride; }
	const Overridable *getFinalOverride() const;

private:
	Overridable *m_nextOverride; // +0x04
	bool m_isOverride;
};

class PlayerTemplate : public Overridable
{
private:
	// Trailing members (name key at +0x10, display name at +0x14, ...) are
	// established by the sibling PlayerTemplateGetName/DisplayName TUs and
	// untouched by this body; the pad only fixes the retail-measured size.
	char m_pad[0x1DC - sizeof(Overridable)];
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(Int i) const;

private:
	// Leading words (subsystem base) untouched by this body.
	char m_pad[0x0C];
	std::vector<PlayerTemplate> m_playerTemplates; // +0x0C
};

// ?getNthPlayerTemplate@PlayerTemplateStore@@QBEPBVPlayerTemplate@@H@Z
const PlayerTemplate *PlayerTemplateStore::getNthPlayerTemplate(Int i) const
{
	if (i >= 0 && i < m_playerTemplates.size())
	{
		const PlayerTemplate &t = *(m_playerTemplates.begin() + i);
		const Overridable *o = t.getNextOverride();
		if (o == NULL)
			return &t;
		return (const PlayerTemplate *)o->getFinalOverride();
	}
	return NULL;
}
