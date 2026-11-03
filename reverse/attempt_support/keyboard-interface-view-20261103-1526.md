# Keyboard: reconcile the two existing interface-pointer views

Prior attempt log85432 already identifies the precise composition prerequisite:
the seed stores IDirectInput8/IDirectInputDevice8 pointers, while the donor
dereferences DI8Obj/DIDevObj raw table views. Both current files are claimed
as one native-approved scope. Match the donor's two storage pointer types to
the seed, preserving the independently witnessed offsets E20/E24, and cast to
the unchanged raw call views at their existing call sites/self arguments.
The E28 storage extent, table slots, stdcall prototypes, failure branches,
descriptor data, property initializer and close/Acquire sequence stay unchanged.
No new virtual slots, SDK interface definition, wrapper, alias, pin or header.

Native normal/frozen/EH and strict receipt checks preserve openKeyboard188B,
all three data rows/56B, its external body/relocations and all non-debug object
sections identically. The body and ABI are not reconstructed anew. This is
the second separately verified prerequisite, after the SDK GUID header repair;
the native composition and link guard still decide whether the source can move.
No runtime, memory or crash improvement is claimed.
