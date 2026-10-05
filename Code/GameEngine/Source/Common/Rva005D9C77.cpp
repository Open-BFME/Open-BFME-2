// cl: /O1 /MD
// ?rva005D9C77@Rva005D9C6C@@QAE_NPAVObject@@@Z @0x005D9C77 48B
// Evidence: gap between Rva005D9C6C dtor 0x005D9C6C and deleting dtor 0x005D9CA7 plus vslot 6 of 0x008763FC.
class Object;
class AIUpdateInterface { public: Object *getCurrentVictim() const; };
class Rva005EE816 { public: unsigned rva005EE3B0(Object *obj, bool flag); };
class Object {
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface *const *)((const char *)this + 0x258); }
};
class Rva005EE30C { public: virtual ~Rva005EE30C(); };
class Rva005D9C6C : public Rva005EE30C {
public:
	bool rva005D9C77(Object *other);
};
bool Rva005D9C6C::rva005D9C77(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (!victim) {
		unsigned v = ((Rva005EE816 *)this)->rva005EE3B0(other, true);
		if (v != 0)
			return true;
	}
	return false;
}
