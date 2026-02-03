#include "DanbooruClient.h"
#include "include/nlohmann/json.hpp"
#include "net/HttpClient.h"

std::vector<DanbooruPost> DanbooruClient::fetchPosts(const std::string& requestUrl, HttpClient& httpClient) {

	const std::string rawData = httpClient.get(requestUrl);
	if(rawData.empty()) {
		std::cerr << "Failed to fetch data from Danbooru API." << std::endl;
		return {};
	}

	std::vector<DanbooruPost> posts;

	try {
		nlohmann::json jsondata = nlohmann::json::parse(rawData);

		if (jsondata.empty()) {
			std::cout << "Response data is empty.";
		}
		else {
			for (const nlohmann::json& post: jsondata) {
				if(!post.contains("id")) continue;

				long long postId = post["id"].get<long long>();

				if (post.contains("file_url") && post["file_url"].is_string()) {
					posts.push_back(DanbooruPost{
						.id = postId,
						.file_url = post["file_url"].get<std::string>()
					});
				}
			}
		}
	}
	catch (const nlohmann::json::parse_error& err) {
		std::cerr << "json_parse failed: " << err.what() << std::endl;
	}

	return posts;
}