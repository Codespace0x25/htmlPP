#include "Componet.hpp"
#include <sstream>

namespace Comment {

Component::Component(const std::string &tag) : tag(tag) {}

Component::~Component() {
  for (auto *c : children)
    delete c;
}

void Component::setAttr(const std::string &key, const std::string &value) {
  attrs[key] = value;
}

void Component::setJS(const std::string &jsCode) { js = jsCode; }

void Component::setStyle(const std::string &css) { style = css; }

void Component::addChild(Component *child) { children.push_back(child); }

void Component::addClass(const std::string &className) {
  std::string existing = "";
  auto it = attrs.find("class");
  if (it != attrs.end())
    existing = it->second;
  if (!existing.empty())
    existing += " ";
  existing += className;
  setAttr("class", existing);
}

size_t Component::getChildCount() const { return children.size(); }
std::string Component::render() const {
  std::ostringstream html;
  html << "<" << tag;

  for (const auto &[key, val] : attrs) {
    html << " " << key << "=\"" << val << "\"";
  }

  html << ">";

  for (const auto &child : children) {
    html << child->render();
  }

  html << "</" << tag << ">";

  if (!style.empty()) {
    html << "<style>" << style << "</style>";
  }

  if (!js.empty()) {
    html << "<script>" << js << "</script>";
  }

  return html.str();
}

} // namespace Comment
