#include "File.h"
#include "Directory.h"

using namespace MStd;

File::File(const std::string& path) :path(path) {}

bool File::exists() const
{
	return fs::exists(path);
}

std::string File::extention() const
{
	return path.extension().string();
}

void File::remove() const
{
	fs::remove(path);
}

void File::copy_to(const std::string& to) const
{
	fs::copy_file(path, to);
}

std::string File::get_full_name() const
{
	return fs::absolute(path).string();
}

std::string File::get_name() const
{
	return path.filename().string();
}

Directory File::parent() const
{
	std::string fname = this->get_full_name();
	return Directory(fname.substr(0,fname.find_last_of('\\')));
}

void File::create() const
{
	std::ofstream file;
	file.open(path.string(),std::ios_base::out);
	file.close();
}

std::ifstream File::open_to_read() const
{
	return std::ifstream(path.string());
}

std::ofstream File::open_to_write(bool append) const
{
	if (!append)
		return std::ofstream(path.string(), std::ios_base::app);
	else return std::ofstream(path.string());
}

void File::move_to(const std::string& new_path)
{
	fs::copy_file(path, new_path);
	this->remove();
	path = fs::path(new_path);
}

Directory File::root() const
{
	std::string fname = this->get_full_name();
	std::string rootName = fname.substr(0, fname.find('\\')+1);
	return Directory(rootName);
}

size_t File::size() const
{
	return fs::file_size(path);
}

void File::set_path(const std::string& path)
{
	if (this->path.string().empty()) {
		this->path = fs::path(path);
	}
}
