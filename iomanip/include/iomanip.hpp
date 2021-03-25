/* Custom manipulators.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */

#ifndef __IOMANIP_HPP__
#define __IOMANIP_HPP__

#include <ostream>

 //{ endm manipulator

template <class charT, class traits>
std::ostream& endm(std::basic_ostream<charT, traits>& os) {
    return os << "[eol]\n";
}

//}


//{ squares manipulator

class SquaresContainer {
private:
    std::ostream* m_os;

public:
    SquaresContainer(std::ostream* os)
        : m_os(os)
    {}

    template<typename T>
    std::ostream& operator<<(const T& str) {
        return ((*m_os) << '[' << str << ']');
    }
};

struct Square {
    friend auto operator<<(std::ostream& os, Square) {
        return SquaresContainer(&os);
    }
};

const Square squares;
//}


//{ add manipulator

template<typename T>
class AddContainerSecond {
private:
    std::ostream* m_os;
    T             m_s1;

public:
    AddContainerSecond(std::ostream* os, const T& s1)
        : m_os(os)
        , m_s1(s1)
    {}

    std::ostream& operator<<(const T& s2) {
        return (*m_os) << m_s1 + s2;
    }
};

class AddContainerFirst {
private:
    std::ostream* m_os;

public:
    AddContainerFirst(std::ostream* os)
        : m_os(os)
    {}

    template<typename T>
    friend decltype(auto) operator<<(AddContainerFirst f1, const T& s1) {
        return AddContainerSecond(f1.m_os, s1);
    }
};

struct Add {
    friend decltype(auto) operator<<(std::ostream& os, Add) {
        return AddContainerFirst(&os);
    }
};

const Add add;

//}

#endif // __IOMANIP_HPP__
