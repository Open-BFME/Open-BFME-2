# type_info header replacement: default argument lookup

Source base: `1f26b04a7b`. Claimed TypeInfoCopyConstructor.cpp and reviewed
`../typeinfo-vector-delete-20261024.md` and the earlier vector-emission
verdicts before trying a new placement of its existing emission adapter.

The original source passes the frozen-file check and both normal build
rows (copy constructor 0x0062903D, 11 bytes; vector deleting destructor
0x00629048, 75 bytes).

Trial: keep the existing empty `_CRTIMP` producer context, replace the
copied class declaration with `<typeinfo.h>`, and move the existing default
argument to the copy-constructor definition:

```cpp
type_info::type_info(const type_info& rhs = typeid(int)) {
    if (0) new type_info[2];
}
```

The supported normal build fails at the array-new expression with C2512,
`'type_info' : no appropriate default constructor available`. The compiler
accepts the definition's syntax but this context does not provide the
default-construction lookup needed for vector-destructor emission. The
earlier handoff already records why declaring array delete or switching
the destructor to dllimport would produce the wrong native callee.

The trial is reverted; the original two rows verify again. The queue's
type_info finding remains. This is an additional compiler-emission
prerequisite, with no source, matching, linking or debt gain from the trial.
t=2min model=gpt-6.1-sol.
