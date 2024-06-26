#pragma once
#include "Reader.h"
#include "BootSector.h"
#include "File.h"
#include <list>


class FAT32FileSystem
{
	Reader* reader;
	BootSector bootSector;
	UINT32* fatTable;
	UINT32 fatTableSize;
	UCHAR* rootDirectory;
	UINT32 rootDirectorySize;


public:
	FAT32FileSystem(Reader* reader) {
		this->reader = reader;
	};
	~FAT32FileSystem() {
		delete[] fatTable;
		delete[] rootDirectory;
	};

	void parseBootSector(UCHAR* info);
	void parseFatTable(UCHAR* buffer, int size);

	void createFatTable();
	void createBootSector();
	void createRootDirectory();

	int getStartSectorOfActiveFat();
	list<int> getFileClusters(const File& file);
	list<int> getRootDirectoryClusters();

	void recoverDeletedFiles(wstring folderName);
	void recoverFile(UINT32 offset, File& fileRecord, wstring folderName);


	bool isCorrectLFN(UINT32 offset);
	bool isFreeCluster(UINT32 offset, int clusterNumber);

	void getFileInfo(UINT32 offset, File& file);

};