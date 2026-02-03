#pragma once

#include <cstdlib>
#include <iostream>
#include "config/UserSetting.h"
#include "download/DownloadState.h"

class DanbooruQuery {
    public:
        DanbooruQuery(const char* apiKeyEnv, const char* apiLoginUsernameEnv);

        std::string buildUrl(const UserSettings& settings, long long oldestId);
    private:
        const char* API_URL = "https://danbooru.donmai.us/posts.json?";
        const char* API_KEY;
        const char* API_LOGIN_USERNAME;
};