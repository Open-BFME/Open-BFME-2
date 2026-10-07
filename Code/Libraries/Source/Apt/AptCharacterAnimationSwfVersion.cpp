// cl: /O2 /Ob1 /arch:SSE /MD /DNDEBUG /EHs-c-
// APT0.19.03 May2006 release PDB/MAP supplies getSwfVersion and pFile/GetAptData.
// Target caller6D17F0 passes this at6D1982 and sends the result to6CD210, which
// stores the version globalE17724 (read by6CD220). Target full26-byte body at
// 6E3E00 matches the release donor including ':' and ASCII-digit/default6 logic.
// Its branch6E3E0A ->6E3E14 proves the return6 tail is not a separate function;
// the old6-byte claim was retracted before landing this complete body.
// Target independently proves pFile+34 and data+10; the final donor uses data+C
// and must NOT supply that field offset. Release PDB AptFile agrees with data+10.
// These are partial views; unused file/animation fields and ownership are opaque.
class AptFile {
    unsigned char unaccessed[16];
    void *mAptData;
public:
    void *GetAptData() { return mAptData; }
};
template<class T> class AptSharedPtr {
    T *pointer;
public:
    T *operator->() const { return pointer; }
};
struct AptCharacterAnimationInst {
    unsigned char unaccessed[52];
    AptSharedPtr<AptFile> pFile;
    int getSwfVersion();
};
int AptCharacterAnimationInst::getSwfVersion()
{
    const char *data=(const char *)pFile->GetAptData();
    if (data[8]==':') return data[9]-'0';
    return 6;
}

// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f provides the named-slot
// lookup in game/GameEngine/Source/Common/SmallGaps/Rva008A1050FindNamedSlot.cpp.
// BFME2 6E32E0..6E340F is the full 303-byte body, including both RET4 exits.
// Target proves filename+8, table+14, count+30, entries+34, values+18 and
// character-count+14. Assert literals independently name the export lookup.
// Receiver/record class names, pointer ownership and unused fields remain
// opaque; int slots preserve the target's 32-bit pointer/index representation.
// __debugbreak intrinsic folds the flag into a memory comparison. The native
// assert blocks load/test the flag around stack cleanup; int3 inline assembly
// retains that proven compiler shape without reproducing the function body.
extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*, const char*, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __cdecl Rva006CC110Log(int,const char*,...);
class EAStringC {
    void* data;
public:
    const char* rva00620090() const;
};
struct Rva006E32E0Entry { const char* name; int slot; };
struct Rva006E32E0Table {
    char pad00[0x14];
    int characterCount;
    int* values;
    char pad1C[0x14];
    int count;
    Rva006E32E0Entry* entries;
};
struct Rva006E32E0Owner {
    char pad00[8];
    EAStringC filename;
    char pad0C[8];
    Rva006E32E0Table* table;
    int findNamedSlot(const char* name);
};
#define APT_ASSERT(test,line) do { if (!(test)) { \
    g_bfmeAptAssertAtE17734(#test,"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptLoad.h",line); \
    if(g_bfmeAptBreakOnAssertAtDDC01C) __asm { int 3 }; \
} } while(0)
int Rva006E32E0Owner::findNamedSlot(const char* name)
{
    for (int i=0; i<table->count; ++i) {
        if(strcmp(name,table->entries[i].name)==0) {
            if (!(table->entries[i].slot>=0 && table->entries[i].slot<table->characterCount)) {
                g_bfmeAptAssertAtE17734("mCharacter->animation.aExports[i].nID >= 0 && mCharacter->animation.aExports[i].nID < mCharacter->animation.nCharacters","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptLoad.h",0x8F);
                if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm { int 3 } }
            }
            int pRet=table->values[table->entries[i].slot];
            APT_ASSERT(pRet,0x91);
            return pRet;
        }
    }
    Rva006CC110Log(4,"Couldn't find export named '%s' in '%s'\n",name,filename.rva00620090());
    g_bfmeAptAssertAtE17734("NOT_REACHED","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptLoad.h",0x96);
    if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm { int 3 } }
    return 0;
}

// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f supplies the fixup loop in
// game/GameEngine/Source/Common/SmallGaps/Rva008A12C0Fixups.cpp, including its
// case-4 fallthrough to four optional link fields. Target adds the import-slot
// assertion and calls the verified 6E32E0 lookup. All accessed offsets, record
// strides and case destinations are independently checked against retail.
// Native executable range is 6E3E20..6E3FCD (429 bytes), RET8 at6E3FCA;
// Ghidra/queue extent426 omits RET8. The three alignment bytes and six-entry
// jump table at6E3FD0 extend the owned compiled span to456 bytes.
// Apt.cpp initializer6CF6CF checks VA E17794 and names gAptFuncs.pfnBindTexture
// in its assert at6CF6E2. Host initializer ABA2F writes callback VA4AB469 at
// ABB17. Retail data is zero before installation; this TU provides that slot.
// Pointer/index representation and receiver identities remain opaque.
struct Rva006E3E20Entry {
    void *m_pad00;
    const char *m_name;
    int m_slot;
    Rva006E32E0Owner *m_owner;
};

struct Rva006E3E20RecordEntry {
    int m_pad00;
    int m_slot;
    char m_pad08[0x3c];
};

struct Rva006E3E20Link {
    int m_slot00;
    int m_slot04;
    int m_slot08;
    int m_slot0c;
};

struct Rva006E3E20Record {
    int m_kind;
    int m_pad04;
    int m_slot08;
    int m_count0c;
    int *m_slots10;
    char m_pad14[0x18];
    int m_count2c;
    Rva006E3E20RecordEntry *m_entries30;
    char m_pad34[8];
    Rva006E3E20Link *m_link3c;
};

typedef void (__cdecl *Rva006E3E20Callback)(void *, int, void *);
// Runtime-installed gAptFuncs.pfnBindTexture slot; zero-filled retail data.
Rva006E3E20Callback g_AptBindTexture=0;

struct Rva006E3E20Object {
    char m_pad00[0x0c];
    int m_recordCount;
    int *m_slots;
    char m_pad14[0x0c];
    int m_namedCount;
    Rva006E3E20Entry *m_namedEntries;

    void rva006E3E20(void *, void *);
    __forceinline void rva006E3E20Slot(int &slot) { slot=m_slots[slot]; }
};

void Rva006E3E20Object::rva006E3E20(void *unused, void *argument)
{
    for (int i = 0; i < m_namedCount; ++i) {
        if(m_slots[m_namedEntries[i].m_slot]!=0) {
            g_bfmeAptAssertAtE17734("apCharacters[aImports[i].nID] == NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp",0x20D);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm { int 3 } }
        }
        Rva006E32E0Owner *owner = m_namedEntries[i].m_owner;
        int value = owner->findNamedSlot(m_namedEntries[i].m_name);
        m_slots[m_namedEntries[i].m_slot] = value;
    }

    for (int i = 0; i < m_recordCount; ++i) {
        Rva006E3E20Record *record =
            ((Rva006E3E20Record **)m_slots)[i];
        if (record == 0)
            continue;

        switch (record->m_kind) {
        case 7:
            g_AptBindTexture(
                argument, i, (void *)record->m_slot08);
            break;

        case 8:
            ((Rva006E3E20Record **)m_slots)[i]->m_slot08 =
                m_slots[((Rva006E3E20Record **)m_slots)[i]->m_slot08];
            ((Rva006E3E20Record **)m_slots)[i]->m_count0c =
                m_slots[((Rva006E3E20Record **)m_slots)[i]->m_count0c];
            break;

        case 4:
            for (int j = 0;
                 j < ((Rva006E3E20Record **)m_slots)[i]->m_count2c; ++j) {
                Rva006E3E20RecordEntry *entry =
                    ((Rva006E3E20Record **)m_slots)[i]->m_entries30 + j;
                rva006E3E20Slot(entry->m_slot);
            }
            if (((Rva006E3E20Record **)m_slots)[i]->m_link3c != 0) {
                Rva006E3E20Link *link =
                    ((Rva006E3E20Record **)m_slots)[i]->m_link3c;
                if (link->m_slot04 != 0)
                    link->m_slot04 = m_slots[link->m_slot04];
                if (link->m_slot0c != 0)
                    link->m_slot0c = m_slots[link->m_slot0c];
                if (link->m_slot00 != 0)
                    link->m_slot00 = m_slots[link->m_slot00];
                if (link->m_slot08 != 0)
                    link->m_slot08 = m_slots[link->m_slot08];
            }
            break;

        case 5:
        case 6:
            break;

        case 3:
            for (int j = 0;
                 j < ((Rva006E3E20Record **)m_slots)[i]->m_count0c; ++j) {
                int *slots = ((Rva006E3E20Record **)m_slots)[i]->m_slots10;
                rva006E3E20Slot(slots[j]);
            }
            break;
        }
    }

    (void)unused;
}
