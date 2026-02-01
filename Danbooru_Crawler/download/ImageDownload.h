#pragma once

#include <string>
#include <vector>

void createImgUrlTxt(std::vector<std::string> imgUrls, const std::string &path);
void downloadImg(const std::string& imgUrlPath, const std::string& destFolderPath);