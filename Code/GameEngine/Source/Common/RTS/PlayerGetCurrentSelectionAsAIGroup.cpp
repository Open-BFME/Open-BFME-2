// cl: /O1 /DNDEBUG /MD /EHsc
// ?getCurrentSelectionAsAIGroup@Player@@QAEXPAVAIGroup@@@Z @0x002AA164 18B
// BFME2 Player selection forward via Gen_0018BC70::bfmeVisitAll row 0x004D6E95.
// Donor: BFME1 Player.cpp getCurrentSelectionAsAIGroup (m_currentSelection at +0x67C calling bfmeForward) plus ZH variant calling aiGroupFromSquad. BFME2 repairs: selection at +0x730 as Gen_0018BC70 calling bfmeVisitAll; AIGroup passed as BfmeVisitorBF visitor.
class BfmeVisitorBF;
class AIGroup;
class Gen_0018BC70
{
public:
	void bfmeVisitAll(BfmeVisitorBF *visitor);
};
class Player
{
public:
	void getCurrentSelectionAsAIGroup(AIGroup *group);
private:
	unsigned char m_pad[0x730];
	Gen_0018BC70 *m_currentSelection;
};
void Player::getCurrentSelectionAsAIGroup(AIGroup *group)
{
	if (m_currentSelection != 0)
		m_currentSelection->bfmeVisitAll(reinterpret_cast<BfmeVisitorBF *>(group));
}
