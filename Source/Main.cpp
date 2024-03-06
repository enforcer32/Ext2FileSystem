#include "buildpch.h"
#include "Core/Logger.h"
#include "Util/linenoise.hpp"
#include "FileSystem/Ext2FileSystem.h"

#include <string>
#include <vector>

using namespace FileSystem;

std::vector<std::string> StringSplit(const std::string& str, char delim)
{
	std::vector<std::string> data;
	std::stringstream ss(str);
	std::string line;
	while (std::getline(ss, line, delim))
		data.push_back(line);
	return data;
}

void PrintHelp()
{
	std::cout << "Commands:\n1. help\n2. exit\n3. clear\n4. ls\n5. cd\n6. cat\n";
}

int main()
{
	Ext2::Logger::Init();

	Ext2FileSystem* ext2fs = new Ext2FileSystem();
	if (!ext2fs->Init())
	{
		LOGGER_ERROR("Failed to Init EXT2FS");
		return 1;
	}

	ext2fs->OpenDevice("hdd.img");
	//ext2fs->DumpSuperblock();
	//ext2fs->DumpBlockGroupDescriptors();

	bool quit = false;
	while (!quit)
	{
		std::string line;
		quit = linenoise::Readline("Ext2FS> ", line);
		if (quit) break;
		if (!line.size()) continue;

		std::vector<std::string> args = StringSplit(line, ' ');

		if (args[0] == "help")
		{
			PrintHelp();
		}
		else if (args[0] == "exit")
		{
			quit = true;
			continue;
		}
		else if (args[0] == "clear")
		{
			linenoise::linenoiseClearScreen();
		}
		else if (args[0] == "ls")
		{
			if (args.size() == 1)
				ext2fs->LS("");
			else 
				ext2fs->LS(args[1]);
		}
		else if (args[0] == "cd")
		{
			if (args.size() == 1)
				std::cout << "cd [dir]\n";
			else ext2fs->CD(args[1]);
		}
		else if (args[0] == "cat")
		{
			if (args.size() == 1)
				std::cout << "cat [file]\n";
			else if (args.size() == 3)
				ext2fs->Cat(args[1], std::atoi(args[2].c_str()));
			else
				ext2fs->Cat(args[1]);
		}
		else
		{
			LOGGER_ERROR("Invalid Command: {}", line);
			LOGGER_INFO("use 'help' for Commands");
			continue;
		}

		linenoise::AddHistory(line.c_str());
	}

	ext2fs->Destroy();
	delete ext2fs;
	return 0;
}
