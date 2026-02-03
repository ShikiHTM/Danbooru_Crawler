#include <iostream>
#include <vector>
#include <string>
#include "config/UserSetting.h"
#include "config/UserSettingParser.h"
#include "danbooru/DanbooruQuery.h"
#include "danbooru/DanbooruClient.h"
#include "net/HttpClient.h"
#include "download/ImageDownload.h"
#include "download/DownloadState.h"
#include "menu/Menu.h"

#define DEBUG(x) std::cout << x << '\n'

const std::string destFolder = "images";
const std::string imgUrlPath = "images.txt";

void writeUrlToFile(std::vector<std::string>& imgUrls) {
	FILE* file = fopen(imgUrlPath.c_str(), "w");
	if (file == nullptr) {
		std::cerr << "Error opening file for writing: " << imgUrlPath << std::endl;
		return;
	}
	for (const auto& url : imgUrls) {
		fprintf(file, "%s\n", url.c_str());
	}
	fclose(file);
}

void runCrawler() {
	DanbooruQuery query("DanbooruApiKey", "DanbooruApiUser");
	DanbooruClient client;
	DownloadState state;
	ImageDownloader downloader;
	HttpClient httpClient;

	Menu menu;

	menu.show();

	const std::vector<MenuOption>& choices = menu.getChoice();

	UserSettings settings = parseUserSettings(choices);

	long long cursor = state.getOldestId(settings.tags.c_str());

	const std::string requestUrl = query.buildUrl(settings, cursor);

	auto posts = client.fetchPosts(requestUrl, httpClient);

	if(posts.empty()) return;

	std::vector<std::string> imgUrls;
	long long oldestId = cursor;

	for(const auto& post: posts) {
		imgUrls.push_back(post.file_url);
		oldestId = std::min(oldestId, post.id);
	}

	if(settings.isDownload) {
		writeUrlToFile(imgUrls);
		downloader.downloadImages(imgUrlPath, destFolder);
	}

	state.updateOldestId(oldestId, settings.tags.c_str());
}

int main() {
	try {
		runCrawler();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}