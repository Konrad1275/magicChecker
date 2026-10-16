#include "signature_detector.h"

#include <istream>
#include <vector>

namespace {

struct Signature {
	const char* format;
	std::vector<unsigned char> bytes;
};

const std::vector<Signature>& signatures() {
	static const std::vector<Signature> knownSignatures = {
		{"PNG", {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}},
		{"JPEG", {0xFF, 0xD8, 0xFF}},
		{"GIF", {0x47, 0x49, 0x46, 0x38}},
		{"PDF", {0x25, 0x50, 0x44, 0x46, 0x2D}},
		{"ZIP", {0x50, 0x4B, 0x03, 0x04}},
		{"GZIP", {0x1F, 0x8B}},
		{"ELF", {0x7F, 0x45, 0x4C, 0x46}},
		{"BMP", {0x42, 0x4D}},
		{"EXE/DLL (MZ)", {0x4D, 0x5A}},
	};
	return knownSignatures;
}

}

std::string detect_format(std::istream& file) {
	std::size_t maxLength = 0;
	for (const auto& signature : signatures())
		if (signature.bytes.size() > maxLength)
			maxLength = signature.bytes.size();

	std::vector<unsigned char> header(maxLength);
	file.read(reinterpret_cast<char*>(header.data()),
			  static_cast<std::streamsize>(header.size()));
	const std::size_t readCount = static_cast<std::size_t>(file.gcount());

	for (const auto& signature : signatures()) {
		if (readCount < signature.bytes.size())
			continue;

		bool matches = true;
		for (std::size_t i = 0; i < signature.bytes.size(); ++i) {
			if (header[i] != signature.bytes[i]) {
				matches = false;
				break;
			}
		}
		if (matches)
			return signature.format;
	}

	return {};
}