#include <string.h>
#include <limits.h>
#include "unity.h"
#include "input.h"
#include "utils.h"


void setUp(void)
{
    // set stuff up here
}


void tearDown()
{
    // clean stuff up here
}


void test_read_int_from_buffer_accepts_correct_values()
{
    size_t BUF_SIZE = 32;
    char buffer[BUF_SIZE];
    int n;

    snprintf(buffer, BUF_SIZE, "%d", 0);
    TEST_ASSERT_EQUAL_INT(0, read_int_from_buffer(buffer, &n));
    TEST_ASSERT_EQUAL_INT(n, 0);

    snprintf(buffer, BUF_SIZE, "%d", -1);
    TEST_ASSERT_EQUAL_INT(0, read_int_from_buffer(buffer, &n));
    TEST_ASSERT_EQUAL_INT(n, -1);

    snprintf(buffer, BUF_SIZE, "%d", 1);
    TEST_ASSERT_EQUAL_INT(0, read_int_from_buffer(buffer, &n));
    TEST_ASSERT_EQUAL_INT(n, 1);

    snprintf(buffer, BUF_SIZE, "%d", INT_MIN);
    TEST_ASSERT_EQUAL_INT(0, read_int_from_buffer(buffer, &n));
    TEST_ASSERT_EQUAL_INT(n, INT_MIN);

    snprintf(buffer, BUF_SIZE, "%d", INT_MAX);
    TEST_ASSERT_EQUAL_INT(0, read_int_from_buffer(buffer, &n));
    TEST_ASSERT_EQUAL_INT(n, INT_MAX);
}


void test_read_int_from_buffer_rejects_incorrect_values()
{
    size_t BUF_SIZE = 32;
    char buffer[BUF_SIZE];
    int n;

    snprintf(buffer, BUF_SIZE, "%ld", LONG_MIN);
    TEST_ASSERT_EQUAL_INT(-1, read_int_from_buffer(buffer, &n));

    snprintf(buffer, BUF_SIZE, "%ld", LONG_MAX);
    TEST_ASSERT_EQUAL_INT(-1, read_int_from_buffer(buffer, &n));

    snprintf(buffer, BUF_SIZE, "%s", "123456789012345678901234567890");
    TEST_ASSERT_EQUAL_INT(-1, read_int_from_buffer(buffer, &n));

    snprintf(buffer, BUF_SIZE, "%s", "-123456789012345678901234567890");
    TEST_ASSERT_EQUAL_INT(-1, read_int_from_buffer(buffer, &n));

    snprintf(buffer, BUF_SIZE, "%s", "x");
    TEST_ASSERT_EQUAL_INT(-1, read_int_from_buffer(buffer, &n));

    snprintf(buffer, BUF_SIZE, "%s", "");
    TEST_ASSERT_EQUAL_INT(-1, read_int_from_buffer(buffer, &n));

    snprintf(buffer, BUF_SIZE, "%s", "123x456");
    TEST_ASSERT_EQUAL_INT(-1, read_int_from_buffer(buffer, &n));

    snprintf(buffer, BUF_SIZE, "%s", "123x");
    TEST_ASSERT_EQUAL_INT(-1, read_int_from_buffer(buffer, &n));

    snprintf(buffer, BUF_SIZE, "%s", "x456");
    TEST_ASSERT_EQUAL_INT(-1, read_int_from_buffer(buffer, &n));
}


void test_read_ip_address_from_buffer_accepts_correct_ip_addresses()
{
    TEST_ASSERT_EQUAL_INT(0, read_ip_address_from_buffer("1.2.3.4"));
    TEST_ASSERT_EQUAL_INT(0, read_ip_address_from_buffer("0.0.0.0"));
    TEST_ASSERT_EQUAL_INT(0, read_ip_address_from_buffer("255.255.255.255"));
}


void test_read_ip_address_from_buffer_rejects_incorrect_ip_addresses()
{
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.2.3.-1"));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.2.3.256"));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.2.3."));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.2.3"));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.2."));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.2"));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1."));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.."));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("..."));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.2..3.4"));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.2.3.4x"));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.2.3.4/"));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("1.2.3.4/5"));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer(""));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer(" "));
    TEST_ASSERT_EQUAL_INT(-1, read_ip_address_from_buffer("x"));
}


void test_read_destination_subnet_from_buffer_accepts_correct_ip_and_mask()
{
    char dst_subnet[IP_ADDR_LEN + 3];
    char ip_addr[IP_ADDR_LEN];
    u16 mask;

    strncpy(dst_subnet, "1.2.3.4/5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(0, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));
    TEST_ASSERT_EQUAL_STRING("1.2.3.4", ip_addr);
    TEST_ASSERT_EQUAL_UINT16(5, mask);

    strncpy(dst_subnet, "0.0.0.0/0", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(0, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));
    TEST_ASSERT_EQUAL_STRING("0.0.0.0", ip_addr);
    TEST_ASSERT_EQUAL_UINT16(0, mask);

    strncpy(dst_subnet, "255.255.255.255/32", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(0, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));
    TEST_ASSERT_EQUAL_STRING("255.255.255.255", ip_addr);
    TEST_ASSERT_EQUAL_UINT16(32, mask);
}


void test_read_destination_subnet_from_buffer_rejects_incorrect_ip_and_mask_limits()
{
    char dst_subnet[IP_ADDR_LEN + 3];
    char ip_addr[IP_ADDR_LEN];
    u16 mask;

    strncpy(dst_subnet, "1.2.3.-1/5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3.0/-5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3.256/5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3.4/33", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));
}


void test_read_destination_subnet_from_buffer_rejects_incomplete_ip()
{
    char dst_subnet[IP_ADDR_LEN + 3];
    char ip_addr[IP_ADDR_LEN];
    u16 mask;

    strncpy(dst_subnet, "1.2.3./5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3/5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2./5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2/5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1./5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1/5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));
}


void test_read_destination_subnet_from_buffer_rejects_missing_ip()
{
    char dst_subnet[IP_ADDR_LEN + 3];
    char ip_addr[IP_ADDR_LEN];
    u16 mask;

    strncpy(dst_subnet, "/5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, " /5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));
}


void test_read_destination_subnet_from_buffer_rejects_missing_mask()
{
    char dst_subnet[IP_ADDR_LEN + 3];
    char ip_addr[IP_ADDR_LEN];
    u16 mask;

    strncpy(dst_subnet, "1", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3.4/", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));
}


void test_read_destination_subnet_from_buffer_rejects_ip_with_dot_problems()
{
    char dst_subnet[IP_ADDR_LEN + 3];
    char ip_addr[IP_ADDR_LEN];
    u16 mask;

    strncpy(dst_subnet, "1../5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, ".../5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2..3.4/5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));
}


void test_read_destination_subnet_from_buffer_rejects_ip_and_mask_with_slash_problems()
{
    char dst_subnet[IP_ADDR_LEN + 3];
    char ip_addr[IP_ADDR_LEN];
    u16 mask;

    strncpy(dst_subnet, "1.2.3.4//5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3.4/5/", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3.4//", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3.4/ ", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3.4/x", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3.4x/5", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "1.2.3.4/5x", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));
}


void test_read_destination_subnet_from_buffer_rejects_empty_or_alpha_subnet()
{
    char dst_subnet[IP_ADDR_LEN + 3];
    char ip_addr[IP_ADDR_LEN];
    u16 mask;

    strncpy(dst_subnet, "", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, " ", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));

    strncpy(dst_subnet, "x", IP_ADDR_LEN + 3);
    TEST_ASSERT_EQUAL_INT(-1, read_destination_subnet_from_buffer(dst_subnet, ip_addr, &mask));
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_read_int_from_buffer_accepts_correct_values);
    RUN_TEST(test_read_int_from_buffer_rejects_incorrect_values);

    RUN_TEST(test_read_ip_address_from_buffer_accepts_correct_ip_addresses);
    RUN_TEST(test_read_ip_address_from_buffer_rejects_incorrect_ip_addresses);

    RUN_TEST(test_read_destination_subnet_from_buffer_accepts_correct_ip_and_mask);
    RUN_TEST(test_read_destination_subnet_from_buffer_rejects_incorrect_ip_and_mask_limits);
    RUN_TEST(test_read_destination_subnet_from_buffer_rejects_incomplete_ip);
    RUN_TEST(test_read_destination_subnet_from_buffer_rejects_missing_ip);
    RUN_TEST(test_read_destination_subnet_from_buffer_rejects_missing_mask);
    RUN_TEST(test_read_destination_subnet_from_buffer_rejects_ip_with_dot_problems);
    RUN_TEST(test_read_destination_subnet_from_buffer_rejects_ip_and_mask_with_slash_problems);
    RUN_TEST(test_read_destination_subnet_from_buffer_rejects_empty_or_alpha_subnet);

    return UNITY_END();
}