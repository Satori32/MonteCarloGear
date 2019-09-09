#include <iostream>
#include <random>

template<class T,class F,class... FArg>
T MonteCarloReActer(const std::size_t N, F Body,FArg&... A) {
	T R(0);

	for (std::size_t i = 0; i < N; i++) {//crazy count is absorve noize.
		T Temp =  Body(A...);
		R += Temp;
	}

	return R / N;
}

int main() {
	std::mt19937 mt;
	std::uniform_real_distribution<> ur(0, 1);
	auto F1 = [&]() {
		std::random_device rd;
		return rd()/(double)rd.max();
	};

	//mt.discard(624*624);

	auto F2 = [&]()->double {
		return mt()/(double)mt.max();
	};

	std::minstd_rand mr;
	
	auto F3 = [&]()->double {//1% noize at 10000count??
		return mr()/(double)mr.max();
	};
	auto R1 = MonteCarloReActer<double>(10000, F2);

	return 0;
}