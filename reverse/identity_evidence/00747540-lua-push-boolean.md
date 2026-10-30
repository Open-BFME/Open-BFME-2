# 0x00747540 is lapi.c's push for EA's boolean tag, not a game-side function

The row was `?bfmeGo1039E@@YAXPAUBfmeQ1039@@H@Z` in
`Code/GameEngine/Source/Common/BfmeConv1039E.cpp`, a C++ body over a private
three-field copy of `lua_State`. It now lives in
`Code/Libraries/Source/Lua/lapi.c` with C linkage as `_bfmeGo1039E`.

Target facts (BFME 2 retail):

- Body (45 B): stores tag 6 at `L->top`, the int argument at `L->top + 8`,
  then `if (L->top == L->stack_last) luaD_checkstack(L, 1)` (0x0074D650,
  ldo.c) and `L->top += 0x10`. That is upstream lapi.c's push shape
  (`lua_pushnil`/`lua_pushnumber`: set the tag and value, `api_incr_top`).
- Tag 6 is EA's added boolean tag, the one lvm.c and lobject.c switch on as a
  literal 6 (`Code/Libraries/Source/Lua/lvm.c:67,297,437`).
- Placement: 0x00747540 sits between `_lua_pushnil` (0x00747510, 36 B) and
  `_lua_pushnumber` (0x00747570), both lapi.c rows.
- Callers are game-side Lua bindings only (LuaScriptEngine condition/action
  wrappers and event dispatch, e.g. 0x00334212, 0x0033436F, 0x00334634,
  0x00334860, 0x0033508F), each passing the `lua_State *` they hold.

Inference: EA added a boolean push to lapi.c next to lua_pushnil. EA's name is
not witnessed (Lua 5.0's `lua_pushboolean` is a hint, not evidence), so the row
keeps its placeholder `bfmeGo1039E` with C linkage.
