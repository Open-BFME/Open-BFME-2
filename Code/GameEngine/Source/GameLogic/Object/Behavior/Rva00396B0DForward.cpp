// cl: /Ireference/shims/bfme2_ascii /Oy- /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00396B0D@Rva00396B0D@@QAEHXZ @0x00396B0D 24B forward of the
// controlling player of the +8 Object to the +4 lookup's pinned 0x00396A5C
// entry (NameKey map find, recovery blocked). Evidence: m08 feeds the rowed
// Object::getControllingPlayer at 0x0028AFA9, its result is pushed for the
// 0x00396A5C REL32 read at 0x00396B1E, m04 is reloaded into ecx; flags and
// Object/Player decls follow neighbouring Rva00396B25Receiver.cpp.
class Player;

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

class Rva00396A5C
{
public:
	int rva00396A5C(Player *player);
};

class Rva00396B0D
{
public:
	int rva00396B0D(void);

private:
	char m_pad00[4];
	Rva00396A5C *m_lookup04;
	Object *m_object08;
};

int Rva00396B0D::rva00396B0D(void)
{
	Object *object = m_object08;
	Rva00396A5C *lookup = m_lookup04;
	return lookup->rva00396A5C(object->getControllingPlayer());
}
