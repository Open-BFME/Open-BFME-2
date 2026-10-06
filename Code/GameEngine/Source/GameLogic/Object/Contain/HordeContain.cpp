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
