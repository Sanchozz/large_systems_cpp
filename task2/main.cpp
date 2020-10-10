#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <tuple>
#include <sstream>

struct Printer {
public:
    std::string str() const {
        return buffer.str();
    }

    // tuple printer
    template<std::size_t...> struct seq{};

    template<std::size_t N, std::size_t... Is>
    struct gen_seq : gen_seq<N-1, N-1, Is...>{};

    template<std::size_t... Is>
    struct gen_seq<0, Is...> : seq<Is...>{};

    template<class Tuple, std::size_t... Is>
    void tuple_printer(const Tuple &t, seq<Is...>) {
        int tuple_iterator[] = {0, (buffer << (Is == 0? "" : ", "), format(std::get<Is>(t)), 42)...};
        (void)tuple_iterator;
    }

    // vector printer
    template<typename T> 
    Printer& format(const std::vector<T> &v) {
        buffer << "[ ";
        format_iterable(v);
        buffer << " ]";
        return *this;
    }

    // set printer
    template<typename T> 
    Printer& format(const std::set<T> &s) {
        buffer << "{ ";
        format_iterable(s);
        buffer << " }";
        return *this;
    }

    // pair printer
    template<typename T1, typename T2> 
    Printer& format(const std::pair<T1, T2> &p) {
        buffer << "(";
        format(p.first);
        buffer << ", ";
        format(p.second);
        buffer << ")";
        return *this;
    }

    // tuple printer
    template<typename ...Args> 
    Printer& format(const std::tuple<Args...> &t) {
        buffer << "( ";
        tuple_printer(t, gen_seq<sizeof...(Args)>());
        buffer << " )";
        return *this;
    }

    // default printer
    template<typename T>
    Printer& format(const T& element) {
        buffer << element;
        return *this;
    }
    
private:
    // iterable containter printer (set and vector in this case)
    template<typename T>
    void format_iterable(T& container) {
        auto begin_it = container.begin();
        auto end_it = container.end();

        if (begin_it != end_it) {
            format(*begin_it++);
        }

        while (begin_it != end_it) {
            buffer << ", ";
            format(*begin_it++);
        }
    }
    
private:
    std::stringstream buffer;
};


template<typename T>
std::string format(const T& t) {
    return Printer().format(t).str();
}


int main()
{
    std::tuple<std::string, int, int> t = {"xyz", 1, 2};
    std::vector<std::pair<int, int> > v = {{1, 4}, {5, 6}};
    std::cout << Printer().format(" vector: ").format(v).str() << std::endl;
    std::cout << Printer().format(t).format(" ! ").format(0).str() << std::endl;
}