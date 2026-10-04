// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
class BfmeArg985
{
public:
	char bfmeHas985C(int v);
	char bfmeBlocked985C(int v);
};

class BfmeC985
{
public:
	char bfmeGo985C(BfmeArg985 *a);

	char m_bfmePad[8];
	int m_bfmeVal;
};

char BfmeC985::bfmeGo985C(BfmeArg985 *a)
{
	if (a->bfmeHas985C(m_bfmeVal) && !a->bfmeBlocked985C(m_bfmeVal))
		return 1;

	return 0;
}
