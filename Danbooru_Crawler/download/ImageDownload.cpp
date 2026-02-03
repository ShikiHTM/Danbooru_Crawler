#include "ImageDownload.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>

namespace fs = std::filesystem;

struct stat info;

void ImageDownloader::downloadImages(const std::string& imgUrlPath, const std::string& destFolderPath) {
	// Check if folder is exist
	if (stat(destFolderPath.c_str(), &info)) {
		printf("Cannot access %s\n", destFolderPath.c_str());
	}
	else if (info.st_mode & S_IFDIR) {
		// The path exists
	}
	else {
		// The path doesn't exist
		printf("%s doesn't exist, creating a new folder...", destFolderPath.c_str());
		fs::create_directory(destFolderPath);
		if (fs::exists(destFolderPath)) printf("Created %s sucessfully.", destFolderPath.c_str());
	}

	// Using wget to download image;

	const std::string command = "wget --progress=bar:force --tries=3 -nv -i " + imgUrlPath + " -P " + destFolderPath;

	FILE* imgUrl = _popen(command.c_str(), "r");

	_pclose(imgUrl);
}