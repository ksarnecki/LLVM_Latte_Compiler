void f(int a) {
  int x = 5;
  x += 2;
  return;
}

int g() {
  int c = 2-1;
  return 2*c;
}

int main() {
  int x = 1;
  f(x);
  return g();
}
