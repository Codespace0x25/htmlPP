#pragma once
#include <string>
#include <unordered_map>
#include <functional>

namespace Server {

  class Server {
  public:
    Server(const std::string& ip, int port);

    // static HTML routes
    void addPath(const std::string& path, const std::string& html, const std::string method = "GET");

    // dynamic function routes
    void addPath(const std::string& path, std::function<std::string(const std::string&)> func, const std::string method = "GET");

    void setStaticDir(const std::string& dir);

    void StartServe(const std::string& siteName = "");

    ~Server();

  private:
    std::unordered_map<std::string, std::unordered_map<std::string,std::string>> staticMap;
    std::unordered_map<std::string, std::unordered_map<std::string,std::function<std::string(const std::string&)>>> funcMap;
    std::string ip;
    int port;
    std::string staticDir;
  };

}
