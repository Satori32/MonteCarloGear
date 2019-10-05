#include <iostream>
#include <random>
#include <cstdint>
#include <algorithm>

template<class T, class F, class... FArg>
T MonteCarloReActer(const std::uintmax_t N, F Body, FArg& ... A) {
	T R(0);

	for (std::uintmax_t i = 0; i < N; i++) {//crazy count is absorve noize.
		T Temp = Body(A...);
		R += Temp;
	}

	return R / N;
}
template<class T, class Fun, class... FArg>
T MonteCarloEnCounter(std::intmax_t F, std::intmax_t E, Fun Body, FArg& ... A) {
	if (F > E) {
		std::swap(F, E);
	}
	T R(0);

	for (std::intmax_t i = F; i < E; i++) {//crazy count is absorve noize.
		T Temp = Body(i, A...);
		R += Temp;
	}

	return R / std::abs(E-F);
}
int main() {
	std::mt19937 mt;
	std::uniform_real_distribution<> ur(0, 1);
	auto F1 = [&]() {
		std::random_device rd;
		return rd() / (double)rd.max();
	};

	//mt.discard(624*624);

	auto F2 = [&]()->double {
		return mt() / (double)mt.max();
	};

	std::minstd_rand mr;

	auto F3 = [&]()->double {//1% noize at 10000count??
		return mr() / (double)mr.max();
	};
	//auto R1 = MonteCarloReActer<double>(10000, F2);

	auto F4 = [&](auto& o){
		std::cout << o << std::endl;
		return o;
	};
	auto R2 = MonteCarloEnCounter<double>(0, 16, F4);

	return 0;
}