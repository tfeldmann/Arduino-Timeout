#include <Timeout.h>
#include <unity.h>

using namespace fakeit;

void setUp(void)
{
    ArduinoFakeReset();
}

void set_millis(uint32_t ms)
{
    When(Method(ArduinoFake(), millis)).AlwaysReturn(ms);
}

void timer()
{
    Timeout t;
    set_millis(100);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);

    t.start(100);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 100);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    set_millis(150);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 50);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    set_millis(200);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);
    set_millis(250);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);
}

void heartbeat()
{
    Timeout hb;
    set_millis(100);
    TEST_ASSERT_EQUAL(hb.time_over(), true);
    set_millis(150);
    TEST_ASSERT_EQUAL(hb.time_over(), true);
    set_millis(200);
    TEST_ASSERT_EQUAL(hb.time_over(), true);
    set_millis(250);
    TEST_ASSERT_EQUAL(hb.time_over(), true);

    hb.start(100);
    set_millis(300);
    TEST_ASSERT_EQUAL(hb.time_over(), false);
    set_millis(340);
    TEST_ASSERT_EQUAL(hb.time_over(), false);
    set_millis(350);
    TEST_ASSERT_EQUAL(hb.time_over(), true);
    set_millis(400);
    TEST_ASSERT_EQUAL(hb.time_over(), true);
}

void expiration()
{
    Timeout t;
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);

    set_millis(500);
    t.start(1000);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 1000);
    TEST_ASSERT_EQUAL(t.time_over(), false);

    set_millis(600);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 900);
    TEST_ASSERT_EQUAL(t.time_over(), false);

    set_millis(700);
    t.expire();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);

    set_millis(800);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);

    set_millis(900);
    t.start(1000);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 1000);
    TEST_ASSERT_EQUAL(t.time_over(), false);
}

void pause_resume()
{
    Timeout t;
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(500);
    t.start(1000);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 1000);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(600);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 900);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(700);
    t.pause();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 800);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), true);

    set_millis(800);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 800);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), true);

    set_millis(900);
    t.resume();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 800);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(1000);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 700);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(1700);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(2000);
    t.start(1000);
    t.pause();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 1000);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), true);
    t.expire();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);
    TEST_ASSERT_EQUAL(t.is_paused(), false);
}

void no_expiration_in_pause()
{
    Timeout t;
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(500);
    t.start(500);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 500);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(600);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 400);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(700);
    t.pause();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 300);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), true);

    set_millis(800);
    t.pause();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 300);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), true);

    set_millis(900);
    t.pause();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 300);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), true);

    set_millis(1000);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 300);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), true);

    set_millis(1100);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 300);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), true);

    set_millis(1200);
    t.resume();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 300);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(1300);
    t.resume();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 200);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(1400);
    t.resume();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 100);
    TEST_ASSERT_EQUAL(t.time_over(), false);
    TEST_ASSERT_EQUAL(t.is_paused(), false);

    set_millis(1500);
    t.resume();
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);
    TEST_ASSERT_EQUAL(t.is_paused(), false);
}

void periodic()
{
    Timeout t;
    set_millis(1000);

    int out[10] = { 0 };
    int index = 0;

    t.start(100);
    for (int i = 0; i < 400; i++) {
        set_millis(1000 + i);
        if (t.periodic(100)) {
            out[index] = i;
            index++;
        }
    }

    int expected[] = { 100, 200, 300, 0, 0 };
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, out, 5);
}

void rollover()
{
    Timeout t;
    uint32_t start_time = 4294967290;

    set_millis(start_time);
    t.start(1000);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 1000);
    TEST_ASSERT_EQUAL(t.time_over(), false);

    set_millis(start_time + 100);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 900);
    TEST_ASSERT_EQUAL(t.time_over(), false);

    set_millis(start_time + 500);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 500);
    TEST_ASSERT_EQUAL(t.time_over(), false);

    set_millis(start_time + 1000);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);

    set_millis(start_time + start_time);
    TEST_ASSERT_EQUAL(t.time_left_ms(), 0);
    TEST_ASSERT_EQUAL(t.time_over(), true);
}

int main(int argc, char** argv)
{
    UNITY_BEGIN();
    RUN_TEST(timer);
    RUN_TEST(heartbeat);
    RUN_TEST(expiration);
    RUN_TEST(pause_resume);
    RUN_TEST(no_expiration_in_pause);
    RUN_TEST(periodic);
    RUN_TEST(rollover);
    return UNITY_END();
}
