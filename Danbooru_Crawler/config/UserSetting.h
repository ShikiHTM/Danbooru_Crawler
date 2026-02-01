#ifndef UserSetting_H
#define UserSetting_H

#include <string>
#include <vector>
#include "menu/Menu.h"

using std::vector;

struct UserSettings {
	std::string tags = "";
	std::string postId = "";
	int limits = 0;
	bool isDownload = false;
	bool isRandom = false;
	bool nsfw = false;
	int statusCode = 1;

	void debug();
};


void downloadImg(const char* imgUrl, const std::wstring& destFolderPath);
#endif