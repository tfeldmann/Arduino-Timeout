#include <unity.h>

#include <timeout.cpp>

void timer_usecase()
{
    Timeout t;
    current_time = 0;
    t.start(100);
    current_time = 50;
    TEST_ASSERT_FALSE(t.time_over());
    current_time = 99;
    TEST_ASSERT_FALSE(t.time_over());
    current_time = 150;
    TEST_ASSERT(t.time_over());

    current_time = 150;
    t.reset();
    TEST_ASSERT_FALSE(t.time_over());
    current_time = 200;
    TEST_ASSERT_FALSE(t.time_over());
    current_time = 251;
    TEST_ASSERT(t.time_over());

    current_time = 251;
    t.reset();
    TEST_ASSERT_FALSE(t.time_over());
}

void heartbeat_usecase()
{
    Timeout t;
    current_time = 0;
    t.prepare(100);
    TEST_ASSERT_TRUE(t.time_over());
    current_time = 50;
    TEST_ASSERT_TRUE(t.time_over());
    current_time = 102;
    TEST_ASSERT_TRUE(t.time_over());
    current_time = 150;
    TEST_ASSERT_TRUE(t.time_over());
    t.reset();
    current_time = 170;
    TEST_ASSERT_FALSE(t.time_over());
    current_time = 300;
    TEST_ASSERT_TRUE(t.time_over());
}

void heartbeat_expiration_usecase()
{
    Timeout t;
    TEST_ASSERT_TRUE(t.time_over());
    current_time = 0;
    t.expire();
    TEST_ASSERT_TRUE(t.time_over());
    current_time = 102;
    TEST_ASSERT_TRUE(t.time_over());
    t.start(100);
    TEST_ASSERT_FALSE(t.time_over());
    current_time = 200;
    TEST_ASSERT_FALSE(t.time_over());
    current_time = 300;
    TEST_ASSERT_TRUE(t.time_over());
}

void horn_usecase()
{
    Timeout t;
    current_time = 0;
    t.start(0);
    t.expire();
    TEST_ASSERT_TRUE(t.time_over());
    current_time = 10;
    TEST_ASSERT_TRUE(t.time_over());
    current_time = 100;
    TEST_ASSERT_TRUE(t.time_over());
    current_time = 200;
    t.start(500);
    current_time = 400;
    TEST_ASSERT(!t.time_over());
    current_time = 1000;
    TEST_ASSERT(t.time_over());
}

void periodic_usecase()
{
    Timeout t;
    current_time = 0;
    int out[10] = {0};
    int index = 0;

    t.start(100);
    for (int i = 0; i < 400; i++)
    {
        current_time = i;
        if (t.periodic())
        {
            out[index] = i;
            index++;
        }
    }

    int expected[] = {100, 200, 300, 0, 0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, out, 5);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(timer_usecase);
    RUN_TEST(heartbeat_usecase);
    RUN_TEST(heartbeat_expiration_usecase);
    RUN_TEST(horn_usecase);
    RUN_TEST(periodic_usecase);
    return UNITY_END();
}
