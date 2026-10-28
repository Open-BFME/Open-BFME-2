// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Trimmed to the two T1 bodies the sweep places; the donor's other
// definitions are omitted.

// Both are the same guarded indirect call; only the member offset where the function
// pointer sits differs (0x1E0 vs 0x1E4), so retail's two bodies differ only
// in that displacement.

struct BfmeThingEHCa
{
	int bfmeGoEHCa(void *a, void *b, void *c);
	unsigned char m_bfmeHead[0x1e0];
	int (__cdecl *m_bfmeFn)(void *self, void *a, void *b, void *c);
};

int BfmeThingEHCa::bfmeGoEHCa(void *a, void *b, void *c)
{
	int (__cdecl *fn)(void *, void *, void *, void *) = m_bfmeFn;
	if (fn)
		return fn(this, a, b, c);
	return 0;
}

// Native GameWindow table C0BBCC slot 2 selects this complete35B body.
// The placeholder method name is retained; this recovers its class/ABI,
// not an original method name. Only the prefix through callback+1E4 is used.
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
class WinInstanceData;
class GameWindow;
typedef WindowMsgHandledType (__cdecl *GameWinSystemFunc)(
    GameWindow *, unsigned int, unsigned int, unsigned int);

class GameWindow
{
protected:
    virtual ~GameWindow();
public:
    virtual WindowMsgHandledType input(unsigned int, unsigned int, unsigned int);
    virtual WindowMsgHandledType bfmeGoEHCb(unsigned int, unsigned int, unsigned int);
    virtual int draw(void *);
    virtual int tooltip(WinInstanceData *, unsigned int);
    virtual int rva0009FD78();
    virtual bool vslot6() const;
    virtual void *fetchCreateInstance() = 0;
    virtual bool vslot8() const;
    virtual bool vslot9() const;
    virtual void vslot10() = 0;
private:
    unsigned char m_unmodelled04[0x1E4 - 4];
    GameWinSystemFunc m_system;
};

WindowMsgHandledType GameWindow::bfmeGoEHCb(
    unsigned int msg, unsigned int mData1, unsigned int mData2)
{
    GameWinSystemFunc fn = m_system;
    if (fn)
        return fn(this, msg, mData1, mData2);
    return MSG_IGNORED;
}
