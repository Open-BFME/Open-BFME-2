// ?removeAllContained@Rva0047CD98@@UAEX_N@Z
// partial score=0.82 date=2026-10-08
// ?removeAllContained@Rva0047CD98@@UAEX_N@Z
// partial score=0.35 date=2026-10-06
// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// ?removeAllContained@Rva0047CD98@@UAEX_N@Z @ 0x0047CD98 (54B)
// Retail walks the sentinel at this+0x108, calls the OpenContain slot at vtable
// +0xA4 for each non-null item, then calls OpenContain::removeAllContained.
// The vtable word at +0xA4 is 0x00463509, immediately before the matched base
// body at 0x004635C0; the Zero Hour OpenContain declaration orders
// removeFromContain immediately before removeAllContained.

typedef bool Bool;
class Object;

struct OpenContain
{
	virtual void removeAllContained(Bool exposeStealthUnits) = 0;
};

struct Rva0047CD98 : OpenContain
{
	virtual void removeAllContained(Bool exposeStealthUnits) = 0;
};

namespace
{
struct RetailContainVtablePrefix
{
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
};

struct RetailContainVtableView : RetailContainVtablePrefix
{
	virtual void removeFromContain(Object *obj, Bool exposeStealthUnits) = 0;
};

struct RetailContainNode
{
	RetailContainNode *next;
	RetailContainNode *prev;
	Object *object;
};
}

void Rva0047CD98::removeAllContained(Bool exposeStealthUnits)
{
    for (;;)
    {
        RetailContainNode *head = *(RetailContainNode *volatile *)((char *)this + 0x108);
        RetailContainNode *node = head->next;
        if (node == head)
        {
            OpenContain::removeAllContained(exposeStealthUnits);
            return;
        }
        Object *obj = node->object;
        if (obj) ((RetailContainVtableView *)this)->removeFromContain(obj, exposeStealthUnits);
    }
}
