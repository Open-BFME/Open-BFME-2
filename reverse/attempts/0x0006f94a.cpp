// ?rva0006F94A@RTS3DScene@@QAEPAVW3DDynamicLight@@XZ
// partial score=0.94 date=2026-10-09
// ?rva0006F94A@RTS3DScene@@QAEPAVW3DDynamicLight@@XZ
// partial score=0.85 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc

class RenderObjClass;

template <class T>
class RefMultiListClass
{
public:
	char m_fields[8];
	void *m_head;
};

template <class T>
class RefMultiListIterator
{
public:
	RefMultiListIterator(RefMultiListClass<T> *list)
	{
		m_list = list;
		m_current = list->m_head;
	}

private:
	RefMultiListClass<T> *m_list;
	void *m_current;
};

struct Rva0006F94ANode
{
	char m_pad0[4];
	Rva0006F94ANode *m_next;
	char m_pad8[4];
	struct Rva0006F94AMultiListBase *m_value;
};

struct Rva0006F94AReferenceBase {
    virtual void rva0006F94ARelease();
    int m_refs;
};
struct Rva0006F94AMultiListBase { void *node; };
class W3DDynamicLight : public Rva0006F94AReferenceBase, public Rva0006F94AMultiListBase {
public:
    W3DDynamicLight();
    void setEnabled(bool enabled);
    char m_pad0C[0x144-0xC];
    bool m_inUse;
    char m_tail145[0x174-0x145];
};
static __forceinline W3DDynamicLight *PeekLight(Rva0006F94ANode *node) {
    return static_cast<W3DDynamicLight *>(node->m_value);
}
class Rva0006F219
{
public:
	bool rva0006F219(RenderObjClass *obj);
};

class RTS3DScene
{
public:
	RefMultiListIterator<RenderObjClass> *createLightsIterator();
	W3DDynamicLight *rva0006F94A();

private:
	char m_fields[0x8c];
	RefMultiListClass<RenderObjClass> m_lightList;
	char m_pad98[0x118 - 0x98];
	Rva0006F94ANode m_lightSentinel;
};

RefMultiListIterator<RenderObjClass> *RTS3DScene::createLightsIterator()
{
	return new RefMultiListIterator<RenderObjClass>(&m_lightList);
}

// ?rva0006F94A@RTS3DScene@@QAEPAVW3DDynamicLight@@XZ @0x0006F94A
W3DDynamicLight *RTS3DScene::rva0006F94A()
{
	W3DDynamicLight *light;
	for (Rva0006F94ANode *node = m_lightSentinel.m_next; node != &m_lightSentinel; node = node->m_next)
	{
		light = PeekLight(node);
		if (!light->m_inUse)
		{
			goto found;
		}
	}
	light = new W3DDynamicLight;
	reinterpret_cast<Rva0006F219 *>(this)->rva0006F219((RenderObjClass *)light);
	if (--light->m_refs == 0)
	{
		light->rva0006F94ARelease();
	}
found:
	light->setEnabled(true);
	return light;
}
