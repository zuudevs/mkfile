/**
 * @file mkfile.cpp
 * @author zuudevs (zuudevs@gmail.com)
 * @brief CLI tool to create files (similar to touch)
 * @version 1.0.0
 * @date 2026-04-01
 */

#include <filesystem>
#include <fstream>
#include <print>
#include <string_view>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

namespace credit {
	constexpr std::string_view author = "zuudevs";
	constexpr std::string_view version = "1.0.0";
	constexpr std::string_view email = "zuudevs@gmail.com";
	constexpr std::string_view repository = "https://github.com/zuudevs/mkfile.git";
} // namespace credit

// ANSI colors (portable escape)
namespace ansi {
	constexpr std::string_view red = "\033[0;31m";
	constexpr std::string_view green = "\033[0;32m";
	constexpr std::string_view yellow = "\033[0;33m";
	constexpr std::string_view blue = "\033[0;34m";
	constexpr std::string_view cyan = "\033[0;36m";
	constexpr std::string_view white = "\033[0;37m";
} // namespace ansi

inline bool is_verbose = false;

std::string colorize(
	std::string_view str, 
	std::string_view color
) noexcept {
    return std::string(color) + str.data() + ansi::white.data();
}

void print_about() {
	println("author: {}", colorize(credit::author, ansi::blue));
	println("email: {}", colorize(credit::email, ansi::blue));
	println("repository: {}", colorize(credit::repository, ansi::blue));
	println("version: {}", colorize(credit::version, ansi::blue));
}

void print_version() {
    println(
		"mkfile version {}", 
		colorize(credit::version, ansi::blue)
	);
    println("--------------------------------------------------");
    println(
		"Maintained by {}", 
		colorize(credit::author, ansi::blue)
	);
}

void print_help() {
    println(
		"{} mkfile [OPTIONS] <files...>", 
		colorize("Usage:", ansi::blue)
	);
    println();
    println(
		"{:>6}, {:<12} Show help", 
		colorize("-h", ansi::cyan), 
		colorize("--help", ansi::cyan)
	);
    println(
		"{:>6}, {:<12} Show version", 
		colorize("-v", ansi::cyan), 
		colorize("--version", ansi::cyan)
	);
    println(
		"{:>6}, {:<12} Verbose output", 
		colorize("-V", ansi::cyan),
        colorize("--verbose", ansi::cyan)
	);
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
                println(
					"{} Failed to create {}", 
					colorize("ERROR:", ansi::red), 
					filename
				);
                return;
            }

            if (is_verbose) {
                println(
					"{} Created file {}", 
					colorize("SUCCESS:", ansi::green), 
					filename
				);
            }
        } else {
            // mimic touch → update timestamp
            fs::last_write_time(path, fs::file_time_type::clock::now());

            if (is_verbose) {
                println(
					"{} Updated timestamp {}", 
					colorize("INFO:", ansi::yellow), 
					filename
				);
            }
        }
    } catch (const std::exception &e) {
        println(
			"{} {} ({})", 
			colorize("ERROR:", ansi::red), 
			filename, 
			e.what()
		);
    }
}

int main(int argc, char *argv[]) {
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
            println(
				"{} Unknown option {}", 
				colorize("ERROR:", ansi::red), 
				arg
			);
            return 1;
        } else {
            files.push_back(arg);
        }
    }

    if (files.empty()) {
        println(
			"{} No file specified", 
			colorize("ERROR:", ansi::red)
		);
        return 1;
    }

    for (const auto &file : files) {
        create_file(file);
    }

    return 0;
}