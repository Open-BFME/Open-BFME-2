// cl: /O1 /MD /DNDEBUG
// The named QuickMatch gadget callback stores a non-owning GameWindow pointer
// at screen+80. Complete native 5BA593 calls the shared empty destructor on
// this member before destroying preferences at+64. WB 15875B0 corroborates
// that member cleanup. Its one-byte RET is folded with Coord2D's destructor.
class GameWindow;
class OnlineQuickMatchWindowRef {
public:
    ~OnlineQuickMatchWindowRef();
private:
    GameWindow *m_window;
};
OnlineQuickMatchWindowRef::~OnlineQuickMatchWindowRef() {}
