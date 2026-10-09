// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 0x0006F94A..0x0006F9D6, 140B. RTS3DScene's dynamic-light pool: the first
// light on the +0x118 list whose in-use byte (+0x144) is clear is reused,
// otherwise a new 0x174-byte W3DDynamicLight is built, registered with the scene
// (0x6F219) and released; either way it is enabled and returned. ZH
// RTS3DScene::getADynamicLight is the semantic lead; the list node layout
// (next +4, value +0xC at the second base, minus 8 to the light) is measured.

class RenderObjClass;

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
    char *p = reinterpret_cast<char *>(node->m_value);
    return reinterpret_cast<W3DDynamicLight *>(p ? p - 8 : 0);
}
class Rva0006F219
{
public:
	bool rva0006F219(RenderObjClass *obj);
};

class RTS3DScene
{
public:
	W3DDynamicLight *rva0006F94A();

private:
	char m_fields[0x118];
	Rva0006F94ANode m_lightSentinel;
};

// ?rva0006F94A@RTS3DScene@@QAEPAVW3DDynamicLight@@XZ @0x0006F94A
W3DDynamicLight *RTS3DScene::rva0006F94A()
{
	for (Rva0006F94ANode *node = m_lightSentinel.m_next; node != &m_lightSentinel; node = node->m_next)
	{
		W3DDynamicLight *light = PeekLight(node);
		if (!light->m_inUse)
		{
			light->setEnabled(true);
			return light;
		}
	}
	W3DDynamicLight *light = new W3DDynamicLight;
	reinterpret_cast<Rva0006F219 *>(this)->rva0006F219((RenderObjClass *)light);
	if (--light->m_refs == 0)
		light->rva0006F94ARelease();
	light->setEnabled(true);
	return light;
}
