/**
 * @file mkfile.cpp
 * @author zuudevs (zuudevs@gmail.com)
 * @brief A CLI utility for creating files.
 * @version 1.0.0
 * @date 2026-04-01
 *
 * @copyright Copyright (c) 2026
 * 
 */

#include <filesystem>
#include <fstream>
#include <print>
#include <string_view>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

namespace credit {
	[[maybe_unused]] constexpr std::string_view author = "zuudevs";
	[[maybe_unused]] constexpr std::string_view version = "1.0.0";
	[[maybe_unused]] constexpr std::string_view email = "zuudevs@gmail.com";
	[[maybe_unused]] constexpr std::string_view repository = "https://github.com/zuudevs/mkfile.git";
} // namespace credit

namespace ansi {
	[[maybe_unused]] constexpr std::string_view black = "\033[0;30m"; 
    [[maybe_unused]] constexpr std::string_view red = "\033[0;31m"; 
    [[maybe_unused]] constexpr std::string_view green = "\033[0;32m"; 
    [[maybe_unused]] constexpr std::string_view yellow = "\033[0;33m"; 
    [[maybe_unused]] constexpr std::string_view blue = "\033[0;34m"; 
    [[maybe_unused]] constexpr std::string_view purple = "\033[0;35m"; 
    [[maybe_unused]] constexpr std::string_view cyan = "\033[0;36m"; 
    [[maybe_unused]] constexpr std::string_view white = "\033[0;37m";
    [[maybe_unused]] constexpr std::string_view reset = "\033[0m";
} // namespace ansi

inline bool is_verbose = false;

[[nodiscard]] inline
std::string colorize(std::string_view str, std::string_view color) noexcept {
	return std::string(color) + str.data() + ansi::reset.data();
}

void print_about() {
	std::println(
		"{}", 
		colorize("=== About mkfile ===", ansi::purple)
	);
	std::println("mkfile (Make File) is a simple command line utility");
    std::println("which is designed to create a file.");
    std::println();
	std::println(
		"{:<12} {}", "Author:", 
		colorize(credit::author, ansi::blue)
	);
    std::println(
		"{:<12} {}", "Email:", 
		colorize(credit::email, ansi::blue)
	);
    std::println(
		"{:<12} {}", "Repository:", 
		colorize(credit::repository, ansi::blue)
	);
    std::println(
		"{:<12} {}", "Version:", 
		colorize(credit::version, ansi::blue)
	);
}

void print_version() {
	std::println(
		"mkfile version {}", 
		colorize(credit::version, ansi::blue)
	);
    std::println("--------------------------------------------------");
    std::println(
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
	std::println(
		"{}", 
		colorize("Options:", ansi::blue)
	);
  	println(
		"  {:<18} Show this help message", 
		colorize("-h, --help", ansi::cyan)
	);
	println(
		"  {:<18} Show application about/credits", 
		colorize("-a, --about", ansi::cyan)
	);
	println(
		"  {:<18} Show version information", 
		colorize("-v, --version", ansi::cyan)
	);
	println(
		"  {:<18} Verbose output", 
		colorize("-V, --verbose", ansi::cyan)
	);
}

void create_file(std::string_view filename) {
  	try {
    	fs::path path(filename);

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
    	} else if (arg == "-a" || "--about") {
      		print_about();
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