#include <iostream>
#include <functional>
#include <vector>
#include <string>

int main(int argc, const char** argv) {
  if (argc < 3 || argc > 4) {
    std::cerr << "Usage: " << argv[0] << " count alphabet [string]"
              << std::endl
              << std::endl
              << "If the optional string argument is used, the program will print "
                 "the position of the given string in the sequence"
              << std::endl;
    return -1;
  }

  const bool gen = (argc == 3);

  std::string alphabet(argv[2]);
  if (alphabet == "AA")
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  else if (alphabet == "00")
    alphabet = "0123456789";

  if (alphabet.size() > 256)
    throw std::invalid_argument("more than 256 chars in an alphabet is disallowed");

  const size_t n = std::stoull(argv[1]);
  const size_t k = alphabet.size();
  std::vector<uint8_t> a(k * n, 0);

  std::string ret;

  std::function<void(size_t, size_t)> inner = [&](size_t t, size_t p) {
    if (__builtin_expect(t <= n, 0)) {
      a[t] = a[t - p];
      inner(t + 1, p);
      for (size_t i = a[t - p] + 1; i < k; ++i) {
        a[t] = i;
        inner(t + 1, t);
      }
    }
    else if (__builtin_expect(!(n % p), 0)) {
      auto begin = a.begin() + 1;
      auto end = begin + p;
      for (auto iter = a.begin() + 1; iter != end; ++iter)
        ret.push_back(alphabet[*iter]);
    }
  };

  inner(1, 1);

  if (gen)
    std::cout << ret << std::endl;
  else {
    std::cout << ret.find(argv[3]) << std::endl;
  }

  return 0;
}
