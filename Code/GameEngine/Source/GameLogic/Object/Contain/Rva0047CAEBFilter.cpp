// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0047CAEB, 84 bytes, thiscall (ret 8). A null object argument takes
// the base SlaughterHordeContain path. Otherwise it asks the controlling player
// of the object at this-0x18, and when the filter at this-0x1C +0x18C accepts
// the argument it copy-constructs the record at +0x1A4 into the out object.
// The base path tail-calls the base body with (out, obj). Returns out.
class Player;
class Object;
class BfmeObject872Header;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

class BfmeObject872Header
{
public:
	BfmeObject872Header(const BfmeObject872Header &src);
};

inline void *operator new(unsigned int, void *place)
{
	return place;
}

class SlaughterHordeContain
{
public:
	virtual BfmeObject872Header *rva00462CE1(BfmeObject872Header *out, int flag);
};

class Rva0047CAEBOwner : public SlaughterHordeContain
{
public:
	BfmeObject872Header *rva0047CAEB(BfmeObject872Header *out, Object *obj);
};

BfmeObject872Header *Rva0047CAEBOwner::rva0047CAEB(BfmeObject872Header *out, Object *obj)
{
	Object *a = *(Object **)((char *)this - 0x18);
	if (obj)
	{
		char *b = *(char **)((char *)this - 0x1C);
		Player *p = a->getControllingPlayer();
		Rva2225E0Filter *f = (Rva2225E0Filter *)(b + 0x18C);
		if (f->accepts(obj, p))
		{
			__assume(out != 0);
			new (out) BfmeObject872Header(*(BfmeObject872Header *)(*(char **)((char *)this - 0x1C) + 0x1A4));
			return out;
		}
	}
	SlaughterHordeContain::rva00462CE1(out, (int)obj);
	return out;
}
