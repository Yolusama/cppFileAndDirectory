#pragma once
#include<string>
#include<filesystem>
#include"Vector.h"


namespace fs = std::filesystem;
namespace MStd {
	class File;
	class Directory
	{
	private:
		fs::path path;	
	public:
		Directory(const std::string& path);
		Directory() {}
		void set_path(const std::string& path);
		bool exists()const;
		void create()const;
		std::string get_dir_name()const;
		std::string get_dir_full_name()const;
		Vector<Directory> get_sub_dirs()const;
		Vector<File> get_files()const;
		void clear()const;
		Directory parent()const;
		void copy_to(const std::string& to)const;
		static Directory current_directory();
		void move_to(const std::string& new_path);
		Directory root()const;
		size_t size()const;
	};
}

