// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// The Object block. It is one line: read the name and hand off to the shared
// four-argument body at 0x00139D00, which the ObjectReskin and ChildObject
// blocks also use -- they pass the original's name where this one passes empty
// strings, which is why that function carries both "ObjectReskin must come after
// the original Object (%s, %s)." and "ChildObject must come after the original
// Object (%s, %s)."
//
// That body is ThingFactory::parseObjectDefinition, as in Zero Hour, whose
// shared body takes two names; BFME's takes three.
#include "ascii_string.h"
#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/ThingFactory.h"

// BFME-only. Same shape as the reskin block, but the second name goes to the
// fourth argument rather than the third -- which is what makes it a child of the
// original rather than a reskin of it.
void INI::parseChildObjectDefinition( INI* ini )
{
	AsciiString name( ini->getNextToken() );
	AsciiString childOf( ini->getNextToken() );
	ThingFactory::parseObjectDefinition( ini, name, AsciiString::TheEmptyString, childOf );
}
