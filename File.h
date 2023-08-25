#pragma once
#include<string>
#include<filesystem>
#include<fstream>

namespace MStd {
	class Directory;
	namespace fs = std::filesystem;
	class File
	{
	private:
		fs::path path;
	public:
		File() {}
		File(const std::string& path);
		bool exists()const;
		std::string extention()const;
		void remove()const;
		void copy_to(const std::string& to)const;
		std::string get_full_name()const;
		std::string get_name()const;
		Directory parent()const;
		void create()const;
		std::ifstream open_to_read()const;
		std::ofstream open_to_write(bool append=false)const;
		void move_to(const std::string& new_path);
		Directory root()const;
		size_t size()const;
		void set_path(const std::string& path);
	};
}

