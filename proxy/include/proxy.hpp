/* Proxy object.
 * @file
 * @date 2018-08-07
 * @author Anonymous
 */

#ifndef __PROXY_HPP__
#define __PROXY_HPP__

#include <mutex>

template<
    typename T>
    class ptr_holder {
    public:
        ptr_holder(T* ptr)
            : m_ptr(ptr)
        {}

        class proxy : private std::lock_guard<std::mutex> {
        public:
            proxy(T* ptr, std::mutex& mutex)
                : std::lock_guard<std::mutex>(mutex)
                , m_ptr(ptr)
            {}

            auto operator->() const {
                return m_ptr;
            }

        private:
            T* m_ptr;
        };

        proxy operator->() const {
            return { m_ptr, m_mutex };
        }

    private:
        mutable std::mutex m_mutex;
        T* m_ptr;
};

#endif // __PROXY_HPP__
