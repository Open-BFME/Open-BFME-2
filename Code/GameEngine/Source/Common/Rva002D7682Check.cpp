// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc

class Rva00270260
{
public:
	bool rva00270260();
};

class Drawable : public Rva00270260
{
public:
	char m_padToType[0x164];
	int m_type;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

// ?Rva002D7682Check@@YI_NPAX@Z @0x002D7682 36B
// Target evidence: direct call from FUN_00450125 and calls rowed
// Thing::getDrawable and the address-derived Drawable predicate. The first
// argument view and field meaning remain structural inferences.
unsigned char __fastcall Rva002D7682Check(void *object)
{
	Thing *thing = *(Thing **)((char *)object + 4);
	Drawable *drawable = thing->getDrawable();
	if (drawable == 0 || drawable->m_type == 5 || drawable->rva00270260())
		return 1;
	return 0;
}
