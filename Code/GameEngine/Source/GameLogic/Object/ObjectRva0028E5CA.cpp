// cl: /DNDEBUG /MD
// ?rva0028E5CA@Object@@QAEXPAVAIGroup@@@Z @0x0028E5CA 22B: Object group setter calls leaveGroup 0x0028C01F then stores AIGroup at +0x1A8. Evidence: same +0x1A8 as leaveGroup m_group; callee rowed leaveGroup; caller 0x0036E649 in AIGroup::add passes its this as arg; neighbours ObjectRva TU with same flags.
class AIGroup;
class Object
{
public:
	void leaveGroup();
	void rva0028E5CA(AIGroup *group);
private:
	unsigned char m_pad[0x1A8];
	AIGroup *m_group;
};
void Object::rva0028E5CA(AIGroup *group)
{
	leaveGroup();
	m_group = group;
}
