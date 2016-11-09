#ifndef __NCRPRAGUE_TYPES_H__
#define __NCRPRAGUE_TYPES_H__
/******************************************************************************
*                             Standard Library                                *
******************************************************************************/
#include <string>
#include <cctype>
#include <stdexcept>
/*****************************************************************************/
namespace DEDUP {
    template<typename TyN>
    TyN to_num(std::wstring strNum) {}
    template<>
    int to_num<int>(std::wstring strNum) {
        std::size_t pos;
        auto val = std::stoi(strNum, &pos);
        for (std::size_t i = pos; i < strNum.size(); i++) {
            if (!std::isspace(strNum[i])) {
                throw std::invalid_argument("Non Space character after number");
            }
        }
        return val;
    }
    template<>
    long to_num<long>(std::wstring strNum) {
        std::size_t pos;
        auto val = std::stol(strNum, &pos);
        for (std::size_t i = pos; i < strNum.size(); i++) {
            if (!std::isspace(strNum[i])) {
                throw std::invalid_argument(nullptr);
            }
        }
        return val;
    }
    template<>
    unsigned long to_num<unsigned long>(std::wstring strNum) {
        std::size_t pos;
        auto val = std::stoul(strNum, &pos);
        for (std::size_t i = pos; i < strNum.size(); i++) {
            if (!std::isspace(strNum[i])) {
                throw std::invalid_argument(nullptr);
            }
        }
        return val;
    }
    template<>
    long long to_num<long long>(std::wstring strNum) {
        std::size_t pos;
        auto val = std::stoll(strNum, &pos);
        for (std::size_t i = pos; i < strNum.size(); i++) {
            if (!std::isspace(strNum[i])) {
                throw std::invalid_argument(nullptr);
            }
        }
        return val;
    }
    template<>
    unsigned long long to_num<unsigned long long>(std::wstring strNum) {
        std::size_t pos;
        auto val = std::stoull(strNum, &pos);
        for (std::size_t i = pos; i < strNum.size(); i++) {
            if (!std::isspace(strNum[i])) {
                throw std::invalid_argument(nullptr);
            }
        }
        return val;
    }
    template<>
    float to_num<float>(std::wstring strNum) {
        std::size_t pos;
        auto val = std::stof(strNum, &pos);
        for (std::size_t i = pos; i < strNum.size(); i++) {
            if (!std::isspace(strNum[i])) {
                throw std::invalid_argument(nullptr);
            }
        }
        return val;
    }
    template<>
    double to_num<double>(std::wstring strNum) {
        std::size_t pos;
        auto val = std::stod(strNum, &pos);
        for (std::size_t i = pos; i < strNum.size(); i++) {
            if (!std::isspace(strNum[i])) {
                throw std::invalid_argument(nullptr);
            }
        }
        return val;
    }
    template<>
    long double to_num<long double>(std::wstring strNum) {
        std::size_t pos;
        auto val = std::stold(strNum, &pos);
        for (std::size_t i = pos; i < strNum.size(); i++) {
            if (!std::isspace(strNum[i])) {
                throw std::invalid_argument(nullptr);
            }
        }
        return val;
    }

}
#endif

