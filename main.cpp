#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include "signature_detector.h"

namespace {

bool has_executable_extension(const std::string& path) {
	const std::size_t dot = path.find_last_of('.');
	const std::size_t separator = path.find_last_of("/\\");
	if (dot == std::string::npos ||
		(separator != std::string::npos && dot < separator))
		return false;

	std::string extension = path.substr(dot);
	std::transform(extension.begin(), extension.end(), extension.begin(),
			   [](unsigned char character) {
				   return static_cast<char>(std::tolower(character));
			   });

	return extension == ".exe" || extension == ".dll" ||
		   extension == ".com" || extension == ".scr" ||
		   extension == ".sys" || extension == ".ocx" ||
		   extension == ".cpl" || extension == ".drv";
}

}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Uzycie: " << argv[0] << " <plik>\n";
		return 1;
	}

	std::ifstream file(argv[1], std::ios::binary);
	if (!file) {
		std::cerr << "Nie mozna otworzyc pliku: " << argv[1] << '\n';
		return 1;
	}

	const std::string format = detect_format(file);
	if (!format.empty()) {
		std::cout << "Rozpoznany format: " << format << '\n';
		if (format == "EXE/DLL (MZ)" && !has_executable_extension(argv[1]))
			std::cout << "Ostrzezenie: sygnatura wskazuje na plik wykonywalny, "
						 "ale rozszerzenie nie jest typowe dla pliku EXE/DLL. "
						 "To moze byc podejrzana zmiana nazwy, ale nie potwierdza "
						 "obfuskacji.\n";
		return 0;
	}

	std::cout << "Nie rozpoznano sygnatury pliku.\n";
	return 0;
}
