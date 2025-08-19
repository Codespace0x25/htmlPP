#pragma once
#include <string>
#include <unordered_map>

namespace Server {

  class Server {
  public:
    Server(const std::string& ip, int port);

    void addPath(const std::string& path, const std::string& html,const std::string methon = "GET");

    void setStaticDir(const std::string& dir);

    void StartServe(const std::string& siteName = "");

    ~Server();

  private:
    std::unordered_map<std::string, std::unordered_map<std::string,std::string>> map;
    std::string ip;
    int port;
    std::string staticDir;
  };

}
