#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <format>
#include <cmath>


std::vector<unsigned int> collect() {
    std::vector<unsigned int> v{};

    unsigned int xn_;
    do {
        std::cin >> xn_;
        v.push_back(xn_);
    } while (xn_ != 0);

    v.pop_back();
    return v;
}


int main() {
    auto v = collect();
    auto s = std::reduce(v.begin(), v.end()) / (long double) v.size();

    auto fn = [&](auto &el) {
        return std::pow(el - s, 2);
    };

    std::vector<long double> sig_v{};
    std::transform(v.begin(), v.end(), std::back_inserter(sig_v), fn);

    auto sigma = std::sqrt(std::reduce(sig_v.begin(), sig_v.end()) / (v.size() - 1));
    std::cout << std::format("{}", sigma) << std::endl;

    return 0;
}