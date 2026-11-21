# 0x00879428 / 0x00879438: Rva005F3EE3 and Rva005F3FFC tables (blocked: rename refusals)

Target facts (retail):
- Base table 0x00879428 = 4x 0x0047A69C (`ret 4`). Derived table 0x00879438 =
  [0x005F3EF3, 0x005F3EFE, 0x005F3F09, 0x0047A69C]. Neither table has a destructor slot.
- Dtor 0x005F3FFC stores 0xC79438 at entry and 0xC79428 at exit; 0x005F3EE3
  (`mov [ecx],0xC79428; ret`) is the out-of-line base dtor, called by the unwind funclets.
- 0x005F3EF3/EFE/F09 are `mov ecx,[ecx+4]; mov eax,[ecx]; call [eax+0x14/0x1C/0x18]; ret 4`.

Inference: both destructors are non-virtual, and the four base virtuals are `void (int)`.
Under MSVC 7.1, an `int` body that is only `ret 4` is error C4716. A scratch compile of
`void D::f(int) { m_04->v5(); }` gives exactly the retail 11 bytes, and the empty base
gives `ret 4`.

Needed changes (all refused by tools/rename.py on 2026-11-21):
1. `??1Rva005F3FFC@@UAE@XZ` -> `QAE`: plain respell refused (special member); `--identity`
   refused (shape UAE->QAE). A pin `??1Rva005F3FFC@@QAE@XZ` (symbols.csv) and the
   `/alternatename` QAE=UAE in FamilyDeletingDtors10.cpp exist only because of this
   wrong spelling; both go once the row is QAE.
2. `??1Rva005F3EE3@@UAE@XZ` (0x005F3EE3, fold-proof row) -> `QAE`: same refusal.
3. `?rva005F3EF3/EFE/F09@Rva005F3EF3@@QAEHH@Z` (VslotSmallBodiesAJ.cpp) -> `--to-class
   Rva005F3FFC` as `UAEXH`: refused, because the return type changes H->X.
4. Four base slot rows at 0x0047A69C via `add_match.py --icf-owner`, with `fold-proof=`.

Draft class views for Rva005F3FFCDtor.cpp:

```cpp
class Rva005F3EE3
{
public:
	~Rva005F3EE3() {}
	virtual void rva005F3EF3(int) {}
	virtual void rva005F3EFE(int) {}
	virtual void rva005F3F09(int) {}
	virtual void slot3(int) {}
};
class Rva005F3FFC : public Rva005F3EE3
{
public:
	~Rva005F3FFC();
	virtual void rva005F3EF3(int);   // m_04->v05()
	virtual void rva005F3EFE(int);   // m_04->v07()
	virtual void rva005F3F09(int);   // m_04->v06()
	// m_04 is the target pointer; members +08..+10 as today
};
```

OwnedPointerResets.cpp's view must also lose `virtual` on the dtor.
