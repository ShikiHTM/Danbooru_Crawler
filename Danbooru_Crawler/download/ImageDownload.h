#pragma once

#include <string>
#include <vector>

long long getLastedId(const char* tag);
void lastedIdByTag(long long& lastId, const char* tag);
void createImgUrlTxt(std::vector<std::string> imgUrls, const std::string &path);
void downloadImg(const std::string& imgUrlPath, const std::string& destFolderPath);