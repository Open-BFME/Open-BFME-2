// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::BuildBuildingButton (WorldBuilder
// StrategicInGameUIBuildBuildingButton.cpp). Target facts for OnLeftClicked
// 0x005E92B1 (virtual: its pointer sits at 0x00878014 in a command button
// vtable): appends message 0x6AA through TheMessageStream (vslot 18) with
// three integer arguments: the region's owner id (+0x18 -> +0x1C -> +0x12C), the region id (+0x18 -> +0x18) and
// the building choice's id (+0x1C -> +0x04). Field meanings are inferred.
class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *appendType(int type);
};
extern MessageStream *TheMessageStream;

struct Rva005E92B1Owner
{
	char m_pad00[0x12C];
	int m_id; // +0x12C
};

struct Rva005E92B1Region
{
	char m_pad00[0x18];
	int m_id; // +0x18
	Rva005E92B1Owner *m_owner; // +0x1C
};

struct Rva005E92B1Choice
{
	int m_00;
	int m_id; // +0x04
};

namespace StrategicInGameUI
{
class BuildBuildingButton
{
public:
	virtual void OnLeftClicked();

private:
	char m_pad04[0x18 - 0x04];
	Rva005E92B1Region *m_region; // +0x18
	Rva005E92B1Choice *m_choice; // +0x1C
};
}

void StrategicInGameUI::BuildBuildingButton::OnLeftClicked()
{
	GameMessage *msg = TheMessageStream->appendType(0x6AA);
	msg->appendIntegerArgument(m_region->m_owner->m_id);
	msg->appendIntegerArgument(m_region->m_id);
	msg->appendIntegerArgument(m_choice->m_id);
}
