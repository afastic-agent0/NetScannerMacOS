#ifndef REPORTER_HPP
#define REPORTER_HPP
#include <string>
#include <vector>
#include "scanner.hpp"

class Reporter {
public:
    static void print_console(const std::vector<ScanResult>& results);
    static void save_json(const std::string& filename, const std::vector<ScanResult>& results);
};
#endif
