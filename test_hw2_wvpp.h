/**
 * @file test_hw2_wvpp.h
 * @brief Tests header file for CS 350 Homework #2: West Virginia Population Problem
 * @author Brian Powell
 * @version 3.10
 *
 * Place this file in the same directory as your own source code and add it to your project.
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE.
 */

#pragma once

 // Use GNU source for kill and usleep
#define _GNU_SOURCE

// Include header files
#include "ctest.h"
#include "hw2_wvpp.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// Define constants

#define TIMEOUT_SECONDS 2
#define SLEEP_MICROSECONDS 5
#define WAIT_FOR_FORKED_PROCESS_WITHOUT_LOOPING 0 // False

/**
 * @brief Stores strings for use in testing trim functions
 */
struct test_trim_string
{
	/**
	 * @brief Value to use in testing function
	 */
	char* test_value;

	/**
	 * @brief Expected value after running function
	 */
	char* expected_value;

};

/**
 * @brief Stores strings for use in testing substring function
 */
struct test_substring_string
{
	/**
	 * @brief Value to use in testing function
	 */
	char* test_value;

	/**
	 * @brief Starting index for substring, included in result
	 */
	unsigned int start_index;

	/**
	 * @brief Ending index for substring, excluded from result
	 */
	unsigned int end_index;

	/**
	 * @brief Expected value after running function
	 */
	char* expected_value;
};

/**
 * @brief Struct for holding county information
*/
struct testsupport_county_data
{
	/**
	 * @brief County name
	 */
	char* county_name;

    /**
	 * @brief FIPS code
	 */
	char* fips_code;

    /**
	 * @brief Seat of county
	 */
	char* seat;

    /**
	 * @brief Population of county
	 */
	int population;

    /**
	 * @brief Area of county in square miles
	 */
	int area;
};

 /**
  * @brief Run unit tests
 */
void run_tests(const char* input_file);

/**
 * @brief Test Step 2c: get_programmer_name function
*/
void test_2c_get_programmer_name(void);

/**
 * @brief Test Step 2d: trim function
 */
void test_2d_trim(void);

/**
 * @brief Test Step 2e: substring function
 */
void test_2e_substring(void);

/**
 * @brief Test Step 2f: struct node exists
 */
void test_2f_struct_node_exists(void);

/**
 * @brief Test function for Step 2g: create_list function
 */
void test_2g_create_list(void);

/**
 * @brief Test Step 2h: get_head_node function
 */
void test_2h_get_head_node(void);

/**
 * @brief Test Step 2i: get_county_name function for valid node
 */
void test_2i_get_county_name_valid(void);

/**
 * @brief Test Step 2i: get_county_name function for NULL node
 */
void test_2i_get_county_name_null(void);

/**
 * @brief Test Step 2j: get_fips_code function for valid node
 */
void test_2j_get_fips_code_valid(void);

/**
 * @brief Test Step 2j: get_fips_code function for NULL node
 */
void test_2j_get_fips_code_null(void);

/**
 * @brief Test Step 2k: get_seat function for valid node
 */
void test_2k_get_seat_valid(void);

/**
 * @brief Test Step 2k: get_seat function for NULL node
 */
void test_2k_get_seat_null(void);

/**
 * @brief Test Step 2l: get_population function for valid node
 */
void test_2l_get_population_valid(void);

/**
 * @brief Test Step 2l: get_population function for NULL node
 */
void test_2l_get_population_null(void);

/**
 * @brief Test Step 2m: get_area function for valid node
 */
void test_2m_get_area_valid(void);

/**
 * @brief Test Step 2m: get_area function for NULL node
 */
void test_2m_get_area_null(void);

/**
 * @brief Test Step 2n: get_population_density function for valid node
 */
void test_2n_get_population_density_valid(void);

/**
 * @brief Test Step 2n: get_population_density function for NULL node
 */
void test_2n_get_population_density_null(void);

/**
 * @brief Test Step 2o: get_next_node function for valid node
 */
void test_2o_get_next_node_valid(void);

/**
 * @brief Test Step 2o: get_next_node function for NULL node
 */
void test_2o_get_next_node_null(void);

/**
 * @brief Test Step 2p: create_county function
 */
void test_2p_create_county(void);

/**
 * @brief Test Step 2q: add_and_sort_county function with an empty list
 */
void test_2q_add_and_sort_county_empty_list(void);

/**
 * @brief Test Step 2q: add_and_sort_county function to check for integer division with population density
 */
void test_2q_add_and_sort_county_integer_division(void);

/**
 * @brief Test Step 2q: add_and_sort_county function with adding multiple counties
 */
void test_2q_add_and_sort_county_multiple_counties(void);

/**
 * @brief Test Step 2q: add_and_sort_county function with adding a new node after the head
 */
void test_2q_add_and_sort_county_nonempty_list_after_head(void);

/**
 * @brief Test Step 2q: add_and_sort_county function with adding a new head nnooddee
 */
void test_2q_add_and_sort_county_nonempty_list_new_head(void);

/**
 * @brief Test Step 2r: process_input_line function for Doddridge County
 */
void test_2r_process_input_line_3_digit_area(void);

/**
 * @brief Test Step 2r: process_input_line function for Randolph County
 */
void test_2r_process_input_line_4_digit_area(void);

/**
 * @brief Test Step 2r: process_input_line function for empty string
 */
void test_2r_process_input_line_no_data(void);

/**
 * @brief Test Step 2s: load_counties function
 */
void test_2s_load_counties(void);

/**
 * @brief Test Step 2t: delete_by_county_name function with deleting the first county
 */
void test_2t_delete_by_county_name_first_county(void);

/**
 * @brief Test Step 2t: delete_by_county_name function with deleting a county in middle
 */
void test_2t_delete_by_county_name_middle_county(void);

/**
 * @brief Test Step 2t: delete_by_county_name function with deleting the last county
 */
void test_2t_delete_by_county_name_last_county(void);

/**
 * @brief Test Step 2t: delete_by_county_name function with deleting multiple counties
 */
void test_2t_delete_by_county_name_multiple_counties(void);

/**
 * @brief Test Step 2t: delete_by_county_name function with deleting a county that doesn't exist
 */
void test_2t_delete_by_county_name_nonexistent_county(void);

/**
 * @brief Test Step 2t: delete_by_county_name function with deleting from a NULL list
 */
void test_2t_delete_by_county_name_null_list(void);

/**
 * @brief Test Step 2t: delete_by_county_name function with deleting the only county in a list
 */
void test_2t_delete_by_county_name_one_county(void);

/**
 * @brief Test Step 2u: save_counties function with multiple counties
 */
void test_2u_save_counties_multiple_counties(void);

/**
 * @brief Test Step 2u: save_counties function with one county
 */
void test_2u_save_counties_one_county(void);

/**
 * @brief Build list of counties coming from a linked list
 * @param listPtr List to build from
 * @param last_county Index of last county to include in list
 * @return Comma-separated list of counties
 */
char* testsupport_build_county_names_from_list(struct list* listPtr, int last_county);

/**
 * @brief Build list of counties coming from a struct array
 * @param county_data Array of county data
 * @param last_county Index of last county to include in list
 * @return Comma-separated list of counties
 */
char* testsupport_build_county_names_from_array(struct testsupport_county_data county_data[], int last_county);

/**
 * @brief Checks that list contents are as expected
 * @param listPtr List that should contain the expected values
 * @param expected_values Array of expected values
 * @param expected_values_count Number of expected values *
 * @param message_prefix Prefix for error messages
 */
void testsupport_check_list_contents(struct list* listPtr, struct testsupport_county_data expected_values[], size_t expected_values_count, const char* message_prefix);

/**
 * @brief Counts the number of counties stored in the list
 * @param listPtr List to count
 * @return Number of stored counties
 */
int testsupport_count_counties(struct list* listPtr);

/**
 * @brief Creates a new county for testing
 * @param county_data Data for the county
 * @return Pointer to new county
 */
struct node* testsupport_create_county(struct testsupport_county_data county_data);

/**
 * @brief Fixes problems with null termination leaving 0xFF values at end of string
 * @param string String to fix
 * @return Fixed string, corrected in place
 */
const char* testsupport_fix_null_termination(const char* string);

/**
 * @brief Frees memory allocated for a list
 * @param listPtr List to free
 */
void testsupport_free_list_memory(struct list* listPtr);

/**
 * @brief Determines how much memory was allocated for a pointer
 * @param ptr Pointer to test
 * @return Number of bytes allocated
 */
size_t testsupport_get_malloc_size(void* ptr);

/**
 * @brief Determines if a string is printable
 * @param string String to test
 * @return True if string is printable, false if not
 */
bool testsupport_is_printable(const char* string);

/**
 * @brief Create a node with known test values
 * @return County node with test values
 */
struct node* testsupport_create_test_node(void);

/**
 * @brief Validates that a list that may or may not be empty
 * @param listPtr List to validate
 */
void testsupport_validate_list(struct list* listPtr);

/**
 * @brief Validates that a new list is empty
 * @param listPtr List to validate
 */
void testsupport_validate_new_list(struct list* listPtr);

/**
 * @brief Function to return the name of the programmer
 * @return String with the name of the programmer
 */
const char* helper_get_programmer_name(void);

/**
 * @brief Removes whitespace from the leading and trailing ends of a string
 * @param untrimmed String to remove whitespace from
 * @return New string with whitespace removed
 */
char* helper_trim(const char* untrimmed);

/**
 * @brief Returns substring of original string
 * @param source String to take substring from
 * @param start_index Starting index for substring (character is included in result)
 * @param end_index Ending index for substring (substring ends at character immediately before this index)
 * @return New string containing substring
 */
char* helper_substring(const char* source, unsigned int start_index, unsigned int end_index);

/**
 * @brief Creates a new linked list
 * @return Pointer to new list
*/
struct list* helper_create_list(void);

/**
 * @brief Get the head node for a linked list
 * @param listPtr Linked list to get head node for
 * @return Head node for linked list, or NULL if list is empty
*/
struct node* helper_get_head_node(struct list* listPtr);

/**
 * @brief Get county name from specified node
 * @param nodePtr Node to get county name from
 * @return Name of county
*/
const char* helper_get_county_name(struct node* nodePtr);

/**
 * @brief Get FIPS Code from specified node
 * @param nodePtr Node to get FIPS Code from
 * @return FIPS Code, or NULL if node is invalid
*/
const char* helper_get_fips_code(struct node* nodePtr);

/**
 * @brief Get seat from specified node
 * @param nodePtr Node to get seat from
 * @return Seat, or NULL if node is invalid
*/
const char* helper_get_seat(struct node* nodePtr);

/**
 * @brief Get population from specified node
 * @param nodePtr Node to get population from
 * @return Population, or -999 if node is invalid
*/
int helper_get_population(struct node* nodePtr);

/**
 * @brief Get area from specified node
 * @param nodePtr Node to get area from
 * @return Area, or -999 if node is invalid
*/
int helper_get_area(struct node* nodePtr);

/**
 * @brief Get populationd density (population/area) for specified node
 * @param nodePtr Node to get population density for
 * @return Number of people per square mile, or -999 if node is invalid
*/
double helper_get_population_density(struct node* nodePtr);

/**
 * @brief Get next node for specified node
 * @param nodePtr Node to get next node for
 * @return Next node, or NULL if there are no more nodes in the linked list
*/
struct node* helper_get_next_node(struct node* nodePtr);

/**
 * @brief Create new node to represent a county
 * @param county_name Name of county
 * @param fips_code FIPS Code
 * @param seat Seat of county
 * @param population Population of county
 * @param area Area of county in square miles
 * @return New node loaded with data for the county
*/
struct node* helper_create_county(const char* county_name, const char* fips_code, const char* seat, int population, int area);

/**
 * @brief Create new node to represent a county, but does not have an assert statement
 * @param county_name Name of county
 * @param fips_code FIPS Code
 * @param seat Seat of county
 * @param population Population of county
 * @param area Area of county in square miles
 * @return New node loaded with data for the county
*/
struct node* helper_create_county_without_assert(const char* county_name, const char* fips_code, const char* seat, int population, int area);

/**
 * @brief Add new county node to list, leaving list sorted in descending order by population density
 * @param listPtr Linked list to add county to
 * @param nodePtr Node containing county data
*/
void helper_add_and_sort_county(struct list* listPtr, struct node* nodePtr);

/**
 * @brief Process a line of data from input file
 * @param line Line of data to process
 * @return New node storing data from the line
 */
struct node* helper_process_input_line(const char* line);

/**
 * @brief Load counties from file, storing them each as nodes in linked list
 * @param listPtr Linked list to store counties in as nodes
 * @param filename name of fixed-width column text file to load counties from
*/
void helper_load_counties(struct list* listPtr, const char* filename);

/**
 * @brief Delete node from list by its county name
 * @param listPtr Linked lst to delete from
 * @param county_name Name of county for node to be deleted
 * @return 0 if successfully deleted, 1 if county did not exist
*/
int helper_delete_by_county_name(struct list* listPtr, const char* county_name);

/**
 * @brief Save counties from linked list to CSV file
 * @param listPtr linked list containing counties to be saved
 * @param filename CSV file to save counties in
*/
void helper_save_counties(struct list* listPtr, const char* filename);

