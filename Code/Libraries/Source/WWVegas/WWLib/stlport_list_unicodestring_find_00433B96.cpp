// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// The address-derived helper at 0x00433B96 walks a circular list of
// UnicodeString nodes and returns the matching node or the end node. The
// target evidence is the 39-byte loop and its call to StringBase<wchar_t>::compare.
#include "unicode_string.h"

struct Rva00433B96Node
{
	Rva00433B96Node *next;
	Rva00433B96Node *prev;
	UnicodeString value;
};

void Rva00433B96(Rva00433B96Node **result,
	Rva00433B96Node *first,
	Rva00433B96Node *last,
	const UnicodeString &value)
{
	Rva00433B96Node *current = first;
	while (current != last && current->value.compare(value) != 0) {
		current = current->next;
	}
	*result = current;
}
