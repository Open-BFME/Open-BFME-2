// cl: /O2 /DNDEBUG /MD /EHsc
//
// ?Rva000D1D21ByteResult@@YGEIIII@Z, retail 0x000d1d21, 5 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Exact-byte hypothesis only: RET16 does not prove this four-unsigned-word
// signature or stdcall rather than ignored-this; no target callers/addresses
// or WB function currently provide a callable-contract witness.
unsigned char __stdcall Rva000D1D21ByteResult(unsigned int, unsigned int, unsigned int, unsigned int) { return 1; }
