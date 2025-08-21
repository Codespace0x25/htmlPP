Gotcha! We can just remove the license section entirely and leave it as “free to use” in the description without specifying a formal license. Here's the README adjusted:

---

# htmlpp

`htmlpp` is a lightweight C++ framework for building HTML pages and components with ease. It provides a **React-like component system** in pure C++, allowing you to construct dynamic pages, embed JavaScript, style with CSS, and organize content using reusable components.

---

## Features

* Component-based HTML rendering in C++
* Built-in UI components: `UIButton`, `UIAlert`, `UICard`, `UIHeader`, `UIInput`, `UILink`, `UIModal`, `UINavbar`, `UIP`, `UISandBox`, `UISelect`, `UITabs`, `UITextArea`, `UITextInput`, `UIVideo`, `UIAudio`, `UIImage`
* Script helpers via `ScriptBuilder` and `ScriptFetch`
* Easily extendable: create custom components
* Supports embedding custom CSS and JS
* Includes helper components like `UL` and `CodeBlock`

---

## Installation

Clone the repository:

```bash
git clone https://github.com/codespace0x25/htmlpp.git
cd htmlpp
```

Include the headers in your C++ project:

```cpp
#include "Page.hpp"
#include "Componet/UIButton.hpp"
#include "Componet/UIAlert.hpp"
```

Compile your project with a C++17 or later compiler:

```bash
g++ -std=c++17 main.cpp -o mypage
```

---

## Usage Example

```cpp
#include "Page.hpp"
#include "Componet/UIButton.hpp"
#include "Componet/UIAlert.hpp"
#include "Componet/UIHeader.hpp"
#include <iostream>

int main() {
    Page page;
    page.setTitle("Hello htmlpp!");
    page.setFavicon("🚀");

    page.add(new UIHeader("Welcome to htmlpp", 1));
    page.add(new UIAlert("This is an info alert", "info"));
    page.add(new UIButton("Click Me", "alert('Button clicked!')"));

    std::cout << page.render() << std::endl;
    return 0;
}
```

This generates a fully styled HTML page with interactive components.

---
## Core Components

* **Page & Component System**

  * `Page` – the root page container
  * `Component` – base class for all HTML elements
* **UI Components**

  * Buttons, alerts, modals, inputs, videos, audio, images, cards, headers, navbars, and more
* **Script Components**

  * `ScriptBuilder` – easy JS event binding
  * `ScriptFetch` – fetch API helper
  * `ScriptComponent` – general JS container

---

## Extending Components

You can create custom components by inheriting from `Comment::Component`:

```cpp
class MyCard : public Comment::Component {
public:
    MyCard(const std::string& text) : Component("div") {
        setAttr("class", "ui-card");
        addChild(new TextComponent(text));
    }
};
```

---

## Contributing

Contributions are welcome! Feel free to submit issues, feature requests, or pull requests.
