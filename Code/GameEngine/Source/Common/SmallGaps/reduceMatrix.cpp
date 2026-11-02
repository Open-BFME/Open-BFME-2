// ?reduceMatrix@@YAXPAY0GF@H@Z
void reduceMatrix(int (*costMatrix)[0x65])
{
	int row;
	int column;
	for (row = 0; row < 0x65; ++row) {
		int lowest = 0x7fffffff;
		for (column = 0; column < 0x65; ++column) {
			if (costMatrix[row][column] < lowest)
				lowest = costMatrix[row][column];
		}
		for (column = 0; column < 0x65; ++column)
			costMatrix[row][column] -= lowest;
	}
	for (column = 0; column < 0x65; ++column) {
		int lowest = 0x7fffffff;
		for (row = 0; row < 0x65; ++row) {
			if (costMatrix[row][column] < lowest)
				lowest = costMatrix[row][column];
		}
		if (lowest) {
			for (row = 0; row < 0x65; ++row)
				costMatrix[row][column] -= lowest;
		}
	}
}
