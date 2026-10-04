// _CurDrawableShowModule
// partial score=0.84 date=2026-10-04
// cl: /O1 /MD
// BFME1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 BfmeConv808.cpp.
// Native registration335E7E -> lua_pushcclosure747640 -> lua_setglobal747920
// with VA C0E224 names this callback. Whole donor /O1 /Os /O2 audit found
// only the two adjacent 25-byte wrappers. Original helper3336AD/117 remains
// unrecovered; its bool parameter and AsciiString/Drawable278689 calls are
// independently visible in target instructions. No speculative pin is landed.
struct lua_State;
extern "C" const char *lua_tostring(lua_State *, int);
bool rva003336ADSetModuleHidden(bool hidden, const char *name);
extern "C" int CurDrawableShowModule(lua_State *state)
{
    rva003336ADSetModuleHidden(false, lua_tostring(state, 1));
    return 0;
}
