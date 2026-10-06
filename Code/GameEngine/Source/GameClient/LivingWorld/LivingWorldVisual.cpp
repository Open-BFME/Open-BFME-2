// cl: /O1 /EHsc /MD /arch:SSE
// LivingWorldVisual.cpp -- LivingWorldVisual members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function (vtable pairing) and the member m_primaryRObj at +0x08; retail
// supplies the bytes. The colour goes to render-object slot 126 (+0x1F8) as a
// 16-byte parameter block whose leading 31-bit field is set to 1 (top bit
// kept), followed by the colour and two zero words.

typedef int Int;

struct HouseColorParams
{
	unsigned int m_mode : 31;
	unsigned int m_flag : 1;
	Int m_color;
	Int m_reserved0;
	Int m_reserved1;
};

class RenderObjClass
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003();
	virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007();
	virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011();
	virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015();
	virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019();
	virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023();
	virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027();
	virtual void s028(); virtual void s029(); virtual void s030(); virtual void s031();
	virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035();
	virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039();
	virtual void s040(); virtual void s041(); virtual void s042(); virtual void s043();
	virtual void s044(); virtual void s045(); virtual void s046(); virtual void s047();
	virtual void s048(); virtual void s049(); virtual void s050(); virtual void s051();
	virtual void s052(); virtual void s053(); virtual void s054(); virtual void s055();
	virtual void s056(); virtual void s057(); virtual void s058(); virtual void s059();
	virtual void s060(); virtual void s061(); virtual void s062(); virtual void s063();
	virtual void s064(); virtual void s065(); virtual void s066(); virtual void s067();
	virtual void s068(); virtual void s069(); virtual void s070(); virtual void s071();
	virtual void s072(); virtual void s073(); virtual void s074(); virtual void s075();
	virtual void s076(); virtual void s077(); virtual void s078(); virtual void s079();
	virtual void s080(); virtual void s081(); virtual void s082(); virtual void s083();
	virtual void s084(); virtual void s085(); virtual void s086(); virtual void s087();
	virtual void s088(); virtual void s089(); virtual void s090(); virtual void s091();
	virtual void s092(); virtual void s093(); virtual void s094(); virtual void s095();
	virtual void s096(); virtual void s097(); virtual void s098(); virtual void s099();
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103();
	virtual void s104(); virtual void s105(); virtual void s106(); virtual void s107();
	virtual void s108(); virtual void s109(); virtual void s110(); virtual void s111();
	virtual void s112(); virtual void s113(); virtual void s114(); virtual void s115();
	virtual void s116(); virtual void s117(); virtual void s118(); virtual void s119();
	virtual void s120(); virtual void s121(); virtual void s122(); virtual void s123();
	virtual void s124(); virtual void s125();
	virtual void Set_House_Color_Params(const HouseColorParams *params, Int flags);	// +0x1F8
};

class LivingWorldVisual
{
public:
	virtual void setHouseColor(const Int &color);

private:
	unsigned char m_pad04[4];
	RenderObjClass *m_primaryRObj;		// +0x08
};

// LivingWorldVisual::setHouseColor, retail 0x003FB602.
void LivingWorldVisual::setHouseColor(const Int &color)
{
	if (m_primaryRObj)
	{
		HouseColorParams params;
		params.m_mode = 1;
		params.m_color = color;
		params.m_reserved0 = 0;
		params.m_reserved1 = 0;
		m_primaryRObj->Set_House_Color_Params(&params, 0);
	}
}
