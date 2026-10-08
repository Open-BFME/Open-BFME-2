# Concatenation helper return ABI lead

Retail 0x005EEFA9 is the existing 41-byte `Rva005EEFA9Copy` provider. The current row takes an explicit destination pointer and returns it. This independently compiled clean C++ proposal instead returns the same five-word aggregate by value; MSVC7.1 supplies the first stack argument as its hidden return destination. All 41 retail bytes reproduce exactly. This is evidence about the return convention, with zero additional coverage; the existing provider source and ledger owner remain unchanged.

The complete WorldBuilder body at 0x016190D0 (83 bytes) reads the sixteen-byte source from its second machine argument, appends the third word argument, copies all five words through the first argument and returns that destination. Retail callers in QueuedIconSlot's constructor 0x005F7B25 compose the two-string-plus-text node with a final string reference and materialize the returned twenty-byte node. The original template/function name is unestablished.

The proposal is not admitted source. Callers compiled with the proposed return convention still have prefix/key temporary allocation and evaluation-order differences. Current complete constructor banks are `reverse/attempts/0x005f7b25.cpp` (1026 versus 1020 bytes) and `reverse/attempts/0x005f775e.cpp` (987 versus 967). A future owner rename must follow the separately reviewed real-claim retraction path and verify callers/providers together; a second pin at this address is not a solution.

Save the complete proposal below as `build/FinalConcatReturnTrial.cpp`, then reproduce it with:

```
python tools/explain_mismatch.py '?Rva005EEFA9Copy@@YA?AURva005EEFA9Dst@@ABURva005EEFA9Src@@H@Z' --rva 0x5EEFA9 --size 41 --source build/FinalConcatReturnTrial.cpp
```

Validated at BFME 2 b180cdfa97, BFME 1 clean pointer40e7f2f21f0011b42a5654697cdedbc2658b6d9b. Evidence is full byte comparison of this helper proposal, not linking or runtime qualification.

```cpp
// cl: /O1 /DNDEBUG /MD /EHsc
struct Rva005EEFA9Src { int m00,m04,m08,m0C; };
struct Rva005EEFA9Dst { int m00,m04,m08,m0C,m10; };
Rva005EEFA9Dst __cdecl Rva005EEFA9Copy(const Rva005EEFA9Src &src,int extra) {
 Rva005EEFA9Dst tmp;
 *(Rva005EEFA9Src*)&tmp=src;
 tmp.m10=extra;
 return tmp;
}
```
