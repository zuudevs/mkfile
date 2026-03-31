/**
 * @file main.cpp
 * @author zuudevs (zuudevs@gmail.com)
 * @brief this is main code of mkfile, mkfile is tool for create a file
 * @version 0.1
 * @date 2026-04-01
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <cstdint>
#include <print>
#include <filesystem>
#include <fstream>
#include <string_view>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

constexpr std::string_view ANSI_RED = "\e[0;31m";
constexpr std::string_view ANSI_GREEN = "\e[0;32m";
constexpr std::string_view ANSI_YELLOW = "\e[0;33m";
constexpr std::string_view ANSI_BLUE = "\e[0;34m";
constexpr std::string_view ANSI_WHITE = "\e[0;37m";

inline bool is_verbose = false;

void print_version() noexcept {
	println("mkfile version {}0.0.1{}", ANSI_BLUE, ANSI_WHITE);
	println("----------------------------------------------------------");
	println("Maintained and Supported by {}zuudevs (zuudevs@gmail.com){}", ANSI_BLUE, ANSI_WHITE);
}

// OPTIMIZE: Need clean description
void print_help() noexcept {
	println("{}usage: {} <...>", ANSI_BLUE, ANSI_WHITE);
	println("{}usage: {} [OPTIONS] <...>", ANSI_BLUE, ANSI_WHITE);
	println("{:>4}, {:>12}, ", "-h", "--help");
	println("{:>4}, {:>12}, ", "-v", "--version");
	println("{:>4}, {:>12}, ", "-V", "--verbose");
}

void create_file(std::string_view filename) noexcept {
	if (!fs::exists(filename)) {
		auto newFile = ofstream(filename.data());
		if (is_verbose) {
			println("{}SUCCESS: {}Create file {}.", ANSI_GREEN, ANSI_WHITE, filename);
		}
	} else {
		if (is_verbose) {
			println("{}WARNING: {}File is exist {}.", ANSI_YELLOW, ANSI_WHITE, filename);
		}
	}
}

int main(int argc, char* argv[] ) {
	if (argc < 2)	{
		print_help();
		return 0;
	} 
	
	auto arg1 = std::string_view(argv[1]);
	if (argc == 2) {
		if (arg1 == "-h" || arg1 == "--help") {
			print_help();
			return 0;
		} else if (arg1 == "-v" || arg1 == "--version") {
			print_version();
			return 0;
		} 
		if (arg1 == "-V" || arg1 == "--verbose") {
			println("{}usage: {} -v <ARGS...>", ANSI_BLUE, ANSI_WHITE);
			return 0;
		}
	}

	if (argc >= 2) {
		if (arg1 == "-V" || arg1 == "--verbose") {
			is_verbose = true;
		}
		// FIXME: '-V' or '--verbose' which should be a 'flag' is also created as a file
		std::vector<std::string_view> files(argv + (is_verbose ? 1 : 2), argv + argc);
		for(const auto& file : files) {
			create_file(file);
		}
	}
}