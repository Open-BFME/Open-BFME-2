// cl: /O1 /DNDEBUG /MD
//
// ?appendOnce@GateOpenBehaviorList@@QAEXPAX@Z, retail 0x004E9353, 34 bytes.
// Dedup-append helper: linear find over the pointer range at +0/+4, push_back
// the item only if absent. Sole caller is the GateOpenAndCloseBehavior ctor
// (0x49889C), which registers the new behavior into the global list at
// [0xDFEEF8]+0x940. The holder class is TU-local (the global owner is
// unidentified); identity rests on sole-caller plus vector shape plus the
// push_back fold (0x4DFCB0 folds all 4-byte-pointer vectors; the TU spelling
// rides an alias pin). push_back is declared-only and pinned, never defined.

class GateOpenBehaviorList
{
public:
	void appendOnce(void *item);
	void push_back(void *const &item);

private:
	void **m_begin; // +0
	void **m_end; // +4
};

// ?appendOnce@GateOpenBehaviorList@@QAEXPAX@Z
void GateOpenBehaviorList::appendOnce(void *item)
{
	void **finish = m_end;
	for (void **cursor = m_begin; cursor != finish; ++cursor)
	{
		if (*cursor == item)
			return;
	}
	push_back(item);
}
