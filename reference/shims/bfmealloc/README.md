# bfmealloc

A copy of three vendored STLport 4.5.3 headers with the differences game.dat's
own STLport actually shows. It is opt-in: a unit sees it only by putting
`/Ireference/shims/bfmealloc` on its `// cl:` line, so nothing already landed
is affected.

Each change is here because the retail bytes demand it, not to make something
compile.

## `stl/_alloc.h` - the allocator was replaced

Stock `allocator<T>::allocate` forwards to `__sgi_alloc::allocate(bytes)`: one
argument, a free list, and a 128-byte small/large split. Retail has none of
that. Every allocating container reaches

    push 0 / mov eax,[ebp+8] / shl eax,2 / push eax / call 0x000307F0

which is `(bytes, hint)` __cdecl into a single raw byte allocator - the one
`reverse/symbols.csv` pins, forwarding to the game allocator table at
0x00DE0404 with memory class 3. Deallocation is a plain one-argument `_free`
at 0x00030830, not `__sgi_alloc::deallocate`, so the size argument is computed
and discarded.

## `stl/_algobase.h` - dispatch tags travel by value

The vendored `__copy_aux` and `__copy_ptrs` take their `__true_type` /
`__false_type` tag by `const&`. Retail copies them:

    33 d2 88 55 fb    construct tag
    8a 45 f6 88 45 f8 copy it into the next frame slot

Four tags are constructed and three are copied, which is three by-value
parameters and one const reference - so the outermost layer in
`_uninitialized.h` keeps `const&` and only the two inner ones here change.
Passing by value is also what lets cl expand them at all.

## `stl/_algobase.h` - `__copy_trivial` is not inline

It is a real out-of-line function in the image at 0x000179B0 and every call
site reaches it with a plain three-argument cdecl call, so the shipped header
declared it rather than defining it inline. Left inline, cl expands the
memmove at the call site and the tail of every copying body is wrong.

## `stl/_uninitialized.h` - the dispatch chain was expanded

`__uninitialized_copy` and its neighbours are marked `inline` upstream, but
cl 13.10 declines to expand them through a template specialisation at /Ob1,
which turns the whole tag chain into one out-of-line call. Retail expanded it.
`__forceinline` is how this toolchain is told to do the same; it changes no
semantics, only whether the layer survives as a call.
