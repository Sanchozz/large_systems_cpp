#include <array>
#include <iostream>


template <int N>
constexpr int det(const std::array<std::array<int, N>, N>& a)
{
    int determinant = 0;

    for (int k = 0; k < N; ++k){
        std::array<std::array<int, N - 1>, N - 1> minor{};
        for (int i = 0; i < N - 1; ++i) {
            for (int j = 0; j < N - 1; ++j) {
                (&std::get<0>(((&std::get<0>(minor))[i])))[j] = a[i + 1][j + (j >= k)];
            }
        }

        determinant += (k % 2 ? -1 : 1) * a[0][k] * det<N - 1>(minor);
    }

    return determinant;
}

template<>
constexpr int det<1>(const std::array<std::array<int, 1>, 1>& a)
{
    return a[0][0];
}


int main()
{   
    constexpr std::array<std::array<int, 3>, 3> A = {{
        {0, 1, 2},
        {1, 2, 3},
        {2, 3, 7}
    }};

    constexpr std::array<std::array<int, 4>, 4> B = {{
        {3, 1, 1, 2},
        {3, 5, 7, 13},
        {21, 34, 55, 88},
        {144, 133, 377, 610}
    }};

    constexpr int res = det<3>(A);
    std::cout << res << std::endl;
}