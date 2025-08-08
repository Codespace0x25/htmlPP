#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace Comment {

class Component {
public:
  Component(const std::string &tag = "div");

  void setAttr(const std::string &key, const std::string &value);
  void setJS(const std::string &jsCode);
  void setStyle(const std::string &css);

  void addClass(const std::string &className);
  void addChild(Component *child);

  size_t getChildCount() const;

  virtual std::string render() const;

  virtual ~Component();

protected:
  std::string tag;
  std::unordered_map<std::string, std::string> attrs;
  std::string js;
  std::string style;
  std::vector<Component *> children;
};

} // namespace Comment
