#include "Server.hpp"
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <cstring>      // For strerror
#include <unistd.h>     // For close()
#include <netinet/in.h> // For sockaddr_in
#include <arpa/inet.h>  // For inet_addr

namespace Server {

  Server::Server(const std::string& ip, int port)
    : ip(ip), port(port) {}

  Server::~Server() {}

  void Server::addPath(const std::string& path, const std::string& html) {
    map[path] = html;
  }

  static std::string http_response(const std::string& body, const std::string& contentType = "text/html") {
    std::ostringstream response;
    response << "HTTP/1.1 200 OK\r\n"
             << "Content-Type: " << contentType << "; charset=UTF-8\r\n"
             << "Content-Length: " << body.size() << "\r\n"
             << "Connection: close\r\n\r\n"
             << body;
    return response.str();
  }

  static std::string http_404() {
    return "HTTP/1.1 404 Not Found\r\n"
           "Content-Type: text/html\r\n"
           "Content-Length: 24\r\n"
           "Connection: close\r\n\r\n"
           "<h1>404 Not Found</h1>";
  }

  void handle_client(int client_socket, std::unordered_map<std::string, std::string> map) {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    read(client_socket, buffer, sizeof(buffer) - 1);

    std::istringstream request(buffer);
    std::string method, path;
    request >> method >> path;

    if (method == "GET") {
      auto it = map.find(path);
      std::string response;
      if (it != map.end()) {
        response = http_response(it->second);
      } else {
        response = http_404();
      }
      send(client_socket, response.c_str(), response.size(), 0);
    }

    close(client_socket);
  }

  void Server::StartServe(const std::string& siteName) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
      std::cerr << "Socket failed: " << strerror(errno) << "\n";
      return;
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
      std::cerr << "Bind failed: " << strerror(errno) << "\n";
      return;
    }

    if (listen(server_fd, 10) < 0) {
      std::cerr << "Listen failed: " << strerror(errno) << "\n";
      return;
    }

    std::cout << "🚀 Server '" << siteName << "' started at http://" << ip << ":" << port << "\n";

    while (true) {
      socklen_t addrlen = sizeof(address);
      int client_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
      if (client_socket < 0) {
        std::cerr << "Accept failed: " << strerror(errno) << "\n";
        continue;
      }

      // Copy map to give to thread (could be optimized later with shared_ptr or const ref + mutex)
      std::thread client_thread(handle_client, client_socket, map);
      client_thread.detach(); // We don’t care when it finishes
    }

    close(server_fd);
  }

} // namespace Server
