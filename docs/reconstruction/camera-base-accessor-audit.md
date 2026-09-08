# Camera base accessor identity correction

The Camera translation unit now selects the scoped BFME2 RenderObj declaration.
Its existing 41 unrelated body claims still compile exactly. Four older claims
came from an obsolete base layout or bit mask and were misleading whole-text
placements. The independently reconstructed RenderObj copy constructor and
primary vtable at VA BD2F68 establish the replacements:

| Accessor | Old RVA / bytes | Actual RVA / bytes | Vtable slot | Contract |
| --- | --- | --- | --- | --- |
| Is_Additive | 19B080 / 9 | 6CF83 / 9 | 110 | Bits at +10 masked with 00400000 |
| Set_Additive | 1A30F0 / 21 | 6CF8C / 21 | 111 | Set/clear byte +12 bit40 |
| Is_In_Scene | 41B7F5 / 12 | 6D01F / 9 | 123 | Scene pointer at +78 |
| Get_User_Data | 21914D / 7 | 30C8A7 / 7 | 87 | UserData pointer at +80 |

The three getters compare byte-for-byte without relocations. The old setter
claim is retired: the correct typed inline source currently emits two returns,
whereas retail has a shared return. Its actual location is evidence for a future
match, not a new coverage claim. The independently reconstructed hierarchy
aggregation routine also invokes the additive pair at vtable offsets 1B8/1BC.
No ordinary global or vtable exception was added. The correction has a net
coverage change of -24 bytes (-21 retired setter and -3 scene getter extent).
