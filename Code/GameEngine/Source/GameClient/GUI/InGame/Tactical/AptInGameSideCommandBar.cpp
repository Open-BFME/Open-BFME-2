// cl: /O1 /MD
// Impl::Update is recovered in AptInGameSideCommandBarUpdate.cpp.
class AptInGameSideCommandBar
{
public:
    class Impl { public: void Update(); };
    void Update();
private:
    Impl *impl;
};

// Native 005288BD..005288C4 delegates through the owner pointer at +0.
// The public Update identity follows the proven Impl::Update tail call;
// WorldBuilder does not retain this seven-byte wrapper as a named body.
void AptInGameSideCommandBar::Update()
{
    impl->Update();
}
