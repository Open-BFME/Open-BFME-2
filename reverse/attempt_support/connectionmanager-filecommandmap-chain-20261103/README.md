# FileCommandMap (map<unsigned short, AsciiString>) hint-insert chain in retail

Read-only triage, 2026-11-03, seat claudec (claude-opus-5-5). No source, row,
pin or map edit. Target facts come from retail game.dat disassembly
(`tools/retail_body.py` disasm) and `tools/callers_of.py`; names below are the
current ledger rows, not proposed identities.

## Target facts (retail)

Every link of the chain has exactly one caller, the previous link:

| RVA | size | current row (placeholder) | retail body |
|---|---|---|---|
| 0x004D2941 | 134 | FileCommandMap::operator[] (ConnectionManager.cpp) | calls 0x0046A9AB, then 0x004D272E |
| 0x004D272E | 29 | map<int,Rva004D272ERecord>::insert(hint) (StlSweepR3Rva004D272E.cpp) | forwards to 0x004D2209, `ret 0xc` |
| 0x004D2209 | 310 | BfmeStringRecord004D05B8 set insert_unique(hint) | 16-bit key compares (`cmp cx, word ptr [..]`), calls 0x004D2050, 0x004D20DA, 0x00424250/0x004242C0 (iterator inc/dec) |
| 0x004D20DA | 138 | BfmeStringRecord set insert_unique(v) | 16-bit key compare, calls 0x004D2050 |
| 0x004D2050 | 138 | BfmeStringRecord set _M_insert | 16-bit key compare `cmp cx, word ptr [ebx+0x10]`, calls 0x004D1D0B and rebalance 0x00425490 |
| 0x004D1D0B | 34 | BfmeStringRecord _M_create_node | allocates 0x18 (16-byte node header + 8-byte value), calls 0x004D0FF6 at node+0x10 |
| 0x004D0FF6 | 45 | _Construct<BfmeStringRecord004D05B8> | EH frame, calls 0x004D05B8 |
| 0x004D05B8 | 31 | BfmeStringRecord004D05B8 copy ctor | copies the WORD at +0, AsciiString copy ctor 0x004365F0 on +4 |

So the 8-byte value is a 16-bit key plus an AsciiString at +4, and the only
user is the FileCommandMap subscript: this chain is the pair<const unsigned
short, AsciiString> tree retail's FileCommandMap::operator[] instantiated
(structural inference from the calls, the node size and the copy; the mangled
names are not yet proven for every link). The 310 B hint insert has the same
size as the /O1 map<ushort,uchar> sibling 0x004D1F1A (StlO1Instantiations.cpp),
so the chain is an /O1 instantiation.

## What blocks the real link fix

The FileCommandMap names that operator[] would naturally reference are held by
rows whose bodies are other trees':

- `?insert@?$map@GVAsciiString@@...` is the row 0x0016E310 (31 B) in
  ConnectionManager.cpp, bound through the pin insert_unique<G,AsciiString>(hint)
  -> 0x0016DF60 (the 712 B three-int Gen_p12pod tree). 0x0016E310 sits next to
  map<Gen_p12pod,int>::operator[] 0x0016E330, but neither has an approved TU, so
  it cannot be rehomed (AGENTS.md: move rows only into an approved unit).
- `?_M_create_node@?$_Rb_tree@GU?$pair@$$CBGVAsciiString@@...` is the row
  0x00759460 (approved provisional under CollisionManagerImpl.cpp).

Until 0x0016E310 has an approved TU and gives up the FileCommandMap insert name,
0x004D272E cannot take it, and the adapter names
`Rva004D272EMapHintInsert::insert` / `Rva0046A9ABMapLowerBound::lower_bound`
stay undefined in the real link.

## Next step

1. TU approval for 0x0016E310 (and 0x0016E330/0x0016DF60, the Gen_p12pod map).
2. Rehome 0x0016E310 as map<Gen_p12pod,int>::insert(hint); drop the wrong pin
   insert_unique<G,AsciiString> -> 0x0016DF60 (identity key 97).
3. Rename 0x004D272E (and, if the bytes hold with the real types, the rest of
   the chain above) to the FileCommandMap instantiation, keep it /O1, make
   ConnectionManager.cpp's operator[] plain STLport code with the helpers
   declared only, and drop the two adapter pins.
4. 0x00759460 needs its own owner first (identity key 96), since the
   Rva004D2941MapInstantiationAnchor is what emits it today.
