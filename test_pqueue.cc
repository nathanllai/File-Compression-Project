#include <gtest/gtest.h>

#include <functional>

#include "pqueue.h"

TEST(PQueue, less) {
  PQueue<int> pq;

  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 2);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 23);
}

TEST(PQueue, great) {
  PQueue<int, std::greater<int>> pq;

  pq.Push(42);
  pq.Push(23);
  pq.Push(2);
  pq.Push(34);

  EXPECT_EQ(pq.Top(), 42);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), 34);
}


class MyClass {
 public:
  explicit MyClass(int n) : n_(n) {}
  bool operator < (const MyClass &mc) const { return n_ < mc.n_; }
  int n() { return n_; }
 private:
  int n_;
};

TEST(PQueue, custom_class) {
  std::vector<MyClass> vec{MyClass(42), MyClass(23), MyClass(2), MyClass(34)};

  PQueue<MyClass> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top().n(), vec[2].n());
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top().n(), vec[1].n());
}

class MyClassPtrComp {
 public:
  bool operator()(MyClass *lhs, MyClass *rhs) const {
    return (*lhs).n() < (*rhs).n();
  }
};

TEST(PQueue, custom_class_pointer) {
  std::vector<MyClass*> vec{new MyClass(42), new MyClass(23),
                            new MyClass(2), new MyClass(34)};

  PQueue<MyClass*, MyClassPtrComp> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top(), vec[2]);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), vec[1]);
}

TEST(PQueue, std_errors) {
  PQueue<int> pq;
  pq.Push(42);
  pq.Push(23);
  pq.Pop();
  pq.Pop();

  EXPECT_THROW(pq.Pop(), std::exception);
  EXPECT_THROW(pq.Top(), std::exception);
}

class MyCharClass {
 public:
  explicit MyCharClass(char ch) : c(ch) {}
  bool operator < (const MyCharClass &mc) const { return c < mc.c; }
  char Character() { return c; }
 private:
  char c;
};

TEST(PQueue, custom_char_class) {
  std::vector<MyCharClass> vec{MyCharClass('p'), MyCharClass('c'),
                               MyCharClass('a'), MyCharClass('m')};

  PQueue<MyCharClass> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top().Character(), vec[2].Character());
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top().Character(), vec[1].Character());
}


class MyCharClassPtrComp {
 public:
  bool operator()(MyCharClass *lhs, MyCharClass *rhs) const {
    return (*lhs).Character() < (*rhs).Character();
  }
};

TEST(PQueue, custom_char_class_pointer) {
  std::vector<MyCharClass*> vec{new MyCharClass('p'), new MyCharClass('c'),
                            new MyCharClass('a'), new MyCharClass('m')};

  PQueue<MyCharClass*, MyCharClassPtrComp> pq;
  pq.Push(vec[0]);
  pq.Push(vec[1]);
  pq.Push(vec[2]);
  pq.Push(vec[3]);

  EXPECT_EQ(pq.Top(), vec[2]);
  EXPECT_EQ(pq.Size(), 4);
  pq.Pop();
  EXPECT_EQ(pq.Top(), vec[1]);
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
