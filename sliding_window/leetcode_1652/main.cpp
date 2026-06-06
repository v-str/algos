#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using std::cout;
using std::fill;
using std::format;
using std::pair;
using std::vector;

pair<vector<int>, int> generateData() {
  // thread_local — переменная живёт своё время для каждого потока,
  // инициализируется один раз при первом вызове функции, а не при каждом входе.
  // std::mt19937 — генератор псевдослучайных чисел (алгоритм Mersenne Twister).
  // std::random_device{}() — аппаратный источник энтропии (настоящий шум),
  // используется как зерно (seed) для mt19937.
  thread_local std::mt19937 gen{std::random_device{}()};

  // std::normal_distribution<> — нормальное (гауссово) распределение.
  // Первый параметр — среднее (мат. ожидание), второй — стандартное отклонение.
  // <> без типа внутри означает double по умолчанию.
  // lenDist будет выдавать числа, сгруппированные вокруг 5.0,
  // большинство значений в диапазоне ~ [5 - 1.5, 5 + 1.5] = [3.5, 6.5].
  thread_local std::normal_distribution<> lenDist{5.0, 1.5};
  thread_local std::normal_distribution<> valDist{50.0, 20.0};

  // lenDist(gen) — получить случайное число из распределения lenDist,
  // передавая генератор gen. Возвращается double (напр. 4.732).
  // std::round() — округление до ближайшего целого (4.732 -> 5.0).
  // static_cast<int> — преобразование double в int (отбрасывает дробную часть,
  // но после round её уже нет, так что просто 5.0 -> 5).
  // std::clamp(value, lo, hi) — обрезает value, чтобы оно было в [lo, hi].
  // Итог: n будет целым от 3 до 7 включительно.
  int n = std::clamp(static_cast<int>(std::round(lenDist(gen))), 3, 7);

  // n / 2 — целочисленное деление, дробная часть отбрасывается (напр. 5/2 = 2).
  // kMax — верхняя граница для k, от 0 до n - n/2 (напр. при n=5: 5-2=3).
  int kMax = n - (n / 2);

  // std::uniform_int_distribution<> — равномерное распределение целых чисел.
  // Все числа от 0 до kMax включительно выпадают с равной вероятностью.
  std::uniform_int_distribution<> kDist{0, kMax};

  // Вытягиваем одно значение из этого распределения — итоговое k.
  int k = kDist(gen);

  // std::bernoulli_distribution — распределение Бернулли.
  // Возвращает true с вероятностью 0.45 (45%) и false с вероятностью 0.55
  // (55%).
  std::bernoulli_distribution negateDist{0.45};
  if (negateDist(gen)) {
    k = -k;  // с 45% шансом делаем k отрицательным
  }

  // Создаём пустой вектор для чисел кода.
  vector<int> code;

  // .reserve(n) — заранее выделяем память под n элементов,
  // чтобы push_back не перевыделял память много раз.
  code.reserve(n);

  for (int i = 0; i < n; ++i) {
    // valDist(gen) — случайное double ~ нормальное распределение со средним 50,
    // round -> int, clamp в [1, 100].
    code.push_back(
        std::clamp(static_cast<int>(std::round(valDist(gen))), 1, 100));
  }

  // Возвращаем пару (структуру из двух элементов):
  // вектор чисел и ключ k.
  // Фигурные скобки {} — uniform initialization, компилятор сам понимает,
  // что это pair<vector<int>, int>.
  return {code, k};
}

class Solution {
 public:
  // (2)

  vector<int> decrypt(vector<int>& code, int k) {
    vector<int> tV(code.size(), 0);
    if (!k) {
      return tV;
    }
    if (code.size() == 1) {
      return code;
    }
    int windowSum = 0, left, right;
    bool isNegativeK = (k < 0);

    if (isNegativeK) {
      right = code.size() - 1;
      left = right;
      while ((right - left) < abs(k)) {
        windowSum += code[left];
        --left;
      }
    } else {
      left = 1;
      right = left;
      while ((right - left) < k) {
        windowSum += code[right];
        ++right;
      }
    }

    tV[0] = windowSum;

    for (int i = 1; i < code.size(); ++i) {
      if (isNegativeK) {
        ++right;
        ++left;
      }
      if (right == code.size()) right = 0;
      if (left == code.size()) left = 0;
      windowSum += code[right];
      windowSum -= code[left];
      tV[i] = windowSum;
      if (!isNegativeK) {
        ++right;
        ++left;
      }
    }

    return tV;
  }

  // (2)

  // vector<int> decrypt(vector<int>& code, int k) {
  //   vector<int> tV(code.size(), 0);

  //   if (!k) {
  //     return tV;
  //   }

  //   if (code.size() == 1) {
  //     return code;
  //   }

  //   int windowSum = 0, left, right;

  //   bool isNegativeK = (k < 0);

  //   // если k отрицательное, то окно начнется раньше первого элемента
  //   if (isNegativeK) {
  //     right = code.size() - 1;
  //     left = right;
  //     while ((right - left) < abs(k)) {
  //       windowSum += code[left];
  //       --left;
  //     }
  //   } else {
  //     left = 1;
  //     right = left;
  //     while ((right - left) < k) {
  //       windowSum += code[right];
  //       ++right;
  //     }
  //   }

  //   tV[0] = windowSum;

  //   for (int i = 1; i < code.size(); ++i) {
  //     if (isNegativeK) {
  //       ++right;
  //       ++left;
  //     }

  //     if (right == code.size()) right = 0;
  //     if (left == code.size()) left = 0;

  //     windowSum += code[right];
  //     windowSum -= code[left];

  //     tV[i] = windowSum;

  //     if (!isNegativeK) {
  //       ++right;
  //       ++left;
  //     }
  //   }

  //   // real
  //   return tV;
  // }

  // (3)

  // vector<int> decrypt(vector<int>& code, int k) {
  //   vector<int> tV(code.size(), 0);

  //   if (!k) {
  //     return tV;
  //   }

  //   if (code.size() == 1) {
  //     return code;
  //   }

  //   int windowSum = 0, left = 1, right = left;

  //   bool rightDirection = (k > 0);

  //   // окно двигается циклично вправо
  //   if (rightDirection) {
  //     while ((right - left) < k) {
  //       windowSum += code[right];
  //       ++right;
  //     }
  //     tV[0] = windowSum;

  //     for (int i = 1; i < code.size(); ++i) {
  //       if (right == code.size()) right = 0;
  //       if (left == code.size()) left = 0;

  //       windowSum += code[right];
  //       windowSum -= code[left];

  //       tV[i] = windowSum;

  //       ++right;
  //       ++left;
  //     }
  //   }

  //   // окно двигается циклично влево
  //   if (!rightDirection) {
  //     k = abs(k);
  //     right = code.size() - 1;
  //     left = right;

  //     while ((right - left) < k) {
  //       windowSum += code[left];
  //       --left;
  //     }

  //     tV[0] = windowSum;

  //     for (int i = 1; i < code.size(); ++i) {
  //       if (left < 0) left = code.size() - 1;
  //       if (right < 0) right = code.size() - 1;

  //       windowSum += code[left];
  //       windowSum -= code[right];

  //       tV[i] = windowSum;

  //       --left;
  //       --right;
  //     }
  //   }

  //   return tV;
  // }
};

int main() {
  //   Solution s;
  //
  //   for (int i = 0; i < 5; ++i) {
  //     auto [code, k] = generateData();
  //
  //     auto result = s.decrypt(code, k);
  //
  //     cout << format("Test #{}\ncode: [", i + 1);
  //     for (int j = 0; j < code.size(); ++j) {
  //       if (j) cout << ", ";
  //       cout << code[j];
  //     }
  //     cout << format("], k = {}\n", k);
  //
  //     cout << "result: [";
  //     for (int j = 0; j < result.size(); ++j) {
  //       if (j) cout << ", ";
  //       cout << result[j];
  //     }
  //     cout << "]\n\n";
  //   }
  // }

  vector<pair<vector<int>, int>> tests = {
      {{5, 7, 1, 4}, 3},
      {{1, 2, 3, 4}, 0},
      {{2, 4, 9, 3}, -2},
      {{1, 2}, 1},
  };

  Solution s;

  for (int i = 0; i < tests.size(); ++i) {
    auto& [code, k] = tests[i];
    auto res = s.decrypt(code, k);

    cout << format("Test #{}\ncode: [", i + 1);
    for (int j = 0; j < code.size(); ++j) {
      if (j) cout << ", ";
      cout << code[j];
    }
    cout << format("], k = {}\nresult: [", k);
    for (int j = 0; j < res.size(); ++j) {
      if (j) cout << ", ";
      cout << res[j];
    }
    cout << "]\n\n";
  }
}
