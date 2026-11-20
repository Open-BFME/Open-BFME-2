// LocomotorStore declarations for callers and the reload parser. The parser
// accesses its measured storage through a projection local to its source.
#ifndef CANONICAL_LOCOMOTORSTORE_H
#define CANONICAL_LOCOMOTORSTORE_H

class AsciiString;
class INI;
class Locomotor;
class LocomotorTemplate;

class LocomotorStore
{
public:
	~LocomotorStore();
	static void parseLocomotorTemplateDefinition(INI *ini);
	LocomotorTemplate *findLocomotorTemplate(const AsciiString &name);
	LocomotorTemplate *findLocomotorTemplate(int key);
	Locomotor *newLocomotor(const LocomotorTemplate *tmpl, bool flag);
	LocomotorTemplate *newOverride(LocomotorTemplate *original);
};

#endif // CANONICAL_LOCOMOTORSTORE_H
