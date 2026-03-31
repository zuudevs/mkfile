/**
 * @file mkfile.cpp
 * @author zuudevs
 * @brief CLI tool to create files (similar to touch)
 * @version 1.0.0
 * @date 2026-04-01
 */

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
constexpr std::string_view ANSI_CYAN   = "\033[0;36m";
constexpr std::string_view ANSI_WHITE  = "\033[0;37m";

inline bool is_verbose = false;

std::string colorize(std::string_view str, std::string_view color) noexcept {
	return std::string(color) + str.data() + ANSI_WHITE.data();
}

void print_version() {
    println("{}mkfile version 1.0.0{}", ANSI_BLUE, ANSI_WHITE);
    println("--------------------------------------------------");
    println("Maintained by {}zuudevs{}", ANSI_BLUE, ANSI_WHITE);
}

void print_help() {
    println("{}Usage:{} mkfile [OPTIONS] <files...>", ANSI_BLUE, ANSI_WHITE);
    println();
    println("{:>6}, {:<12} Show help", colorize("-h", ANSI_CYAN), colorize("--help", ANSI_CYAN));
    println("{:>6}, {:<12} Show version", colorize("-v", ANSI_CYAN), colorize("--version", ANSI_CYAN));
    println("{:>6}, {:<12} Verbose output", colorize("-V", ANSI_CYAN), colorize("--verbose", ANSI_CYAN));
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
                println("{} Failed to create {}", colorize("ERROR:", ANSI_RED), filename);
                return;
            }

            if (is_verbose) {
                println("{} Created file {}", colorize("SUCCESS:", ANSI_GREEN), filename);
            }
        } else {
            // mimic touch → update timestamp
            fs::last_write_time(path, fs::file_time_type::clock::now());

            if (is_verbose) {
                println("{} Updated timestamp {}", colorize("INFO:", ANSI_YELLOW), filename);
            }
        }
    } catch (const std::exception& e) {
        println("{} {} ({})", colorize("ERROR:", ANSI_RED), filename, e.what());
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
            println("{} Unknown option {}", colorize("ERROR:", ANSI_RED), arg);
            return 1;
        } else {
            files.push_back(arg);
        }
    }

    if (files.empty()) {
        println("{} No file specified", colorize("ERROR:", ANSI_RED));
        return 1;
    }

    for (const auto& file : files) {
        create_file(file);
    }

    return 0;
}