// cl: /MD /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
//
// Opaque SubsystemInterface-derived destructor whose deleting wrapper uses
// the existing size-independent compiler shape. The native base at
// 0x001B4E74 is declared by the shared header, with its verified layout.
// Derived owner identity remains unknown; original /MD settings are retained.

typedef bool Bool;
#include "subsystem_interface.h"

class Rva006892F0 : public SubsystemInterface
{
public:
	virtual ~Rva006892F0();
};

Rva006892F0::~Rva006892F0()
{
}
