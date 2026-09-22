// cl: /O2 /G7

#define NULL 0
//
// ?bfmeInit@Gen001811E0@@AAEPAV1@PAX@Z at retail 0x001810D0 (83 bytes).
//
// Private initializer behind the Gen001811E0 constructor in
// P8ZeroingCtors.cpp (rowed 73B at 0x001811E0): shares or detaches the
// owned refcounted object based on the source's tag. Semantics read from
// retail:
//
// - src = *(void **)source; when src is null, release the owned object and
//   take null (shared tail).
// - Otherwise the tag virtual at slot 0x34 is called on src and compared
//   against 'NULL' (0x4E554C4C). A NULL-tagged source is shared: its word
//   refcount at +4 is incremented and ownership moves over (with the owned
//   object released first).
// - A non-NULL-tagged source detaches: the owned object is released and the
//   slot is nulled, with no copy.
// - Returns this in eax (ret 4 thiscall).
//
// The tag virtual needs 13 declared-only placeholder slots ahead of it so
// the call lands at [eax+0x34]; placeholders are never constructed, so no
// vtable is emitted (TurretAI precedent). Release_Ref resolves through an
// alias pin at the shared 36B dec-word-at-4 fold (0x0061ED10, rowed as
// TextureBaseClass::Release_Ref). The refcount is an unsigned short at +4
// so the share path emits the retail word add. The tag compare is against
// the multi-char constant 'NULL' (0x4E554C4C); the macro spells it NULL, so
// the literal is written out with the tag name beside it.

class TaggedRefObject
{
public:
	virtual void _slot000();
	virtual void _slot001();
	virtual void _slot002();
	virtual void _slot003();
	virtual void _slot004();
	virtual void _slot005();
	virtual void _slot006();
	virtual void _slot007();
	virtual void _slot008();
	virtual void _slot009();
	virtual void _slot010();
	virtual void _slot011();
	virtual void _slot012();
	virtual int GetTag();
	void Release_Ref();

	unsigned short m_refCount; // +4
};

class Gen001811E0
{
private:
	Gen001811E0 *bfmeInit(void *source);

	TaggedRefObject *m_owned;
};

// ?bfmeInit@Gen001811E0@@AAEPAV1@PAX@Z
//
// Every read of the source goes back through the argument slot: retail
// homes the argument in edi and dereferences [edi] per use (the tag call
// forwards its load, the share check and the copy reload), keeping this in
// esi with no third register. A hoisted source local costs an extra home
// register and breaks the frame, so the loads are written out.
Gen001811E0 *Gen001811E0::bfmeInit(void *source)
{
	if (*(TaggedRefObject **)source != NULL)
	{
		if ((*(TaggedRefObject **)source)->GetTag() != 0x4E554C4C) // 'NULL'
		{
			if (m_owned != NULL)
			{
				m_owned->Release_Ref();
				m_owned = NULL;
			}
			return this;
		}
		if (*(TaggedRefObject **)source != NULL)
			(*(TaggedRefObject **)source)->m_refCount += 1;
	}
	if (m_owned != NULL)
		m_owned->Release_Ref();
	m_owned = *(TaggedRefObject **)source;
	return this;
}
