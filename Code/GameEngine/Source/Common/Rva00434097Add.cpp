// cl: /O1 /MD
// Native Ghidra0x00434097..0x004340A4 (13B, RET8): first stack word
// goes to EAX, second to ECX, and their wrapping 32-bit sum is returned.
// Incoming ECX is unused. The stack-only stdcall projection and unsigned
// words model that observed protocol, not original declaration types.
// Volatile parameter views plus ordered local reads preserve the observed
// load order; original qualifiers and function identity are unresolved.
unsigned __stdcall Rva00434097Add(volatile unsigned a,volatile unsigned b){unsigned x=a;unsigned y=b;return x+y;}
