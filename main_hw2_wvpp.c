/**
 * @file main_hw2_wvpp.c
 * @brief File with main function for CS 350 Homework #2: West Virginia Population Problem
 * @author Brian Powell
 * @version 3.7
 * 
 * Place this file in the same directory as your own source code and add it to your project.
 * 
 * DO NOT MODIFY THE CONTENTS OF THIS FILE OTHER THAN AS INDICATED BELOW.
 */

// Include header files
#include "hw2_wvpp.h"
#include "test_hw2_wvpp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// Function prototypes
const char* build_write_path(const char* filename);
const char* build_read_path(const char* filename);

/**
* @brief Program entry point
*/
int main(void)
{
	// Define filename to read from
	// This code assumes file is in same directory as this file. If it is not, change the variable to provide the correct absolute path.
	const char* input_file = build_read_path("counties.txt");

	// Define filename to save to
	// This code assumes file is in same directory as this file. If it is not, change the variable to provide the correct absolute path.
	const char* output_file = build_write_path("output.csv");

	// Run tests
	run_tests(input_file);

	// Create list
	struct list* listPtr = create_list();

	// Load data into list
	load_counties(listPtr, input_file);

	// Delete specified counties
	delete_by_county_name(listPtr, "Brooke");
	delete_by_county_name(listPtr, "Ohio");

	// Print CSV file with results
	save_counties(listPtr, output_file);

	// Print name of programmer
	printf("Code written by %s\n", get_programmer_name());

	

	return 0;
}

/**
 * @brief Builds absolute path for writing to a file in same directory as this file
 * @param filename File name of file to write to
 * @return Path for file to write to
*/
const char* build_write_path(const char* filename)
{
	// Get path of current file
	const char* path = __FILE__;

	// Find last slash, using appropriate slash for OS
	#ifdef _WIN32
		// Use backslash for Windows
		const char* last_slash = strrchr(path, '\\');
	#else
		// Use forward slash for Unix-based systems
		const char* last_slash = strrchr(path, '/');
	#endif

	// If no slash found, return original filename
	if (last_slash == NULL)
	{
		return filename;
	}

	// Get length of path using pointer arithmetic
	size_t path_len = (size_t)(last_slash - path) + 1;

	// Get size of filename
	size_t filename_len = strlen(filename);

	// Allocate memory for new string
	size_t new_path_len = path_len + filename_len + 1;
	char* new_path = malloc(new_path_len);
	if (new_path == NULL)
	{
		// Memory allocation failed
		printf("Could not allocate memory: %s.\n", strerror(errno));
		return filename;
	}

	// Initialize new string
	memset(new_path, 0, new_path_len);

	// Copy path to new string
	strncpy(new_path, path, path_len);

	// Add file to new string
	strncpy(new_path + path_len, filename, filename_len);

	// Return new string
	return new_path;
}

/**
 * @brief Builds absolute path for reading a file in the same directory as this file
 * @param filename File name of file to read from
 * @return Path for file to read from
 */
const char* build_read_path(const char* filename)
{
	// Get absolute path
	const char* new_path = build_write_path(filename);

	// See if path exists
	if (access(new_path, F_OK) == 0)
	{
		// Absolute path exists
		return new_path;
	}
	else
	{
		// Absolute path does not exist. Return original path.
		return filename;
	}
}
