#include "AssetsPath.h"


AssetsPath::AssetsPath()
{
	DWORD length = GetModuleFileNameA(NULL, path, MAX_PATH);
	cutExecutableName();
}

void AssetsPath::cutExecutableName()
{
    int i = MAX_PATH - 1;
    while (i >= 0 && path[i] != '\\') {
        path[i] = '\0';
        i--;
    }
	const char* assetsFolder = "assets\\";
	int at = 0;
	while (assetsFolder[at] != '\0')
	{
		path[++i] = assetsFolder[at++];
	}
	backslashPos = i;
}
std::string AssetsPath::concatenate(const char * toAdd)
{
	int pathCopyAt = backslashPos + 1;
	char pathCopy[MAX_PATH] = { '\0' };
	strcpy_s(pathCopy, path);
	int toAddAt = 0;
	while (toAdd[toAddAt] != '\0')
	{
		pathCopy[pathCopyAt++] = toAdd[toAddAt++];
	}
	std::string toReturn(pathCopy);
	return toReturn;
}

void AssetsPath::printPath()
{
	for (int i = 0; i < MAX_PATH; i++)
	{
		std::cout << path[i];
	}
}
