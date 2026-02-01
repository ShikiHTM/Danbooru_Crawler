#include <iostream>
#include <curl/curl.h>
#include <stdlib.h>
#include "menu/Menu.h"
#include <vector>
#include "config/UserSetting.h"
#include "download/ImageDownload.h"

#include "danbooru/DanbooruClient.h"
#include "config/UserSettingParser.h"
#include "nlohmann/json.hpp"
#include "cstdlib"

#define DEBUG(x) std::cout << x << '\n'

const std::string destFolder = "images";
const std::string imgUrlPath = "images.txt";

size_t write_callback(void* content, size_t size, size_t nmemb, std::string* output) {
	size_t totalSize = size * nmemb;
	output->append((char*)content, totalSize);
	return totalSize;
}

std::string fetchJSON(const std::string& url) {
	CURL* curl;
	CURLcode res;
	std::string response;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "DanbooruClient/1.0");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		std::cerr << "Curl_easy_perform failed: " << curl_easy_strerror(res) << std::endl;
		response = {};
	}

	curl_easy_cleanup(curl);
	return response;
}

int main() {
	const char* apiKeyEnv = std::getenv("DanbooruApiKey");
	const char* userEnv = std::getenv("DanbooruApiUser");

	if (!apiKeyEnv || !userEnv) {
		std::cerr << "Missing Danbooru API environment variables\n";
		std::exit(1);
	}

	const std::string API_KEY(apiKeyEnv);
	const std::string API_LOGIN_USERNAME(userEnv);

	const std::string API_URL = "https://danbooru.donmai.us/posts.json?api_key=" + API_KEY + "&login=" + API_LOGIN_USERNAME + "&";

	Menu menu;
	menu.show();

	UserSettings userSetting = parseUserSettings(menu.getChoice());

	while (userSetting.statusCode == -1) {
		std::cerr << "Invalid input. Please try again." << std::endl;
		system("pause");
		menu.clear();
		menu.show();
		userSetting = parseUserSettings(menu.getChoice());
	}

	const std::string requestUrl = buildDanbooruUrl(API_URL.c_str(), userSetting);

	userSetting.debug();
	DEBUG(requestUrl);

	const std::string rawData = fetchJSON(requestUrl);

	try {
		nlohmann::json jsondata = nlohmann::json::parse(rawData);
		vector < std::string > imgUrls;

		if (jsondata.empty()) {
			std::cout << "Response data is empty.";
		}
		else {
			for (int i = 0; i < jsondata.size(); i++) {
				nlohmann::json post = jsondata[i];

				if (post.contains("file_url") && post["file_url"].is_string())
				{
					imgUrls.push_back(static_cast<std::string>(jsondata[i]["file_url"]));
				}
			}

			// Create to a .txt file
			createImgUrlTxt(imgUrls, imgUrlPath);
			
			if (userSetting.isDownload) {
				downloadImg(imgUrlPath, destFolder);
			}
		}
	}
	catch (const nlohmann::json::parse_error& err) {
		std::cerr << "json_parse failed: " << err.what() << std::endl;
	}

	return 0;
}