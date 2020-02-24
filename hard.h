#pragma once

struct hard
{
    int fa;
    int fi;
    hard(int fa, int fi) : fa(fa), fi(fi) {};
    hard() : fa(0), fi(0) {};
    hard(const hard &) = delete;
    hard(hard &ha) : fa(ha.fa), fi(ha.fi){};
    hard(hard &&) noexcept = delete;
    ~hard(){};

};

template <typename T>
T factorial (T n)
{
  T res;

  res = 1;
  for (int i = 1; i <= n; i++)
  {
    res = res * i;
  }
  return  res;
}

template <typename T>
T fibonacci (T n)
{
  if (n <= 1)
    return n;
  return fibonacci(n-1) + fibonacci(n-2);
}
