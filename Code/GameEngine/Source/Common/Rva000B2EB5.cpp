// cl: /DNDEBUG /MD
// ?rva000B2EB5@Rva000B2EB5@@QAEMXZ 0x000B2EB5 131B evidence: iface at +0x50 slot3 int vs 0x19 slot0x208 4-outparam then x87 neg check vs BfmeZeroRange SSE int-float compare vs g_Va00BBB8D8 div path else g_00BBB9AC; neighbours 0x000B2D4D/0x000B2F38 same dir
extern const float BfmeZeroRange;
extern float g_Va00BBB8D8;
extern float g_00BBB9AC;

class Iface000B2EB5
{
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual int s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual void s100();
	virtual void s101();
	virtual void s102();
	virtual void s103();
	virtual void s104();
	virtual void s105();
	virtual void s106();
	virtual void s107();
	virtual void s108();
	virtual void s109();
	virtual void s110();
	virtual void s111();
	virtual void s112();
	virtual void s113();
	virtual void s114();
	virtual void s115();
	virtual void s116();
	virtual void s117();
	virtual void s118();
	virtual void s119();
	virtual void s120();
	virtual void s121();
	virtual void s122();
	virtual void s123();
	virtual void s124();
	virtual void s125();
	virtual void s126();
	virtual void s127();
	virtual void s128();
	virtual void s129();
	virtual void s130(float *a, int *b, int *c, int *d);
};

class Rva000B2EB5
{
	char _p0[0x18];
	int m_x18;
	char _p1[0x50 - 0x18 - 4];
	Iface000B2EB5 *m_ptr;
public:
	float rva000B2EB5();
};

float Rva000B2EB5::rva000B2EB5()
{
	if (!m_x18 || !m_ptr)
		return g_00BBB9AC;
	if (m_ptr->s003() != 0x19)
		return g_00BBB9AC;
	float f;
	int n;
	int u1;
	int u2;
	m_ptr->s130(&f, &n, &u1, &u2);
	if (f < 0.0)
		return BfmeZeroRange;
	float fn = (float)n;
	if (f >= fn)
		return g_Va00BBB8D8;
	return f / (fn - g_Va00BBB8D8);
}

// ?g_00BBB9AC@@3MA: matched references place it at VA 0xbbb9ac; also referenced as ?g_00BBB9AC@@3MB.
float g_00BBB9AC = -1.0f;
#pragma comment(linker, "/alternatename:?g_00BBB9AC@@3MB=?g_00BBB9AC@@3MA")
