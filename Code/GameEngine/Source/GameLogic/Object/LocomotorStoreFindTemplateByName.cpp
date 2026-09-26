// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?findLocomotorTemplate@LocomotorStore@@QAEPAVLocomotorTemplate@@ABVAsciiString@@@Z
// retail 0x001E7010 (30 bytes).
//
// BFME2-new AsciiString overload: converts the name through
// TheNameKeyGenerator and forwards the key to the rowed int overload
// (0x001E6FEA) on TheLocomotorStore. Both call sites (the AIUpdate
// LocomotorSet parser near 0x001EA2CF and the vector refill near
// 0x0033B9E0) load TheLocomotorStore into ecx, so this is a
// LocomotorStore member; the body addresses the singletons through the
// globals, matching retail's two mov ecx,[...] loads. Zero Hour has only
// the NameKeyType overloads (Generals Locomotor.h).

class AsciiString;

class LocomotorTemplate;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &str);
};

class LocomotorStore
{
public:
	LocomotorTemplate *findLocomotorTemplate(int namekey);
	LocomotorTemplate *findLocomotorTemplate(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern LocomotorStore *TheLocomotorStore;

LocomotorTemplate *LocomotorStore::findLocomotorTemplate(const AsciiString &name)
{
	return TheLocomotorStore->findLocomotorTemplate(TheNameKeyGenerator->nameToKey(name));
}
