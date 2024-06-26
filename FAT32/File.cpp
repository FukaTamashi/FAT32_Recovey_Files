#include "pch.h"
#include "File.h"
#include <algorithm>
#include "Conversion.h"


void File::deleteSpacesInName()
{
	wstring::iterator it = fileName.begin();
	advance(it, 8);
	fileName.insert(it, '.');
	fileName.erase(std::remove(fileName.begin(), fileName.end(), ' '), fileName.end());
}


void File::createFileName(const UCHAR* record)
{
	char* nameBuffer = (char*)calloc(13, sizeof(char));
	copy(record, record + 11, nameBuffer);
	nameBuffer[0] = '$';
	string fileName(nameBuffer);

	wstring wName(fileName.begin(), fileName.end());
	this->fileName = wName;
	deleteSpacesInName();
	free(nameBuffer);
	//return wName;
}

void File::createSize(const UCHAR* record)
{
	Conversion conversion;
	UINT32 fileSize = conversion.converseToType(record, 28, 31);
	this->size = fileSize;
}

UINT32 File::createFirstCluster(const UCHAR* record)
{
	Conversion conversion;
	UINT16 highBytesOfFirstCluster = conversion.converseToType(record, 20, 21);
	UINT16 lowBytesOfFirstCluster = conversion.converseToType(record, 26, 27);
	UINT32 firstCluster;
	firstCluster = highBytesOfFirstCluster << 16;
	firstCluster += lowBytesOfFirstCluster;
	this->firstCluster = firstCluster;
	return firstCluster;
}

UINT32 File::getFirstCluster() const {
	return firstCluster;
}

void File::setFirstCluster(UINT32 firstCluster) {
	this->firstCluster = firstCluster;
}

UINT32 File::getSize() const {
	return size;
}

void File::setSize(UINT32 size) {
	this->size = size;
}

wstring File::getFileName() const
{
	return fileName;
}

void File::setFileName(wstring& fileName)
{
	this->fileName = fileName;
}