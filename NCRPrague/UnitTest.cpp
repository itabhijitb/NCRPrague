#include "DeDup.h"
#include <sstream>
#include <fstream>
#if(1)
#define BOOST_TEST_MODULE UnitTest
#include <boost/test/unit_test.hpp>
namespace utf = boost::unit_test;
BOOST_AUTO_TEST_SUITE(DeDupTestSuite, * utf::enabled())
    BOOST_AUTO_TEST_CASE(SanityTest)
    {
            DEDUP::DeDup<int> dedup;
            BOOST_TEST((dedup.add(L"1,2,3,4") & DEDUP::ERROR_ARG) == 0);
            BOOST_TEST((dedup.add(L"1,2,2,1") & DEDUP::ERROR_ARG) == 0);
            BOOST_TEST((dedup.add(L"4,3,2,1") & DEDUP::ERROR_ARG) == 0);
            BOOST_TEST((dedup.add(L"2,2,1,1") & DEDUP::ERROR_ARG) == 0);;
            BOOST_TEST((dedup.add(L"2,2,1,1,1") & DEDUP::ERROR_ARG) == 0);;
            BOOST_TEST(dedup.countDup() == 2);
            BOOST_TEST(dedup.countUnique() == 3);
            std::wstring result = [&]() {
                    std::wstringstream ss;
                    for (auto& rec : dedup.mostCommon(4)) {
                            ss << rec.first << ":" << rec.second << "; ";
                    }
                    return ss.str();
            }();
            BOOST_TEST((result == L"1, 1, 2, 2:2; 1, 2, 3, 4:2; 1, 1, 1, 2, 2:1; ") == true);
    }
    BOOST_AUTO_TEST_CASE(EdgeCaseSpuriousSpacesInp)
    {
            DEDUP::DeDup<int> dedup;
            BOOST_TEST((dedup.add(L"1, 2,3,4") & DEDUP::ERROR_ARG) == 0);
            BOOST_TEST((dedup.add(L"1  , 2,   2 ,1") & DEDUP::ERROR_ARG) == 0);
            BOOST_TEST((dedup.add(L"   4,  3,2,1        ") & DEDUP::ERROR_ARG) == 0);
            BOOST_TEST((dedup.add(L"2 , 2 , 1 , 1") & DEDUP::ERROR_ARG) == 0);
            BOOST_TEST((dedup.add(L"   2,2,1,1,1    ") & DEDUP::ERROR_ARG) == 0);
            BOOST_TEST(dedup.countDup() == 2);
            BOOST_TEST(dedup.countUnique() == 3);
            std::wstring result = [&]() {
                    std::wstringstream ss;
                    for (auto& rec : dedup.mostCommon(4)) {
                            ss << rec.first << ":" << rec.second << "; ";
                    }
                    return ss.str();
            }();
            BOOST_TEST((result == L"1, 1, 2, 2:2; 1, 2, 3, 4:2; 1, 1, 1, 2, 2:1; ") == true);
    }
    BOOST_AUTO_TEST_CASE(EdgeCaseInvalidInp)
    {
            DEDUP::DeDup<int> dedup;
            BOOST_TEST((dedup.add(L"50 41 87 95") & DEDUP::ERROR_ARG) != 0);
            BOOST_TEST((dedup.add(L"1,#2,3,4") & DEDUP::ERROR_ARG) != 0);
            BOOST_TEST((dedup.add(L"1,2,2.2,1") & DEDUP::ERROR_ARG) != 0);
            BOOST_TEST((dedup.add(L"4,3,222222222222,1") & DEDUP::ERROR_ARG) != 0);
            BOOST_TEST((dedup.add(L"2,-2,1,1") & DEDUP::ERROR_ARG) == 0);
            BOOST_TEST((dedup.add(L"2,2,1,1,1") & DEDUP::ERROR_ARG) == 0);
            BOOST_TEST(dedup.countDup() == 0);
            BOOST_TEST(dedup.countUnique() == 2);
            std::wstring result = [&]() {
                    std::wstringstream ss;
                    for (auto& rec : dedup.mostCommon(4)) {
                            ss << rec.first << ":" << rec.second << "; ";
                    }
                    return ss.str();
            }();
            BOOST_TEST((result == L"1, 1, 1, 2, 2:1; -2, 1, 1, 2:1; ") == true);
            auto error = dedup.errorReportMR().str();
            BOOST_TEST((error == L"INVALID_ARG:50 41 87 95,1,#2,3,4,1,2,2.2,1,;OORANGE_ARG:4,3,222222222222,1,;") == true);
    }
    BOOST_AUTO_TEST_CASE(EdgeCaseEmptyArg)
    {
            DEDUP::DeDup<int> dedup;
            BOOST_TEST((dedup.add(L"") & DEDUP::ERROR_ARG) != 0);

            std::wstring result = [&]() {
                    std::wstringstream ss;
                    for (auto& rec : dedup.mostCommon(4)) {
                            ss << rec.first << ":" << rec.second << "; ";
                    }
                    return ss.str();
            }();
            BOOST_TEST((result == L"") == true);    
            auto error = dedup.errorReportMR().str(); 
            BOOST_TEST((error == L"EMPTY_ARG:,;") == true);
    }
    BOOST_AUTO_TEST_CASE(TestInpFile, * utf::enabled())
    {
            DEDUP::DeDup<int> dedup;
            std::wifstream input("input.txt", std::ios::binary);

            for (std::wstring line; getline(input, line); )
            {
                dedup.add(line);
            }
            std::wstring result = [&]() {
                    std::wstringstream ss;
                    for (auto& rec : dedup.mostCommon(4)) {
                            ss << rec.first << ":" << rec.second << "; ";
                    }
                    return ss.str();
            }();
            BOOST_TEST(dedup.countDup() == 475);
            BOOST_TEST(dedup.countUnique() == 26);
            BOOST_TEST(dedup.countError() == 6);
            BOOST_TEST(dedup.count() == 507);
            BOOST_TEST((result == L"3, 5, 11, 23, 24, 88, 189:29; 1, 1, 15, 27, 36, 49, 244, 635, 1354:28; 11, 16, 19, 49, 82, 90, 205:28; 1, 2, 13, 35, 68:26; ") == true);
            std::wstring error = dedup.errorReportMR().str();
			BOOST_TEST((error == L"INVALID_ARG:A, B, C,---,This line should be ignored because it's not valid,50 41 87 95,;EMPTY_ARG:,,,,,,,;") == true);
    }
BOOST_AUTO_TEST_SUITE_END()
#else
int main() {
    DEDUP::DeDup<int> dedup;
    std::wifstream input("input.txt");
    std::wstring line;
    for (getline(input, line); getline(input, line); )
    {
        dedup.add(line);
    }
    std::wstringstream ss;
    for (auto& rec : dedup.mostCommon(5)) {
        std::wcout << rec.first << ":" << rec.second << std::endl;
    }
    std::wcout << dedup.errorReport().str() << std::endl;
}
#endif