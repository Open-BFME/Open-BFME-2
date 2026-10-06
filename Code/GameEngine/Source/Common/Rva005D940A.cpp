// cl: /MD
// ?rva005D940A@Rva005D91AB@@QAE_NPAVObject@@@Z @0x005D940A 46B
// Evidence: vslot 6 of 0x00876278 class Rva005D91AB plus AI victim plus picker 0x005D91D2.
class Object;
class AIUpdateInterface { public: Object *getCurrentVictim() const; };
class Rva005EE816 { public: unsigned rva005D91D2(Object *obj); };
class Object {
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface *const *)((const char *)this + 0x258); }
};
class Rva005EE30C { public: virtual ~Rva005EE30C(); };
class Rva005D91AB : public Rva005EE30C {
public:
	bool rva005D940A(Object *other);
};
bool Rva005D91AB::rva005D940A(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (!victim) {
		unsigned v = ((Rva005EE816 *)this)->rva005D91D2(other);
		if (v != 0)
			return true;
	}
	return false;
}
