#include "Directory.h"
#include"File.h"
#include"Stack.h"

using namespace MStd;

Directory::Directory(const std::string& path) :path(path) {}

void Directory::set_path(const std::string& path)
{
	if (!path.empty())return;
	this->path = path;
}

bool Directory::exists() const
{	
	return fs::exists(path);
}

void Directory::create() const
{
	fs::create_directory(path);
}

std::string Directory::get_dir_name() const
{
	return path.filename().string();
}

std::string Directory::get_dir_full_name() const
{
	return fs::absolute(path).string();
}

Vector<Directory> Directory::get_sub_dirs() const
{
	auto dirs = fs::directory_iterator(path);
	Vector<Directory> data;
	for (const auto& entry : dirs) {
		if (entry.is_directory())
		{
			data.emplace_back(entry.path().string());
		}
	}
	return data;
}

Vector<File> Directory::get_files() const
{
	Vector<File> data;
	var files = fs::directory_iterator(path);
	for (const var& entry : files)
	{
		if (entry.is_directory())continue;
		data.emplace_back(entry.path().string());
	} 
	return data;
}

void Directory::clear() const
{
	fs::remove_all(path);
}

Directory Directory::parent() const
{
	return Directory(path.parent_path().string());
}

void Directory::copy_to(const std::string& to) const
{
	fs::copy(path, to);
}

Directory Directory::current_directory()
{
	return Directory(fs::current_path().string());
}

void Directory::move_to(const std::string& new_path)
{
	this->copy_to(new_path);
	path = fs::path(new_path);
}

Directory MStd::Directory::root() const
{
	return Directory(path.root_directory().string());
}

size_t Directory::size() const
{
	Stack<Directory> stack;
	size_t sum = 0;
	stack.push(*this);
	while (!stack.empty()) {
		Directory dir = stack.top();
		var sub_dirs = dir.get_sub_dirs();
		stack.pop();
		var files = dir.get_files();
		for (size_t i = 0; i < files.size(); i++)
		sum += files[i].size();
		if (!sub_dirs.empty())
		{
			for (size_t i = 0; i < sub_dirs.size(); i++)
			{
				stack.push(sub_dirs[i]);
			}
		}
	}
	return sum;
}
