#include "UserSettingParser.h"
#include <algorithm>

bool isNumber(const std::string& s) {
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

UserSettings parseUserSettings(vector<MenuOption> option) {
	UserSettings userSetting;

	for (MenuOption& opt : option) {
		if (opt.operationId == 1) {
			if (opt.input.empty()) continue;
			if (opt.selectedChoiceIndex == 0) {
				userSetting.tags = opt.input;
			}
			else {
				userSetting.postId = opt.input;
			}
		}
		if (opt.operationId == 2) {
			if (opt.input.empty() || !isNumber(opt.input)) {
				return userSetting = { "", "", 0, false, false, false, -1 };
			}
			else {
				userSetting.limits = std::stoi(opt.input);
			}
		}

		if (opt.operationId == 3) userSetting.nsfw = opt.toggle;
		if (opt.operationId == 4) userSetting.isRandom = opt.toggle;
		if (opt.operationId == 5) userSetting.isDownload = opt.toggle;
	}

	return userSetting;
}