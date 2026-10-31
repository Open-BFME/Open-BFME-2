// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva001091A8@Rva00108660ResourceManager@@QAEXPAX@Z, retail 0x001091A8 (142 bytes, RET 4;
// caller 0x00109DA6): queue one projected shadow. A 0x0C00-type shadow whose fade has not
// expired (+0x3C against the client frame, slot 31) restarts it through 0x00330A37 from its
// stored timings (+0x40/+0x48/+0x50/+0x54, the +0x4C elapsed part subtracted unless -1);
// otherwise a 0x3C61-type shadow goes into the +0x0C, +0x1C or +0x08 list by its +0x84/+0x85
// selectors, and whatever is refused lands in the +0x04 list (0x00109129). Shape from the
// WorldBuilder twin 0x008D6550: separate calls per elapsed case and per list (retail merges
// them), field copies into locals first. Offsets are retail observations; names unknown.
struct Rva001087BBNode;
class BfmeDynamicNativeVB;
class DX8IndexBufferClass;
class Rva00108660ResourceManager
{
public:
	bool ReAcquireResources();
	void rva001091A8(void *shadowArg);
	char m_pad00[0x4];
private:
	Rva001087BBNode *m_head04; // +0x04
	Rva001087BBNode *m_head08; // +0x08
	Rva001087BBNode *m_head0C; // +0x0C
	char m_pad10[0xC];
	Rva001087BBNode *m_head1C; // +0x1C
	char m_pad20[0x234];
	BfmeDynamicNativeVB *m_vb; // +0x254
	DX8IndexBufferClass *m_ib; // +0x258
};
class W3DProjectedShadow;
// The fields this queue reads, at retail offsets; W3DProjectedShadow's own header spells a different layout.
class Rva001091A8ShadowView
{
public:
    char m_unknown00[0x34];
    unsigned short m_type;          // +0x34
    char m_unknown36[0x3c - 0x36];
    unsigned int m_expireFrame;     // +0x3C
    int m_40;
    int m_unknown44;
    int m_48;
    int m_elapsed;                  // +0x4C, -1 when unset
    int m_total;                    // +0x50
    int m_54;
    char m_unknown58[0x84 - 0x58];
    bool m_list0C;                  // +0x84
    bool m_list1C;                  // +0x85

};
class Rva00330A37 { public: void rva00330A37(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8); };
struct ShadowList;
class Rva00109129
{
public:
	bool rva00109129(W3DProjectedShadow*,ShadowList*);
	char m_pad00[0x10];
	W3DProjectedShadow *free; // +0x10
	char m_pad14[0x23C];
	int decalCount; // +0x250
};
class Rva001091A8ClientView
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0A(); virtual void v0B(); virtual void v0C(); virtual void v0D(); virtual void v0E(); virtual void v0F();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1A(); virtual void v1B(); virtual void v1C(); virtual void v1D(); virtual void v1E();
    virtual unsigned int getFrame();    // slot 31 (+0x7C)
};
class GameClient;
extern GameClient *TheGameClient;

void Rva00108660ResourceManager::rva001091A8(void *shadowArg)
{
    Rva001091A8ShadowView *shadow = (Rva001091A8ShadowView *)shadowArg;
    if ((shadow->m_type & 0x0C00) && shadow->m_expireFrame > ((Rva001091A8ClientView *)TheGameClient)->getFrame())
    {
        int v40 = shadow->m_40;
        int v48 = shadow->m_48;
        int elapsed = shadow->m_elapsed;
        int total = shadow->m_total;
        int v54 = shadow->m_54;
        if (elapsed == -1)
            ((Rva00330A37 *)shadow)->rva00330A37(0, total, v40, 0, v48, 0, total, v54);
        else
            ((Rva00330A37 *)shadow)->rva00330A37(0, total - elapsed, v40, 0, v48, 0, total - elapsed, v54);
        return;
    }
    if (shadow->m_type & 0x3C61)
    {
        if (shadow->m_list0C)
        {
            if (((Rva00109129 *)this)->rva00109129((W3DProjectedShadow *)shadow, (ShadowList *)&m_head0C))
                return;
        }
        else if (shadow->m_list1C)
        {
            if (((Rva00109129 *)this)->rva00109129((W3DProjectedShadow *)shadow, (ShadowList *)&m_head1C))
                return;
        }
        else if (((Rva00109129 *)this)->rva00109129((W3DProjectedShadow *)shadow, (ShadowList *)&m_head08))
            return;
    }
    ((Rva00109129 *)this)->rva00109129((W3DProjectedShadow *)shadow, (ShadowList *)&m_head04);
}
