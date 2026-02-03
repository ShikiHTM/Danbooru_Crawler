#include "DownloadState.h"
#include <fstream>
#include "include/nlohmann/json.hpp"

long long DownloadState::getOldestId(const char* tag) {
	nlohmann::json j;

	std::ifstream i("lastedId.json");
	if(i.is_open()) {
		i >> j;
		i.close();
	}

	if(j.contains(tag)) {
		return j[tag].get<long long>();
	}
    
	return 999999999;
}

void DownloadState::updateOldestId(long long oldestId, const char* tag) {
	nlohmann::json j;

	std::ifstream i("lastedId.json");
	if(i.is_open()) {
		i >> j;
		i.close();
	}

	if(j.contains(tag)) {
		j[tag] = oldestId;
	} else {
		j.emplace(tag, oldestId);
	}

	std::ofstream o("lastedId.json");
	o << j.dump(4);
	o.close();
}