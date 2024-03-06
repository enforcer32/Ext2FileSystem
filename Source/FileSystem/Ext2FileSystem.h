#pragma once

#include "FileSystem/EXT2Superblock.h"
#include "FileSystem/EXT2Inode.h"

#include <string>
#include <memory>

namespace FileSystem
{
	class Ext2FileSystem
	{
	public:
		bool Init();
		void Destroy();
		bool OpenDevice(const std::string& devpath);
		void LS(const std::string& path);
		void CD(const std::string& path);
		void Cat(const std::string& path, size_t readsize = 4096);

	private:
		bool ParseSuperblock();
		bool ParseBlockGroupDescriptors();
		const Ext2BlockGroupDescriptor& GetBlockGroupDescriptor(uint32_t group) const;
		std::shared_ptr<Ext2Inode> GetInode(uint32_t inode);
		std::shared_ptr<Ext2Inode> GetInodeFromDir(const std::shared_ptr<Ext2Inode>& inodebuf, const std::string& name);
		std::shared_ptr<Ext2Inode> GetInodeFromPath(const std::string& path);

		uint8_t* ReadBlock(uint32_t block);
		uint8_t* ReadFile(const std::shared_ptr<Ext2Inode>& inodebuf, size_t size);

	public:
		// DEBUG
		void DumpSuperblock();
		void DumpBlockGroupDescriptors();
		void DumpInode(const std::shared_ptr<Ext2Inode>& inodebuf);
		void DumpDirInode(const std::shared_ptr<Ext2Inode>& inodebuf);
		void DumpDirent(const Ext2Dirent* dir);

	private:
		std::string m_Device;
		std::string m_CurrentPath;
		std::unique_ptr<Ext2Superblock> m_Superblock;
		uint32_t m_FirstBlockGroup;
		uint32_t m_BlockGroupDescriptorCount;
		std::vector<Ext2BlockGroupDescriptor> m_BlockGroupDescriptors;
		std::shared_ptr<Ext2Inode> m_RootInode;
	};
}
