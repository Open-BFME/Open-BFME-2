// cl: /O1 /MD
// The process-fatal error path terminates with exit status 1.
extern "C" __declspec(dllimport) __declspec(noreturn)
void __cdecl exit(int exitCode);

void ErrorExit()
{
	exit(1);
}
