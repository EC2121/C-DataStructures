#define CUNIT_STRING_EQ(exptected, actual)                                                         \
    if (strcmp(exptected, actual) != 0)                                                         \
    {                                                                                           \
        printf("%s: expected %s but was %s [%d]\n", __FUNCTION__, exptected, actual, __LINE__); \
        exit(-1);                                                                               \
    }

#define CUNIT_IS_NULL(actual)                                                                  \
    if (actual != NULL)                                                                        \
    {                                                                                          \
        printf("%s: expected %s but was %p [%d]\n", __FUNCTION__, "NULL", actual, __LINE__); \
        exit(-1);                                                                              \
    }

#define CUNIT_TEST(name) void name()

#define CUNIT_RUNNER(...)                                                      \
    int main()                                                                 \
    {                                                                          \
        void (*fncptr[])() = {__VA_ARGS__}; \
        int count = sizeof(fncptr) / sizeof(void *);                           \
                                                                               \
        for (int i = 0; i < count; ++i)                                        \
                                                                               \
        {                                                                      \
                                                                               \
            fncptr[i]();                                                       \
        }                                                                      \
                                                                               \
        puts("ALL TEST PASSED");                                               \
                                                                               \
        return 0;                                                              \
    }
