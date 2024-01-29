#include <BTDSTD/IO/File.hpp>

#include <BTDSTD/Types.hpp>

//#include <winapifamily.h>
//#include <commdlg.h>
//#include <GLFW\glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#define LEAN_AND_MEAN
#include <Windows.h>

bool BTD::IO::File::Open(const char* _path, const FileOP& OP)
{
	if (isOpen)
	{
		BTD::Logger::LogError("BTDSTD", "File", "Open",
			(std::string("The File Handler cuurrently had a file open for ") + std::string(path) + ". It will be closed then used on " + std::string(_path)).c_str());
		Close();
	}

	path = _path;
	op = OP;

	file = fopen(path, ConvertToNative());
	if (!file)
	{
		BTD::Logger::LogError("BTDSTD", "File", "Open",
			(std::string("Failed to open file at: ") + std::string(path)).c_str());
		return false;
	}

	isOpen = true;
	return true;
}

bool BTD::IO::File::Open(const std::string& _path, const FileOP& OP)
{
	if (isOpen)
	{
		BTD::Logger::LogError("BTDSTD", "File", "Open",
			(std::string("The File Handler cuurrently had a file open for ") + std::string(path) + ". It will be closed then used on " + std::string(_path)).c_str());
		Close();
	}

	path = _path.c_str();
	op = OP;

	file = fopen(path, ConvertToNative());
	if (!file)
	{
		BTD::Logger::LogError("BTDSTD", "File", "Open",
			(std::string("Failed to open file at: ") + std::string(path)).c_str());
		return false;
	}

	isOpen = true;
	return true;
}

void BTD::IO::File::Close()
{
	fclose(file);
	isOpen = false;
}

unsigned char* BTD::IO::File::ReadUC(size_t& size)
{
	if (!file)
	{
		BTD::Logger::LogError("BTDSTD", "File", "ReadUC", "No file has been opened or created!");
		size = 0;
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned char* text = (unsigned char*)calloc(length, length);
	if (text)
		fread(text, 1, length, file);

	return text;
}

const char* BTD::IO::File::Read(size_t& size)
{
	if (!file)
	{
		BTD::Logger::LogError("BTDSTD", "File", "Read", "No file has been opened or created!");
		size = 0;
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* text = (char*)calloc(length, length);
	if (text)
		fread(text, 1, length, file);

	return text;
}

std::string BTD::IO::File::Read()
{
	if (!file)
	{
		BTD::Logger::LogError("BTDSTD", "File", "Read", "No file has been opened or created!");
		return "";
	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* text = (char*)calloc(length, length);
	if (text)
		fread(text, 1, length, file);

	return text;
}

std::vector<char> BTD::IO::File::ReadVec()
{
	std::vector<char> data;

	if (!file)
	{
		BTD::Logger::LogError("BTDSTD", "File", "ReadVec", "No file has been opened or created!");
		return data;
	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	data.reserve(length);
	fseek(file, 0, SEEK_SET);
	char* text = (char*)calloc(length, length);
	if (text)
		fread(text, 1, length, file);

	for (int32_t i = 0; i < length; ++i)
		data.emplace_back(text[i]);

	return data;
}

void BTD::IO::File::ReadBinary(void* buffer, const size_t& objMemSize, const size_t& count)
{
	fread(buffer, objMemSize, count, file);
}

void BTD::IO::File::Write(const std::string& data)
{
	if (!file)
	{
		BTD::Logger::LogError("BTDSTD", "File", "Write", "No file has been opened or created!");
		return;
	}

	fputs(data.c_str(), file);
}
void BTD::IO::File::Write(const char* data, uint32_t length)
{
	if (!file)
	{
		BTD::Logger::LogError("BTDSTD", "File", "Write", "No file has been opened or created!");
		return;
	}

	fputs(data, file);
}

void BTD::IO::File::WriteBinary(const void* buffer, const size_t& objMemSize, const size_t& count)
{
	if (!file)
	{
		BTD::Logger::LogError("BTDSTD", "File", "WriteBinary", "No file has been opened or created!");
		return;
	}

	fwrite(buffer, objMemSize, count, file);
}

std::string BTD::IO::OpenFileDialog(const char* filter, void* window)
{
	OPENFILENAMEA ofn;
	CHAR szFile[256] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)window);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetOpenFileNameA(&ofn) == TRUE)
		return ofn.lpstrFile;

	return std::string();
}

std::string BTD::IO::SaveFileDialog(const char* filter, void* window)
{
	OPENFILENAMEA ofn;
	CHAR szFile[256] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)window);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetSaveFileNameA(&ofn) == TRUE)
		return ofn.lpstrFile;

	return std::string();
}

std::string BTD::IO::GetDirectoryDialog(void* window)
{
	OPENFILENAMEA ofn;
	CHAR szFile[256] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAMEA));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)window);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Ignore this (blyat.suka)\0.suka\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetSaveFileNameA(&ofn) == TRUE)
	{
		std::string path = ofn.lpstrFile;

		//break the path by stripping off the /
		size_t s = path.size();
		for (uint32 i = s; i < -1; --i)
		{
			if (path[i] == '\\')
			{
				path.resize(i);
				break;
			}
		}

		return path;
	}

	return std::string();
}