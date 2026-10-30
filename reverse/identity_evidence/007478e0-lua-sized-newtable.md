# 0x007478E0 is Lua's sized lua_newtable (lapi.c), not a game-side function

The row was `?bfmeGoUPC@@YAXPAUBfmeStateUPC@@H@Z` in
`Code/GameEngine/Source/Common/BfmeConv1339.cpp`, a C++ body over a private
three-field copy of `lua_State`, bound to the C name `_bfmeGoUPC` that Lua's own
objects call (`lstate.c` f_luaopen, `ldblib.c` getinfo) by an `/alternatename`
hatch. It now lives in `Code/Libraries/Source/Lua/lapi.c` with C linkage, as
Open-BFME-1 did for its twin at BFME 1 0x00990780.

Target facts (BFME 2 retail):

- Callers: `f_luaopen` (0x0074DEF0, lstate.c) at 0x0074DF33 `e8 a8 99 ff ff`,
  `getinfo` (0x00747E00, ldblib.c) at 0x00747ECF `e8 0c fa ff ff`, and
  LuaScriptEngine RegisterObject (0x00333E5B) at 0x00333EF9 `e8 e2 39 41 00`.
  The two Lua callers pass `(L, 0)`; RegisterObject passes the object ID.
- Placement: 0x007478E0 sits between `_lua_getref` (0x00747860, 115 B) and
  `_lua_setglobal` (0x00747920), both lapi.c rows. No ledger row claims a
  one-argument `lua_newtable`.
- Body (59 B): `luaH_new(L, 0, n)` (0x00750770, ltable.c), stores the result at
  `L->top + 8` and tag 4 (LUA_TTABLE) at `L->top`, then
  `if (L->top == L->stack_last) luaD_checkstack(L, 1)` (0x0074D650, ldo.c) and
  `L->top += 0x10`: upstream's `lua_newtable` with `api_incr_top`, the size
  argument passed through to EA's three-argument `luaH_new`.

Donor facts (upstream Lua 4.0.1): f_luaopen does `lua_newtable(L); lua_ref(L,
1);` to create the registry and getinfo starts with `lua_newtable(L)`, at the
points where retail calls this body.

Inference: EA added a sized variant of `lua_newtable` next to the original in
lapi.c. EA's name is not witnessed, so the row keeps the name its callers
already use, `_bfmeGoUPC`.
