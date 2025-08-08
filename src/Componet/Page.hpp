#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Componet.hpp"

class Page {
public:
  Page();
  
  void setTitle(const std::string& title);

  void setFavicon(const std::string& emoji);

  void setCustomCSS(const std::string& css);

  void add(Comment::Component* component);
  void addComponent(Comment::Component* component);

  std::string render() const;

  ~Page();

private:
  std::string title;
  std::string favicon = "🌐";
  std::string customCSS;
  std::vector< Comment::Component*> components;
  

  static std::string defaultCSS();
};
