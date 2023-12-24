#include "TStack.h"
#include <gtest.h>


TEST(TStack, can_create_default_stack) {
    ASSERT_NO_THROW(TStack<size_t> st);
}

TEST(TStack, can_is_empty) {
    TStack<size_t> st;
    ASSERT_TRUE(st.isEmpty());
}

TEST(TStack, can_push) {
    TStack<size_t> st;
    st.Push(1);
    st.Push(4)
    ASSERT_EQ(4, st.Top());
}

TEST(TStack, can_void_pop) {
    TStack<size_t> st;
    st.Push(1);
    st.Push(4);
    ASSERT_EQ(st.Top(),1);
}

TEST(TStack, can_T_pop) {
    TStack<size_t> st;
    st.Push(1);
    st.Push(5);
    size_t tmp = 5;
    st.Top();
   ASSERT_EQ(5,tmp);
}

TEST(TStack, can_asign_stack) {
    TStack<size_t> st1;
    TStack<size_t> st2;
    st1.Push(3);
    st2 = st1;
    ASSERT_EQ(3, st2.Top());
}


TEST(TStack, can_create_copied_stack) {
    TStack<size_t> st;
    ASSERT_NO_THROW(TStack<size_t> st1(st));
}

TEST(TStack, can_compare_stack) {
    TStack<size_t> st1;
    st1.Push(5);
    TStack<size_t> s2;
    st2.Push(8);
    ASSERT_TRUE(s1 == s2);
}

TEST(TStack, throw_top_with_empty) {
    TStack<size_t> st;
    ASSERT_ANY_THROW(st.Top());
}

TEST(TStack, throw_pop_with_empty) {
    TStack<size_t> st;
    ASSERT_ANY_THROW(st.Pop());
}


