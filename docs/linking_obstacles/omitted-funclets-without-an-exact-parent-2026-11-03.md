### Omitted funclets without an EXACT parent (2026-11-03)

`exit_link.py` refused on 13 omitted `uw_gen` funclets. Retail's FuncInfo tables name each one's
parent; none is inferred from adjacency:

- `uw_007770d9`..`uw_00777140` (9): `??1Rva002CD4A6@@UAE@XZ`. Cleared: retail destroys two members
  at +0xD0 and +0xD8 through 0x004C9F38, which tests the word at +4; the view had them at +0xD4 and
  +0xDC. `eh_verify`: EXACT, body unchanged.
- `uw_007660a8`: `??1SimpleSceneClass@@UAE@XZ`. Cleared: the member starts at +0x34 and 0x00141D90
  reads its array at +0x18. `eh_verify`: EXACT, body unchanged.
- `uw_007604bd`: `?initD3DAssets@W3DMouse@@AAEXXZ`. Open. Retail's map at 0xD033E4 has a second
  state, `{toState 0, action NULL}`; ours has one. Body and funclet bytes match.
- `uw_007a8dc0`, `uw_007a8dc8`: six `RVA_APT_CTOR` constructors (0x006DE480 onward). Open. Retail's
  map at 0xD62840 has `{-1, 0xBA8DC0}` (base dtor 0x6D6340) and `{-1, 0xBA8DC8}` (0x6D6470); no write
  ever enters the second state, and ours emits one. Basing `Rva006D6360Base` on
  `BfmeAptValue006DCD20` gives the right first target but not the second state.

Tried without effect on the state count: empty-dtor locals and temporaries beside the lock or in
the dead loop, constant-false and after-return locks (W3DMouse); a dtor or dtor-bearing member on
`Rva006DBits`, an inline `clear()`, an inline setter in the macro body, an out-of-line base dtor
(Apt). Each open table differs only in a state retail's code never enters.
