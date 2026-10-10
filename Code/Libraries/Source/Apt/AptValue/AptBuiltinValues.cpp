// cl: /MD
// The native four-byte undefined-value slot is initially zero. The existing
// AptValue initializer stores its AptValue-derived eight-byte object here;
// Stage and recovered Apt bytecode callbacks read this same canonical name.
// Original source spelling is carried by those recovered interfaces; retail
// independently proves the pointer width, initial bytes, reader and writer.
class AptValue;
AptValue *gpUndefinedValue = 0;
