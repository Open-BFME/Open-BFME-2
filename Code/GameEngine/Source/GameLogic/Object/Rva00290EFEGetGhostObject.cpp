// cl: /O1 /EHs-c-

// Rva00290EFE::getGhostObject, retail 0x00290EFE (189 bytes).
// BFME2 ghost-object predicate for the subobject at Object+0x64: when global
// ghost objects are enabled and the host thing is KINDOF bit-2 flagged it
// scans the thing draw-module vector for a W3DDefaultDraw entry through a
// make-ghost flag cleared plus break on a hit (the donor form; the toolchain
// folds it to direct miss jumps but keeps the late edi save that the flag
// selects). A cleared flag means no ghost (null). On a kept flag it asks the
// for a ghost of the host Object and returns it skipped past its vptr.
// Donor is the BFME1 Rva001CA550::getGhostObject backport (same scan plus the
// same manager tail); BFME2 repairs are the missing override dance plus the
// moved ThingTemplate kindOf (+0x108) and draw-module vector (+0x2F0) plus
// the moved global flag (+0xC69). The getNthName bounds-checked copy-out and
// the 4-byte-string temp teardown resolve through this TU own spellings at
// 0x001F12DF and 0x00036410; strcmp rides the existing _strcmp pin.

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString();
	const char *str() const { return m_data ? m_data + 8 : ""; }

private:
	char *m_data;
};

struct ModuleNugget
{
	char m_bytes[20];
};

class ModuleInfo
{
public:
	BFMERetailAsciiString getNthName(int i) const;
	int getCount() const { return ((char *)m_end - (char *)m_begin) / 20; }

	ModuleNugget *m_begin;
	ModuleNugget *m_end;
	ModuleNugget *m_cap;
};

class ThingTemplate
{
public:
	char m_pad00[0x108];
	unsigned char m_kindOf;  // +0x108
	char m_pad109[0x2F0 - 0x109];
	ModuleInfo m_drawModuleInfo;  // +0x2F0
};

class Object;

class GhostObjectManager
{
public:
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual void vslot10();
	virtual void vslot14();
	virtual void vslot18();
	virtual void *addGhostObject(Object *object);
};

extern GhostObjectManager *TheGhostObjectManager;

class GlobalData
{
public:
	char m_pad[0xC69];
	unsigned char m_ghostObjectsEnabled;  // +0xC69
};

extern GlobalData *TheWritableGlobalData;

extern "C" int __cdecl strcmp(const char *a, const char *b);

class Rva00290EFE
{
public:
	void *getGhostObject();
};

// ?getGhostObject@Rva00290EFE@@QAEPAXXZ @0x00290EFE
void *Rva00290EFE::getGhostObject()
{
	if (TheWritableGlobalData->m_ghostObjectsEnabled == 0)
		return 0;
	ThingTemplate *thing = *(ThingTemplate **)((char *)this - 0x60);
	if ((thing->m_kindOf & 4) != 0) {
		ModuleInfo *drawMod = &thing->m_drawModuleInfo;
		int makeGhostObject = 1;
		for (int i = 0; i < drawMod->getCount(); i++) {
			if (strcmp(drawMod->getNthName(i).str(), "W3DDefaultDraw") == 0) {
				makeGhostObject = 0;
				break;
			}
		}
		if (makeGhostObject != 0) {
			void *ghost = TheGhostObjectManager->addGhostObject((Object *)((char *)this - 0x64));
			return ghost != 0 ? (char *)ghost + 4 : 0;
		}
	}
	return 0;
}
