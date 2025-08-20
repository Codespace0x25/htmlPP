#pragma once
#include <functional>
#include <string>
#include <unordered_map>

namespace Server {

struct Request {
  std::string method;
  std::string path;
  std::unordered_map<std::string, std::string> query;
  std::string body;
};

class Server {
public:
  Server(const std::string &ip, int port);
  void setStaticDir(const std::string &dir);

  void addPath(const std::string &path,
               std::function<std::string(const Request &)> func,
               const std::string &method = "GET");

  void addPath(const std::string &path, const std::string &response,
               const std::string &method = "GET");

  void StartServe(const std::string &name);

private:
  std::string ip;
  int port;
  std::string staticDir;

  std::unordered_map<std::string,
                     std::unordered_map<std::string, std::function<std::string(
                                                         const Request &)>>>
      funcMap;

  std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
      stringMap;

  void handle_client(int client_socket);
  std::string get_mime_type(const std::string &path);
};

} // namespace Server
