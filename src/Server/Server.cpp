#include "Server.hpp"
#include <arpa/inet.h>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <stream>
#include <unistd.h>
#include <vector>

namespace Server {

Server::Server(const std::string &ip, int port) : ip(ip), port(port) {}

void Server::setStaticDir(const std::string &dir) { staticDir = dir; }

void Server::addPath(const std::string &path,
                     std::function<std::string(const Request &)> func,
                     const std::string &method) {
  funcMap[path][method] = func;
}

void Server::addPath(const std::string &path, const std::string &response,
                     const std::string &method) {
  stringMap[path][method] = response;
}

std::string Server::get_mime_type(const std::string &path) {
  if (path.ends_with(".html"))
    return "text/html";
  if (path.ends_with(".css"))
    return "text/css";
  if (path.ends_with(".js"))
    return "application/javascript";
  if (path.ends_with(".png"))
    return "image/png";
  if (path.ends_with(".jpg") || path.ends_with(".jpeg"))
    return "image/jpeg";
  if (path.ends_with(".mp3"))
    return "audio/mpeg";
  if (path.ends_with(".mp4"))
    return "video/mp4";
  return "text/plain";
}

void Server::handle_client(int client_socket) {
  char buffer[4096];
  int bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
  if (bytes_read <= 0) {
    close(client_socket);
    return;
  }
  buffer[bytes_read] = '\0';
  std::string fullRequest(buffer, bytes_read);

  std::istringstream requestStream(fullRequest);
  std::string method, path, version;
  requestStream >> method >> path >> version;

  // extract query params
  std::string queryStr;
  size_t qpos = path.find('?');
  if (qpos != std::string::npos) {
    queryStr = path.substr(qpos + 1);
    path = path.substr(0, qpos);
  }

  std::unordered_map<std::string, std::string> query;
  std::istringstream qss(queryStr);
  std::string kv;
  while (std::getline(qss, kv, '&')) {
    size_t eq = kv.find('=');
    if (eq != std::string::npos) {
      query[kv.substr(0, eq)] = kv.substr(eq + 1);
    } else {
      if (!kv.empty())
        query[kv] = "";
    }
  }

  // clean body
  std::string body;
  size_t headerEnd = fullRequest.find("\r\n\r\n");
  if (headerEnd != std::string::npos) {
    body = fullRequest.substr(headerEnd + 4);
  }

  std::string response;
  // function-based routes
  if (funcMap.count(path) && funcMap[path].count(method)) {
    Request req{method, path, query, body};
    std::string result = funcMap[path][method](req);
    response =
        "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" + result;
  }
  // string-based routes
  else if (stringMap.count(path) && stringMap[path].count(method)) {
    std::string result = stringMap[path][method];
    response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + result;
  }
  // static file serving
  else if (!staticDir.empty()) {
    std::string filePath = staticDir + path;
    if (std::filesystem::is_directory(filePath)) {
      filePath += "/index.html";
    }
    if (std::filesystem::exists(filePath)) {
      std::ifstream file(filePath, std::ios::binary);
      std::ostringstream ss;
      ss << file.rdbuf();
      std::string fileContent = ss.str();
      response = "HTTP/1.1 200 OK\r\nContent-Type: " + get_mime_type(filePath) +
                 "\r\n\r\n" + fileContent;
    } else {
      response =
          "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
    }
  }
  // fallback
  else {
    response =
        "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found";
  }

  send(client_socket, response.c_str(), response.size(), 0);
  close(client_socket);
}

void Server::StartServe(const std::string &name) {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    perror("socket failed");
    exit(1);
  }

  int opt = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ip.c_str());
  address.sin_port = htons(port);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    close(server_fd);
    exit(1);
  }

  if (listen(server_fd, 10) < 0) {
    perror("listen failed");
    close(server_fd);
    exit(1);
  }

  std::cout << name << " running on http://" << ip << ":" << port << "\n";

  while (true) {
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int client_socket =
        accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket < 0) {
      perror("accept failed");
      continue;
    }
    handle_client(client_socket);
  }
}

} // namespace Server
