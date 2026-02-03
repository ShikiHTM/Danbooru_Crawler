#pragma once
#include <string>
#include <curl/curl.h>

class HttpClient {
public:
        HttpClient();
        ~HttpClient();

        std::string get(const std::string& url);
private:
        static size_t writeCallBack(void* contents, size_t size, size_t nmemb, void* userp);
};