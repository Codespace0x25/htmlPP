#include "Page/Main.hpp"
#include "Componet/CodeBlock.hpp"
#include "Componet/Componet.hpp"
#include "Componet/Page.hpp"
#include "Componet/ScriptBuilder.hpp"
#include "Componet/ScriptComponet.hpp"
#include "Componet/TextComponet.hpp"
#include "Componet/UIAlert.hpp"
#include "Componet/UIHeader.hpp"
#include "Componet/UILink.hpp"
#include "Componet/UINavbar.hpp"
#include "Componet/UIP.hpp"
#include "Componet/UISandBox.hpp"
#include "Componet/UITabs.hpp"
#include "Server/Server.hpp"
#include <iostream>



int main() {
  Server::Server server("0.0.0.0", 8080);

  Main main;

  std::cout << main.render() << "\n";
  server.addPath("/", main.render());

  server.StartServe("example");
}
