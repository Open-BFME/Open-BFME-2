// cl: /MD
// ?rva005D8EA7@Rva005D8C25@@QAE_NPAVObject@@@Z @0x005D8EA7 47B
// Evidence: vslot 6 of 0x00876230 class Rva005D8C25 plus AI victim plus picker 0x005D8C4C.
class Object;
class AIUpdateInterface { public: Object *getCurrentVictim() const; };
class Rva005EE816 { public: unsigned rva005D8C4C(Object *obj); };
class Object {
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface *const *)((const char *)this + 0x258); }
};
class Rva005EE30C { public: virtual ~Rva005EE30C(); };
class Rva005D8C25 : public Rva005EE30C {
public:
	virtual bool rva005D8EA7(Object *other);
};
bool Rva005D8C25::rva005D8EA7(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (victim) {
		unsigned v = ((Rva005EE816 *)this)->rva005D8C4C(other);
		if (v >= 2)
			return true;
	}
	return false;
}
