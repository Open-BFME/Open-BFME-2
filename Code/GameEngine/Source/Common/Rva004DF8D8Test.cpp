// cl: /MD
// ?Rva004DF8D8Test@@YA_NPBUVec2@@00MMMM@Z @0x004DF8D8 133B
// Evidence: EBP-frame SSE comiss/divss/mulss shape; 3 Vec2 ptrs + 4 floats; dot/cross/sum-squared test; caller at 0x0028F38A.
struct Vec2
{
	float x;
	float y;
};
bool __cdecl Rva004DF8D8Test(const Vec2 *a, const Vec2 *b, const Vec2 *dir, float f1, float f2, float f3, float f4)
{
	float dx = a->x - b->x;
	float dy = a->y - b->y;
	float dot = dir->x * dx + dy * dir->y;
	float cross = dx * dir->y - dir->x * dy;
	cross /= f2;
	if (dot < 0.0f)
		dot /= f3;
	float sum = f1 + f4;
	float tot = cross * cross + dot * dot;
	float ss = sum * sum;
	if (tot < ss)
		return true;
	return false;
}
