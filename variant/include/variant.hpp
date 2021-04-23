/* Variant classes.
 * @file
 * @date 2018-08-12
 * @author Anonymous
 */

#ifndef __VARIANT_HPP__
#define __VARIANT_HPP__

#include <map>
#include <memory>
#include <variant>
#include <vector>
#include <type_traits>

#include <boost/variant.hpp>

struct number
    : public std::variant<
    int,
    float
    > {
    using variant::variant;
};

struct array
    : public std::vector<
    number
    > {
    using vector::vector;
};

struct recursive_array
    : public std::vector<
    std::variant<
    number,
    std::shared_ptr<recursive_array>
    >
    > {
    using vector::vector;
};

struct recursive_array2
    : public std::vector<
    std::variant<
    number,
    boost::recursive_wrapper<recursive_array2>
    >
    > {
    using vector::vector;
};

template<typename... variant_types_pack>
struct variant_decorator
    : public std::variant<variant_types_pack...> {
    using std::variant<variant_types_pack...>::variant;

    template<typename T>
    decltype(auto) as() {
        if constexpr (std::disjunction_v<
            std::is_same<
            boost::recursive_wrapper<T>, variant_types_pack
            >...
        >) {
            return std::get<boost::recursive_wrapper<T>>(*this).get();
        }
        else {
            return std::get<T>(*this);
        }
    }

    template<typename T>
    decltype(auto) as() const {
        if constexpr (std::disjunction_v<
            std::is_same<
            boost::recursive_wrapper<T>, variant_types_pack
            >...
        >) {
            return std::get<boost::recursive_wrapper<T>>(*this).get();
        }
        else {
            return std::get<T>(*this);
        }
    }
};

struct recursive_map : public std::map<
    std::string,
    variant_decorator<
    int,
    std::string,
    boost::recursive_wrapper<recursive_map>,
    bool
    >
> {
    using map::map;
};

#endif // __VARIANT_HPP__
