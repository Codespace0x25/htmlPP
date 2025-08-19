#include "Page.hpp"
#include <sstream>

Page::Page() : title("Untitled Page") {}

Page::~Page() {}

void Page::setTitle(const std::string &t) { title = t; }

void Page::setFavicon(const std::string &emoji) { favicon = emoji; }

void Page::setCustomCSS(const std::string &css) { customCSS = css; }

void Page::add(Comment::Component *component) {
  components.push_back(component);
}

void Page::addComponent(Comment::Component *component) {
  add(component); // same thing
}

std::string Page::defaultCSS() {
  return R"(
    body {
      background-color: #0b0b15;
      color: #e0d8ff;
      font-family: 'Segoe UI', sans-serif;
      padding: 2rem;
      max-width: 800px;
      margin: auto;
      line-height: 1.6;
    }

    a, .ui-link {
      color: #cda1ff;
      text-decoration: none;
    }

    a:hover, .ui-link:hover {
      text-decoration: underline;
    }

    .comment {
      border: 1px solid #333;
      background-color: #1e1e2f;
      border-radius: 5px;
      padding: 1rem;
      margin-bottom: 1rem;
    }

    .ui-alert {
      padding: 1rem;
      border-radius: 5px;
      margin: 1rem 0;
      font-weight: bold;
    }

    .ui-alert-info    { background-color: #222244; color: #aaccff; }
    .ui-alert-warning { background-color: #443322; color: #ffcc88; }
    .ui-alert-error   { background-color: #442222; color: #ff8888; }
    .ui-alert-success { background-color: #224422; color: #88ff88; }

    .ui-button {
      background-color: #8758ff;
      border: none;
      color: white;
      padding: 0.6rem 1.2rem;
      border-radius: 4px;
      font-size: 1rem;
      cursor: pointer;
      transition: background 0.2s ease-in-out;
    }

    .ui-button:hover {
      background-color: #a078ff;
    }

    .ui-input,
    .ui-textinput,
    .ui-textarea,
    .ui-select {
      background-color: #1c1c2b;
      border: 1px solid #444;
      color: #eee;
      border-radius: 4px;
      padding: 0.5rem;
      width: 100%;
      margin-bottom: 1rem;
      box-sizing: border-box;
    }

    .ui-card {
      background-color: #1c1c2c;
      border-radius: 6px;
      padding: 1rem;
      box-shadow: 0 0 10px #00000088;
      margin: 1rem 0;
    }

    .ui-header {
      color: #d3bfff;
      margin: 1rem 0 0.5rem;
    }

    .ui-checkbox {
      display: flex;
      align-items: center;
      margin: 0.5rem 0;
      gap: 0.5rem;
    }

    .ui-modal {
      position: fixed;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      background: rgba(0, 0, 0, 0.6);
      display: none;
      justify-content: center;
      align-items: center;
      z-index: 999;
    }

    .ui-modal-content {
      background: #1e1e2f;
      padding: 2rem;
      border-radius: 6px;
      max-width: 500px;
      width: 90%;
      box-shadow: 0 0 20px #000000aa;
    }

    .ui-modal-header {
      font-size: 1.2rem;
      font-weight: bold;
      margin-bottom: 1rem;
      color: #f0d0ff;
    }

    .ui-modal-body {
      font-size: 1rem;
      color: #ccc;
    }

    .ui-p {
      margin: 1rem 0;
    }

    .code-block-wrapper {
      background: #16161e;
      border-radius: 6px;
      margin: 1rem 0;
      overflow: hidden;
      box-shadow: 0 0 10px #0006;
    }
    
    .code-block-header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      background: #1e1e2f;
      padding: 0.5rem 1rem;
      font-size: 0.8rem;
      color: #cda1ff;
      border-bottom: 1px solid #333;
    }
    
    .code-lang-label {
      font-weight: bold;
      text-transform: uppercase;
      color: #b392f0;
    }
    
    .copy-btn {
      background: #292944;
      border: none;
      color: #eee;
      padding: 0.3rem 0.8rem;
      font-size: 0.8rem;
      border-radius: 3px;
      cursor: pointer;
    }
    
    .copy-btn:hover {
      background: #423080;
    }
    
    .code-block {
      padding: 1rem;
      font-family: 'Fira Code', monospace;
      font-size: 0.9rem;
      overflow-x: auto;
      color: #c0c0ff;
    }

    .UISandBox-iframe {
      border: none;
      width: 100%;
      height: 400px;
      margin-top: 1rem;
      border-radius: 5px;
      background-color: #1a1a2a;
    }

    ul {
      padding-left: 1.2rem;
    }

    li {
      margin: 0.4rem 0;
    }

    .ui-navbar {
        position: fixed;
        top: 0%;
        left: 0%;
        width: 100%;
        background: #1b1b2b;
        color: #f0f0ff;
        display: flex;
        align-items: center;
        padding: 0.8rem 1.5rem;
        box-shadow: 0 2px 4px #000a;
        z-index: 999;
    }
    
    .ui-navbar-title {
        font-size: 1.2rem;
        font-weight: bold;
        color: #b294ff;
        margin-right: 10px;
    }
    
    .ui-navbar-menu {
        display: flex;
        gap: 1rem;
    }
    
    .ui-nav-item {
        text-decoration: none;
        color: #ccc;
        font-weight: 500;
    }
    
    .ui-nav-item:hover {
        color: #fff;
    }
    
    .ui-navbar-avatar {
        height: 32px;
        width: 32px;
        border-radius: 50%;
        margin-left: 1rem;
    }
    
    /* Tabs */
    .ui-tabs {
        margin-top: 4rem;
    }
    
    .ui-tab-buttons {
        display: flex;
        gap: 1rem;
        padding-bottom: 0.5rem;
        border-bottom: 2px solid #333;
    }
    
    .ui-tab-button {
        background: none;
        border: none;
        color: #ccc;
        padding: 0.5rem 1rem;
        font-size: 1rem;
        cursor: pointer;
    }
    
    .ui-tab-button:hover {
        color: #fff;
    }
    
    .ui-tab-views {
        margin-top: 1rem;
    }
    
    .ui-tab-content.hidden {
       display: none;
    }


  )";
}

std::string Page::render() const {
  std::ostringstream html;

  html << "<!DOCTYPE html><html><head><meta charset='UTF-8'>"
       << "<title>" << title << "</title>";

  html << "<link rel='icon' href='data:image/svg+xml,<svg "
          "xmlns=%22http://www.w3.org/2000/svg%22>"
       << "<text y=%22.9em%22 font-size=%2216%22>" << favicon
       << "</text></svg>' />";

  html << "<style>" << (customCSS.empty() ? defaultCSS() : customCSS)
       << "</style>"
       << "</head><body>";

  for (const auto *c : components)
    html << c->render();

  html << "</body></html>";
  return html.str();
}
