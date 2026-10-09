// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva003980BF@Rva003980BF@@QAEPAXPAXHH@Z retail 0x003980BF..0x0039815B
// (156 bytes ret 0xC). Picks one of two ID lists (+0x50 or +0x74 when the
// target's KindOf bits at +0x108 have bit 0x40 set and the +0x74 list is
// not empty) and hands IDs to the pinned cdecl helper 0x00397FEB
// (context +0x38 id target mode). Index -2 tries every ID until the helper
// returns non-null; any other index is clamped to the list and tried once.
// Caller 0x003BE38B passes (template -2 0) per the existing pin note. The
// WorldBuilder twin 0x00EBC470 (callgraph evidence) shows the block-scope
// id and result locals and the local copy of the index that set retail's
// register allocation. Class and method names stay address-derived; the
// list element type is inferred from the helper's unsigned id argument.
typedef unsigned int ObjectID;

class Rva003980BFIdList
{
public:
	typedef unsigned int size_type;
	const ObjectID *begin() const { return m_begin; }
	const ObjectID *end() const { return m_end; }
	size_type size() const { return size_type(m_end - m_begin); }
	const ObjectID &operator[](size_type i) const { return m_begin[i]; }

private:
	ObjectID *m_begin;
	ObjectID *m_end;
	ObjectID *m_capacity;
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int bit) const { return (m_kindOf[bit >> 3] & (1 << (bit & 7))) != 0; }

private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
};

void *__cdecl rva00397FEB(void *context, ObjectID id, void *target, int mode);

class Rva003980BF
{
public:
	void *rva003980BF(void *target, int which, int mode);

private:
	char m_pad00[0x38];
	void *m_context; // +0x38
	char m_pad3C[0x50 - 0x3C];
	Rva003980BFIdList m_normal; // +0x50
	char m_pad5C[0x74 - 0x5C];
	Rva003980BFIdList m_alternate; // +0x74
};

void *Rva003980BF::rva003980BF(void *target, int which, int mode)
{
	if (target == 0)
		return 0;
	const Rva003980BFIdList *ids = &m_normal;
	if (static_cast<ThingTemplate *>(target)->isKindOf(0x40) && m_alternate.size() > 0)
		ids = &m_alternate;
	if (which == -2)
	{
		for (const ObjectID *it = ids->begin(); it != ids->end(); ++it)
		{
			ObjectID id = *it;
			void *result = rva00397FEB(m_context, id, target, mode);
			if (result != 0)
				return result;
		}
	}
	else if (ids->size() > 0)
	{
		int index = which;
		if (index > ids->size() - 1)
			index = ids->size() - 1;
		else if (index < 0)
			index = 0;
		ObjectID id = (*ids)[index];
		void *result = rva00397FEB(m_context, id, target, mode);
		if (result != 0)
			return result;
	}
	return 0;
}
