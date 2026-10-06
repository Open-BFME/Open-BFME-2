// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// ?newTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z @0x002D7283 82B. Evidence: BFME1 donor game/GameEngine/Source/GameClient/System/Anim2DCollectionTemplates.cpp newTemplate plus ZH GeneralsMD Anim2D.cpp:820; placeholder comment in Anim2D.cpp:660 names this mangling; retail new 0x1c plus Anim2DTemplate ctor VAsciiString row 0x002D6CDE plus link [esi+0xc]/[eax+4] matches collection head/template next.
#include "ascii_string.h"

class Anim2DTemplate
{
public:
	Anim2DTemplate(AsciiString name);
	virtual ~Anim2DTemplate();
	Anim2DTemplate *m_nextTemplate;
	unsigned char m_pad[0x14];
};

class Anim2DCollection
{
public:
	virtual ~Anim2DCollection();
	virtual void init();
	virtual void update();
	Anim2DTemplate *newTemplate(const AsciiString &name);
private:
	unsigned char m_filler[8];
	Anim2DTemplate *m_templateList;
};

Anim2DTemplate *Anim2DCollection::newTemplate(const AsciiString &name)
{
	Anim2DTemplate *createdTemplate = new Anim2DTemplate(name);
	createdTemplate->m_nextTemplate = m_templateList;
	m_templateList = createdTemplate;
	return createdTemplate;
}
