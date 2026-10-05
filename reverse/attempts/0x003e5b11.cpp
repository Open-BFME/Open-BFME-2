// ?Rva003E5B11Check@@YG_NPAVParameter@@0@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc
// ?Rva003E5B11Check@@YG_NPAVParameter@@0@Z
// retail 0x003E5B11 243B leaf free stdcall bool of 2x Parameter ret 8. Evidence:
// rowed ScriptEngine::getUnitNamed via g_Va009FE16C plus rowed rva00357B82
// plus rowed PlayerList::getPlayerFromMask via ThePlayerList plus rowed
// Object::getControllingPlayer twice plus static CastleBehavior::rva0003955DA
// plus rowed Object::findModule plus rowed Rva003971BF::rva003971BF with 0
// then FoundationAIUpdate fallback via static NameKeyType from
// TheNameKeyGenerator->nameToKey("FoundationAIUpdate") plus Object+4 flag
// at +0x115 plus Foundation module+0x20 virtual slot 0xc returning inverted bool;
// globals g_Va009FE16C ThePlayerList TheNameKeyGenerator; siblings /O1 /EHsc.
class Parameter
{
};

class Player
{
};

class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
};
extern PlayerList *ThePlayerList;

class Object;

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
	int rva00357B82(Parameter *p);
};
extern ScriptEngine *g_Va009FE16C;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

struct Arg3971BF
{
};

class Rva003971BF
{
public:
	bool rva003971BF(Arg3971BF *arg);
};

struct ObjPlus4
{
	char m_pad[0x115];
	unsigned char m_115;
};

class FoundationInner
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual bool v03();
};

class FoundationModule
{
public:
	char m_pad[0x20];
	FoundationInner m_20;
};

class Object
{
	friend bool __stdcall Rva003E5B11Check(Parameter *, Parameter *);
public:
	Player *getControllingPlayer() const;
	char m_pad00[4];
	ObjPlus4 *m_04;
protected:
	Module *findModule(NameKeyType key) const;
};

bool __stdcall Rva003E5B11Check(Parameter *a, Parameter *b)
{
	Object *obj = g_Va009FE16C->getUnitNamed(b);
	if (!obj)
		return false;
	int mask = g_Va009FE16C->rva00357B82(a);
	if (!mask)
		return false;
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player != 0) {
		Player *ctrl1 = obj->getControllingPlayer();
		if (ctrl1 == player) {
			Player *ctrl2 = obj->getControllingPlayer();
			if (player == ctrl2) {
				Module *mod = obj->findModule(CastleBehavior::rva0003955DA());
				if (mod != 0) {
					unsigned char r = ((Rva003971BF *)mod)->rva003971BF(0);
					if (r)
						return true;
					else
						return false;
				}
				if ((obj->m_04->m_115 & 1) != 0) {
					static NameKeyType foundationKey =
						TheNameKeyGenerator->nameToKey("FoundationAIUpdate");
					FoundationModule *fnd = (FoundationModule *)obj->findModule(foundationKey);
					if (fnd != 0) {
						unsigned char v = fnd->m_20.v03();
						if (!v)
							return true;
						else
							return false;
					}
				}
			}
		}
	}
	return false;
}
