#ifndef __NCRPRAGUE_DEDUP_H__
#define __NCRPRAGUE_DEDUP_H__
/******************************************************************************
*                             Standard Library                                *
******************************************************************************/
#include <sstream>
#include <iostream>
#include <map>
/*****************************************************************************/

/******************************************************************************
*                             Project Library                                 *
******************************************************************************/
#include "Bag.h"
#include "types.h"
/*****************************************************************************/
namespace DEDUP {
    enum  ETYPE {
        INVALID_ARG = 0b1000,
        EMPTY_ARG = 0b1001,
        OORANGE_ARG = 0b1010,
        ERROR_ARG = 0b1000,
        DUP = 0b0001,
        UNIQUE = 0b0010
    };
    std::wostream& operator<<(std::wostream& os, const ETYPE& error) {
        switch (error) {
        case ETYPE::EMPTY_ARG:
            os << "EMPTY_ARG";
            break;
        case ETYPE::INVALID_ARG:
            os << "INVALID_ARG";
            break;
        case ETYPE::OORANGE_ARG:
            os << "OORANGE_ARG";
            break;
        default:
            break;
        }
        return os;
    }
    template<typename Ty>
    class DeDup {
        // DeDup is a library to detect duplicate sets of integer values. 
        // Two sets are considered duplicate when they contain the same number
        // of items and their items are of the same value no matter what 
        // positions they are at.
        // Example:
        //    1, 2, 3 is considered a duplicate of 2, 1, 3
        //    1, 2, 3 is not considered a duplicate of 1, 2, 3, 1
        // Library is required to provide :
        // a) a way to accept a string representing a new set of values
        //    delimited by comma sign �, �(e.g. �1, 2, 3�) and return true / false
        //    if the given set is a duplicate of a set seen before,
        // b) a way to return an information on number of duplicates and 
        //    non - duplicates seen so far,
        // c) a way to list members of the most frequent duplicate group seen so far,
        // d) a way to return human readable report on list of invalid inputs 
        //    seen so far.
    public:
        typedef Ty elem_type;
        DeDup() {}
        /**
        * Comma Seperated Number Parser
        *
        * Parses a comma seperated numbers and converts it to a Bag
        * Whitespaces between the numbers and or delimiters are
        * generally ignored.
        * The input id regected and  is errored out if
        * 1. one or more numbers is prefixed/ suffixed by non-white-space
        *    character(s)
        * 2. If one or numbers are outside the accepted range of the number
        * 3. If the input line is empty or empty between two delimiters, the
        *    input if flagged as empty.
        *
        * @param  A comma seperated list of numbers
        *
        * @return Error code reported while parsing
        */
        ETYPE add(std::wstring inp) {
            
            BAG::Bag<Ty> tokens;
            std::wstringstream ss(inp);
            m_size++;
            ETYPE eState = ETYPE::UNIQUE;
            wchar_t sep = ',';
            if (inp.empty()) {
                eState = ETYPE::EMPTY_ARG;
            }
            for (std::wstring item; std::getline(ss, item, sep);) {
                try {
                    if (!item.empty()) {
                        elem_type val = DEDUP::to_num<elem_type>(item);
                        tokens.add(val);
                    }
                    else {
                        eState = ETYPE::EMPTY_ARG;
                        break;
                    }
                }
                catch (const std::invalid_argument&) {
                    eState = ETYPE::INVALID_ARG;
                    break;
                }
                catch (const std::out_of_range&) {
                    eState = ETYPE::OORANGE_ARG;
                    break;
                }
            }
            if (! (eState & ETYPE::ERROR_ARG)) {
                if (bag.add(tokens)) {
                    eState = ETYPE::DUP;
                }
            }
            else {
                m_errored_recs++;
                m_invalid_records[eState].push_back(inp);
            }
            return eState;
        }
        auto count() {
            return m_size;
        }
        auto countDup() {
            return bag.dupCount();
        }
        auto countUnique() {
            return bag.uniqueCount();
        }
        auto countError() {
            return m_errored_recs;
        }
        auto mostCommon(std::size_t n) {
            return bag.mostCommon(n);
        }
        /**
        * Human Readable Error Report Generator
        *
        * Generated a human redable report displaying all records
        * that has been rejected by the parser. The records are 
        * grouped by parse error code.
        *
        * @return A wide string stream report
        */
        std::wstringstream errorReport() {
            std::wstringstream ss;
            if (m_invalid_records.size() > 0) {
                ss << "Invalid Records" << std::endl;
            }

            for (auto& elem : m_invalid_records) {
                ss << "Error Type: " << elem.first << std::endl;
                for (auto& rec : elem.second) {
                    ss << std::wstring(4, ' ') << rec << std::endl;
                }
            }
            return ss;
        }
        // For Unit Testing we need a report format that can be easily compared.
        /**
        * Machine Readable Error Report Generator
        *
        * For Unit Testing we need a error report format that can be easily compared
        *
        * @return A wide string stream report
        */
        std::wstringstream errorReportMR() {
            std::wstringstream ss;
            for (auto& elem : m_invalid_records) {
                ss << elem.first << ":";
                for (auto& rec : elem.second) {
                    ss << rec << ",";
                }
                ss << ";";
            }
            return ss;
        }
    private:
        BAG::Bag<BAG::Bag<Ty>> bag;
        std::map<ETYPE, std::vector<std::wstring>> m_invalid_records;
        std::size_t m_errored_recs = 0;
        std::size_t m_size = 0;
    };
}
#endif
