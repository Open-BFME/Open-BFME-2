// cl: /MD
//
// Constructor of a BFME2NativeNetwork-derived object, sitting after the
// GameEngineDeletingBase-derived destructor pair. It plants the shared base
// through the pinned BFME2NativeNetwork::baseConstruct (0x001B4E63, reached by
// its void-decorated pin), then stores the three arguments at +0x0C/+0x10/+0x14.
// Retail writes the vptr (0x00CE4918) between the first and second member store,
// so the constructor models it as the base's first word rather than leaning on
// compiler vptr emission (the class is non-polymorphic here). Class and member
// names are this image's addresses.

extern char g_Va00CE4918;		// 0x00CE4918, opaque table/data address

class BFME2NativeNetwork
{
public:
	void baseConstruct();

	void *m_bfmeVptr;		// +0x00
	char m_bfmePad[8];		// +0x04, base size 0x0C
};

class Rva00689320 : public BFME2NativeNetwork
{
public:
	Rva00689320(int first, int second, int third);

private:
	int m_0C;
	int m_10;
	int m_14;
};

Rva00689320::Rva00689320(int first, int second, int third)
{
	baseConstruct();
	m_0C = first;
	((void **)this)[0] = &g_Va00CE4918;
	m_10 = second;
	m_14 = third;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_Va00CE4918@@3DA=??_7VideoPlayer@@6B@")
