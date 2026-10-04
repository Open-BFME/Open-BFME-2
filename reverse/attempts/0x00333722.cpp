// _CurDrawableHideModule
// partial score=0.84 date=2026-10-04
// cl: /O1 /MD
// BFME1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 BfmeConv808.cpp.
// Native registration 335E63 -> lua_pushcclosure747640 -> lua_setglobal747920
// with VA C0E23C names this callback. The whole eight-function donor was
// compiled under /O1 /Os /O2; only the two adjacent 25-byte wrappers place.
// Native helper3336AD/117 constructs AsciiString and invokes Drawable278689.
// Its shared implementation is still blocked; no speculative pin is landed.
struct lua_State;
extern "C" const char *lua_tostring(lua_State *, int);
bool rva003336ADSetModuleHidden(bool hidden, const char *name);
extern "C" int CurDrawableHideModule(lua_State *state)
{
    rva003336ADSetModuleHidden(true, lua_tostring(state, 1));
    return 0;
}
