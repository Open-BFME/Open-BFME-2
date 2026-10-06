// cl: /MD
// ?rva005D916A@Rva005D8EE8@@QAE_NPAVObject@@@Z @0x005D916A 47B
// Evidence: vslot 6 of 0x00876254 class Rva005D8EE8 plus AI victim plus picker 0x005D8F0F.
class Object;
class AIUpdateInterface { public: Object *getCurrentVictim() const; };
class Rva005EE816 { public: unsigned rva005D8F0F(Object *obj); };
class Object {
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface *const *)((const char *)this + 0x258); }
};
class Rva005EE30C { public: virtual ~Rva005EE30C(); };
class Rva005D8EE8 : public Rva005EE30C {
public:
	bool rva005D916A(Object *other);
};
bool Rva005D8EE8::rva005D916A(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (victim) {
		unsigned v = ((Rva005EE816 *)this)->rva005D8F0F(other);
		if (v >= 2)
			return true;
	}
	return false;
}
