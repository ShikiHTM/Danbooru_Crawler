#pragma once

#include <string>
#include <vector>

class ImageDownloader {
    public:
        static void downloadImages(const std::string& imgUrlPath, const std::string& destFolderPath);
};