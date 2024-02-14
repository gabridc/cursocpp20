#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <concepts>
#include <algorithm>
#include <assert.h>
 
namespace rg = std::ranges;
 
template<rg::input_range R> requires rg::view<R>
class custom_take_view : public rg::view_interface<custom_take_view<R>>
{
private:
    R                                         base_ {};
    std::iter_difference_t<rg::iterator_t<R>> count_ {};
    rg::iterator_t<R>                         iter_ {std::begin(base_)};
public:
    custom_take_view() = default;
    
    custom_take_view(R base, std::iter_difference_t<rg::iterator_t<R>> count)
        : base_(base)
        , count_(count)
        , iter_(std::begin(base_))
    {}
    
    R base() const &
    {return base_;}
    R base() && 
    {return std::move(base_);}
    
    auto begin() const
    {return iter_;}
    auto end() const
    { 
        return std::next(iter_, count_); 
    }
    
    auto size() const requires rg::sized_range<const R>
    { 
        const auto s = rg::size(base_);
        const auto c = static_cast<decltype(s)>(count_);
        return s < c ? 0 : s - c;    
    }
};
 
template<class R>
custom_take_view(R&& base, std::iter_difference_t<rg::iterator_t<R>>)
    -> custom_take_view<rg::views::all_t<R>>;
 
namespace details
{
    struct custom_take_range_adaptor_closure
    {
        std::size_t count_;
        custom_take_range_adaptor_closure(std::size_t count): count_(count)
        {}
 
        template <rg::viewable_range R>
        auto operator()(R && r) const
        {
            return custom_take_view(std::forward<R>(r), count_);
        }
    } ;
 
    struct custom_take_range_adaptor
    {
        template<rg::viewable_range R>
        auto operator () (R && r, std::iter_difference_t<rg::iterator_t<R>> count)
        {
            return custom_take_view( std::forward<R>(r), count ) ;
        }
 
        auto operator () (std::size_t count)
        {
            return custom_take_range_adaptor_closure(count);
        }   
    };
 
    template <rg::viewable_range R>
    auto operator | (R&& r, custom_take_range_adaptor_closure const & a)
    {
        return a(std::forward<R>(r)) ;
    }
}
 
namespace views
{
    details::custom_take_range_adaptor custom_take;
}

namespace rv = std::ranges::views;
int main()
{
    auto is_even = [](int const n) {return n % 2 == 0;};
    
    std::vector<int> n{1,1,2,3,5,8,13,21,34,55,89,144,233,377};
    auto v = n | rv::filter(is_even) | rv::reverse | views::custom_take(2) ;
    std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
}