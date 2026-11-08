# Object death handler adopts canonical Thing, 2026-11-08

ObjectOnDie.cpp replaces its private 0x48-byte Thing prefix with the canonical
0x60-byte class. The following padding shrinks to 0x60..0x74, preserving all
accessed Object member offsets. The bounded Object view remains incomplete;
this does not recover its full extent or class declaration. Existing template
reads use the canonical public member directly, retaining the old inline
accesses without introducing calls to its declared getter. Position and
orientation accessors retain their canonical offsets and existing code.

The full 798-byte death handler, its eight-byte cleanup and ten-byte handler
row pass normal verification. Its parent EH graph is EXACT, the native path
literal and both floats verify, and the source is unfrozen. Owning-tool
acceptance retires one Thing header debt. Strict preparation passes 142/142
rows across this source and the unchanged Recorder provider (including its
two data rows). Paired checking and current-object preview pass.

All eleven retained code COMDAT facts, relocation bindings, flags and
selection policies agree; all three named data allocations and undefined
references remain equal. The removed four-byte getTemplate copy has outside
callers, so Recorder was explicitly claimed and strictly prepared. Its
earlier path-order copy has identical body, relocations, flags and policy;
the cached census retains outside copies too. No native RVA or original
out-of-line identity is claimed for this getter. The sole added compiler
iterator exactly matches native 0x00001423 and the existing ATL provider's
flags/policy. No row, pin, alias, flag, shared header or source path changes.

This clears one header debt and removes one private class copy. It is scoped
code/provider evidence against current explicit inputs and index d171e84869,
not a full current image, new census, coverage gain or runtime result. Full
Object recovery and retail TU consolidation remain separate work.
