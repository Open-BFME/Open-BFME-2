#ifndef BFME_RVA003769C2_STRING_VECTOR_H
#define BFME_RVA003769C2_STRING_VECTOR_H

class AsciiString;

// Existing rowed erase view: three pointers to four-byte AsciiString elements.
// This is a shared reconstruction view, not a claim about the original type name.
class Rva003769C2StringVector {
public:
 AsciiString *first;
 AsciiString *finish;
 AsciiString *capacity;
 AsciiString *end() { return finish; }
 AsciiString *begin() { return first; }
 AsciiString *erase(AsciiString *position);
};

#endif
