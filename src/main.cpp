#include <iostream>
#include <json.hpp>
#include <HTTPRequest.hpp>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " [word]" << std::endl;
        return 1;
    }
    std::string target = argv[1];
    for (int i = 2; i < argc; ++i) {
        target += "%20";
        target += argv[i];
    }
    std::string url = "http://www.iciba.com/index.php?a=getWordMean&c=search&list=1&word=" + target;
    http::Request request(url);
    http::Response response;
    try {
        response = request.send("GET");
    } catch (std::exception &e) {
        std::cerr << "fatal: Request failed, error: " << e.what();
        return 1;
    }
    auto result = json::parse(response.body.data());
    auto meanings = result["baesInfo"]["symbols"];
    for (auto &meaning : meanings[0]["parts"]) {
        auto part = meaning["part"].get<std::string>();
        char left[17] = "            ";
        strcpy(left, part.data());
        left[part.size()] = ':';
        std::cout << left;
        bool first = true;
        for (auto &text : meaning["means"]) {
            if (!first) {
                std::cout << ", ";
            } else {
                first = false;
            }
            std::cout << text.get<std::string>();
        }
        std::cout << std::endl;
    }
    return 0;
}
