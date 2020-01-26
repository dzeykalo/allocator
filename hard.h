
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
  T f[n+1];
  f[0] = 0;
  f[1] = 1;

  for (size_t i= 2; i <= n; i++)
  {
    f[i] = f[i-1] + f[i-2];
  }

  return f[n];
}
