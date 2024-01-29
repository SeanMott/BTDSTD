#pragma once

//defines a file IO

#include <BTDSTD/Logger.hpp>

#include <stdio.h>
#include <vector>
#include <string>

namespace BTD::IO
{
	//defines a file operation
	enum class FileOP
	{
		TextRead_OpenExisting = 0,
		TextWrite_OpenCreateStart,
		TextWrite_OpenCreateApp,
		TextBoth_OpenCreate,
		TextBoth_OpenCreateNuke,
		TextBoth_OpenCreateApp,
		BinaryRead_OpenExisting,
		BinaryWrite_OpenCreateStart,
		BinaryWrite_OpenCreateApp,
		BinaryBoth_OpenCreate,
		BinaryBoth_OpenCreateNuke,
		BinaryBoth_OpenCreateApp,
	};

	//defines a file
	class File
	{
		//vars
	private:

		bool isOpen = false;
		FILE* file = nullptr;
		FileOP op;
		const char* path = "";

		//methods
	public:

		//Deconstructor
		~File() { Close(); }

		//opens a file
		bool Open(const char* _path, const FileOP& OP = FileOP::TextRead_OpenExisting);
		//opens a file
		bool Open(const std::string& _path, const FileOP& OP = FileOP::TextRead_OpenExisting);
		//closes a file
		void Close();

		//reads the data from a file
		unsigned char* ReadUC(size_t& size);
		//reads the data from a file
		const char* Read(size_t& size);
		//reads the data from a file
		std::string Read();
		//reads the data from a file into a vector
		std::vector<char> ReadVec();

		//reads binary data from the file
		void ReadBinary(void* buffer, const size_t& objMemSize, const size_t& count = 1);

		//writes the data to the file
		void Write(const std::string& data);
		//writes the data to the file
		void Write(const char* data, uint32_t length);

		//writes binary data to the file
		void WriteBinary(const void* buffer, const size_t& objMemSize, const size_t& count = 1);

		//if the file is open
		inline bool IsOpen() { return isOpen; }
		//gets the file path
		inline const char* Filepath() { return path; }

	private:

		//converts a file op to the native one
		inline const char* ConvertToNative()
		{
			switch (op)
			{
			case FileOP::TextRead_OpenExisting:
				return "r";
			case FileOP::TextWrite_OpenCreateStart:
				return "w";
			case FileOP::TextWrite_OpenCreateApp:
				return "a";
			case FileOP::TextBoth_OpenCreate:
				return "r+";
			case FileOP::TextBoth_OpenCreateNuke:
				return "w+";
			case FileOP::TextBoth_OpenCreateApp:
				return "a+";
			case FileOP::BinaryRead_OpenExisting:
				return "rb";
			case FileOP::BinaryWrite_OpenCreateStart:
				return "wb";
			case FileOP::BinaryWrite_OpenCreateApp:
				return "ab";
			case FileOP::BinaryBoth_OpenCreate:
				return "rb+";
			case FileOP::BinaryBoth_OpenCreateNuke:
				return "r+b";
			case FileOP::BinaryBoth_OpenCreateApp:
				return "wb+";
			default:
				BTD::Logger::LogError("BTDSTD", "File", "ConvertToNative", "The flag give was not valid for file reading or writing!");
				return "";
			}
		}
	};

	//defines a open file dialog || returns the absolute file path
	//if a empty string, it has been cancaled
	std::string OpenFileDialog(const char* filter, void* window);
	//defines a save file dialog || returns the absolute file path
	//if a empty string, it has been cancaled
	std::string SaveFileDialog(const char* filter, void* window);

	//defines a get directory dialog || returns the absolute file path
	//if a empty string, it has been cancaled
	std::string GetDirectoryDialog(void* window);
}