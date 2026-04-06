#include "reporter.hpp"
#include "scanner.hpp"
#include <iostream>
#include <fstream>

void Reporter::print_console(const std::vector<ScanResult>& results) {
    if (results.empty()) {
        std::cout << "[Reporter] No active hosts found to report." << std::endl;
        return;
    }

    std::cout << "\n--- Scan Summary ---\n";
    for (const auto& r : results) {
        std::cout << "Host: " << r.ip << " | Active: Yes\n  Ports: ";
        for (size_t i = 0; i < r.open_ports.size(); ++i) {
            std::cout << r.open_ports[i] << (i == r.open_ports.size() - 1 ? "" : ", ");
        }
        std::cout << "\n";
    }
    std::cout << "--------------------\n" << std::endl;
}

void Reporter::save_json(const std::string& filename, const std::vector<ScanResult>& results) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << ScannerEngine::format_as_json(results);
        file.close();
        std::cout << "[Reporter] Saved to " << filename << std::endl;
    } else {
        std::cerr << "[Reporter] Failed to save: " << filename << std::endl;
    }
}
