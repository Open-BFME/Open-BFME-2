// cl: /O1 /MD /arch:SSE
// ?rva005D9CE0@Rva005D9CD5@@QAE_NPAVObject@@@Z @0x005D9CE0 76B
// Evidence: gap between Rva005D9CD5 dtor 0x005D9CD5 and deleting dtor 0x005D9D2C plus vslot 6 of 0x00876424.
extern float g_00C76420;
class Object;
class AIUpdateInterface { public: Object *getCurrentVictim() const; };
class Rva005EE816 { public: unsigned rva005EE3B0(Object *obj, bool flag); };
class Rva005D9Float {
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual float getFloat();
};
class Object {
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface *const *)((const char *)this + 0x258); }
	Rva005D9Float *getBody() const { return *(Rva005D9Float *const *)((const char *)this + 0x254); }
};
class Rva005EE30C { public: virtual ~Rva005EE30C(); };
class Rva005D9CD5 : public Rva005EE30C {
public:
	bool rva005D9CE0(Object *other);
};
bool Rva005D9CD5::rva005D9CE0(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (victim) {
		unsigned v = ((Rva005EE816 *)this)->rva005EE3B0(other, false);
		if (v > 20)
			return true;
		if (v != 0) {
			if (g_00C76420 > other->getBody()->getFloat())
				return true;
		}
	}
	return false;
}
