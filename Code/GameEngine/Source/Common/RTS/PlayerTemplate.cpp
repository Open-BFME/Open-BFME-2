// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <set>
#include "ascii_string.h"
#include "unicode_string.h"
class INI;
struct BfmeObject476 { virtual ~BfmeObject476(); unsigned char opaque[472]; BfmeObject476 &operator=(const BfmeObject476 &); };
extern template void _STL::vector<BfmeObject476>::push_back(const BfmeObject476 &);
//
// Reference guide: BFME1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe
// game/GameEngine/Source/Common/RTS/PlayerTemplate.cpp parser and the same
// Zero Hour function supply the name/lookup/parse/new-template flow. Retail
// 1FEFEC..1FF218 adds override modes2/5, reload messaging and side-index
// filtering. The +150/+151 flags, +24 store index and GlobalData+9D4
// condition are kept neutral; their application meanings are unproven.
// The rowed 476-byte vector and assignment provider retain their neutral
// BfmeObject476 ABI rather than asserting names for their internal fields.
//
// PlayerTemplate.cpp: the PlayerTemplateStore lookups retail links from this TU
// (tu_map approved), folded from two split units with these exact flags. One
// Overridable/PlayerTemplate view carries both bodies' offsets: next override
// at +0x04, name key at +0x10, vector element stride 0x1DC, vector first/last
// at +0x0C/+0x10 of the store. The override hop uses the pinned
// getFinalOverride at 0x001E35DF.

enum NameKeyType
{
	NAMEKEY_INVALID = -1,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	virtual ~Overridable();
	Overridable *m_nextOverride;
	bool m_isOverride;
    char pad09[3];
	int m_extra0C;
};

class PlayerTemplate : public Overridable
{
public:
	PlayerTemplate();
    virtual ~PlayerTemplate();
    NameKeyType m_nameKey; // +0x10
    char display14[4];
    AsciiString side;
    char before150[0x150-0x1c];
    bool flag150,flag151;
    char tail152[0x1dc-0x152];
};

class PlayerTemplateVector
{
public:
	unsigned size() const { return static_cast<unsigned>(m_last - m_first); }
	const PlayerTemplate &operator[](int index) const { return m_first[index]; }

	PlayerTemplate *m_first;
	PlayerTemplate *m_last;
    PlayerTemplate *m_capacity;
    void push_back(const PlayerTemplate &pt) { reinterpret_cast<_STL::vector<BfmeObject476> *>(this)->push_back(reinterpret_cast<const BfmeObject476 &>(pt)); }
};

class PlayerTemplateStore
{
public:
	static void parsePlayerTemplateDefinition(INI *);
    const PlayerTemplate *findPlayerTemplate(NameKeyType namekey) const;
	const PlayerTemplate *getNthPlayerTemplate(int index) const;

private:
	public:
    char m_pad00[4];
    bool showReload;
    char m_pad05[7];
	PlayerTemplateVector m_playerTemplates;
    _STL::set<int> playableIndices;
    int index24;
};

// ?findPlayerTemplate@PlayerTemplateStore@@QBEPBVPlayerTemplate@@W4NameKeyType@@@Z @0x001FD31B 45B
// BFME1 PlayerTemplate.cpp findPlayerTemplate with BFME2 Overridable final-override lookup.
// Retail vector first/last at +0x0C/+0x10 stride 0x1DC nameKey at +0x10 (PlayerTemplateGetName
// proves key at +0x10 and GetDisplayName proves display name at +0x14). Callers pass a
// NameKeyType e.g. call at 0x002B5D66 after nameToKey at 0x0009FA65.
const PlayerTemplate *PlayerTemplateStore::findPlayerTemplate(NameKeyType namekey) const
{
	for (const PlayerTemplate *it = m_playerTemplates.m_first; it != m_playerTemplates.m_last; ++it)
	{
		if (it->m_nameKey == namekey)
		{
			if (it->m_nextOverride)
				return static_cast<const PlayerTemplate *>(it->m_nextOverride->getFinalOverride());
			return it;
		}
	}
	return 0;
}

// BFME1 PlayerTemplateStore::getNthPlayerTemplate, with the retail
// 0x1DC-byte vector element and its Overridable final-override lookup.
const PlayerTemplate *PlayerTemplateStore::getNthPlayerTemplate(int index) const
{
	if (index >= 0 && static_cast<unsigned>(index) < m_playerTemplates.size()) {
		const PlayerTemplate *playerTemplate = &m_playerTemplates[index];
		const PlayerTemplate *result;
		if (playerTemplate->m_nextOverride)
			result = static_cast<const PlayerTemplate *>(playerTemplate->m_nextOverride->getFinalOverride());
		else
			result = playerTemplate;
		return result;
	}
	return 0;
}

class INI { public: const char *getNextToken(const char *); char prefix[8]; int mode; };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
extern PlayerTemplateStore *ThePlayerTemplateStore;
extern unsigned char g_00E01EA8;
class Rva001FE70F { public: void rva001FE70F(INI *); };
class GlobalData { public: char prefix[0x9d4]; int restriction; };
extern GlobalData *TheWritableGlobalData;
class InGameUI { public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void ReloadMessage(UnicodeString,...);
};
extern InGameUI *TheInGameUI;
// WB0x00A78AA0 names parsePlayerTemplateDefinition and PlayerTemplate.cpp;
// retail proves the full556-byte static parser and all lifecycle call sites.
void PlayerTemplateStore::parsePlayerTemplateDefinition(INI *ini)
{
    const char *name=ini->getNextToken(0);
    NameKeyType key=TheNameKeyGenerator->nameToKey(name);
    PlayerTemplate *pt=const_cast<PlayerTemplate *>(ThePlayerTemplateStore->findPlayerTemplate(key));
    if(pt) {
        if(ini->mode==2) {
            PlayerTemplate *overridePt=new PlayerTemplate;
            g_00E01EA8=1;
            reinterpret_cast<BfmeObject476 *>(overridePt)->operator=(reinterpret_cast<const BfmeObject476 &>(*pt));
            g_00E01EA8=0;
            reinterpret_cast<Rva001FE70F *>(overridePt)->rva001FE70F(ini);
            overridePt->m_nameKey=key;
            overridePt->m_isOverride=true;
            pt->m_nextOverride=overridePt;
        } else if(ini->mode==5) {
            reinterpret_cast<Rva001FE70F *>(pt)->rva001FE70F(ini);
            pt->m_nameKey=key;
        }
        if(ThePlayerTemplateStore->showReload)
            TheInGameUI->ReloadMessage(L"The PlayerTemplate, '%S' was reloaded.",name);
    } else {
        PlayerTemplate npt;
        reinterpret_cast<Rva001FE70F *>(&npt)->rva001FE70F(ini);
        npt.m_nameKey=key;
        int index=ThePlayerTemplateStore->m_playerTemplates.size();
        g_00E01EA8=1;
        ThePlayerTemplateStore->m_playerTemplates.push_back(npt);
        g_00E01EA8=0;
        if(npt.flag150) { ThePlayerTemplateStore->index24=index; index=-1; }
        else if(npt.flag151) {
            for(_STL::set<int>::iterator it=ThePlayerTemplateStore->playableIndices.begin();it!=ThePlayerTemplateStore->playableIndices.end();++it) {
                const PlayerTemplate *other=ThePlayerTemplateStore->getNthPlayerTemplate(*it);
                if(other && other->side == npt.side) { index=-1; break; }
            }
        } else index=-1;
        if(TheWritableGlobalData->restriction>0 && TheWritableGlobalData->restriction<=2) {
            if(npt.side.compare("Dwarves") != 0 && npt.side.compare("Wild") != 0) index=-1;
        }
        if(index!=-1) ThePlayerTemplateStore->playableIndices.insert(index);
    }
}
