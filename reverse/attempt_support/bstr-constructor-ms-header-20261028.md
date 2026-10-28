# `_bstr_t` constructor Microsoft-header migration

Inspected 2026-10-28 at `125d718628`. The queue serves
`Code/GameEngine/Source/GameNetwork/WOLBrowser/Bstr_t_ctor.cpp` for adoption
of `<comutil.h>` and `<comdef.h>`. The original source is restored.

A direct substitution of `<comutil.h>` for the local class and declarations,
keeping the placement-new anchor, fails all four rows in `./build.sh`: the
constructor compiles to `mov eax,ecx; ret 4`, `??0Data@_bstr_t@@QAE@PBD@Z`
is absent, and the parent unwind and EH handler are absent. Adding `/Ob0`
does not change that result. The sweep shim `reference/shims/sweep/comdef.h`
defines an empty `_bstr_t(const char*)`, explaining that observed body; the
build can retry with the sweep include directory after header resolution fails.

The VS2003 toolchain's actual `comutil.h` defines the nested class as `Data_t`,
where the currently matched standalone row uses `Data`; it also defines the
constructor inline. A successful migration needs the actual SDK header to be
available to the normal build, an evidence-backed resolution of the nested
row's symbol identity, and preservation of the out-of-line parent and its EH
graph. Do not infer byte equivalence from the matching source shape alone.
No shared header or ledger was changed.

After restoration, the scoped build passes all four function rows, including
the renumbered unwind label, and string, float and import checks. The frozen
file check reports all defined functions matched.
