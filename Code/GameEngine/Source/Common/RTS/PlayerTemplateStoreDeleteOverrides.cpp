// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// PlayerTemplateStore::reset, retail 0x001FD4A2 (63 B; WB 0x00A78370,
// unnamed, reached through a vtable): drops the INI overrides of every
// player template (Overridable::deleteOverrides 0x001E35ED) in the store's
// template vector at +0x0C (stride 0x1DC, as the rowed lookups in
// PlayerTemplate.cpp read it). Zero Hour's reset() keeps the list; this is
// BFME's override-aware counterpart: slot 9, the subsystem reset slot.
#include <vector>

enum NameKeyType
{
	NAMEKEY_INVALID = -1,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Overridable
{
public:
	Overridable *deleteOverrides();
	const Overridable *getFinalOverride() const;

	virtual ~Overridable();
	Overridable *m_nextOverride;
	bool m_isOverride;
    char pad09[3];
	int m_extra0C;
};

struct PlayerTemplateOverrideView : public Overridable
{
	NameKeyType m_nameKey;
	char m_rest[0x1DC - 0x14];
};

class PlayerTemplateStore
{
public:
	void reset();
private:
	char m_pad00[0x0C];
	_STL::vector<PlayerTemplateOverrideView> m_playerTemplates;	// +0x0C
};

void PlayerTemplateStore::reset()
{
	for (unsigned int i = 0; i < m_playerTemplates.size(); ++i)
		m_playerTemplates[i].deleteOverrides();
}
