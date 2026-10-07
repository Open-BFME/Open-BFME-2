// cl: /O1 /Ob0 /EHsc /MD
// Reference: STLport 4.5.3 min returns one of its two argument references.
// Target: preceding RET boundary and 16 exact bytes. No target type/name proof;
// signed-word comparison and reference ABI are carried from the emitted body.
const int &Rva000E13BAMin(const int &a, const int &b)
{
    return b < a ? b : a;
}
