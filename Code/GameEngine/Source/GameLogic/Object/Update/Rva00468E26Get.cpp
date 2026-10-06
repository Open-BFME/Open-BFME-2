// cl: /DNDEBUG /MD /EHsc
//
// ?Rva00468E26Get@@YGPAVModule@@PAVObject@@@Z, retail 0x00468E26 83B.
// Static-guarded BannerCarrierUpdate key plus Object::findModule.
// Evidence: BannerCarrierUpdate string at 0x007F5390, nameToKey row,
// findModule row, guard/key DIR32, callers 0x468E7D 0x469394 0x46D134,
// prev 0x468A3F setter, next 0x469075 setter, scopetable via EH_prolog.

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;
class Object;

Module *__stdcall Rva00468E26Get(Object *obj);

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend Module *__stdcall Rva00468E26Get(Object *obj);
};

Module *__stdcall Rva00468E26Get(Object *obj)
{
	static NameKeyType key = TheNameKeyGenerator->nameToKey("BannerCarrierUpdate");
	return obj->findModule(key);
}
