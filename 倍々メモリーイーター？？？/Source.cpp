#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>

//Memory Exproder Enc/Dec.

typedef std::vector<std::uint8_t> DType;

DType MemoryExproderEnc(const DType& D) {
	DType R;
	for (auto& o: D) {
		for (std::size_t i = 0; i < std::numeric_limits<DType::value_type>::digits; i++) {
			R.push_back((o & (1 << i)) ? 1 : 0);
		}
	}
	return R;
}
DType MemoryExproderDec(const DType& D) {
	DType R;
	std::size_t L = std::numeric_limits<DType::value_type>::digits;
	std::size_t i = 0;
	DType::value_type N = 0;
	for (auto& o : D) {
		N |= (o << i);
		i++;
		if (i == L) {
			R.push_back(N);
			N = 0;
		}
		i %= L;
	}
	return R;
}

DType MakeVector(std::size_t N) {
	DType R;
	for (std::size_t i = 0; i < N; i++) {
		R.push_back(i);
	}

	return R;
}


int main() {
	auto D = MakeVector(16);
	auto X = MemoryExproderEnc(D);
	auto Y = MemoryExproderDec(X);

	if (D == Y) {
		std::cout << "True" << std::endl;
	}
	else {
		std::cout << "False" << std::endl;
	}

	return 0;
}