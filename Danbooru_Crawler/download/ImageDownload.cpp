#include "ImageDownload.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>
#include <fstream>
#include "include/nlohmann/json.hpp"

namespace fs = std::filesystem;

struct stat info;

long long getLastedId(const char* tag) {
	nlohmann::json j;

	std::ifstream i("lastedId.json");
	if(i.is_open()) {
		i >> j;
		i.close();
	}

	if(j.contains(tag)) {
		return j[tag].get<long long>();
	}

	return 999999999;
}

void lastedIdByTag(long long& lastId, const char* tag) {
	// This will update lastId based on the tag provided after each download session in order to avoid downloading duplicate images.
	nlohmann::json j;

	std::ifstream i("lastedId.json");
	if(i.is_open()) {
		i >> j;
		i.close();
	}

	j[tag] = lastId;

	std::ofstream o("lastedId.json");
	o << j.dump(4);
	o.close();
}

void createImgUrlTxt(std::vector<std::string> imgUrls, const std::string& path) {
	FILE* txtPath = fopen(path.c_str(), "w");

	for (int i = 0; i < (int)imgUrls.size(); ++i) {
		fprintf(txtPath, "%s\n", imgUrls[i].c_str());
	}

	fclose(txtPath);
}

void downloadImg(const std::string& imgUrlPath, const std::string& destFolderPath) {
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