/**
 * @file mkfile.cpp
 * @author zuudevs
 * @brief CLI tool to create files (similar to touch)
 * @version 0.2
 * @date 2026-04-01
 */

#include <cstdint>
#include <print>
#include <filesystem>
#include <fstream>
#include <string_view>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// ANSI colors (portable escape)
constexpr std::string_view ANSI_RED    = "\033[0;31m";
constexpr std::string_view ANSI_GREEN  = "\033[0;32m";
constexpr std::string_view ANSI_YELLOW = "\033[0;33m";
constexpr std::string_view ANSI_BLUE   = "\033[0;34m";
constexpr std::string_view ANSI_WHITE  = "\033[0;37m";

inline bool is_verbose = false;

void print_version() {
    println("{}mkfile version 0.2{}", ANSI_BLUE, ANSI_WHITE);
    println("--------------------------------------------------");
    println("Maintained by {}zuudevs{}", ANSI_BLUE, ANSI_WHITE);
}

void print_help() {
    println("{}Usage:{} mkfile [OPTIONS] <files...>", ANSI_BLUE, ANSI_WHITE);
    println();
    println("{:>6}, {:<12} Show help", "-h", "--help");
    println("{:>6}, {:<12} Show version", "-v", "--version");
    println("{:>6}, {:<12} Verbose output", "-V", "--verbose");
}

void create_file(std::string_view filename) {
    try {
        fs::path path(filename);

        // Create parent directories if needed
        if (!path.parent_path().empty()) {
            fs::create_directories(path.parent_path());
        }

        if (!fs::exists(path)) {
            std::ofstream file(path);
            if (!file) {
                println("{}ERROR:{} Failed to create {}", ANSI_RED, ANSI_WHITE, filename);
                return;
            }

            if (is_verbose) {
                println("{}SUCCESS:{} Created file {}", ANSI_GREEN, ANSI_WHITE, filename);
            }
        } else {
            // mimic touch → update timestamp
            fs::last_write_time(path, fs::file_time_type::clock::now());

            if (is_verbose) {
                println("{}INFO:{} Updated timestamp {}", ANSI_YELLOW, ANSI_WHITE, filename);
            }
        }
    } catch (const std::exception& e) {
        println("{}ERROR:{} {} ({})", ANSI_RED, ANSI_WHITE, filename, e.what());
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 0;
    }

    std::vector<std::string_view> files;

    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            print_help();
            return 0;
        } else if (arg == "-v" || arg == "--version") {
            print_version();
            return 0;
        } else if (arg == "-V" || arg == "--verbose") {
            is_verbose = true;
        } else if (arg.starts_with("-")) {
            println("{}ERROR:{} Unknown option {}", ANSI_RED, ANSI_WHITE, arg);
            return 1;
        } else {
            files.push_back(arg);
        }
    }

    if (files.empty()) {
        println("{}ERROR:{} No file specified", ANSI_RED, ANSI_WHITE);
        return 1;
    }

    for (const auto& file : files) {
        create_file(file);
    }

    return 0;
}