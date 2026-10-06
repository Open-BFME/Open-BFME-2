// cl: /DNDEBUG /MD /EHsc
// InGameUI::FormationPreviewPoolObject::dismiss / assign (WorldBuilder names, InGameUI.cpp lines 8200 and 8189: hide/show the +0x00 drawable through 0x002707FA and set +0x08 to 0 / 1).
// was ?rva0029B1C2@Rva0029B1C2@@QAEXXZ 0x0029B1C2 22B evidence: chain via rowed 0x002707FA; clears byte at +8 after forwarding 0
class Rva002707FA
{
public:
	void rva002707FA(unsigned char value);
};

class InGameUI
{
public:
	class FormationPreviewPoolObject;
};
class InGameUI::FormationPreviewPoolObject
{
	Rva002707FA *m00;
	char _p04[4];
	unsigned char m08;
public:
	void dismiss();
	void assign();
};

void InGameUI::FormationPreviewPoolObject::dismiss()
{
	if (m00 != 0)
		m00->rva002707FA(0);
	m08 = 0;
}

void InGameUI::FormationPreviewPoolObject::assign()
{
	if (m00 != 0)
		m00->rva002707FA(1);
	m08 = 1;
}
