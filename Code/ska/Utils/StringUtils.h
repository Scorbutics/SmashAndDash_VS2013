#pragma once
#include <string>
#include <vector>

namespace ska {
	class StringUtils
	{
	private:
		StringUtils();

	public:
		static std::string intToStr(const int x);
		static int strToInt(const std::string& str);
		static std::string uintToStr(const unsigned int x);

		static std::vector<std::string>& split(const std::string &s, const char delim, std::vector<std::string> &elems);
		static std::vector<std::string> split(const std::string &s, const char delim);
		static std::string &ltrim(std::string &s);
		static std::string &rtrim(std::string &s);
		static std::string &trim(std::string &s);

		static std::string extractTo(const int start, const std::string& s, const char to, int *entier);

		static void replaceAll(std::string& str, const std::string& from, const std::string& to);
		static void replaceAll(std::string& str, const char from, const char to);
		static bool isInt(const std::string& s, const int base);
		~StringUtils();
	};
}
