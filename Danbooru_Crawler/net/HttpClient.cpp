#include "HttpClient.h"
#include <stdexcept>

HttpClient::HttpClient() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

HttpClient::~HttpClient() {
    curl_global_cleanup();
}

size_t HttpClient::writeCallBack(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    std::string* str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string HttpClient::get(const std::string& url) {
    CURL* curl;
	CURLcode res;
	std::string response;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());;
	curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallBack);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "DanbooruClient/1.0");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

	if (res != CURLE_OK) {
		throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
	}

	return response;
}