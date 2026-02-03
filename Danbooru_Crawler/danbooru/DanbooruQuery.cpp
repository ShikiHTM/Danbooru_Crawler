#include "danbooru/DanbooruQuery.h"
#include <string>
#include <sstream>

DanbooruQuery::DanbooruQuery(const char* apiKeyEnv, const char* apiLoginUsernameEnv) {
	this->API_KEY = std::getenv(apiKeyEnv);
	this->API_LOGIN_USERNAME = std::getenv(apiLoginUsernameEnv);

	if(!this->API_KEY || !this->API_LOGIN_USERNAME) {
		throw std::runtime_error("Missing Danbooru API environment variables");
	}
}

std::string DanbooruQuery::buildUrl(const UserSettings& settings, long long oldestId) {
	std::ostringstream requestUrl;
	requestUrl << API_URL;

	// Append authentication parameters
	requestUrl << "api_key=" << API_KEY << "&login=" << API_LOGIN_USERNAME << "&";

	if(!settings.tags.empty()) {
		requestUrl << "tags=" << settings.tags << "&";
	}

	if(settings.limits > 0) {
		requestUrl << "limit=" << settings.limits << "&";
	}

	if(!settings.nsfw) {
		requestUrl << "rating=-explicit&";
	}

	requestUrl << "page=b" << oldestId << "&";

	return requestUrl.str();
};