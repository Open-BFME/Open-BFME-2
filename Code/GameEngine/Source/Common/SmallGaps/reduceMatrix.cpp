// ?reduceMatrix@@YAXPAY0GF@H@Z
void reduceMatrix(int (*m)[0x65])
{
	int r;
	int c;
	for (r = 0; r < 0x65; ++r) {
		int lowest = 0x7fffffff;
		for (c = 0; c < 0x65; ++c) {
			if (m[r][c] < lowest)
				lowest = m[r][c];
		}
		for (c = 0; c < 0x65; ++c)
			m[r][c] -= lowest;
	}
	for (c = 0; c < 0x65; ++c) {
		int lowest = 0x7fffffff;
		for (r = 0; r < 0x65; ++r) {
			if (m[r][c] < lowest)
				lowest = m[r][c];
		}
		if (lowest) {
			for (r = 0; r < 0x65; ++r)
				m[r][c] -= lowest;
		}
	}
}
