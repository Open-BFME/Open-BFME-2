// cl: /O1 /MD
// ?rva005D997C@Rva005D96FA@@QAE_NPAVObject@@@Z @0x005D997C 47B
// Evidence: vslot 6 of 0x008762E4 class Rva005D96FA plus AI victim plus picker 0x005D9721.
class Object;
class AIUpdateInterface { public: Object *getCurrentVictim() const; };
class Rva005EE816 { public: unsigned rva005D9721(Object *obj); };
class Object {
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface *const *)((const char *)this + 0x258); }
};
class Rva005EE30C { public: virtual ~Rva005EE30C(); };
class Rva005D96FA : public Rva005EE30C {
public:
	bool rva005D997C(Object *other);
};
bool Rva005D96FA::rva005D997C(Object *other)
{
	Object *victim = other->getAI()->getCurrentVictim();
	if (victim) {
		unsigned v = ((Rva005EE816 *)this)->rva005D9721(other);
		if (v >= 2)
			return true;
	}
	return false;
}
