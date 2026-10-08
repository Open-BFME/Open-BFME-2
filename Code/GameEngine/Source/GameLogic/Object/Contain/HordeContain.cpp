// cl: /DNDEBUG /MD
//
// Target evidence: the existing ModuleFactory callback pin and its registry
// dispatch establish this as a three-argument cdecl callback. At 0x00469B9F it
// forwards those arguments to the sibling callback 0x00467564, then walks the
// four-byte range beginning at argument 1 +0x218 and ending at +0x21C. Each
// element address is passed to the rowed ThingFactory::findTemplate through
// TheThingFactory (VA 0x00DFF000); a non-null result receives arguments 2 and 3
// at 0x0033CF34. The range element type and the final callee's target identity
// remain unresolved.
//
// The `Rva0020AA00Target::notify` spelling below is carried by the pre-existing
// 0x0033CF34 donor pin. It supplies the call ABI and symbol binding only; this
// caller does not establish that class or method's target identity.

class AsciiString;
class ThingTemplate;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

void __cdecl ModuleFactoryHookAt00467564(void *owner, int value, void *context);

class Rva0020AA00Target
{
public:
	void notify(int value, int context);
};

class ModuleFactoryHookRange
{
public:
	unsigned char m_pad000[0x218];
	unsigned char *m_begin;
	unsigned char *m_end;
};

class Rva002CA9CA
{
public:
	void rva002CAC6E(int value, int context);
};

struct ModuleFactoryStringListNode
{
	ModuleFactoryStringListNode *m_next;
	ModuleFactoryStringListNode *m_previous;
};

struct GameLODManagerHookView
{
	unsigned char m_pad000[0x1774];
	int m_1774;
};

class GameLODManager;
extern GameLODManager *TheGameLODManager;

struct AIHookInnerView
{
	unsigned char m_pad000[0xBB];
	unsigned char m_BB;
};

struct AIHookView
{
	unsigned char m_pad000[0x18];
	AIHookInnerView *m_18;
};

class AI;
extern AI *TheAI;

// ?ModuleFactoryHookAt00467564@@YAXPAXH0@Z
// Target evidence: the TransportContain registration at ModuleFactory::init
// (0x00257CB8) supplies this three-argument callback. Its body reads the
// eight-byte list through module-data +0xA4, resolves each stored AsciiString
// through TheThingFactory, and calls the rowed 0x0033CF34 target with the
// callback integer and a byte initialized from the context. A second target
// gate reads GameLODManager +0x1774, the template bytes +0x109/+0x113, and
// TheAI +0x18/+0xBB. If module-data +0x144 is non-null, retail also calls
// 0x002CAC6E with the original integer and context.
//
// Donor evidence: GeneralsMD TransportContainModuleData::InitialPayload
// establishes the payload-name role in this subsystem. The donor stores one
// name/count pair; BFME2's +0xA4 list and eight-byte elements come from target
// bytes and the matched module-data constructor, so the donor layout is not
// copied here. The 0x0033CF34 pin supplies a callable name/ABI only; its target
// identity and the meaning of the byte tests remain unresolved.
void __cdecl ModuleFactoryHookAt00467564(void *owner, int value, void *context)
{
	unsigned char lowDetailPayload = 0;
	GameLODManagerHookView *lod = (GameLODManagerHookView *)TheGameLODManager;
	if (lod && lod->m_1774 < 3)
		lowDetailPayload = 1;

	ModuleFactoryStringListNode *head =
		*(ModuleFactoryStringListNode **)((char *)owner + 0xA4);
	ModuleFactoryStringListNode *entry = head->m_next;
	if (entry != head) {
		do {
			const ThingTemplate *thingTemplate =
				TheThingFactory->findTemplate(*(const AsciiString *)(entry + 1));
			if (thingTemplate) {
				unsigned char notifyContext = *(unsigned char *)context;
				const unsigned char *templateBytes =
					(const unsigned char *)thingTemplate;
				AIHookView *ai = (AIHookView *)TheAI;
				if (lowDetailPayload && !(templateBytes[0x113] & 4)
					&& !(templateBytes[0x109] & 4)
					&& ai->m_18->m_BB)
					notifyContext = 1;
				((Rva0020AA00Target *)thingTemplate)->notify(
					value, (int)&notifyContext);
			}
			entry = entry->m_next;
		} while (entry != *(ModuleFactoryStringListNode **)((char *)owner + 0xA4));
	}

	Rva002CA9CA *extra = *(Rva002CA9CA **)((char *)owner + 0x144);
	if (extra)
		extra->rva002CAC6E(value, (int)context);
}

void __cdecl ModuleFactoryHookAt00469B9F(void *owner, int value, void *context)
{
	ModuleFactoryHookAt00467564(owner, value, context);

	ModuleFactoryHookRange *range = (ModuleFactoryHookRange *)owner;
	unsigned char *element = range->m_begin;
	while (element != range->m_end) {
		const ThingTemplate *thingTemplate =
			TheThingFactory->findTemplate(*(const AsciiString *)element);
		if (thingTemplate)
			((Rva0020AA00Target *)thingTemplate)->notify(value, (int)context);
		element += 4;
	}
}
