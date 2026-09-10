// cl: /O2 /Os /arch:SSE /DNDEBUG /MD
//
// normalizeAngle, retail 0x00238954, 75 bytes. SSE comiss loops against
// PI / 2PI then fld the spill for the x87 return.

float normalizeAngle(float a)
{
	while (a > 3.14159274f)
		a -= 6.28318548f;
	while (a <= -3.14159274f)
		a += 6.28318548f;
	return a;
}
