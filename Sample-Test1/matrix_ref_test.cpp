#include "pch.h"
#include "../LinearAlgebra/matrix_ref.h"

TEST(MATRIX_REF, ITERATOR_IS_WORKING)
{
    size_t start = 2;
    std::array<size_t, 3> extents = { 3, 3, 2 };
    matrix_slice<3> ms(start, extents);

    std::vector<int> items{};
    for (size_t i = 0; i < 18; i++)
    {
        items.push_back(i);
    }
    matrix_ref<int, 3> mr(ms, items.data());

    int j = 0;
    for (auto& v : mr)
    {
        EXPECT_EQ(v, j);
        j++;
    }


}

TEST(matrix_ref_test, COPY_CONSTRUCTOR)
{
    size_t start = 2;
    std::array<size_t, 3> extents = { 3, 3, 2 };
    matrix_slice<3> ms(start, extents);

    std::vector<int> items{};
    for (size_t i = 0; i < 18; i++)
    {
        items.push_back(i);
    }
    matrix_ref<int, 3> mr(ms, items.data());
    matrix_ref<int, 3>copy{ mr };
    int j = 0;
    for (auto& v : copy)
    {
        EXPECT_EQ(v, j);
        j++;
    }


}

TEST(matrix_ref_test, COPY_ASSIGNEMENT)
{
    size_t start = 2;
    std::array<size_t, 3> extents = { 3, 3, 2 };
    matrix_slice<3> ms(start, extents);

    std::vector<int> items{};
    for (size_t i = 0; i < 18; i++)
    {
        items.push_back(i);
    }
    matrix_ref<int, 3> mr(ms, items.data());
    matrix_ref<int, 3>copy = mr;
    int j = 0;
    for (auto& v : copy)
    {
        EXPECT_EQ(v, j);
        j++;
    }


}

TEST(matrix_ref_test, MOVE_CONSTRUCTOR)
{
    size_t start = 2;
    std::array<size_t, 3> extents = { 3, 3, 2 };
    matrix_slice<3> ms(start, extents);

    std::vector<int> items{};
    for (size_t i = 0; i < 18; i++)
    {
        items.push_back(i);
    }
    matrix_ref<int, 3> mr(ms, items.data());
    matrix_ref<int, 3>mv(std::move(mr));
    int j = 0;
    for (auto& v : mv)
    {
        EXPECT_EQ(v, j);
        j++;
    }
}

TEST(matrix_ref_test, MOVE_CONSTRUCTOR_OPERATOR)
{
    size_t start = 2;
    std::array<size_t, 3> extents = { 3, 3, 2 };
    matrix_slice<3> ms(start, extents);

    std::vector<int> items{};
    for (size_t i = 0; i < 18; i++)
    {
        items.push_back(i);
    }
    matrix_ref<int, 3> mr(ms, items.data());
    matrix_ref<int, 3>mv = std::move(mr);
    int j = 0;
    for (auto& v : mv)
    {
        EXPECT_EQ(v, j);
        j++;
    }
}