#pragma once

#include <string>
#include <vector>
#include "config/UserSetting.h"
#include "net/HttpClient.h"

struct DanbooruPost {
    long long id;
    std::string file_url;
};

class DanbooruClient {
    public:
        std::vector<DanbooruPost> fetchPosts(const std::string& requestUrl, HttpClient& httpClient);
};