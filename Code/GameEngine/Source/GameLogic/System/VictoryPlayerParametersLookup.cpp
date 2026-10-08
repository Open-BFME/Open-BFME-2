// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BF1 ba7ddda BfmeCellGrid.cpp and VictorySystem family semantic leads.
// Native 404C26..404C60, WB1076A20: player indices +28, vector +120,
// stride24 and sign-bit mask. Retain the already-pinned address-derived name.
// The typed STLport vector size/accessors reproduce both native begin reloads;
// the previous raw-pointer bank retained begin in EDI and did not match.
#include <vector>
class Rva00404781;
class Rva00404927
{
public:
	int rva00404927(Rva00404781 *, int);
private:
	char data[24];
};
// The 24-byte parameter record is established by the existing 404927 consumer
// and the native faction parameter table. Its application class name is unknown.
class Rva00404C26
{
public:
	Rva00404927 *rva00404C26(int player);
private:
	char unknown00[0x28];
	unsigned playerParameters[62];
	_STL::vector<Rva00404927> parameters;
};

Rva00404927 *Rva00404C26::rva00404C26(int player)
{
	unsigned index = playerParameters[player] & 0x7fffffff;
	if (index < parameters.size())
	 return &parameters[index];
	return 0;
}
