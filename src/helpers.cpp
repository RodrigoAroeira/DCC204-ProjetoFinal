#include <cstdlib>
#include <iostream>
#include <sstream>

void limparTela() {
  int val =
#ifdef _WIN32
      system("cls");
#else
      system("clear");
#endif

  (void)val; // Evitar warn_unused_result
}

[[nodiscard]] std::streambuf *spoofInput(const std::string &txt) {
  static std::istringstream inputSpoof;
  inputSpoof.str(txt);
  return std::cin.rdbuf(inputSpoof.rdbuf());
}
