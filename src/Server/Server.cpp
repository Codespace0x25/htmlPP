#include "Server.hpp"
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <cstring>      // For strerror
#include <unistd.h>     // For close()
#include <netinet/in.h> // For sockaddr_in
#include <arpa/inet.h>  // For inet_addr
#include <fstream>      // For file reading
#include <sys/stat.h>   // For stat()

namespace Server {

  Server::Server(const std::string& ip, int port)
    : ip(ip), port(port) {}

  Server::~Server() {}

  void Server::addPath(const std::string& path, const std::string& html,const std::string methon) {
    map[methon][path] = html;
  }

  void Server::setStaticDir(const std::string& dir) {
    staticDir = dir;
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

  static std::string http_response_raw(const std::vector<char>& data, const std::string& contentType) {
    std::ostringstream response;
    response << "HTTP/1.1 200 OK\r\n"
             << "Content-Type: " << contentType << "\r\n"
             << "Content-Length: " << data.size() << "\r\n"
             << "Connection: close\r\n\r\n";
    std::string headers = response.str();
    return headers + std::string(data.begin(), data.end());
  }

  static std::string http_404() {
    return "HTTP/1.1 404 Not Found\r\n"
           "Content-Type: text/html\r\n"
           "Content-Length: 24\r\n"
           "Connection: close\r\n\r\n"
           "<h1>404 Not Found</h1>";
  }

static std::string get_mime_type(const std::string& path) {
    if (path.ends_with(".html") || path.ends_with(".htm")) return "text/html";
    if (path.ends_with(".css"))  return "text/css";
    if (path.ends_with(".js"))   return "application/javascript";
    if (path.ends_with(".png"))  return "image/png";
    if (path.ends_with(".jpg") || path.ends_with(".jpeg")) return "image/jpeg";
    if (path.ends_with(".gif"))  return "image/gif";
    if (path.ends_with(".svg"))  return "image/svg+xml";
    if (path.ends_with(".ico"))  return "image/x-icon";
    if (path.ends_with(".webp")) return "image/webp";
    if (path.ends_with(".mp3"))  return "audio/mpeg";
    if (path.ends_with(".wav"))  return "audio/wav";
    if (path.ends_with(".ogg"))  return "audio/ogg";
    if (path.ends_with(".flac")) return "audio/flac";
    if (path.ends_with(".aac"))  return "audio/aac";
    if (path.ends_with(".m4a"))  return "audio/mp4";
    if (path.ends_with(".mp4"))  return "video/mp4";
    if (path.ends_with(".webm")) return "video/webm";
    if (path.ends_with(".ogg"))  return "video/ogg";
    if (path.ends_with(".mov"))  return "video/quicktime";
    if (path.ends_with(".avi"))  return "video/x-msvideo";
    if (path.ends_with(".mkv"))  return "video/x-matroska";
    if (path.ends_with(".woff"))  return "font/woff";
    if (path.ends_with(".woff2")) return "font/woff2";
    if (path.ends_with(".ttf"))   return "font/ttf";
    if (path.ends_with(".otf"))   return "font/otf";
    return "application/octet-stream";
}

  void handle_client(int client_socket,
                     std::unordered_map<std::string, std::unordered_map<std::string,std::string>> map,
                     std::string staticDir) {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    read(client_socket, buffer, sizeof(buffer) - 1);

    std::istringstream request(buffer);
    std::string method, path;
    request >> method >> path;

    if (method == "GET") {
      auto it = map["GET"].find(path);
      std::string response;
      if (it != map["GET"].end()) {
        response = http_response(it->second);
        send(client_socket, response.c_str(), response.size(), 0);
      } else {
        // Try static dir
        std::string filepath = staticDir + path;
        struct stat s;
        if (stat(filepath.c_str(), &s) == 0 && S_ISREG(s.st_mode)) {
          std::ifstream file(filepath, std::ios::binary);
          std::vector<char> data((std::istreambuf_iterator<char>(file)), {});
          std::string mime = get_mime_type(filepath);
          std::string raw = http_response_raw(data, mime);
          send(client_socket, raw.c_str(), raw.size(), 0);
        } else {
          response = http_404();
          send(client_socket, response.c_str(), response.size(), 0);
        }
      }
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

      std::thread client_thread(handle_client, client_socket, map, staticDir);
      client_thread.detach();
    }

    close(server_fd);
  }

} // namespace Server
