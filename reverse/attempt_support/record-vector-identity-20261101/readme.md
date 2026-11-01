# Record vector push-back identity correction

LINK-092's native 6BF950/59-byte body copies a nonpolymorphic 36-byte record.
Its calls at +15 and +33 reach the existing record copy 63BE4/79 and vector
overflow 6BF5E0/268. The current Money-labelled whole-vector instantiation
instead emits incompatible Money constructors, overflow and three unresolved
Money virtuals. Its preview is nonlinking; the two real providers already link.
No original application type or source path is inferred from matching bytes.

The private replacement uses the existing BfmeVecBE/BfmeElemBE ABI views and
existing BfmeStringRecord00063BE4 copy owner. It performs ordinary placement
copy when capacity remains, otherwise calls the existing overflow with a
default-initialized empty trait object. Both complete 59-byte bodies are raw
identical; new symbolic relocations bind directly to the two real providers.
Private verification resolves every byte and call target to retail. There is
no new pin, alias, manual storage reuse or generated body.

The record copy declaration exposes its no-C++-throw contract to the caller.
This is supported by the complete owned call chain, independently of EH shape:
the 79-byte copy writes seven words, calls StringBase<char>'s 66-byte copy,
then writes two bytes. StringBase shares the buffer and increments its count
under Enter/LeaveCriticalSection; it allocates no string and invokes no callback.
Its getter 35C90 constructs a static lock, with argument one to 411C1, and
registers cleanup with atexit. The current constructor owner is
MilesMutexGuard.cpp; that argument skips its optional virtual-lock call.
Critical-section imports are declared C and nonthrowing. AtexitThunk.cpp
registers the callback through CRT onexit functions and returns success/failure,
without invoking it. This establishes the C++ exception contract under /EHsc;
it does not claim that Windows structured exceptions cannot occur.

The empty trait must be default-initialized. Value-initializing the POD trait
adds a byte store and a different frame (67 bytes). A default-initialized local
keeps the native 59-byte body; the compiler chooses its storage. No source
assumption about the original local variable or application record is made.

## Required publication sequence

The existing Money row is a real claim, so add_match's scaffold replacement
path is inapplicable. First retract exactly that row, record its tombstone and
remove its now-rowless source in a separate normal commit. Then readmit the
verified neutral body at the same source path. The current TU map does not
approve a source move; the misleading legacy filename is retained pending TU
approval. Audit the old row and removed COMDAT providers' consumers, retire
unused false pins only after their real bindings verify, and retire registered
identity/header debt solely through each register's owning tool.

The source retraction is not completion or byte progress. Final publication
must preserve the body and its verified providers. Current scoped strict
preparation passes 97/97 rows across the old source and two real providers.
