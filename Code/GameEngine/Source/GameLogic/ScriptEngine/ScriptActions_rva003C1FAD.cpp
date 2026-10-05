// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
// ?Rva003C1FADDestroy@@YAXXZ @0x003C1FAD 49B
// Destroy flagged GameLogic objects via rowed getFirstObject 0x0023CAD2
// and destroyObject 0x00242C09. Evidence: caller 0x003CDA80;
// neighbours 0x003C0FEA 0x003C10D8; global TheGameLogic.
class Object {
public:
	char m_pad8c[0x8c];
	Object *m_next;
	char m_pad9[0x1c8 - 0x8c - 4];
	unsigned char m_flags1c8;
};

class GameLogic {
public:
	Object *getFirstObject();
	void destroyObject(Object *o);
};

extern GameLogic *TheGameLogic;

void __cdecl Rva003C1FADDestroy(void)
{
	Object *o = TheGameLogic->getFirstObject();
	while (o != 0) {
		if ((o->m_flags1c8 & 0x20) != 0)
			TheGameLogic->destroyObject(o);
		o = o->m_next;
	}
}
