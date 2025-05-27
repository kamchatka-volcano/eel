#include <eel/string_utils.h>
#include <gtest/gtest.h>

using namespace eel;

TEST(String, TrimFront)
{
    EXPECT_EQ(trim_front("  Hello world"), "Hello world");
    EXPECT_EQ(trim_front("  Hello world "), "Hello world ");
    EXPECT_EQ(trim_front(" \n\t Hello world"), "Hello world");
    EXPECT_EQ(trim_front("Hello world "), "Hello world ");
    EXPECT_EQ(trim_front(" \n \t   "), "");
    EXPECT_EQ(trim_front("\n\t"), "");
    EXPECT_EQ(trim_front(""), "");

    auto str = [](auto strVal)
    {
        return std::string{strVal};
    };
    EXPECT_EQ(trim_front(str("  Hello world")), "Hello world");
    EXPECT_EQ(trim_front(str("  Hello world ")), "Hello world ");
    EXPECT_EQ(trim_front(str(" \n\t Hello world")), "Hello world");
    EXPECT_EQ(trim_front(str("Hello world ")), "Hello world ");
    EXPECT_EQ(trim_front(str(" \n \t   ")), "");
    EXPECT_EQ(trim_front(str("\n\t")), "");
    EXPECT_EQ(trim_front(str("")), "");
}

TEST(String, TrimBack)
{
    EXPECT_EQ(trim_back("Hello world  "), "Hello world");
    EXPECT_EQ(trim_back(" Hello world  "), " Hello world");
    EXPECT_EQ(trim_back("Hello world \n\t"), "Hello world");
    EXPECT_EQ(trim_back(" \n \t   "), "");
    EXPECT_EQ(trim_back("\n\t"), "");
    EXPECT_EQ(trim_back(""), "");

    auto str = [](auto strVal)
    {
        return std::string{strVal};
    };
    EXPECT_EQ(trim_back(str("Hello world  ")), "Hello world");
    EXPECT_EQ(trim_back(str(" Hello world  ")), " Hello world");
    EXPECT_EQ(trim_back(str("Hello world \n\t")), "Hello world");
    EXPECT_EQ(trim_back(str(" \n \t   ")), "");
    EXPECT_EQ(trim_back(str("\n\t")), "");
    EXPECT_EQ(trim_back(str("")), "");
}

TEST(String, Trim)
{
    EXPECT_EQ(trim("  Hello world"), "Hello world");
    EXPECT_EQ(trim("  Hello world "), "Hello world");
    EXPECT_EQ(trim("Hello world "), "Hello world");
    EXPECT_EQ(trim(" \n\t Hello world"), "Hello world");
    EXPECT_EQ(trim(" \n\t   "), "");
    EXPECT_EQ(trim("\n\t"), "");
    EXPECT_EQ(trim(""), "");

    auto str = [](auto strVal)
    {
        return std::string{strVal};
    };
    EXPECT_EQ(trim(str("  Hello world")), "Hello world");
    EXPECT_EQ(trim(str("  Hello world ")), "Hello world");
    EXPECT_EQ(trim(str("Hello world ")), "Hello world");
    EXPECT_EQ(trim(str(" \n\t Hello world")), "Hello world");
    EXPECT_EQ(trim(str(" \n\t   ")), "");
    EXPECT_EQ(trim(str("\n\t")), "");
    EXPECT_EQ(trim(str("")), "");
}

TEST(String, Split)
{
    EXPECT_EQ(split("hello world"), (std::vector<std::string_view>{"hello", "world"}));
    EXPECT_EQ(split("hello world", ","), (std::vector<std::string_view>{"hello world"}));
    EXPECT_EQ(split("hello world, nice weather", ","), (std::vector<std::string_view>{"hello world", "nice weather"}));
    EXPECT_EQ(
            split("hello world\n, nice weather", ",", false),
            (std::vector<std::string_view>{"hello world\n", " nice weather"}));
    EXPECT_EQ(split(""), (std::vector<std::string_view>{""}));
    EXPECT_EQ(split("hello world", ""), (std::vector<std::string_view>{"hello world"}));
    EXPECT_EQ(split("", ""), (std::vector<std::string_view>{""}));

    auto str = [](auto strVal)
    {
        return std::string{strVal};
    };
    EXPECT_EQ(split(str("hello world")), (std::vector<std::string>{"hello", "world"}));
    EXPECT_EQ(split(str("hello world"), ","), (std::vector<std::string>{"hello world"}));
    EXPECT_EQ(split(str("hello world, nice weather"), ","), (std::vector<std::string>{"hello world", "nice weather"}));
    EXPECT_EQ(
            split(str("hello world\n, nice weather"), ",", false),
            (std::vector<std::string>{"hello world\n", " nice weather"}));
    EXPECT_EQ(split(str("")), (std::vector<std::string>{""}));
    EXPECT_EQ(split(str("hello world"), ""), (std::vector<std::string>{"hello world"}));
    EXPECT_EQ(split(str(""), ""), (std::vector<std::string>{""}));
}

TEST(String, Replace)
{
    EXPECT_EQ(replace("hello world", "world", "space"), "hello space");
    EXPECT_EQ(replace("hello world and other world", "world", "space"), "hello space and other space");
    EXPECT_EQ(replace("hello world", "moon", "space"), "hello world");
    EXPECT_EQ(replace("hello world", "world", ""), "hello ");
    EXPECT_EQ(replace("hello world", "", "space"), "hello world");
    EXPECT_EQ(replace("", "moon", "space"), "");
    EXPECT_EQ(replace("", "", ""), "");
}

TEST(String, Join)
{
    {
        auto stringList = std::vector<std::string>{"a", "b", "c"};
        EXPECT_EQ(join(stringList, ""), "abc");
        EXPECT_EQ(join(stringList, ", "), "a, b, c");

        stringList = {"a"};
        EXPECT_EQ(join(stringList, ""), "a");
        EXPECT_EQ(join(stringList, ", "), "a");

        stringList = {};
        EXPECT_EQ(join(stringList, ""), "");
        EXPECT_EQ(join(stringList, ", "), "");
    }
    {
        auto viewList = std::vector<std::string_view>{"a", "b", "c"};
        EXPECT_EQ(join(viewList, ""), "abc");
        EXPECT_EQ(join(viewList, ", "), "a, b, c");

        viewList = {"a"};
        EXPECT_EQ(join(viewList, ""), "a");
        EXPECT_EQ(join(viewList, ", "), "a");

        viewList = {};
        EXPECT_EQ(join(viewList, ""), "");
        EXPECT_EQ(join(viewList, ", "), "");
    }
    {
        EXPECT_EQ(join(std::vector<std::string>{"a", "b", "c"}, ""), "abc");
        EXPECT_EQ(join(std::vector<std::string>{"a", "b", "c"}, ", "), "a, b, c");

        EXPECT_EQ(join(std::vector<std::string>{"a"}, ""), "a");
        EXPECT_EQ(join(std::vector<std::string>{"a"}, ", "), "a");

        EXPECT_EQ(join(std::vector<std::string>{}, ""), "");
        EXPECT_EQ(join(std::vector<std::string>{}, ", "), "");
    }
}

TEST(String, StartsWith)
{
    EXPECT_TRUE(starts_with("hello world", "hell"));
    EXPECT_FALSE(starts_with("hello world", "moon"));
    EXPECT_FALSE(starts_with("", "moon"));
    EXPECT_TRUE(starts_with("hello world", ""));
    EXPECT_TRUE(starts_with("", ""));
}

TEST(String, EndsWith)
{
    EXPECT_TRUE(ends_with("hello world", "world"));
    EXPECT_FALSE(ends_with("hello world", "moon"));
    EXPECT_FALSE(ends_with("", "moon"));
    EXPECT_TRUE(ends_with("hello world", ""));
    EXPECT_TRUE(ends_with("", ""));
}

TEST(String, Before)
{
    EXPECT_TRUE(before("hello world", "world").has_value());
    EXPECT_EQ(before("hello world", "world").value(), "hello ");

    EXPECT_FALSE(before("hello world", "moon").has_value());
    EXPECT_FALSE(before("hello world", "").has_value());
    EXPECT_FALSE(before("", "moon").has_value());
    EXPECT_FALSE(before("", "").has_value());

    auto str = [](auto strVal)
    {
        return std::string{strVal};
    };

    EXPECT_TRUE(before(str("hello world"), "world").has_value());
    EXPECT_EQ(before(str("hello world"), "world").value(), "hello ");

    EXPECT_FALSE(before(str("hello world"), "moon").has_value());
    EXPECT_FALSE(before(str("hello world"), "").has_value());
    EXPECT_FALSE(before(str(""), "moon").has_value());
    EXPECT_FALSE(before(str(""), "").has_value());
}

TEST(String, After)
{
    EXPECT_TRUE(after("hello world", "hello").has_value());
    EXPECT_EQ(after("hello world", "hello").value(), " world");

    EXPECT_FALSE(after("hello world", "moon").has_value());
    EXPECT_FALSE(after("hello world", "").has_value());
    EXPECT_FALSE(after("", "moon").has_value());
    EXPECT_FALSE(after("", "").has_value());

    auto str = [](auto strVal)
    {
        return std::string{strVal};
    };
    EXPECT_TRUE(after(str("hello world"), "hello").has_value());
    EXPECT_EQ(after(str("hello world"), "hello").value(), " world");

    EXPECT_FALSE(after(str("hello world"), "moon").has_value());
    EXPECT_FALSE(after(str("hello world"), "").has_value());
    EXPECT_FALSE(after(str(""), "moon").has_value());
    EXPECT_FALSE(after(str(""), "").has_value());
}

TEST(String, Between)
{
    EXPECT_TRUE(between("hello world!", "hello", "!").has_value());
    EXPECT_EQ(between("hello world!", "hello", "!").value(), " world");
    EXPECT_FALSE(between("hello world!", "hello", "moon").has_value());
    EXPECT_FALSE(between("hello world!", "moon", "!").has_value());
    EXPECT_FALSE(between("hello world!", "moon", "!").has_value());
    EXPECT_FALSE(between("hello world!", "", "!").has_value());
    EXPECT_FALSE(between("hello world!", "hello", "").has_value());
    EXPECT_FALSE(between("", "hello", "moon").has_value());
    EXPECT_FALSE(between("", "", "moon").has_value());
    EXPECT_FALSE(between("", "moon", "").has_value());
    EXPECT_FALSE(between("", "", "").has_value());

    auto str = [](auto strVal)
    {
        return std::string{strVal};
    };
    EXPECT_TRUE(between(str("hello world!"), "hello", "!").has_value());
    EXPECT_EQ(between(str("hello world!"), "hello", "!").value(), " world");
    EXPECT_FALSE(between(str("hello world!"), "hello", "moon").has_value());
    EXPECT_FALSE(between(str("hello world!"), "moon", "!").has_value());
    EXPECT_FALSE(between(str("hello world!"), "moon", "!").has_value());
    EXPECT_FALSE(between(str("hello world!"), "", "!").has_value());
    EXPECT_FALSE(between(str("hello world!"), "hello", "").has_value());
    EXPECT_FALSE(between(str(""), "hello", "moon").has_value());
    EXPECT_FALSE(between(str(""), "", "moon").has_value());
    EXPECT_FALSE(between(str(""), "moon", "").has_value());
    EXPECT_FALSE(between(str(""), "", "").has_value());
}

TEST(String, cctypeWrappers)
{
    EXPECT_TRUE(isalnum('9'));
    EXPECT_TRUE(isalnum('z'));
    EXPECT_FALSE(isalnum('!'));

    EXPECT_TRUE(isalpha('a'));
    EXPECT_FALSE(isalpha('9'));

    EXPECT_TRUE(isblank(' '));
    EXPECT_FALSE(isblank('9'));

    EXPECT_TRUE(iscntrl(0x7F));
    EXPECT_FALSE(iscntrl('9'));

    EXPECT_TRUE(isdigit('9'));
    EXPECT_FALSE(isdigit('a'));

    EXPECT_TRUE(isgraph('!'));
    EXPECT_TRUE(isgraph('9'));
    EXPECT_FALSE(isgraph(' '));
    EXPECT_FALSE(isgraph(0x7F));

    EXPECT_TRUE(islower('a'));
    EXPECT_FALSE(islower('A'));

    EXPECT_TRUE(isprint('!'));
    EXPECT_TRUE(isprint('9'));
    EXPECT_TRUE(isprint(' '));
    EXPECT_FALSE(isprint(0x7F));

    EXPECT_TRUE(ispunct(','));
    EXPECT_FALSE(ispunct('A'));

    EXPECT_TRUE(isspace(' '));
    EXPECT_FALSE(isspace('A'));

    EXPECT_TRUE(isupper('A'));
    EXPECT_FALSE(isupper('a'));

    EXPECT_TRUE(isxdigit('9'));
    EXPECT_TRUE(isxdigit('A'));
    EXPECT_FALSE(isxdigit('U'));

    EXPECT_EQ(tolower('a'), 'a');
    EXPECT_EQ(tolower('A'), 'a');
    EXPECT_NE(tolower('Z'), 'a');

    EXPECT_EQ(toupper('a'), 'A');
    EXPECT_EQ(toupper('A'), 'A');
    EXPECT_NE(toupper('z'), 'z');
}

TEST(String, Concat)
{
    EXPECT_EQ(concat(""), std::string{});
    EXPECT_EQ(concat("", ""), std::string{});
    EXPECT_EQ(concat("", "test"), std::string{"test"});
    EXPECT_EQ(concat("test", ""), std::string{"test"});
    EXPECT_EQ(concat("hello", " ", "world"), std::string{"hello world"});
    EXPECT_EQ(concat("hello", std::string{" "}, std::string_view{"world"}), std::string{"hello world"});
    auto string = std::string{" "};
    EXPECT_EQ(concat("hello", string, std::string_view{"world"}), std::string{"hello world"});
}