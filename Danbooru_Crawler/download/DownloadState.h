#pragma once

class DownloadState {
    public:
        long long getOldestId(const char* tag);
        void updateOldestId(long long oldestId, const char* tag);
};