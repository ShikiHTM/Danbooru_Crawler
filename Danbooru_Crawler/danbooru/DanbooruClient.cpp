#include "danbooru/DanbooruClient.h"
#include <string>
#include <sstream>
#include "config/UserSetting.h"

std::string buildDanbooruUrl(const char* apiUrl, const UserSettings& s) {
	std::ostringstream url;
	url << apiUrl;

	if (!s.tags.empty()) {
		url << "tags=" << s.tags << "&";
	}

	if (!s.nsfw) {
		url << "rating=-explicit&";
	}

	if (s.limits > 0) {
		url << "limit=" << s.limits << "&";
	}

	return url.str();
}