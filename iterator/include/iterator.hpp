/* Image iterator.
 * @file
 * @date 2018-08-05
 * @author Anonymous
 */

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <algorithm>
#include <type_traits>
#include <vector>
#include <utility>

#include <boost/iterator/iterator_adaptor.hpp>

template< typename Container = std::vector<uint8_t> >
class image {
public:
    template< typename Iterator >
    class image_iterator
        : public boost::iterator_adaptor<
        image_iterator<Iterator>,
        Iterator
        > {
    public:
        using TAdapter = boost::iterator_adaptor<image_iterator<Iterator>, Iterator>;

        image_iterator(Iterator    it,
            std::size_t w,
            std::size_t st,
            std::size_t shift = 0,
            std::size_t cur_h = 0
        )
            : TAdapter(it)
            , m_width(w)
            , m_stride(st)
            , m_trash(st - w)
            , m_shift(shift)
            , m_current_height(cur_h)
        {}

        void increment() {
            if (m_shift < m_width - 1) {
                ++m_shift;
                ++this->base_reference();
            }
            else {
                m_shift = 0;
                ++m_current_height;
                this->base_reference() += (m_trash + 1);
            }
        }

        void decrement() {
            if (m_shift > 0) {
                --m_shift;
                --this->base_reference();
            }
            else {
                m_shift = m_width - 1;
                --m_current_height;
                this->base_reference() -= (m_trash + 1);
            }
        }

        void advance(const typename TAdapter::difference_type n) {
            if (n > 0) {
                for (std::size_t i = 0; i < static_cast<std::size_t>(n); ++i) {
                    increment();
                }
            }
            else {
                for (std::size_t i = 0; i < static_cast<std::size_t>(-n); ++i) {
                    decrement();
                }
            }
        }

        typename TAdapter::difference_type distance_to(const image_iterator& it) const {
            return (it.m_current_height - m_current_height) * m_width + (it.m_shift - m_shift);
        }

    private:
        std::size_t m_width;
        std::size_t m_stride;
        std::size_t m_trash;
        std::size_t m_shift;
        std::size_t m_current_height;
    };

    image(std::size_t width, std::size_t height, std::size_t stride)
        : m_data(stride* height)
        , m_width(width)
        , m_stride(stride)
    {}

    auto begin() {
        return image_iterator(m_data.begin(), m_width, m_stride);
    }

    auto end() {
        return image_iterator(m_data.end(), m_width, m_stride, 0, m_data.size() / m_stride);
    }

    auto begin() const {
        return image_iterator(m_data.begin(), m_width, m_stride);
    }

    auto end() const {
        return image_iterator(m_data.end(), m_width, m_stride, 0, m_data.size() / m_stride);
    }

private:
    Container   m_data;    // image data including strides. Access by (x, y): data[y * m_stride + x]
    std::size_t m_width;
    std::size_t m_stride;
};

#endif // __ITERATOR_HPP__

