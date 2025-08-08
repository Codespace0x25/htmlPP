#pragma once
#include <string>
#include <unordered_map>

namespace Server {

  class Server {
  public:
    Server(const std::string& ip, int port);

    // maps a URL path ("/home", "/about") to raw HTML to serve
    void addPath(const std::string& path, const std::string& html);

    // starts the server — likely blocking call
    void StartServe(const std::string& siteName = "");

    ~Server();

  private:
    std::unordered_map<std::string, std::string> map; // path -> HTML
    std::string ip;
    int port;
  };

}
