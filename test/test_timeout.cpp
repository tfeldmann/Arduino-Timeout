#include <Arduino.h>
#include <unity.h>

using namespace fakeit;

#include <timeout.cpp>

void timer_usecase()
{
    Timeout t;
    When(Method(ArduinoFake(), millis)).AlwaysReturn(0);
    t.start(100);
    When(Method(ArduinoFake(), millis)).AlwaysReturn(50);
    TEST_ASSERT_FALSE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(99);
    TEST_ASSERT_FALSE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(150);
    TEST_ASSERT(t.time_over());

    When(Method(ArduinoFake(), millis)).AlwaysReturn(150);
    t.reset();
    TEST_ASSERT_FALSE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(200);
    TEST_ASSERT_FALSE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(251);
    TEST_ASSERT(t.time_over());

    When(Method(ArduinoFake(), millis)).AlwaysReturn(251);
    t.reset();
    TEST_ASSERT_FALSE(t.time_over());
}

void heartbeat_usecase()
{
    Timeout t;
    When(Method(ArduinoFake(), millis)).AlwaysReturn(0);
    t.prepare(100);
    TEST_ASSERT_TRUE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(50);
    TEST_ASSERT_TRUE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(102);
    TEST_ASSERT_TRUE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(150);
    TEST_ASSERT_TRUE(t.time_over());
    t.reset();
    When(Method(ArduinoFake(), millis)).AlwaysReturn(170);
    TEST_ASSERT_FALSE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(300);
    TEST_ASSERT_TRUE(t.time_over());
}

void heartbeat_expiration_usecase()
{
    Timeout t;
    TEST_ASSERT_TRUE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(0);
    t.expire();
    TEST_ASSERT_TRUE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(102);
    TEST_ASSERT_TRUE(t.time_over());
    t.start(100);
    TEST_ASSERT_FALSE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(200);
    TEST_ASSERT_FALSE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(300);
    TEST_ASSERT_TRUE(t.time_over());
}

void horn_usecase()
{
    Timeout t;
    When(Method(ArduinoFake(), millis)).AlwaysReturn(0);
    t.start(0);
    t.expire();
    TEST_ASSERT_TRUE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(10);
    TEST_ASSERT_TRUE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(100);
    TEST_ASSERT_TRUE(t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(200);
    t.start(500);
    When(Method(ArduinoFake(), millis)).AlwaysReturn(400);
    TEST_ASSERT(!t.time_over());
    When(Method(ArduinoFake(), millis)).AlwaysReturn(1000);
    TEST_ASSERT(t.time_over());
}

void periodic_usecase()
{
    Timeout t;
    When(Method(ArduinoFake(), millis)).AlwaysReturn(0);
    int out[10] = {0};
    int index = 0;

    t.start(100);
    for (int i = 0; i < 400; i++)
    {
        When(Method(ArduinoFake(), millis)).AlwaysReturn(i);
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
