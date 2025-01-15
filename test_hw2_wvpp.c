/**
 * @file test_hw2_wvpp.c
 * @brief Tests source code file for CS 350 Homework #2: West Virginia Population Problem
 * @author Brian Powell
 * @version 3.10
 *
 * Place this file in the same directory as your own source code and add it to your project.
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 */

// Use GNU source for kill and usleep
#define _GNU_SOURCE

 // Include header files
#include "hw2_wvpp.h"
#include "test_hw2_wvpp.h"
#include "ctest.h"
#include "unity.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
#include <time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdbool.h>
#include <regex.h>
#include <errno.h>

// OS-specific includes
#ifdef __APPLE__
	#include <malloc/malloc.h>
#else
	#include <malloc.h>
#endif


// Define test values
static const char* testvalue_county_name = "Test County";
static const char* testvalue_fips_code = "999";
static const char* testvalue_seat = "Test Seat";
static const int testvalue_population = 999999;
static const int testvalue_area = 888;

/**
 * @brief location of input file
*/
const char* test_input_file = "counties.txt";

// Define variables to track if functions have been implemented
static bool not_implemented_get_programmer_name = false;
static bool not_implemented_trim = false;
static bool not_implemented_substring = false;
static bool not_implemented_create_list = false;
static bool not_implemented_get_head_node = false;
static bool not_implemented_get_county_name = false;
static bool not_implemented_get_fips_code = false;
static bool not_implemented_get_seat = false;
static bool not_implemented_get_population = false;
static bool not_implemented_get_area = false;
static bool not_implemented_get_population_density = false;
static bool not_implemented_get_next_node = false;
static bool not_implemented_create_county = false;
static bool not_implemented_add_and_sort_county = false;
static bool not_implemented_process_input_line = false;
static bool not_implemented_load_counties = false;
static bool not_implemented_delete_by_county_name = false;
static bool not_implemented_save_counties = false;

// Define variables to track if functions crash
static bool crashes_get_programmer_name = false;
static bool crashes_trim = false;
static bool crashes_substring = false;
static bool crashes_create_list = false;
static bool crashes_get_head_node = false;
static bool crashes_get_county_name = false;
static bool crashes_get_fips_code = false;
static bool crashes_get_seat = false;
static bool crashes_get_population = false;
static bool crashes_get_area = false;
static bool crashes_get_population_density = false;
static bool crashes_get_next_node = false;
static bool crashes_create_county = false;
static bool crashes_add_and_sort_county = false;
static bool crashes_process_input_line = false;
static bool crashes_load_counties = false;
static bool crashes_delete_by_county_name = false;
static bool crashes_save_counties = false;

// Provide weak versions of functions from hw2_wvpp.h
// Do not modify these functions. They will be superseded by the actual functions in hw2_wvpp.c.
struct list* __attribute__((weak)) create_list(void)
{
	printf("create_list is not implemented\n");

	// Mark function as not implemented
	not_implemented_create_list = true;

	return NULL;
}

struct node* __attribute__((weak)) get_head_node(struct list* listPtr)
{
	printf("get_head_node is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_head_node = true;

	return NULL;
}

struct node* __attribute__((weak)) process_input_line(const char* line)
{
	printf("process_input_line is not implemented\n");

	// Mark function as not implemented
	not_implemented_process_input_line = true;

	return NULL;
}

struct node* __attribute__((weak)) create_county(const char* county_name, const char* fips_code, const char* seat, int population, int area)
{
	printf("create_county_node is not implemented\n");

	// Mark function as not implemented
	not_implemented_create_county = true;

	return NULL;
}

void __attribute__((weak)) add_and_sort_county(struct list* listPtr, struct node* county_nodePtr)
{
	printf("add_and_sort_county is not implemented\n");

	// Mark function as not implemented
	not_implemented_add_and_sort_county = true;

	// Do nothing
}

int __attribute__((weak)) delete_by_county_name(struct list* listPtr, const char* county_name)
{
	printf("delete_by_county_name is not implemented\n");

	// Mark function as not implemented
	not_implemented_delete_by_county_name = true;

	return -999;
}

const char* __attribute__((weak)) get_county_name(struct node* nodePtr)
{
	printf("get_county_name is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_county_name = true;

	return NULL;
}

const char* __attribute__((weak)) get_fips_code(struct node* nodePtr)
{
	printf("get_fips_code is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_fips_code = true;

	return NULL;
}

const char* __attribute__((weak)) get_seat(struct node* nodePtr)
{
	printf("get_seat is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_seat = true;

	return NULL;
}

int __attribute__((weak)) get_population(struct node* nodePtr)
{
	printf("get_population is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_population = true;

	return -999;
}

int __attribute__((weak)) get_area(struct node* nodePtr)
{
	printf("get_area is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_area = true;

	return -999;
}

double __attribute__((weak)) get_population_density(struct node* nodePtr)
{
	printf("get_population_density is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_population_density = true;

	return -999.0;
}

struct node* __attribute__((weak)) get_next_node(struct node* nodePtr)
{
	printf("get_next_node is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_next_node = true;

	return NULL; // Return same node
}

void __attribute__((weak)) load_counties(struct list* listPtr, const char* filename)
{
	printf("load_counties is not implemented\n");

	// Mark function as not implemented
	not_implemented_load_counties = true;

	// Do nothing
}

void __attribute__((weak)) save_counties(struct list* listPtr, const char* filename)
{
	printf("save_counties is not implemented\n");

	// Mark function as not implemented
	not_implemented_save_counties = true;

	// Do nothing
}

char* __attribute__((weak)) trim(const char* string)
{
	printf("trim is not implemented\n");

	// Mark function as not implemented
	not_implemented_trim = true;

	return NULL;
}

char* __attribute__((weak)) substring(const char* source, unsigned int start_index, unsigned int end_index)
{
	printf("substring is not implemented\n");

	// Mark function as not implemented
	not_implemented_substring = true;

	return NULL;
}

const char* __attribute__((weak)) get_programmer_name(void)
{
	printf("get_programmer_name is not implemented\n");

	// Mark function as not implemented
	not_implemented_get_programmer_name = true;

	return NULL;
}

void run_tests(const char* input_file)
{
	// Store input file
	test_input_file = input_file;

	// Display status
	puts("");
	puts("==========");
	puts("Running tests...");
	puts("");

	// Run tests
	UNITY_BEGIN();

	puts("Step 2c: Running get_programmer_name tests...");
	RUN_TEST(test_2c_get_programmer_name);
	puts("");

	puts("Step 2d: Running trim tests...");
	puts("Due to limitations of C, it is possible for these tests to falsely PASS when you have not allocated enough memory or failed to null-terminate your trimmed strings.");
	RUN_TEST(test_2d_trim);
	puts("");

	puts("Step 2e: Running substring tests...");
	puts("Due to limitations of C, it is possible for these tests to falsely PASS when you have not allocated enough memory or failed to null-terminate your substrings.");
	RUN_TEST(test_2e_substring);
	puts("");

	puts("Step 2f: No tests are available for struct_node.");
	puts("");

	puts("Step 2g: Running create_list tests...");
	RUN_TEST(test_2g_create_list);
	puts("");

	puts("Step 2h: Running get_head_node tests...");
	RUN_TEST(test_2h_get_head_node);
	puts("");

	puts("Step 2i: Running get_county_name tests...");
	RUN_TEST(test_2i_get_county_name_valid);
	RUN_TEST(test_2i_get_county_name_null);
	puts("");

	puts("Step 2j: Running get_fips_code tests...");
	RUN_TEST(test_2j_get_fips_code_valid);
	RUN_TEST(test_2j_get_fips_code_null);
	puts("");

	puts("Step 2k: Running get_seat tests...");
	RUN_TEST(test_2k_get_seat_valid);
	RUN_TEST(test_2k_get_seat_null);
	puts("");

	puts("Step 2l: Running get_population tests...");
	RUN_TEST(test_2l_get_population_valid);
	RUN_TEST(test_2l_get_population_null);
	puts("");

	puts("Step 2m: Running get_area tests...");
	RUN_TEST(test_2m_get_area_valid);
	RUN_TEST(test_2m_get_area_null);
	puts("");

	puts("Step 2n: Running get_population_density tests...");
	RUN_TEST(test_2n_get_population_density_valid);
	RUN_TEST(test_2n_get_population_density_null);
	puts("");

	puts("Step 2o: Running get_next_node tests...");
	RUN_TEST(test_2o_get_next_node_valid);
	RUN_TEST(test_2o_get_next_node_null);
	puts("");

	puts("Step 2p: Running create_county tests...");
	puts("Due to limitations of C, it is possible for these tests to falsely PASS when you have not set the next node to NULL.");
	RUN_TEST(test_2p_create_county);
	puts("");

	puts("Step 2q: Running add_and_sort_county tests...");
	RUN_TEST(test_2q_add_and_sort_county_empty_list);
	RUN_TEST(test_2q_add_and_sort_county_nonempty_list_after_head);
	RUN_TEST(test_2q_add_and_sort_county_nonempty_list_new_head);
	RUN_TEST(test_2q_add_and_sort_county_multiple_counties);
	RUN_TEST(test_2q_add_and_sort_county_integer_division);
	puts("");

	puts("Step 2r: Running process_input_line tests...");
	RUN_TEST(test_2r_process_input_line_3_digit_area);
	RUN_TEST(test_2r_process_input_line_4_digit_area);
	// Enable for Summer 2024: RUN_TEST(test_2r_process_input_line_no_data);
	puts("");

	puts("Step 2s: Running load_counties tests...");
	puts("This test is relatively slow. Please be patient.");
	RUN_TEST(test_2s_load_counties);
	puts("");

	puts("Step 2t: Running delete_by_county_name tests...");
	RUN_TEST(test_2t_delete_by_county_name_one_county);
	RUN_TEST(test_2t_delete_by_county_name_first_county);
	RUN_TEST(test_2t_delete_by_county_name_last_county);
	RUN_TEST(test_2t_delete_by_county_name_middle_county);
	RUN_TEST(test_2t_delete_by_county_name_multiple_counties);
	RUN_TEST(test_2t_delete_by_county_name_nonexistent_county);
	RUN_TEST(test_2t_delete_by_county_name_null_list);
	puts("");

	puts("Step 2u: Running save_counties tests...");
	RUN_TEST(test_2u_save_counties_one_county);
	RUN_TEST(test_2u_save_counties_multiple_counties);
	puts("");

	UNITY_END();

	// Display message about evaluating with different unit tests 
	puts("");
	puts("Your instructor may evaluate your program with different unit tests than were provided to you.");

	// Display blank lines
	puts("");
	puts("==========");
	puts("");
}

void setUp(void)
{
	// set up test environment
}

void tearDown(void)
{
	// clean up test environment
}

void test_2c_get_programmer_name(void)
{
	// Use helper function to get programmer name
	const char* actual = helper_get_programmer_name();

	// Check that the string is not NULL
	TEST_ASSERT_NOT_NULL_MESSAGE(actual, "The get_programmer_name function returned NULL.");

	// Check that the string is not empty
	TEST_ASSERT_NOT_EMPTY_MESSAGE(actual, "The programmer name is empty.");
}

void test_2d_trim(void) {

	// Define test strings
	struct test_trim_string test_strings[] = {
		{.test_value = "ABCD EFG", .expected_value = "ABCD EFG"},
		{.test_value = "ABCDEFG", .expected_value = "ABCDEFG"},
		{.test_value = "  ABCD EFG  ", .expected_value = "ABCD EFG"},
		{.test_value = "ABCD EFG  ", .expected_value = "ABCD EFG"},
		{.test_value = "  ABCD EFG", .expected_value = "ABCD EFG"},
		{.test_value = "  ABCD EFG       1", .expected_value = "ABCD EFG       1"},
		{.test_value = "   ", .expected_value = ""},
		{.test_value = "", .expected_value = ""},
		// Enable for Summer 2024: {.test_value = NULL, .expected_value = NULL}
	};

	// Loop to compare each item
	for (int i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
		// Run function via forked process
		char* trimmedPtr = helper_trim(test_strings[i].test_value);

		// Mark as not working if result is NULL when it should not be
		if (trimmedPtr == NULL && test_strings[i].expected_value != NULL) {
			char error_message[1000];
			sprintf(error_message, "The trim function returned NULL when it should not have. This may have been caused by returning a local variable. Test value: '%s', expected value: '%s'", test_strings[i].test_value, test_strings[i].expected_value);
			TEST_FAIL_MESSAGE(error_message);
		}

		// Compare result
		TEST_ASSERT_EQUAL_STRING_MESSAGE(test_strings[i].expected_value, trimmedPtr, "The trim function does not return the expected value.");

		// Check length if not null
		if (test_strings[i].expected_value != NULL && trimmedPtr != NULL) {
			TEST_ASSERT_EQUAL_MESSAGE(strlen(test_strings[i].expected_value), strlen(trimmedPtr), "The length of the trimmed string does not match the expected length.");
		}		
		
		// Free memory
		free(trimmedPtr);
		trimmedPtr = NULL;
	}
}

void test_2e_substring(void) {
	// Define test strings
	struct test_substring_string test_strings[] = {
		{.test_value = "ABCDEFG", .expected_value = "ABC", .start_index = 0, .end_index = 3},
		{.test_value = "ABCDEFG", .expected_value = "ABCDEFG", .start_index = 0, .end_index = 7},
		{.test_value = "ABCD EFGH", .expected_value = "ABCD ", .start_index = 0, .end_index = 5},
		{.test_value = "  ABCD EFG  ", .expected_value = NULL, .start_index = 0, .end_index = 15},
		{.test_value = "West Virginia", .expected_value = "t V", .start_index = 3, .end_index = 6},
		{.test_value = "West Virginia ", .expected_value = NULL, .start_index = 7, .end_index = 6},
		{.test_value = "  ABCD EFG       1", .expected_value = "ABCD E", .start_index = 2, .end_index = 8 },
		{.test_value = "   ", .expected_value = " ", .start_index = 0, .end_index = 1},
		{.test_value = "Doddridge       017        West Union           7808        320 ", .expected_value="017", .start_index = 16, .end_index = 19}};

	// Loop to compare each item
	for (int i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
		// Run function via forked process
		char* substringPtr = helper_substring(test_strings[i].test_value, test_strings[i].start_index, test_strings[i].end_index);

		// Mark as not working if result is NULL when it should not be
		if (substringPtr == NULL && test_strings[i].expected_value != NULL) {
			char error_message[1000];
			sprintf(error_message, "The substring function returned NULL when it should not have. This may have been caused by returning a local variable. Test value: '%s', start index: %d, end index: %d, expected value: '%s'", test_strings[i].test_value, test_strings[i].start_index, test_strings[i].end_index, test_strings[i].expected_value);
			TEST_FAIL_MESSAGE(error_message);
		}

		// Compare result
		TEST_ASSERT_EQUAL_STRING_MESSAGE(test_strings[i].expected_value, substringPtr, "The substring function does not return the expected value.");

		// Check length if not null
		if (test_strings[i].expected_value != NULL && substringPtr != NULL)
		{
			char error_message[1000];

			// Get amount of memory allocated depending on platform
			size_t substringPtr_size = 0;
			#ifdef __APPLE__
				substringPtr_size = malloc_size(substringPtr);
			#else
				substringPtr_size = malloc_usable_size(substringPtr);
			#endif
			
			sprintf(error_message, "The length of the substring does not match the expected length. Test value: '%s', start index: %d, end index: %d, expected value: '%s'", test_strings[i].test_value, test_strings[i].start_index, test_strings[i].end_index, test_strings[i].expected_value);
			TEST_ASSERT_EQUAL_MESSAGE(strlen(test_strings[i].expected_value), strlen(substringPtr), error_message);

			sprintf(error_message, "The amount of memory allocated for the substring is too small. Test value: '%s', start index: %d, end index: %d, expected value: '%s'", test_strings[i].test_value, test_strings[i].start_index, test_strings[i].end_index, test_strings[i].expected_value);
			TEST_ASSERT_GREATER_OR_EQUAL_MESSAGE(strlen(test_strings[i].expected_value) + 1, substringPtr_size, error_message);
		}

		// Free memory
		free(substringPtr);
		substringPtr = NULL;
	}
}

void test_2f_struct_node_exists(void)
{
	TEST_FAIL_MESSAGE("No test has been implemented for struct node.");
}

void test_2g_create_list(void)
{
	// Use helper to create list
	struct list* listPtr = helper_create_list();

	// Check list is not NULL
	testsupport_validate_new_list(listPtr);

	// Free memory
	testsupport_free_list_memory(listPtr);
	listPtr = NULL;
}

void test_2h_get_head_node(void)
{
	// Use helper to create list
	struct list* listPtr = helper_create_list();

	// Make test node
	struct node* nodePtr = testsupport_create_test_node();

	// Assign test node as head node of list
	listPtr->headPtr = nodePtr;

	// Check to ensure get_head_node function has been implemented
	struct node* headPtr = helper_get_head_node(listPtr);

	// Get head node
	TEST_ASSERT_EQUAL_PTR(nodePtr, headPtr);

	// Free memory
	testsupport_free_list_memory(listPtr); // Includes node since it was added to list
	listPtr = NULL;
}

void test_2i_get_county_name_valid(void)
{
	// Create test node
	struct node* nodePtr = testsupport_create_test_node();

	const char* county_name = helper_get_county_name(nodePtr);

	TEST_ASSERT_EQUAL_STRING_MESSAGE(testvalue_county_name, county_name, "County name does not match expected value.");

	// Free memory
	free(nodePtr);
	nodePtr = NULL;
}

void test_2i_get_county_name_null(void)
{
	const char* county_name = helper_get_county_name(NULL);

	TEST_ASSERT_NULL_MESSAGE(county_name, "County name does not match expected value.");
}

void test_2j_get_fips_code_valid(void)
{
	// Create test node
	struct node* nodePtr = testsupport_create_test_node();

	const char* fips_code = helper_get_fips_code(nodePtr);

	TEST_ASSERT_EQUAL_STRING_MESSAGE(testvalue_fips_code, fips_code, "FIPS code does not match expected value.");

	// Free memory
	free(nodePtr);
	nodePtr = NULL;
}

void test_2j_get_fips_code_null(void)
{
	const char* fips_code = helper_get_fips_code(NULL);

	TEST_ASSERT_NULL_MESSAGE(fips_code, "FIPS code does not match expected value.");
}

void test_2k_get_seat_valid(void)
{
	// Create test node
	struct node* nodePtr = testsupport_create_test_node();

	const char* seat = helper_get_seat(nodePtr);

	TEST_ASSERT_EQUAL_STRING_MESSAGE(testvalue_seat, seat, "Seat does not match expected value.");

	// Free memory
	free(nodePtr);
	nodePtr = NULL;
}

void test_2k_get_seat_null(void)
{
	const char* seat = helper_get_seat(NULL);

	TEST_ASSERT_NULL_MESSAGE(seat, "Seat does not match expected value.");
}

void test_2l_get_population_valid(void)
{
	// Create test node
	struct node* nodePtr = testsupport_create_test_node();

	int population = helper_get_population(nodePtr);

	TEST_ASSERT_EQUAL_MESSAGE(testvalue_population, population, "Population does not match expected value.");

	// Free memory
	free(nodePtr);
	nodePtr = NULL;
}

void test_2l_get_population_null(void)
{
	int population = helper_get_population(NULL);

	TEST_ASSERT_EQUAL_MESSAGE(-1, population, "Population does not match expected value.");
}

void test_2m_get_area_valid(void)
{
	// Create test node
	struct node* nodePtr = testsupport_create_test_node();

	int area = helper_get_area(nodePtr);

	TEST_ASSERT_EQUAL_MESSAGE(testvalue_area, area, "Area does not match expected value.");

	// Free memory
	free(nodePtr);
	nodePtr = NULL;
}

void test_2m_get_area_null(void)
{
	int area = helper_get_area(NULL);

	TEST_ASSERT_EQUAL_MESSAGE(-1, area, "Area does not match expected value.");
}

void test_2n_get_population_density_valid(void)
{
	// Create test node
	struct node* nodePtr = testsupport_create_test_node();

	double population_density = helper_get_population_density(nodePtr);

	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE((double)testvalue_population / testvalue_area, population_density, "Population density does not match expected value.");

	// Free memory
	free(nodePtr);
	nodePtr = NULL;
}

void test_2n_get_population_density_null(void)
{

	double population_density = helper_get_population_density(NULL);

	TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(-1.0, population_density, "Population density does not match expected value.");
}

void test_2o_get_next_node_valid(void)
{
	// Create test node
	struct node* nodePtr = testsupport_create_test_node();

	// Check that the function has been implemented
	struct node* nextPtr = helper_get_next_node(nodePtr);

	// Display error if next node is not NULL (which it should be for new node) or not 0xFFFFFFFFFFFFFFFF (which it should be if create_county does not initialize properly)
	if (nextPtr != NULL && nextPtr != (void*)0xFFFFFFFFFFFFFFFF)
	{
		TEST_FAIL_MESSAGE("The next node pointer does not match the expected value.");
	}

	// Free memory
	free(nodePtr);
	nodePtr = NULL;
}

void test_2o_get_next_node_null(void)
{
	// Check that the function has been implemented
	struct node* nextPtr = helper_get_next_node(NULL);

	TEST_ASSERT_NULL_MESSAGE(nextPtr, "The next node pointer must be NULL when get_next_node is given a NULL node.");
}

void test_2p_create_county(void)
{
	// Assume at this point that the create_county function works
	struct node* nodePtr = helper_create_county(testvalue_county_name, testvalue_fips_code, testvalue_seat, testvalue_population, testvalue_area);

	// Check that the node is not NULL
	TEST_ASSERT_NOT_NULL_MESSAGE(nodePtr, "The county structure cannot be NULL.");

	// Try running get_... functions to test if they have been implemented
	const char* county_name = helper_get_county_name(nodePtr);
	const char* fips_code = helper_get_fips_code(nodePtr);
	const char* seat = helper_get_seat(nodePtr);
	int population = helper_get_population(nodePtr);
	int area = helper_get_area(nodePtr);
	double population_density = helper_get_population_density(nodePtr);
	struct node* nextPtr = helper_get_next_node(nodePtr);

	// Check that the population is correct
	TEST_ASSERT_EQUAL_MESSAGE(testvalue_population, population, "Population does not match expected value.");

	// Check that the area is correct
	TEST_ASSERT_EQUAL_MESSAGE(testvalue_area, area, "Area does not match expected value.");

	// Check that the population density is correct
	TEST_ASSERT_EQUAL_MESSAGE((double)testvalue_population / testvalue_area, population_density, "Population density does not match expected value.");

	// Check that the county name is correct
	TEST_ASSERT_EQUAL_STRING_MESSAGE(testvalue_county_name, county_name, "County name does not match expected value.");

	// Check that the FIPS code is correct
	TEST_ASSERT_EQUAL_STRING_MESSAGE(testvalue_fips_code, fips_code, "FIPS code does not match expected value.");

	// Check that the seat is correct
	TEST_ASSERT_EQUAL_STRING_MESSAGE(testvalue_seat, seat, "Seat does not match expected value.");

	// Check that the next node is NULL
	TEST_ASSERT_NULL_MESSAGE(nextPtr, "The last node's next node must be NULL.");

	// Free memory
	free(nodePtr);
	nodePtr = NULL;
}

void test_2q_add_and_sort_county_empty_list(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first node
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first node
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyOne }, 1, "Error adding first county.");

	// Free memory
	testsupport_free_list_memory(listPtr);
	listPtr = NULL;
}
void test_2q_add_and_sort_county_integer_division(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyOne }, 1, "Error adding first county.");

	// Create second county
	struct testsupport_county_data countyTwo = { .county_name = "CountyTwo", .fips_code = "222", .seat = "Seat Two", .population = 2222, .area = 100 };
	struct node* countyTwo_nodePtr = testsupport_create_county(countyTwo);

	// Add second county
	helper_add_and_sort_county(listPtr, countyTwo_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyTwo, countyOne }, 2, "Error adding second county, which should go in index 0.");

	// Create third county
	struct testsupport_county_data countyThree = { .county_name = "CountyThree", .fips_code = "333", .seat = "Seat Three", .population = 3333, .area = 100 };
	struct node* countyThree_nodePtr = testsupport_create_county(countyThree);

	// Add third county
	helper_add_and_sort_county(listPtr, countyThree_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyTwo, countyOne }, 3, "Error adding third county, which should go in index 0.");

	// Create fourth county
	struct testsupport_county_data countyFour = { .county_name = "CountyFour", .fips_code = "444", .seat = "Seat Four", .population = 2222, .area = 102 };
	struct node* countyFour_nodePtr = testsupport_create_county(countyFour);

	// Add fourth county
	helper_add_and_sort_county(listPtr, countyFour_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyTwo, countyFour, countyOne }, 4, "Error adding fourth county, which should go in index 2.");

	// Create fifth county
	struct testsupport_county_data countyFive = { .county_name = "CountyFive", .fips_code = "555", .seat = "Seat Five", .population = 2222, .area = 99 };
	struct node* countyFive_nodePtr = testsupport_create_county(countyFive);

	// Add fifth county
	helper_add_and_sort_county(listPtr, countyFive_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFive, countyTwo, countyFour, countyOne }, 5, "Error adding fifth county, which should go in index 1. You may be using integer division when calculating population densities.");

	// Create sixth county
	struct testsupport_county_data countySix = { .county_name = "CountySix", .fips_code = "666", .seat = "Seat Six", .population = 2222, .area = 101 };
	struct node* countySix_nodePtr = testsupport_create_county(countySix);

	// Add sixth county
	helper_add_and_sort_county(listPtr, countySix_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFive, countyTwo, countySix, countyFour, countyOne }, 6, "Error adding sixth county, which should go in index 3. You may be using integer division when calculating population densities.");

	// Create seventh county
	struct testsupport_county_data countySeven = { .county_name = "CountySeven", .fips_code = "777", .seat = "Seat Seven", .population = 2223, .area = 101 };
	struct node* countySeven_nodePtr = testsupport_create_county(countySeven);

	// Add seventh county
	helper_add_and_sort_county(listPtr, countySeven_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFive, countyTwo, countySeven, countySix, countyFour, countyOne }, 7, "Error adding seventh county, which should go in index 3. You may be using integer division when calculating population densities.");

	// Free memory
	testsupport_free_list_memory(listPtr);
	listPtr = NULL;
}

void test_2q_add_and_sort_county_multiple_counties(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyOne }, 1, "Error adding first county.");

	// Create second county
	struct testsupport_county_data countyTwo = { .county_name = "CountyTwo", .fips_code = "222", .seat = "Seat Two", .population = 2222, .area = 100 };
	struct node* countyTwo_nodePtr = testsupport_create_county(countyTwo);

	// Add second county
	helper_add_and_sort_county(listPtr, countyTwo_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyTwo, countyOne }, 2, "Error adding second county, which should go in index 0.");

	// Create third county
	struct testsupport_county_data countyThree = { .county_name = "CountyThree", .fips_code = "333", .seat = "Seat Three", .population = 3333, .area = 100 };
	struct node* countyThree_nodePtr = testsupport_create_county(countyThree);

	// Add third county
	helper_add_and_sort_county(listPtr, countyThree_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyTwo, countyOne }, 3, "Error adding third county, which should go in index 0.");

	// Create fourth county
	struct testsupport_county_data countyFour = { .county_name = "CountyFour", .fips_code = "444", .seat = "Seat Four", .population = 2333, .area = 100 };
	struct node* countyFour_nodePtr = testsupport_create_county(countyFour);

	// Add fourth county
	helper_add_and_sort_county(listPtr, countyFour_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyTwo, countyOne }, 4, "Error adding fourth county, which should go in index 1.");

	// Create fourth county
	struct testsupport_county_data countyFive = { .county_name = "CountyFive", .fips_code = "555", .seat = "Seat Five", .population = 555, .area = 100 };
	struct node* countyFive_nodePtr = testsupport_create_county(countyFive);

	// Add fourth county
	helper_add_and_sort_county(listPtr, countyFive_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyTwo, countyOne, countyFive }, 5, "Error adding fifth county, which should go in index 4.");

	// Free memory
	testsupport_free_list_memory(listPtr);
	listPtr = NULL;
}

void test_2q_add_and_sort_county_nonempty_list_after_head(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyOne }, 1, "Error adding first county.");

	// Create second county
	struct testsupport_county_data countyTwo = { .county_name = "CountyTwo", .fips_code = "222", .seat = "Seat Two", .population = 999, .area = 100 };
	struct node* countyTwo_nodePtr = testsupport_create_county(countyTwo);

	// Add second county
	helper_add_and_sort_county(listPtr, countyTwo_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyOne, countyTwo }, 2, "Error adding second county, which should go in index 1.");

	// Free memory
	testsupport_free_list_memory(listPtr);
	listPtr = NULL;
}

void test_2q_add_and_sort_county_nonempty_list_new_head(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyOne }, 1, "Error adding first county.");

	// Create second county
	struct testsupport_county_data countyTwo = { .county_name = "CountyTwo", .fips_code = "222", .seat = "Seat Two", .population = 2222, .area = 100 };
	struct node* countyTwo_nodePtr = testsupport_create_county(countyTwo);

	// Add second county
	helper_add_and_sort_county(listPtr, countyTwo_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyTwo, countyOne }, 2, "Error adding second county, which should go in index 0.");

	// Free memory
	testsupport_free_list_memory(listPtr);
	listPtr = NULL;
}

void test_2r_process_input_line_3_digit_area(void)
{
	// Create test node
	const char* line = "Doddridge       017        West Union           7808        320 ";
	struct node* dataPtr = helper_process_input_line(line);

	// Check that the node is not NULL
	TEST_ASSERT_NOT_NULL_MESSAGE(dataPtr, "The process_input_line function should not have returned NULL.");

	// Try running get_... functions to test if they have been implemented
	const char* county_name = testsupport_fix_null_termination(helper_get_county_name(dataPtr));
	const char* fips_code = testsupport_fix_null_termination(helper_get_fips_code(dataPtr));
	const char* seat = testsupport_fix_null_termination(helper_get_seat(dataPtr));
	int population = helper_get_population(dataPtr);
	int area = helper_get_area(dataPtr);
	double population_density = helper_get_population_density(dataPtr);
	struct node* nextPtr = helper_get_next_node(dataPtr);

	// Check numeric values
	TEST_ASSERT_EQUAL_MESSAGE(7808, population, "The population was not processed correctly.");
	TEST_ASSERT_EQUAL_MESSAGE(320, area, "The area was not processed correctly.");
	TEST_ASSERT_EQUAL_MESSAGE(7808.0 / 320.0, population_density, "The population density was not processed correctly.");

	// Check for nonprintable characters, which may indicate a problem in the trim or substring functions
	TEST_ASSERT_TRUE_MESSAGE(testsupport_is_printable(county_name), "The county name contains nonprintable characters. This is likely caused by a problem with not allocating enough memory or null-terminating strings in your trim or substring functions.");
	TEST_ASSERT_TRUE_MESSAGE(testsupport_is_printable(fips_code), "The FIPS code contains nonprintable characters. This is likely caused by a problem with not allocating enough memory or null-terminating strings in your trim or substring functions.");
	TEST_ASSERT_TRUE_MESSAGE(testsupport_is_printable(seat), "The seat contains nonprintable characters. This is likely caused by a problem with not allocating enough memory or null-terminating strings in your trim or substring functions.");

	// Check values for Doddridge County for string contents
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Doddridge", county_name, "The county name was not processed correctly.");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("017", fips_code, "The FIPS code was not processed correctly.");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("West Union", seat, "The seat was not processed correctly.");
	
	// Check that the next node is NULL
	if (nextPtr != NULL)
	{
		puts("The next node is not NULL. Check your create_county function.");
	}

	// Free memory
	free(dataPtr);
	dataPtr = NULL;
}

void test_2r_process_input_line_4_digit_area(void)
{
	// Create test node
	const char* line = "Randolph        083        Elkins               27932       1040";
	struct node* dataPtr = helper_process_input_line(line);

	// Check that the node is not NULL
	TEST_ASSERT_NOT_NULL_MESSAGE(dataPtr, "The process_input_line function should not have returned NULL.");

	// Try running get_... functions to test if they have been implemented
	const char* county_name = testsupport_fix_null_termination(helper_get_county_name(dataPtr));
	const char* fips_code = testsupport_fix_null_termination(helper_get_fips_code(dataPtr));
	const char* seat = testsupport_fix_null_termination(helper_get_seat(dataPtr));
	int population = helper_get_population(dataPtr);
	int area = helper_get_area(dataPtr);
	double population_density = helper_get_population_density(dataPtr);
	struct node* nextPtr = helper_get_next_node(dataPtr);

	// Check numeric values
	TEST_ASSERT_EQUAL_MESSAGE(27932, population, "The population was not processed correctly.");
	TEST_ASSERT_EQUAL_MESSAGE(1040, area, "The area was not processed correctly.");
	TEST_ASSERT_EQUAL_MESSAGE(27932.0 / 1040.0, population_density, "The population density was not processed correctly.");

	// Check for nonprintable characters, which may indicate a problem in the trim or substring functions
	TEST_ASSERT_TRUE_MESSAGE(testsupport_is_printable(county_name), "The county name contains nonprintable characters. This is likely caused by a problem with not allocating enough memory or null-terminating strings in your trim or substring functions.");
	TEST_ASSERT_TRUE_MESSAGE(testsupport_is_printable(fips_code), "The FIPS code contains nonprintable characters. This is likely caused by a problem with not allocating enough memory or null-terminating strings in your trim or substring functions.");
	TEST_ASSERT_TRUE_MESSAGE(testsupport_is_printable(seat), "The seat contains nonprintable characters. This is likely caused by a problem with not allocating enough memory or null-terminating strings in your trim or substring functions.");

	// Check values for string contents
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Randolph", county_name, "The county name was not processed correctly.");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("083", fips_code, "The FIPS code was not processed correctly.");
	TEST_ASSERT_EQUAL_STRING_MESSAGE("Elkins", seat, "The seat was not processed correctly.");	
	
	// Check that the next node is NULL
	if (nextPtr != NULL)
	{
		puts("The next node is not NULL. Check your create_county function.");
	}

	// Free memory
	free(dataPtr);
	dataPtr = NULL;
}

void test_2r_process_input_line_no_data(void)
{
	// Create test node
	const char* line = "";
	struct node* dataPtr = helper_process_input_line(line);

	// Check that the node is not NULL
	TEST_ASSERT_NULL_MESSAGE(dataPtr, "The process_input_line function should have returned NULL.");

	// Free memory
	free(dataPtr);
	dataPtr = NULL;
}

void test_2s_load_counties(void)
{
	// Define county data
	struct testsupport_county_data county_data[] = {
		{.county_name = "Ohio", .fips_code = "069", .seat = "Wheeling", .population = 42425, .area = 106 },
		{.county_name = "Berkeley", .fips_code = "003", .seat = "Martinsburg", .population = 122076, .area = 321 },
		{.county_name = "Hancock", .fips_code = "029", .seat = "New Cumberland", .population = 29095, .area = 83 },
		{.county_name = "Cabell", .fips_code = "011", .seat = "Huntington", .population = 94350, .area = 282 },
		{.county_name = "Monongalia", .fips_code = "061", .seat = "Morgantown", .population = 105822, .area = 361 },
		{.county_name = "Jefferson", .fips_code = "037", .seat = "Charles Town", .population = 57701, .area = 210 },
		{.county_name = "Brooke", .fips_code = "009", .seat = "Wellsburg", .population = 22559, .area = 89 },
		{.county_name = "Wood", .fips_code = "107", .seat = "Parkersburg", .population = 84296, .area = 367 },
		{.county_name = "Kanawha", .fips_code = "039", .seat = "Charleston", .population = 180745, .area = 903 },
		{.county_name = "Marion", .fips_code = "049", .seat = "Fairmont", .population = 56205, .area = 310 },
		{.county_name = "Putnam", .fips_code = "079", .seat = "Winfield", .population = 57440, .area = 346 },
		{.county_name = "Harrison", .fips_code = "033", .seat = "Clarksburg", .population = 65291, .area = 416 },
		{.county_name = "Mercer", .fips_code = "055", .seat = "Princeton", .population = 59664, .area = 420 },
		{.county_name = "Raleigh", .fips_code = "081", .seat = "Beckley", .population = 74591, .area = 607 },
		{.county_name = "Marshall", .fips_code = "051", .seat = "Moundsville", .population = 30591, .area = 307 },
		{.county_name = "Taylor", .fips_code = "091", .seat = "Grafton", .population = 16705, .area = 173 },
		{.county_name = "Mineral", .fips_code = "057", .seat = "Keyser", .population = 26938, .area = 328 },
		{.county_name = "Wayne", .fips_code = "099", .seat = "Wayne", .population = 38982, .area = 506 },
		{.county_name = "Morgan", .fips_code = "065", .seat = "Berkeley Springs", .population = 17063, .area = 229 },
		{.county_name = "Logan", .fips_code = "045", .seat = "Logan", .population = 32567, .area = 454 },
		{.county_name = "Upshur", .fips_code = "097", .seat = "Buckhannon", .population = 23816, .area = 355 },
		{.county_name = "Fayette", .fips_code = "019", .seat = "Fayetteville", .population = 40488, .area = 664 },
		{.county_name = "Jackson", .fips_code = "035", .seat = "Ripley", .population = 27791, .area = 466 },
		{.county_name = "Mason", .fips_code = "053", .seat = "Point Pleasant", .population = 25453, .area = 432 },
		{.county_name = "Pleasants", .fips_code = "073", .seat = "Saint Marys", .population = 7653, .area = 131 },
		{.county_name = "Mingo", .fips_code = "059", .seat = "Williamson", .population = 23568, .area = 423 },
		{.county_name = "Preston", .fips_code = "077", .seat = "Kingwood", .population = 34216, .area = 648 },
		{.county_name = "Lincoln", .fips_code = "043", .seat = "Hamlin", .population = 20463, .area = 438 },
		{.county_name = "Barbour", .fips_code = "001", .seat = "Philippi", .population = 15465, .area = 341 },
		{.county_name = "Lewis", .fips_code = "041", .seat = "Weston", .population = 17033, .area = 389 },
		{.county_name = "Boone", .fips_code = "005", .seat = "Madison", .population = 21809, .area = 503 },
		{.county_name = "Wyoming", .fips_code = "109", .seat = "Pineville", .population = 21382, .area = 501 },
		{.county_name = "Wetzel", .fips_code = "103", .seat = "New Martinsville", .population = 14442, .area = 359 },
		{.county_name = "Nicholas", .fips_code = "067", .seat = "Summersville", .population = 24604, .area = 649 },
		{.county_name = "Hampshire", .fips_code = "027", .seat = "Romney", .population = 23093, .area = 642 },
		{.county_name = "McDowell", .fips_code = "047", .seat = "Welch", .population = 19111, .area = 535 },
		{.county_name = "Summers", .fips_code = "089", .seat = "Hinton", .population = 11959, .area = 361 },
		{.county_name = "Greenbrier", .fips_code = "025", .seat = "Lewisburg", .population = 32977, .area = 1021 },
		{.county_name = "Tyler", .fips_code = "095", .seat = "Middlebourne", .population = 8313, .area = 258 },
		{.county_name = "Roane", .fips_code = "087", .seat = "Spencer", .population = 14028, .area = 484 },
		{.county_name = "Randolph", .fips_code = "083", .seat = "Elkins", .population = 27932, .area = 1040 },
		{.county_name = "Monroe", .fips_code = "063", .seat = "Union", .population = 12376, .area = 473 },
		{.county_name = "Hardy", .fips_code = "031", .seat = "Moorefield", .population = 14299, .area = 583 },
		{.county_name = "Doddridge", .fips_code = "017", .seat = "West Union", .population = 7808, .area = 320 },
		{.county_name = "Braxton", .fips_code = "007", .seat = "Sutton", .population = 12447, .area = 514 },
		{.county_name = "Clay", .fips_code = "015", .seat = "Clay", .population = 8051, .area = 342 },
		{.county_name = "Grant", .fips_code = "023", .seat = "Petersburg", .population = 10976, .area = 477 },
		{.county_name = "Wirt", .fips_code = "105", .seat = "Elizabeth", .population = 5194, .area = 233 },
		{.county_name = "Calhoun", .fips_code = "013", .seat = "Grantsville", .population = 6229, .area = 281 },
		{.county_name = "Gilmer", .fips_code = "021", .seat = "Glenville", .population = 7408, .area = 340 },
		{.county_name = "Ritchie", .fips_code = "085", .seat = "Harrisville", .population = 8444, .area = 454 },
		{.county_name = "Tucker", .fips_code = "093", .seat = "Parsons", .population = 6762, .area = 419 },
		{.county_name = "Webster", .fips_code = "101", .seat = "Webster Springs", .population = 8378, .area = 556 },
		{.county_name = "Pendleton", .fips_code = "071", .seat = "Franklin", .population = 6143, .area = 698 },
		{.county_name = "Pocahontas", .fips_code = "075", .seat = "Marlinton", .population = 7869, .area = 940 }
	};

	// Create list
	struct list* listPtr = helper_create_list();

	// Load counties
	helper_load_counties(listPtr, test_input_file);

	// Check list to ensure counties were loaded correctly
	testsupport_check_list_contents(listPtr, county_data, 55, "County data not loaded correctly.");

	// Free memory
	testsupport_free_list_memory(listPtr); // Includes freeing the nodes
	listPtr = NULL;
}

void test_2t_delete_by_county_name_first_county(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Create second county
	struct testsupport_county_data countyTwo = { .county_name = "CountyTwo", .fips_code = "222", .seat = "Seat Two", .population = 2222, .area = 100 };
	struct node* countyTwo_nodePtr = testsupport_create_county(countyTwo);
	helper_add_and_sort_county(listPtr, countyTwo_nodePtr); \

		// Create third county
		struct testsupport_county_data countyThree = { .county_name = "CountyThree", .fips_code = "333", .seat = "Seat Three", .population = 3333, .area = 100 };
	struct node* countyThree_nodePtr = testsupport_create_county(countyThree);
	helper_add_and_sort_county(listPtr, countyThree_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFour = { .county_name = "CountyFour", .fips_code = "444", .seat = "Seat Four", .population = 2333, .area = 100 };
	struct node* countyFour_nodePtr = testsupport_create_county(countyFour);
	helper_add_and_sort_county(listPtr, countyFour_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFive = { .county_name = "CountyFive", .fips_code = "555", .seat = "Seat Five", .population = 555, .area = 100 };
	struct node* countyFive_nodePtr = testsupport_create_county(countyFive);
	helper_add_and_sort_county(listPtr, countyFive_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyTwo, countyOne, countyFive }, 5, "Counties in list are not in the correct order. Have not tried to delete any counties yet.");

	// Delete first county
	int delete_return = helper_delete_by_county_name(listPtr, countyThree.county_name);

	// Check delete return values	
	TEST_ASSERT_EQUAL_MESSAGE(0, delete_return, "The delete_by_county_name function did not return 0 when deleting a node that existed.");
	TEST_ASSERT_EQUAL_MESSAGE(1, helper_delete_by_county_name(listPtr, countyThree.county_name), "The delete_by_county_name function did not return 1 when attempting to delete a county that had already been deleted.");

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyFour, countyTwo, countyOne, countyFive }, 4, "Counties list is not correct after deleting the first county.");

	// Free memory
	testsupport_free_list_memory(listPtr); // Includes freeing the nodes
	listPtr = NULL;
}

void test_2t_delete_by_county_name_last_county(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Create second county
	struct testsupport_county_data countyTwo = { .county_name = "CountyTwo", .fips_code = "222", .seat = "Seat Two", .population = 2222, .area = 100 };
	struct node* countyTwo_nodePtr = testsupport_create_county(countyTwo);
	helper_add_and_sort_county(listPtr, countyTwo_nodePtr);

	// Create third county
	struct testsupport_county_data countyThree = { .county_name = "CountyThree", .fips_code = "333", .seat = "Seat Three", .population = 3333, .area = 100 };
	struct node* countyThree_nodePtr = testsupport_create_county(countyThree);
	helper_add_and_sort_county(listPtr, countyThree_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFour = { .county_name = "CountyFour", .fips_code = "444", .seat = "Seat Four", .population = 2333, .area = 100 };
	struct node* countyFour_nodePtr = testsupport_create_county(countyFour);
	helper_add_and_sort_county(listPtr, countyFour_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFive = { .county_name = "CountyFive", .fips_code = "555", .seat = "Seat Five", .population = 555, .area = 100 };
	struct node* countyFive_nodePtr = testsupport_create_county(countyFive);
	helper_add_and_sort_county(listPtr, countyFive_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyTwo, countyOne, countyFive }, 5, "Counties in list are not in the correct order. Have not tried to delete any counties yet.");

	// Delete first county
	int delete_return = helper_delete_by_county_name(listPtr, countyFive.county_name);

	// Check delete return values	
	TEST_ASSERT_EQUAL_MESSAGE(0, delete_return, "The delete_by_county_name function did not return 0 when deleting a node that existed.");
	TEST_ASSERT_EQUAL_MESSAGE(1, helper_delete_by_county_name(listPtr, countyFive.county_name), "The delete_by_county_name function did not return 1 when attempting to delete a county that had already been deleted.");

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyTwo, countyOne }, 4, "Counties list is not correct after deleting the last county.");

	// Free memory
	testsupport_free_list_memory(listPtr); // Includes freeing the nodes
	listPtr = NULL;
}

void test_2t_delete_by_county_name_middle_county(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Create second county
	struct testsupport_county_data countyTwo = { .county_name = "CountyTwo", .fips_code = "222", .seat = "Seat Two", .population = 2222, .area = 100 };
	struct node* countyTwo_nodePtr = testsupport_create_county(countyTwo);
	helper_add_and_sort_county(listPtr, countyTwo_nodePtr); \

		// Create third county
		struct testsupport_county_data countyThree = { .county_name = "CountyThree", .fips_code = "333", .seat = "Seat Three", .population = 3333, .area = 100 };
	struct node* countyThree_nodePtr = testsupport_create_county(countyThree);
	helper_add_and_sort_county(listPtr, countyThree_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFour = { .county_name = "CountyFour", .fips_code = "444", .seat = "Seat Four", .population = 2333, .area = 100 };
	struct node* countyFour_nodePtr = testsupport_create_county(countyFour);
	helper_add_and_sort_county(listPtr, countyFour_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFive = { .county_name = "CountyFive", .fips_code = "555", .seat = "Seat Five", .population = 555, .area = 100 };
	struct node* countyFive_nodePtr = testsupport_create_county(countyFive);
	helper_add_and_sort_county(listPtr, countyFive_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyTwo, countyOne, countyFive }, 5, "Counties in list are not in the correct order. Have not tried to delete any counties yet.");

	// Delete first county
	int delete_return = helper_delete_by_county_name(listPtr, countyTwo.county_name);

	// Check delete return values	
	TEST_ASSERT_EQUAL_MESSAGE(0, delete_return, "The delete_by_county_name function did not return 0 when deleting a node that existed.");
	TEST_ASSERT_EQUAL_MESSAGE(1, helper_delete_by_county_name(listPtr, countyTwo.county_name), "The delete_by_county_name function did not return 1 when attempting to delete a county that had already been deleted.");

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyOne, countyFive }, 4, "Counties list is not correct after deleting the third county.");

	// Free memory
	testsupport_free_list_memory(listPtr); // Includes freeing the nodes
	listPtr = NULL;
}

void test_2t_delete_by_county_name_multiple_counties(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Create second county
	struct testsupport_county_data countyTwo = { .county_name = "CountyTwo", .fips_code = "222", .seat = "Seat Two", .population = 2222, .area = 100 };
	struct node* countyTwo_nodePtr = testsupport_create_county(countyTwo);
	helper_add_and_sort_county(listPtr, countyTwo_nodePtr);

	// Create third county
	struct testsupport_county_data countyThree = { .county_name = "CountyThree", .fips_code = "333", .seat = "Seat Three", .population = 3333, .area = 100 };
	struct node* countyThree_nodePtr = testsupport_create_county(countyThree);
	helper_add_and_sort_county(listPtr, countyThree_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFour = { .county_name = "CountyFour", .fips_code = "444", .seat = "Seat Four", .population = 2333, .area = 100 };
	struct node* countyFour_nodePtr = testsupport_create_county(countyFour);
	helper_add_and_sort_county(listPtr, countyFour_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFive = { .county_name = "CountyFive", .fips_code = "555", .seat = "Seat Five", .population = 555, .area = 100 };
	struct node* countyFive_nodePtr = testsupport_create_county(countyFive);
	helper_add_and_sort_county(listPtr, countyFive_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyTwo, countyOne, countyFive }, 5, "Counties in list are not in the correct order. Have not tried to delete any counties yet.");

	// Delete middle county
	int delete_return = helper_delete_by_county_name(listPtr, countyTwo.county_name);

	// Check delete return values	
	TEST_ASSERT_EQUAL_MESSAGE(0, delete_return, "The delete_by_county_name function did not return 0 when deleting a node that existed.");
	TEST_ASSERT_EQUAL_MESSAGE(1, helper_delete_by_county_name(listPtr, countyTwo.county_name), "The delete_by_county_name function did not return 1 when attempting to delete a county that had already been deleted.");

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyOne, countyFive }, 4, "Counties list is not correct after deleting a middle county.");

	// Delete another middle county
	delete_return = helper_delete_by_county_name(listPtr, countyOne.county_name);

	// Check delete return values	
	TEST_ASSERT_EQUAL_MESSAGE(0, delete_return, "The delete_by_county_name function did not return 0 when deleting a node that existed.");
	TEST_ASSERT_EQUAL_MESSAGE(1, helper_delete_by_county_name(listPtr, countyOne.county_name), "The delete_by_county_name function did not return 1 when attempting to delete a county that had already been deleted.");

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyFive }, 3, "Counties list is not correct after deleting another middle county.");

	// Delete first county
	delete_return = helper_delete_by_county_name(listPtr, countyThree.county_name);

	// Check that the function has been implemented
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_delete_by_county_name, "The delete_by_county_name function has not been implemented.");

	// Check delete return values	
	TEST_ASSERT_EQUAL_MESSAGE(0, delete_return, "The delete_by_county_name function did not return 0 when deleting a node that existed.");
	TEST_ASSERT_EQUAL_MESSAGE(1, helper_delete_by_county_name(listPtr, countyThree.county_name), "The delete_by_county_name function did not return 1 when attempting to delete a county that had already been deleted.");

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyFour, countyFive }, 2, "Counties list is not correct after deleting the first county.");

	// Free memory
	testsupport_free_list_memory(listPtr); // Includes freeing the nodes
	listPtr = NULL;
}

void test_2t_delete_by_county_name_nonexistent_county(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Create second county
	struct testsupport_county_data countyTwo = { .county_name = "CountyTwo", .fips_code = "222", .seat = "Seat Two", .population = 2222, .area = 100 };
	struct node* countyTwo_nodePtr = testsupport_create_county(countyTwo);
	helper_add_and_sort_county(listPtr, countyTwo_nodePtr); \

		// Create third county
		struct testsupport_county_data countyThree = { .county_name = "CountyThree", .fips_code = "333", .seat = "Seat Three", .population = 3333, .area = 100 };
	struct node* countyThree_nodePtr = testsupport_create_county(countyThree);
	helper_add_and_sort_county(listPtr, countyThree_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFour = { .county_name = "CountyFour", .fips_code = "444", .seat = "Seat Four", .population = 2333, .area = 100 };
	struct node* countyFour_nodePtr = testsupport_create_county(countyFour);
	helper_add_and_sort_county(listPtr, countyFour_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFive = { .county_name = "CountyFive", .fips_code = "555", .seat = "Seat Five", .population = 555, .area = 100 };
	struct node* countyFive_nodePtr = testsupport_create_county(countyFive);
	helper_add_and_sort_county(listPtr, countyFive_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyTwo, countyOne, countyFive }, 5, "Counties in list are not in the correct order. Have not tried to delete any counties yet.");

	// Delete first county
	int delete_return = helper_delete_by_county_name(listPtr, "CountyDoesNotExist");

	// Check delete return values	
	TEST_ASSERT_EQUAL_MESSAGE(1, delete_return, "The delete_by_county_name function did not return 1 when attempting to delete a county that did not exist.");

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyTwo, countyOne, countyFive }, 5, "Counties list is not correct after deleting the first county.");

	// Free memory
	testsupport_free_list_memory(listPtr); // Includes freeing the nodes
	listPtr = NULL;
}

void test_2t_delete_by_county_name_null_list(void)
{
	// Attempt to delete from an empty list
	int delete_return = helper_delete_by_county_name(NULL, "CountyDoesNotExist");

	// Ensure that the function has been implemented
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_delete_by_county_name, "The delete_by_county_name function has not been implemented.");

	TEST_ASSERT_EQUAL_MESSAGE(2, delete_return, "The delete_by_county_name function did not return 2 when deleting from a NULL list.");
}

void test_2t_delete_by_county_name_one_county(void)
{
	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyOne }, 1, "Counties in list are not in the correct order. Have not tried to delete any counties yet.");

	// Delete first county
	int delete_return = helper_delete_by_county_name(listPtr, countyOne.county_name);

	// Check delete return values	
	TEST_ASSERT_EQUAL_MESSAGE(0, delete_return, "The delete_by_county_name function did not return 0 when deleting a node that existed.");
	TEST_ASSERT_EQUAL_MESSAGE(1, helper_delete_by_county_name(listPtr, countyOne.county_name), "The delete_by_county_name function did not return 1 when attempting to delete a county that had already been deleted.");

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) {  }, 0, "Counties list is not correct after deleting the only county.");

	// Free memory
	testsupport_free_list_memory(listPtr); // Includes freeing the nodes
	listPtr = NULL;
}

void test_2u_save_counties_multiple_counties(void)
{
	// Define filename
	const char* filename = "test_save_counties_multiple_counties.txt";

	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Create second county
	struct testsupport_county_data countyTwo = { .county_name = "CountyTwo", .fips_code = "222", .seat = "Seat Two", .population = 2222, .area = 100 };
	struct node* countyTwo_nodePtr = testsupport_create_county(countyTwo);
	helper_add_and_sort_county(listPtr, countyTwo_nodePtr);

	// Create third county
	struct testsupport_county_data countyThree = { .county_name = "CountyThree", .fips_code = "333", .seat = "Seat Three", .population = 3333, .area = 100 };
	struct node* countyThree_nodePtr = testsupport_create_county(countyThree);
	helper_add_and_sort_county(listPtr, countyThree_nodePtr);

	// Create fourth county
	struct testsupport_county_data countyFour = { .county_name = "CountyFour", .fips_code = "444", .seat = "Seat Four", .population = 2333, .area = 100 };
	struct node* countyFour_nodePtr = testsupport_create_county(countyFour);
	helper_add_and_sort_county(listPtr, countyFour_nodePtr);

	// Create fifth county
	struct testsupport_county_data countyFive = { .county_name = "CountyFive", .fips_code = "555", .seat = "Seat Five", .population = 555, .area = 100 };
	struct node* countyFive_nodePtr = testsupport_create_county(countyFive);
	helper_add_and_sort_county(listPtr, countyFive_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyThree, countyFour, countyTwo, countyOne, countyFive }, 5, "Problem with add_and_sort county function. Counties are missing or not in correct order.");

	// Save counties
	helper_save_counties(listPtr, filename);

	// Define what should be in the file
	const char* expected_file_contents[] = { "County Name,FIPS Code,Seat,Population,Area,Population Density",
		"CountyThree,333,Seat Three,3333,100,33.33",
		"CountyFour,444,Seat Four,2333,100,23.33",
		"CountyTwo,222,Seat Two,2222,100,22.22",
		"CountyOne,111,Seat One,1111,100,11.11",
		"CountyFive,555,Seat Five,555,100,5.55"
	};

	// Read file to make sure it matches
	FILE* filePtr = fopen(filename, "r");

	// Ensure file was opened
	char message[100];
	sprintf(message, "Could not open file %s to read.", filename);
	TEST_ASSERT_NOT_NULL_MESSAGE(filePtr, message);

	// Loop over expected file contents
	int line_number = 0;
	char line[100];
	while (fgets(line, sizeof(line), filePtr) != NULL)
	{
		// Clean line to fix spacing with commas
		char* position = strstr(line, ", ");
		while (position != NULL) {
			memmove(position + 1, position + 2, strlen(position));
			position = strstr(line, ", ");
		}

		// Clean line to remove newline symbols
		size_t len = strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
			line[len - 1] = '\0';
			len--;
		}

		// Construct error message
		char message[200];
		sprintf(message, "File contents do not match expected contents at line %d, where the first line is line 1.", line_number + 1);

		// Check that the line matches
		TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_file_contents[line_number], line, message);

		// Increment line number
		line_number++;
	}

	// Display error if there are no lines in the file
	if (line_number == 0)
	{
		char message[200];
		sprintf(message, "The file %s appears to be empty. Ensure that you are writing to the file and that you are closing it at the end of your save_counties function.", filename);
		TEST_FAIL_MESSAGE(message);
	}

	// Ensure that the file has the correct number of lines
	if (line_number != sizeof(expected_file_contents) / sizeof(expected_file_contents[0]))
	{
		char message[200];
		sprintf(message, "The file %s does not have the correct number of lines. The file has %d lines, but should have %zu lines.", filename, line_number, sizeof(expected_file_contents) / sizeof(expected_file_contents[0]));
		TEST_FAIL_MESSAGE(message);
	}

	// Close file
	fclose(filePtr);
	filePtr = NULL;

	// Delete file
	//remove(filename);

	// Free memory
	testsupport_free_list_memory(listPtr); // Includes freeing the nodes
	listPtr = NULL;
}

void test_2u_save_counties_one_county(void)
{
	// Define filename
	const char* filename = "test_save_counties_one_county.txt";

	// Create list
	struct list* listPtr = helper_create_list();

	// Create first county
	struct testsupport_county_data countyOne = { .county_name = "CountyOne", .fips_code = "111", .seat = "Seat One", .population = 1111, .area = 100 };
	struct node* countyOne_nodePtr = testsupport_create_county(countyOne);

	// Add first county
	helper_add_and_sort_county(listPtr, countyOne_nodePtr);

	// Check list contents
	testsupport_check_list_contents(listPtr, (struct testsupport_county_data[]) { countyOne }, 1, "Problem with add_and_sort county function. Counties are missing or not in correct order.");

	// Save counties
	helper_save_counties(listPtr, filename);

	// Define what should be in the file
	const char* expected_file_contents[] = {
		"County Name,FIPS Code,Seat,Population,Area,Population Density",
		"CountyOne,111,Seat One,1111,100,11.11",
	};

	// Read file to make sure it matches
	FILE* filePtr = fopen(filename, "r");

	// Ensure file was opened
	char message[100];
	sprintf(message, "Could not open file %s to read.", filename);
	TEST_ASSERT_NOT_NULL_MESSAGE(filePtr, message);

	// Loop over expected file contents
	int line_number = 0;
	char line[100];
	while (fgets(line, sizeof(line), filePtr) != NULL)
	{
		// Clean line to fix spacing with commas
		char* position = strstr(line, ", ");
		while (position != NULL) {
			memmove(position + 1, position + 2, strlen(position));
			position = strstr(line, ", ");
		}

		// Clean line to remove newline symbols
		size_t len = strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
			line[len - 1] = '\0';
			len--;
		}

		// Construct error message
		char message[200];
		sprintf(message, "File contents do not match expected contents at line %d, where the first line is line 1.", line_number + 1);

		// Check that the line matches
		TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_file_contents[line_number], line, message);

		// Increment line number
		line_number++;
	}

	// Display error if there are no lines in the file
	if (line_number == 0)
	{
		char message[200];
		sprintf(message, "The file %s appears to be empty. Ensure that you are writing to the file and that you are closing it at the end of your save_counties function.", filename);
		TEST_FAIL_MESSAGE(message);
	}

	// Ensure that the file has the correct number of lines
	if (line_number != sizeof(expected_file_contents) / sizeof(expected_file_contents[0]))
	{
		char message[200];
		sprintf(message, "The file %s does not have the correct number of lines. The file has %d lines, but should have %zu lines.", filename, line_number, sizeof(expected_file_contents) / sizeof(expected_file_contents[0]));
		TEST_FAIL_MESSAGE(message);
	}

	// Close file
	fclose(filePtr);
	filePtr = NULL;

	// Delete file
	//remove(filename);

	// Free memory
	testsupport_free_list_memory(listPtr); // Includes freeing the nodes
	listPtr = NULL;
}

const char* helper_get_programmer_name(void)
{
	// Check if function works in forked process
	CALL_FUNCTION_STRING(get_programmer_name);

	// Return programmer name
	return get_programmer_name();

}

char* helper_trim(const char* untrimmed)
{
	// Check if function works in forked process
	CALL_FUNCTION_STRING(trim, untrimmed);

	// Return trimmed string
	return trim(untrimmed);
}

char* helper_substring(const char* source, unsigned int start_index, unsigned int end_index)
{
	// Check if function works in forked process
	CALL_FUNCTION_STRING(substring, source, start_index, end_index);

	// Return substring
	return substring(source, start_index, end_index);
}

struct list* helper_create_list(void)
{
	// Check if function works in forked process
	CALL_FUNCTION_POINTER_NOT_NULL(create_list);

	// Create list
	struct list* listPtr = create_list();

	// Validate list
	testsupport_validate_new_list(listPtr);

	// Return list
	return listPtr;
}

struct node* helper_get_head_node(struct list* listPtr)
{
	// Check if function works in forked process
	CALL_FUNCTION_POINTER(get_head_node, listPtr);

	// Return head node
	return get_head_node(listPtr);
}

const char* helper_get_county_name(struct node* nodePtr)
{
	// Check if function works in forked process
	CALL_FUNCTION_STRING(get_county_name, nodePtr);

	// Return county name
	return get_county_name(nodePtr);
}

const char* helper_get_fips_code(struct node* nodePtr)
{
	// Check if function works in forked process
	CALL_FUNCTION_STRING(get_fips_code, nodePtr);

	// Return FIPS code
	return get_fips_code(nodePtr);
}

const char* helper_get_seat(struct node* nodePtr)
{
	// Check if function works in forked process
	CALL_FUNCTION_STRING(get_seat, nodePtr);

	// Return seat
	return get_seat(nodePtr);
}

int helper_get_population(struct node* nodePtr)
{
	// Check if function works in forked process
	CALL_FUNCTION_INT(get_population, nodePtr);

	// Return population
	return get_population(nodePtr);
}

int helper_get_area(struct node* nodePtr)
{
	// Check if function works in forked process
	CALL_FUNCTION_INT(get_area, nodePtr);

	// Return area
	return get_area(nodePtr);
}

double helper_get_population_density(struct node* nodePtr)
{
	// Check if function works in forked process
	CALL_FUNCTION_DOUBLE(get_population_density, nodePtr);

	// Return population density
	return get_population_density(nodePtr);
}

struct node* helper_get_next_node(struct node* nodePtr)
{
	// Check if function works in forked process
	CALL_FUNCTION_POINTER(get_next_node, nodePtr);

	// Return next node
	return get_next_node(nodePtr);
}

struct node* helper_create_county(const char* county_name, const char* fips_code, const char* seat, int population, int area)
{
	// Check if function works in forked process
	CALL_FUNCTION_POINTER_NOT_NULL(create_county, county_name, fips_code, seat, population, area);

	// Create county
	struct node* countyPtr = create_county(county_name, fips_code, seat, population, area);

	// Validate node
	TEST_ASSERT_NULL_MESSAGE(get_next_node(countyPtr), "The next node of a newly created node is not NULL. Check your create_county function.");

	return countyPtr;
}

struct node* helper_create_county_without_assert(const char* county_name, const char* fips_code, const char* seat, int population, int area)
{
	// Check if function works in forked process
	CALL_FUNCTION_POINTER_NOT_NULL(create_county, county_name, fips_code, seat, population, area);

	// Create county
	struct node* countyPtr = create_county(county_name, fips_code, seat, population, area);

	// Validate node
	if (helper_get_next_node(countyPtr) != NULL)
	{
		puts("The next node of a newly created node is not NULL. Check your create_county function.");
	 }

	return countyPtr;
}

void helper_add_and_sort_county(struct list* listPtr, struct node* nodePtr)
{
	// Check if function works in forked process
	CALL_FUNCTION_VOID(add_and_sort_county, listPtr, nodePtr);

	// Add and sort county
	add_and_sort_county(listPtr, nodePtr);
}

struct node* helper_process_input_line(const char* line)
{
	// Ensure required functions have been implemented and do not crash
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_trim, "The trim function has not been implemented.");
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_substring, "The substring function has not been implemented.");
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_create_county, "The create_county function has not been implemented.");

	// Check if function works in forked process
	CALL_FUNCTION_POINTER(process_input_line, line);

	// Process input line
	return process_input_line(line);
}

void helper_load_counties(struct list* listPtr, const char* filename)
{
	// Ensure required functions have been implemented and do not crash
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_trim, "The trim function has not been implemented.");
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_substring, "The substring function has not been implemented.");
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_create_county, "The create_county function has not been implemented.");
	TEST_ASSERT_FALSE_MESSAGE(not_implemented_process_input_line, "The process_input_line function has not been implemented.");

	// Check if function works in forked process
	CALL_FUNCTION_VOID(load_counties, listPtr, filename);

	// Process load file
	load_counties(listPtr, filename);
}

int helper_delete_by_county_name(struct list* listPtr, const char* county_name)
{
	// Check if function works in forked process
	CALL_FUNCTION_INT(delete_by_county_name, listPtr, county_name);

	// Delete by county name
	return delete_by_county_name(listPtr, county_name);
}

void helper_save_counties(struct list* listPtr, const char* filename)
{
	// Check if function works in forked process
	CALL_FUNCTION_VOID(save_counties, listPtr, filename);

	// Save counties
	save_counties(listPtr, filename);
}

char* testsupport_build_county_names_from_array(struct testsupport_county_data county_data[], int last_county)
{
	// Define array size
	size_t county_names_size = 10000;

	// Allocate memory
	char* county_names = malloc(county_names_size * sizeof(char));
	if (county_names == NULL)
	{
		return NULL;
	}

	// Initialize memory
	memset(county_names, 0, county_names_size * sizeof(char));

	// Loop through list
	for (int i = 0; i <= last_county; i++)
	{
		// Get county name
		const char* county_name = county_data[i].county_name;

		// Copy county name to array
		strncat(county_names, county_name, county_names_size - strlen(county_names) - 1);

		// Add comma if not last county
		if (i < last_county)
		{
			strncat(county_names, ", ", county_names_size - strlen(county_names) - 1);
		}
	}

	// Realloc to shrink memory
	char* tempPtr = realloc(county_names, strlen(county_names) + 1);
	if (tempPtr != NULL)
	{
		// Assign new version as county_names
		county_names = tempPtr;
	}

	return county_names;
}

char* testsupport_build_county_names_from_list(struct list* listPtr, int last_county)
{
	// Define array size
	size_t county_names_size = 10000;

	// Allocate memory
	char* county_names = malloc(county_names_size * sizeof(char));
	if (county_names == NULL)
	{
		return NULL;
	}

	// Initialize memory
	memset(county_names, 0, county_names_size * sizeof(char));

	// Loop through list
	struct node* nodePtr = listPtr->headPtr;
	for (int i = 0; i <= last_county && nodePtr != NULL; i++)
	{
		// Get county name
		const char* county_name = helper_get_county_name(nodePtr);

		// Copy county name to array
		strncat(county_names, county_name, county_names_size - strlen(county_names) - 1);

		// Add comma if not last county
		if (i < last_county)
		{
			strncat(county_names, ", ", county_names_size - strlen(county_names) - 1);
		}

		// Advance node pointer
		nodePtr = helper_get_next_node(nodePtr);
	}

	// Realloc to shrink memory
	char* tempPtr = realloc(county_names, strlen(county_names) + 1);
	if (tempPtr != NULL)
	{
		// Assign new version as county_names
		county_names = tempPtr;
	}

	return county_names;
}

void testsupport_check_list_contents(struct list* listPtr, struct testsupport_county_data expected_values[], size_t expected_values_count, const char* message_prefix)
{
	// Define error messages
	char error_message[10000];

	// Check for valid input values
	TEST_ASSERT_NOT_NULL_MESSAGE(listPtr, "The list pointer is NULL.");
	TEST_ASSERT_NOT_NULL_MESSAGE(expected_values, "The expected_values array is NULL.");

	// Build error message for count
	if (message_prefix != NULL)
	{
		sprintf(error_message, "%s The count of items stored in the list does not match the expected count.", message_prefix);
	}
	else
	{
		sprintf(error_message, "The count of items stored in the list does not match the expected count.");
	}
	TEST_ASSERT_EQUAL_MESSAGE(expected_values_count, testsupport_count_counties(listPtr), error_message);

	// Validate list
	testsupport_validate_list(listPtr);

	// Iterate through list, checking that values match what is expected.
	bool population_density_integer_division_warning = false;
	bool fips_code_substring_warning = false;
	struct node* curPtr = listPtr->headPtr;
	for (int i = 0; i < expected_values_count; i++)
	{
		// Get list of counties that should be in the list
		char* expected_county_names = testsupport_build_county_names_from_array(expected_values, i);
		char* actual_county_names = testsupport_build_county_names_from_list(listPtr, i);

		// Construct error message
		if (message_prefix != NULL)
		{
			sprintf(error_message, "%s Expected counties through index %d: %s. Actual counties through index %d: %s. County at index %d does not match the expected value for", message_prefix, i, expected_county_names, i, actual_county_names, i);
		}
		else
		{
			sprintf(error_message, "Expected counties through index %d: %s. Actual counties through index %d: %s. County at index %d does not match the expected value for", i, expected_county_names, i, actual_county_names, i);
		}

		// Free memory from county lists
		free(expected_county_names);
		expected_county_names = NULL;
		free(actual_county_names);
		actual_county_names = NULL;

		// Place to store customized message
		char customized_message[11000];

		// Check that the county name is correct
		sprintf(customized_message, "%s %s.", error_message, "county name");
		const char* county_name = helper_get_county_name(curPtr);
		TEST_ASSERT_FALSE_MESSAGE(not_implemented_get_county_name, "The get_county_name function has not been implemented.");
		TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_values[i].county_name, county_name, customized_message);

		// Check that the FIPS code is correct
		sprintf(customized_message, "%s %s.", error_message, "FIPS code");
		const char* fips_code = helper_get_fips_code(curPtr);
		TEST_ASSERT_FALSE_MESSAGE(not_implemented_get_fips_code, "The get_fips_code function has not been implemented.");

		// Determine if fips_code is contained in the expected_values[i].fips_code
		if (strstr(expected_values[i].fips_code, fips_code) == NULL || strstr(fips_code, expected_values[i].fips_code) == NULL)
		{
			fips_code_substring_warning = true;
		}

		//TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_values[i].fips_code, fips_code, customized_message);

		// Check that the seat is correct
		sprintf(customized_message, "%s %s.", error_message, "seat");
		const char* seat = helper_get_seat(curPtr);
		TEST_ASSERT_FALSE_MESSAGE(not_implemented_get_seat, "The get_seat function has not been implemented.");
		TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_values[i].seat, seat, customized_message);

		// Check that the population is correct
		sprintf(customized_message, "%s %s.", error_message, "population");
		int population = helper_get_population(curPtr);
		TEST_ASSERT_FALSE_MESSAGE(not_implemented_get_population, "The get_population function has not been implemented.");
		TEST_ASSERT_EQUAL_MESSAGE(expected_values[i].population, population, customized_message);

		// Check that the area is correct
		sprintf(customized_message, "%s %s.", error_message, "area");
		int area = helper_get_area(curPtr);
		TEST_ASSERT_FALSE_MESSAGE(not_implemented_get_area, "The get_area function has not been implemented.");
		TEST_ASSERT_EQUAL_MESSAGE(expected_values[i].area, area, customized_message);

		// Check that the population density is correct
		sprintf(customized_message, "%s %s.", error_message, "population density");
		double population_density = helper_get_population_density(curPtr);
		TEST_ASSERT_FALSE_MESSAGE(not_implemented_get_population_density, "The get_population_density function has not been implemented.");
		TEST_ASSERT_EQUAL_MESSAGE(expected_values[i].population / expected_values[i].area, population_density, customized_message); // Check int value to avoid unnecessary flagging of errors

		// Display message if the population density is not correct with a double comparison
		if (fabs((expected_values[i].population / (double) expected_values[i].area) - population_density) > 0.01)
		{
			population_density_integer_division_warning = true;
		}

		
		// Check next node is expected one
		struct node* nextPtr = helper_get_next_node(curPtr);
		
		TEST_ASSERT_FALSE_MESSAGE(not_implemented_get_next_node, "Cannot get the next node until the get_next_node function is implemented.");
		if (nextPtr != NULL && nextPtr != (void*) 0xFFFFFFFFFFFFFFFF) {
			// Check to see if none of the expected values for the next node appear match
			if (strcmp(expected_values[i + 1].county_name, helper_get_county_name(nextPtr)) != 0 &&
				(strstr(helper_get_fips_code(nextPtr), expected_values[i + 1].fips_code) == NULL && strstr(expected_values[i + 1].fips_code, helper_get_fips_code(nextPtr)) == NULL) && // Handle truncated FIPS code
				(strcmp(expected_values[i + 1].seat, helper_get_seat(nextPtr)) != 0) &&
				expected_values[i + 1].population != helper_get_population(nextPtr) &&
				(expected_values[i + 1].area != helper_get_area(nextPtr) && expected_values[i + 1].population / 10 != helper_get_area(nextPtr)) // Handle truncated area
				)
			{
				sprintf(customized_message, "%s %s, which should be %s.", error_message, "next node", expected_values[i+1].county_name);
				TEST_FAIL_MESSAGE(customized_message);
			}
		}
		

		// Advance curPtr
		curPtr = nextPtr;		
	}

	// Display message if the population density is not correct with a double comparison
	if (population_density_integer_division_warning)
	{
		puts("The population density was improperly calculated using integer division.");
	}

	// Display message if FIPS code is not equal to the expected value
	if (fips_code_substring_warning)
	{
		puts("The FIPS code does not match the expected value. The loaded value is either a substring or superstring of the expected value.");
	}
}

int testsupport_count_counties(struct list* listPtr)
{
	// Ensure list is not NULL
	TEST_ASSERT_NOT_NULL_MESSAGE(listPtr, "The list cannot be NULL.");

	// Variable to count nodes
	int count = 0;

	// Iterate over list
	struct node* curPtr = listPtr->headPtr;
	while (curPtr != NULL && curPtr != (void*) 0xFFFFFFFFFFFFFFFF)
	{
		// Increment count
		count++;

		// Advance to next node
		curPtr = helper_get_next_node(curPtr);
	}

	return count;
}

struct node* testsupport_create_county(struct testsupport_county_data county_data)
{
	struct node* countyPtr = helper_create_county_without_assert(county_data.county_name, county_data.fips_code, county_data.seat, county_data.population, county_data.area);

	// Ensure county data is not null
	TEST_ASSERT_NOT_NULL_MESSAGE(countyPtr, "The create_county function did not return a valid county.");

	// Ensure next node pointer is null
	//TEST_ASSERT_NULL_MESSAGE(helper_get_next_node(countyPtr), "The next pointer for the county node must be NULL. Check your create_county function.");

	return countyPtr;
}

bool testsupport_is_printable(const char* string)
{
		// Check if string is NULL
	if (string == NULL)
	{
		return false;
	}

	// Check if string is empty
	if (strlen(string) == 0)
	{
		return false;
	}

	// Loop to look for non-printable characters
	for (size_t i = 0; i < strlen(string); i++)
	{
		// Check if character is not printable
		if (!isprint(string[i]))
		{
			return false;
		}
	}

	return true;

}

void testsupport_free_list_memory(struct list* listPtr)
{
	// Ensure list is not NULL
	TEST_ASSERT_NOT_NULL_MESSAGE(listPtr, "The list cannot be NULL.");

	// Get head node
	struct node* nodePtr = listPtr->headPtr;

	// Iterate through list to free memory while node is not NULL or an uninitialized value
	while (nodePtr != NULL && nodePtr != (void*) 0xFFFFFFFFFFFFFFFF)
	{
		// Save current pointer as temp pointer
		struct node* tempPtr = nodePtr;

		// Advance nodePtr to next location
		nodePtr = helper_get_next_node(nodePtr);

		// Free memory from tempPtr
		free(tempPtr);
	}

	// Free memory from lilst
	free(listPtr);
	listPtr = NULL;
}

size_t testsupport_get_malloc_size(void* ptr)
{
	// See if pointer is valid
	if (ptr == NULL)
	{
		return 0;
	}

	// Get size
#ifdef __APPLE__ 
	return malloc_size(ptr);
#else 
	return malloc_usable_size(ptr);
#endif 
}

struct node* testsupport_create_test_node(void) {
	// Create test node
	struct node* test_nodePtr = helper_create_county_without_assert(testvalue_county_name, testvalue_fips_code, testvalue_seat, testvalue_population, testvalue_area);

	// If node is not valid, return
	if (test_nodePtr == NULL) {
		TEST_FAIL_MESSAGE("We cannot create a test node until the create_county function is implemented.");
	}

	return test_nodePtr;
}

void testsupport_validate_list(struct list* listPtr)
{
	// Ensure list is not NULL
	TEST_ASSERT_NOT_NULL_MESSAGE(listPtr, "The tested list is not valid because it was NULL.");
}

void testsupport_validate_new_list(struct list* listPtr)
{
	// Validate core of list
	testsupport_validate_list(listPtr);

	// Ensure head pointer is null
	TEST_ASSERT_NULL_MESSAGE(listPtr->headPtr, "The head pointer must be NULL on an empty list. Check your create_list function.");
}

const char* testsupport_fix_null_termination(const char* string)
{
	// Check if string is NULL
	if (string == NULL)
	{
		return NULL;
	}

	// Malloc new string
	char* fixedPtr = malloc(strlen(string) + 1);
	if (fixedPtr == NULL)
	{
		return NULL;
	}

	// Initialize to null
	memset(fixedPtr, 0, strlen(string) + 1);

	// Copy string
	strncpy(fixedPtr, string, strlen(string));

	// Get position of last character
	size_t position = strlen(fixedPtr) - 1;

	// Loop from end of string, moving left
	while (position >= 0 && !isgraph(fixedPtr[position]))
	{
		fixedPtr[position] = '\0';
		position--;
	}

	return fixedPtr;
}