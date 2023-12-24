#include "postfix.h"
#include "TStack.h"

#include <gtest.h>
#include <cmath>

TEST(TArithmeticExpression, can_create_postfix) {
    ASSERT_NO_THROW(TArithmeticExpression expr("(8-2*3)+2-(6*9/3-1)+(8-2*3)/2*4*(7-3)/2+(6+(5-2)-8)"));
}

TEST(TArithmeticExpression, get_infix) {
    TArithmeticExpression expr("(8-2*3)+2-(6*9/3-1)+(8-2*3)/2*4*(7-3)/2+(6+(5-2)-8)");

    ASSERT_EQ("(8-2*3)/2", expr.GetInfix());
}

TEST(TArithmeticExpression, get_postfix1) {
    TArithmeticExpression expr("(8-2*3)+2-(6*9/3-1)+(8-2*3)/2*4*(7-3)/2+(6+(5-2)-8)");

    expr.ToPostfix();
    ASSERT_EQ("8 2 3 * - 2 + 6 9 * 3 / 1 - - 8 2 3 * - 2 / 4 * 7 3 - * 2 / + 6 5 2 - + 8 - +", expr.GetPostfix());
}

TEST(TArithmeticExpression, get_postfix2) {
    TArithmeticExpression expr("(8-2*3)+2-(6*9/3-1)+(8-2*3)/2*4*(7-3)/2+(6+(5-2)-8)");
    expr.ToPostfix();
    double ans = expr.Calculate();
    ASSERT_EQ(-4, ans);
}

TEST(TArithmeticExpression, with_an_unequal_number_of_different_brackets) {

    ASSERT_ANY_THROW(TArithmeticExpression expr("(1+2))"));
}

TEST(TArithmeticExpression, with_an_unequal_number_of_different_brackets2) {

    ASSERT_ANY_THROW(TArithmeticExpression expr("((1+2)"));
}

TEST(TArithmeticExpression, incorrect_form) {
    TArithmeticExpression expr("2/*+-3");
    expr.ToPostfix();
    ASSERT_ANY_THROW(expr.Calculate());
}
