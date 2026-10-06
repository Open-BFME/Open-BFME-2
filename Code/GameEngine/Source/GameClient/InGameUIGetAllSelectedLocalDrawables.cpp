// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?getAllSelectedLocalDrawables@InGameUI@@UAEPBV?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@XZ @0x002A3908 84B: InGameUI virtual slot 64 clears m_selectedLocalDrawables then collects selected drawables whose Object isLocallyControlled. ZH donor InGameUI.cpp getAllSelectedLocalDrawables via BFME1 shape; retail vtables at RVA 0x007C7AB0 and 0x007FD438 both carry this slot; neighbours getMoney and dword getters prove table.
#include <list>

class Drawable;
typedef _STL::list<Drawable *> BfmeDrawableList;

class Rva00239380Holder
{
public:
	void rva00239380();
};

class Object
{
public:
	bool isLocallyControlled() const;
};

class Drawable
{
public:
	void *m_vtable;
	unsigned char m_unmodelled004[0xF8];
	Object *m_object; // +0xFC
};

class InGameUI
{
public:
	virtual const BfmeDrawableList *getAllSelectedLocalDrawables();

private:
	unsigned char m_unmodelled004[0x1C]; // +0x04..0x1F
	BfmeDrawableList *m_selectedDrawables; // +0x20 pointer to selected list sentinel
	BfmeDrawableList m_selectedLocalDrawables; // +0x24
};

const BfmeDrawableList *InGameUI::getAllSelectedLocalDrawables()
{
	((Rva00239380Holder *)&m_selectedLocalDrawables)->rva00239380();
	for (void *node = *(void **)(void *)m_selectedDrawables; node != (void *)m_selectedDrawables; node = *(void **)node)
	{
		Drawable *draw = *(Drawable **)((char *)node + 8);
		if (draw && draw->m_object && draw->m_object->isLocallyControlled())
			m_selectedLocalDrawables.push_back(draw);
	}
	return &m_selectedLocalDrawables;
}
