// cl: /O1 /DNDEBUG /MD /EHsc
// ?duplicate@Script@@QBEPAV1@XZ, retail 0x003B7550 (55 bytes).
// Identity: WorldBuilder's debug TeamPrototype::getGenericScript (Team.cpp)
// calls this address on each script its ScriptEngine lookup (0x003573C4)
// finds and stores the result as the copy to run, the place Zero Hour's
// TeamPrototype::getGenericScript calls Script::duplicate. Retail allocates
// 0x54 bytes and runs the one-argument constructor at 0x003B7448 on this
// object, i.e. BFME 2's duplicate is a copy construction (inference: the
// constructor is taken as Script's copy constructor from that shape).
class Script
{
public:
	Script(const Script &that);
	Script *duplicate() const;

private:
	unsigned char m_pad00[0x54];
};

Script *Script::duplicate() const
{
	return new Script(*this);
}
