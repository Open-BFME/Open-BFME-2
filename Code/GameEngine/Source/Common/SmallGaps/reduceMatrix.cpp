// ?reduceMatrix@@YAXPAY0GF@H@Z
void reduceMatrix(int (*costMatrix)[0x65])
{
	int r;
	int c;
	for (r = 0; r < 0x65; ++r) {
		int lowest = 0x7fffffff;
		for (c = 0; c < 0x65; ++c) {
			if (costMatrix[r][c] < lowest)
				lowest = costMatrix[r][c];
		}
		for (c = 0; c < 0x65; ++c)
			costMatrix[r][c] -= lowest;
	}
	for (c = 0; c < 0x65; ++c) {
		int lowest = 0x7fffffff;
		for (r = 0; r < 0x65; ++r) {
			if (costMatrix[r][c] < lowest)
				lowest = costMatrix[r][c];
		}
		if (lowest) {
			for (r = 0; r < 0x65; ++r)
				costMatrix[r][c] -= lowest;
		}
	}
}
