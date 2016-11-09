#ifndef __NCRPRAGUE_BAG_H__
#define __NCRPRAGUE_BAG_H__
/******************************************************************************
*                             Standard Library                                *
******************************************************************************/
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <iostream>
#include <functional>
#include <initializer_list>
/*****************************************************************************/
namespace BAG {
    template<typename Ty>
    class Bag : public std::map<Ty, std::size_t> {
        // Bag is an unordered collection of objects with memory i.e. duplicate
        // objects are reported with occurance count. Bag subclasses std::dict,
        // so Bag is still a dict except that, the occurance count is stored
        // as values
        // References:
        //   http ://en.wikipedia.org/wiki/Multiset
        //   http ://www.gnu.org/software/smalltalk/manual-base/html_node/Bag.html
        //   Knuth, TAOCP Vol.II section 4.6.3
        // Order of Complexity O(log(n))
    public:
        typedef Ty elem_type;
        typedef std::map<elem_type, std::size_t> bag_type;
        typedef std::pair<typename bag_type::key_type, typename bag_type::mapped_type> pair_type;
        template<typename TyF>
        friend std::wostream& operator<<(std::wostream& os, const Bag& bag);
        Bag() {}
        /**
        * Constructor that sets Bag from a collection
        *
        *
        * @param  Initialization list
        */
        Bag(std::initializer_list<elem_type>& il) {
            for (auto& elem : il) {
                (*this) += elem;
            }
        }
        /**
        * Constructor that sets Bag from a an iterator
        *
        *
        * @param  Start Iterator
        * @param  Stop Iterator
        */
        template<typename Iter>
        Bag(const Iter& begin, const  Iter& end) {
            for (auto& it = begin; it != end; it++) {
                (*this) += *it;
            }
        }
        /**
        * Adds an elements in the Bag
        *
        *
        * @param  Element
        * @return Boolean flag which determines if the entry added is a duplicate or unique
        *         where true is unique and false is duplicate
        */
        bool add(const elem_type& elem) {
            (*this)[elem] += 1;
            if ((*this)[elem] > 1) {
                m_dupCount++;
                return false;
            }
            return true;
        }
        /**
        * Compare two Bags
        *
        *
        * @param  Constant Reference to Bag
        * @return Boolean indicating whether two bags are equal or not
        */
        bool operator==(const Bag& rhs) {
            return std::all_of(
                std::begin(*this),
                std::end(*this),
                [](const pair_type& lhs, const pair_type& rhs) {
                return lhs.first == rhs.first && lhs.second == rhs.second;
            });
        }
        /**
        * Returns number of duplicates
        *
        */
        std::size_t dupCount() {
            return m_dupCount;
        }
        /**
        * Returns number of unique
        *
        */
        std::size_t uniqueCount() {
            return std::map<Ty, std::size_t>::size();
        }
        /**
        * Emulates Bag.sortedByCount from Smalltalk
        *
        * reports at most n most common elements and their counts from the most
        * common to the least. Elements ordered by occurance count. If, two or 
        * more elements have the same occurance, the results are unordered
        *
        * @param  A number indicating no of elements to return
        * @return A vector of pair of most common elemenet and occurance count
        */
        auto mostCommon(std::size_t n) {
            std::vector<pair_type> stk;
            auto comp = [](const pair_type& lhs, const pair_type& rhs) {
                return lhs.second < rhs.second;
            };
            typedef std::priority_queue <
                pair_type,
                std::vector < pair_type >,
                decltype(comp)> heapq;
            heapq heap(
                std::begin(*this),
                std::end(*this),
                comp);
            for (size_t i = 0; i < n && heap.size(); i++, heap.pop()) {
                stk.push_back(heap.top());
            }
            return stk;
        }
    private:
        std::size_t m_dupCount = 0;
    };
    template<typename TyF>
    std::wostream& operator<<(std::wostream& os, const Bag<TyF>& bag) {
        for (auto it = std::cbegin(bag); it != std::cend(bag); it++) {

            if (!std::is_fundamental<decltype(it->first)>::value) {
                os << it->first << ": " << it->second;
            }
            else {
                for (std::size_t i = 0; i < it->second; i++) {
                    os << std::to_wstring(it->first);
                    if (it->second - i > 1) {
                        os << ", ";
                    }
                }
            }
            if (std::distance(it, std::end(bag)) > 1) {
                os << ", ";
            }
        }
        if (!std::is_fundamental<decltype(std::begin(bag)->first)>::value) {
            os << std::endl;
        }
        return os;
    }
}

#endif
