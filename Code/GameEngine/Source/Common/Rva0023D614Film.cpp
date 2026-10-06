// cl: /MD
// ?Rva0023D614Set@@YAXPAV?$StringBase@D@@@Z, retail 0x0023D614, 77 bytes.
// push ebp frame with buf[60], GetGameClientRandomValue clamp sprintf set.
// Evidence: unlock lane; callers push none (this in arg); format StillImage_Film%02d.
template <typename T> class StringBase
{
public:
	void set(const T *str);
};
int GetGameClientRandomValue(int lo, int hi, char *file, int line);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buf, const char *fmt, ...);
void Rva0023D614Set(StringBase<char> *out)
{
	char buf[60];
	unsigned int v = (unsigned int)GetGameClientRandomValue(1, 21, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\GameLogic.cpp", 0x6BB);
	if (v < 1)
		v = 1;
	if (v > 21)
		v = 21;
	sprintf(buf, "StillImage_Film%02d", v);
	out->set(buf);
}
