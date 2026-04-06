#include <iostream>
#include <vector>
#include "discovery.hpp"
#include "scanner.hpp"
#include "reporter.hpp"

int main() {
    std::cout << "=== NetScannerMacOS Fixed Scan ===" << std::endl;
    DiscoveryModule discovery;
    ScannerEngine scanner;
    Reporter reporter;

    auto interfaces = discovery.get_interfaces();
    for (const auto& i : interfaces) std::cout << "  -> Found: " << i << std::endl;

    std::string target = "127.0.0.1";
    int min_p = 1;
    int max_p = 1500;

    std::cout << "[Main] Starting scan for: " << target << " (Ports: " << min_p << "-" << max_p << ")" << std::endl;
    
    auto results = scanner.scan_subnet(target, min_p, max_p);
    reporter.print_console(results);
    reporter.save_json("scan_results.json", results);

    std::cout << "[Main] Scan complete." << std::endl;

    return 0;
}
