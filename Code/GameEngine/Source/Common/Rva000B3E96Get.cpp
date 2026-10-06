// cl: /DNDEBUG /MD
// ?Rva000B3E96Get@@YGHH@Z retail 0x000B3E96 29B
// Wrapper over rowed GetGameClientRandomValue 0x0023404A: return
// GetGameClientRandomValue(0 arg-1 file 0x28F8). Evidence: mov eax-esp+4
// push 0x28f8 push 0xBC9C40 dec eax push eax push 0 E8 then add esp-0x10
// ret 4; callee YAHHHPADH int-int-char*-int; caller 0x000BF5DC.
int __stdcall Rva000B3E96Get(int n);
int GetGameClientRandomValue(int lo, int hi, char *file, int line);
int __stdcall Rva000B3E96Get(int n)
{
	return GetGameClientRandomValue(0, n - 1, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp", 0x28F8);
}
