#include "UserSetting.h"
#include <algorithm>
#include <windows.h>
#include <cstdio>
#include <filesystem>
#include <curl/curl.h>

void UserSettings::debug() {
	printf("statusCode: %d\ntags: %s\nlimits: %d\nisNSFW: %d\nisRandom: %d\nisDownload: %d\n", 
		this->statusCode,
		this->tags.c_str(),
		this->limits,
		this->nsfw,
		this->isRandom,
		this->isDownload);
}