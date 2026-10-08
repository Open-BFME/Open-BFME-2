// cl: /MD
// ABI repair: retail 29C823 and named WB DBA3A0 dispatch through TheActionManager.
// The unused manager this is still part of the calling convention. Existing
// return representations are preserved. No additional name or pin is introduced.
// ?Rva0041BB87IsRelated@ActionManager@@QAEEPAVObject@@0H@Z @0x0041BB87 65B
// Evidence: caller 0x0029CB07; rowed rva002931F5 0x002931F5 and rva0028C1A9 0x0028C1A9; virtual slot +8 on rva0028C1A9 result.

class Object;

class Object
{
public:
	Object *rva002931F5(bool checkProducer);
	void *rva0028C1A9() const;
};

struct Rva0041BB87Iface
{
	virtual void d00();
	virtual void d01();
	virtual unsigned char Check(Object *obj);
};

class ActionManager { public: unsigned char Rva0041BB87IsRelated(Object*, Object*, int); };

unsigned char ActionManager::Rva0041BB87IsRelated(Object *a, Object *b, int unused)
{
	if (a == 0 || b == 0)
		return false;
	Object *related = b->rva002931F5(false);
	if (a == related)
		return false;
	void *p = a->rva0028C1A9();
	if (p == 0)
		return false;
	Rva0041BB87Iface *iface = (Rva0041BB87Iface *)p;
	return iface->Check(b) != 0;
}
